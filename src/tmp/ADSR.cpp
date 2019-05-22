
#include "ADSR.hpp"

void ADSR::onReset() {
	_gateTrigger.reset();
	_envelope.reset();
	_modulationStep = modulationSteps;
}

void ADSR::onSampleRateChange() {
	_envelope.setSampleRate(engineGetSampleRate());
	_modulationStep = modulationSteps;
}

void ADSR::step() {
	lights[LINEAR_LIGHT].value = _linearMode = params[LINEAR_PARAM].getValue() > 0.5f;
	if (!(outputs[OUT_OUTPUT].isConnected() || inputs[GATE_INPUT].isConnected())) {
		return;
	}

	++_modulationStep;
	if (_modulationStep >= modulationSteps) {
		_modulationStep = 0;

		_envelope.setAttack(powf(params[ATTACK_PARAM].getValue(), 2.0f) * 10.f);
		_envelope.setDecay(powf(params[DECAY_PARAM].getValue(), 2.0f) * 10.f);
		_envelope.setSustain(params[SUSTAIN_PARAM].getValue());
		_envelope.setRelease(powf(params[RELEASE_PARAM].getValue(), 2.0f) * 10.f);
		_envelope.setLinearShape(_linearMode);
	}

	_gateTrigger.process(inputs[GATE_INPUT].getVoltage());
	_envelope.setGate(_gateTrigger.isHigh());
	outputs[OUT_OUTPUT].setVoltage(_envelope.next() * 10.0f);

	lights[ATTACK_LIGHT].value = _envelope.isStage(bogaudio::dsp::ADSR::ATTACK_STAGE);
	lights[DECAY_LIGHT].value = _envelope.isStage(bogaudio::dsp::ADSR::DECAY_STAGE);
	lights[SUSTAIN_LIGHT].value = _envelope.isStage(bogaudio::dsp::ADSR::SUSTAIN_STAGE);
	lights[RELEASE_LIGHT].value = _envelope.isStage(bogaudio::dsp::ADSR::RELEASE_STAGE);
}

struct ADSRWidget : ModuleWidget {
	static constexpr int hp = 3;

	ADSRWidget(ADSR* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

		{
			SVGPanel *panel = new SVGPanel();
			panel->box.size = box.size;
			panel->setBackground(SVG::load(asset::plugin(pluginInstance, "res/ADSR.svg")));
			addChild(panel);
		}

		addChild(createWidget<ScrewSilver>(Vec(0, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 15, 365)));

		// generated by svg_widgets.rb
		auto attackParamPosition = Vec(8.0, 33.0);
		auto decayParamPosition = Vec(8.0, 90.0);
		auto sustainParamPosition = Vec(8.0, 147.0);
		auto releaseParamPosition = Vec(8.0, 204.0);
		auto linearParamPosition = Vec(32.0, 245.7);

		auto gateInputPosition = Vec(10.5, 265.0);

		auto outOutputPosition = Vec(10.5, 303.0);

		auto attackLightPosition = Vec(20.8, 65.0);
		auto decayLightPosition = Vec(20.8, 122.0);
		auto sustainLightPosition = Vec(20.8, 179.0);
		auto releaseLightPosition = Vec(20.8, 236.0);
		auto linearLightPosition = Vec(4.0, 247.0);
		// end generated by svg_widgets.rb

		addParam(createParam<Knob29>(attackParamPosition, module, ADSR::ATTACK_PARAM, 0.0, 1.0, 0.12));
		addParam(createParam<Knob29>(decayParamPosition, module, ADSR::DECAY_PARAM, 0.0, 1.0, 0.31623));
		addParam(createParam<Knob29>(sustainParamPosition, module, ADSR::SUSTAIN_PARAM, 0.0, 1.0, 1.0));
		addParam(createParam<Knob29>(releaseParamPosition, module, ADSR::RELEASE_PARAM, 0.0, 1.0, 0.31623));
		addParam(createParam<StatefulButton9>(linearParamPosition, module, ADSR::LINEAR_PARAM, 0.0, 1.0, 0.0));

		addInput(createInput<Port24>(gateInputPosition, module, ADSR::GATE_INPUT));

		addOutput(createOutput<Port24>(outOutputPosition, module, ADSR::OUT_OUTPUT));

		addChild(createLight<TinyLight<GreenLight>>(attackLightPosition, module, ADSR::ATTACK_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(decayLightPosition, module, ADSR::DECAY_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(sustainLightPosition, module, ADSR::SUSTAIN_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(releaseLightPosition, module, ADSR::RELEASE_LIGHT));
		addChild(createLight<SmallLight<GreenLight>>(linearLightPosition, module, ADSR::LINEAR_LIGHT));
	}
};

Model* modelADSR = createModel<ADSR, ADSRWidget>("Bogaudio-ADSR", "ADSR",  "utility envelope", ENVELOPE_GENERATOR_TAG);
