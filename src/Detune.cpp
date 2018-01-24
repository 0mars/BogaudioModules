
#include "bogaudio.hpp"
#include "dsp/pitch.hpp"

using namespace bogaudio::dsp;

struct Detune : Module {
	enum ParamsIds {
		CENTS_PARAM,
		NUM_PARAMS
	};

	enum InputsIds {
		CV_INPUT,
		IN_INPUT,
		NUM_INPUTS
	};

	enum OutputsIds {
		THRU_OUTPUT,
		OUT_PLUS_OUTPUT,
		OUT_MINUS_OUTPUT,
		NUM_OUTPUTS
	};

	enum LightsIds {
		NUM_LIGHTS
	};

	Detune() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
	}

	virtual void step() override;
};

void Detune::step() {
	if (!(outputs[OUT_PLUS_OUTPUT].active || outputs[OUT_MINUS_OUTPUT].active || outputs[THRU_OUTPUT].active)) {
		return;
	}

	float cents = params[CENTS_PARAM].value;
	if (inputs[CV_INPUT].active) {
		cents *= clampf(inputs[CV_INPUT].value, 0.0, 10.0) / 10.0;
		cents = roundf(cents);
	}
	cents /= 100.0;

	if (inputs[IN_INPUT].active) {
		float cv = inputs[IN_INPUT].value;
		outputs[THRU_OUTPUT].value = cv;
		if (cents < 0.001) {
			outputs[OUT_PLUS_OUTPUT].value = cv;
			outputs[OUT_MINUS_OUTPUT].value = cv;
		}
		else {
			float semitone = cvToSemitone(cv);
			outputs[OUT_PLUS_OUTPUT].value = semitoneToCV(semitone + cents);
			outputs[OUT_MINUS_OUTPUT].value = semitoneToCV(semitone - cents);
		}
	}
	else {
		outputs[THRU_OUTPUT].value = 0.0;
		if (cents < 0.001) {
			outputs[OUT_PLUS_OUTPUT].value = 0.0;
			outputs[OUT_MINUS_OUTPUT].value = 0.0;
		}
		else {
			outputs[OUT_PLUS_OUTPUT].value = semitoneToCV(referenceSemitone + cents);
			outputs[OUT_MINUS_OUTPUT].value = semitoneToCV(referenceSemitone - cents);
		}
	}
}


DetuneWidget::DetuneWidget() {
	Detune *module = new Detune();
	setModule(module);
	box.size = Vec(RACK_GRID_WIDTH * 3, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Detune.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(0, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 15, 365)));

	// generated by svg_widgets.rb
	auto centsParamPosition = Vec(9.5, 32.5);

	auto cvInputPosition = Vec(10.5, 77.0);
	auto inInputPosition = Vec(10.5, 126.0);

	auto thruOutputPosition = Vec(10.5, 164.0);
	auto outPlusOutputPosition = Vec(10.5, 200.0);
	auto outMinusOutputPosition = Vec(10.5, 236.0);
	// end generated by svg_widgets.rb

	{
		auto w = createParam<Knob26>(centsParamPosition, module, Detune::CENTS_PARAM, 0.0, 50.0, 0.0);
		dynamic_cast<Knob*>(w)->snap = true;
		addParam(w);
	}

	addInput(createInput<Port24>(cvInputPosition, module, Detune::CV_INPUT));
	addInput(createInput<Port24>(inInputPosition, module, Detune::IN_INPUT));

	addOutput(createOutput<Port24>(thruOutputPosition, module, Detune::THRU_OUTPUT));
	addOutput(createOutput<Port24>(outPlusOutputPosition, module, Detune::OUT_PLUS_OUTPUT));
	addOutput(createOutput<Port24>(outMinusOutputPosition, module, Detune::OUT_MINUS_OUTPUT));
}
