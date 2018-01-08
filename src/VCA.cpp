
#include "BogaudioModules.hpp"

struct VCA : Module {
	enum ParamsIds {
		LEVEL1_PARAM,
		LEVEL2_PARAM,
		NUM_PARAMS
	};

	enum InputsIds {
		CV1_INPUT,
		IN1_INPUT,
		CV2_INPUT,
		IN2_INPUT,
		NUM_INPUTS
	};

	enum OutputsIds {
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		NUM_OUTPUTS
	};

	enum LightsIds {
		NUM_LIGHTS
	};

	VCA() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}

	virtual void step() override;
	void channelStep(Input& input, Output& output, Param& knob, Input& cv);
};

void VCA::step() {
	channelStep(inputs[IN1_INPUT], outputs[OUT1_OUTPUT], params[LEVEL1_PARAM], inputs[CV1_INPUT]);
	channelStep(inputs[IN2_INPUT], outputs[OUT2_OUTPUT], params[LEVEL2_PARAM], inputs[CV2_INPUT]);
}

void VCA::channelStep(Input& input, Output& output, Param& knob, Input& cv) {
	if (input.active && output.active) {
		float level = clampf(knob.value, 0.0, 1.0);
		if (cv.active) {
			level *= clampf(cv.value, 0.0, 10.0) / 10.0;
		}
		level = powf(level, 2.0);
		output.value = level * input.value;
	}
	else {
		output.value = 0.0;
	}
}


VCAWidget::VCAWidget() {
	VCA *module = new VCA();
	setModule(module);
	box.size = Vec(RACK_GRID_WIDTH * 3, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/VCA.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(0, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 15, 365)));

	// generated by svg_widgets.rb
	auto level1ParamPosition = Vec(9.5, 28.5);
	auto level2ParamPosition = Vec(9.5, 189.5);

	auto cv1InputPosition = Vec(10.5, 66.0);
	auto in1InputPosition = Vec(10.5, 101.0);
	auto cv2InputPosition = Vec(10.5, 227.0);
	auto in2InputPosition = Vec(10.5, 262.0);

	auto out1OutputPosition = Vec(10.5, 139.0);
	auto out2OutputPosition = Vec(10.5, 300.0);
	// end generated by svg_widgets.rb

	addParam(createParam<Knob26>(level1ParamPosition, module, VCA::LEVEL1_PARAM, 0.0, 1.0, 0.5));
	addParam(createParam<Knob26>(level2ParamPosition, module, VCA::LEVEL2_PARAM, 0.0, 1.0, 0.5));

	addInput(createInput<Port24>(cv1InputPosition, module, VCA::CV1_INPUT));
	addInput(createInput<Port24>(in1InputPosition, module, VCA::IN1_INPUT));
	addInput(createInput<Port24>(cv2InputPosition, module, VCA::CV2_INPUT));
	addInput(createInput<Port24>(in2InputPosition, module, VCA::IN2_INPUT));

	addOutput(createOutput<Port24>(out1OutputPosition, module, VCA::OUT1_OUTPUT));
	addOutput(createOutput<Port24>(out2OutputPosition, module, VCA::OUT2_OUTPUT));
}