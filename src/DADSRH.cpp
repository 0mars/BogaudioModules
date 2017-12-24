
#include "DADSRHCore.hpp"

struct DADSRH : Module {
	enum ParamsIds {
	  DELAY_PARAM,
	  ATTACK_PARAM,
	  DECAY_PARAM,
	  SUSTAIN_PARAM,
	  RELEASE_PARAM,
	  HOLD_PARAM,
	  ATTACK_SHAPE_PARAM,
	  DECAY_SHAPE_PARAM,
	  RELEASE_SHAPE_PARAM,
	  TRIGGER_PARAM,
	  MODE_PARAM,
	  LOOP_PARAM,
	  SPEED_PARAM,
	  RETRIGGER_PARAM,
	  NUM_PARAMS
	};

	enum InputsIds {
	  TRIGGER_INPUT,
	  NUM_INPUTS
	};

	enum OutputsIds {
	  ENV_OUTPUT,
	  INV_OUTPUT,
	  TRIGGER_OUTPUT,
	  NUM_OUTPUTS
	};

	enum LightsIds {
	  DELAY_LIGHT,
	  ATTACK_LIGHT,
	  DECAY_LIGHT,
	  SUSTAIN_LIGHT,
	  RELEASE_LIGHT,
	  ATTACK_SHAPE1_LIGHT,
	  ATTACK_SHAPE2_LIGHT,
	  ATTACK_SHAPE3_LIGHT,
	  DECAY_SHAPE1_LIGHT,
	  DECAY_SHAPE2_LIGHT,
	  DECAY_SHAPE3_LIGHT,
	  RELEASE_SHAPE1_LIGHT,
	  RELEASE_SHAPE2_LIGHT,
	  RELEASE_SHAPE3_LIGHT,
	  NUM_LIGHTS
	};

	DADSRHCore _core;

	DADSRH() : Module(
		NUM_PARAMS,
		NUM_INPUTS,
		NUM_OUTPUTS,
		NUM_LIGHTS
	)
	, _core(
		params[DELAY_PARAM],
		params[ATTACK_PARAM],
		params[DECAY_PARAM],
		params[SUSTAIN_PARAM],
		params[RELEASE_PARAM],
		params[HOLD_PARAM],
		params[ATTACK_SHAPE_PARAM],
		params[DECAY_SHAPE_PARAM],
		params[RELEASE_SHAPE_PARAM],
		params[TRIGGER_PARAM],
		params[MODE_PARAM],
		params[LOOP_PARAM],
		params[SPEED_PARAM],
		params[RETRIGGER_PARAM],

		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		inputs[TRIGGER_INPUT],

		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		outputs[ENV_OUTPUT],
		outputs[INV_OUTPUT],
		outputs[TRIGGER_OUTPUT],

		lights[DELAY_LIGHT],
		lights[ATTACK_LIGHT],
		lights[DECAY_LIGHT],
		lights[SUSTAIN_LIGHT],
		lights[RELEASE_LIGHT],
		lights[ATTACK_SHAPE1_LIGHT],
		lights[ATTACK_SHAPE2_LIGHT],
		lights[ATTACK_SHAPE3_LIGHT],
		lights[DECAY_SHAPE1_LIGHT],
		lights[DECAY_SHAPE2_LIGHT],
		lights[DECAY_SHAPE3_LIGHT],
		lights[RELEASE_SHAPE1_LIGHT],
		lights[RELEASE_SHAPE2_LIGHT],
		lights[RELEASE_SHAPE3_LIGHT]
	) {
		reset();
	}

  virtual void reset() override {
		_core.reset();
	}

  virtual void step() override {
		_core.step();
	}
};


DADSRHWidget::DADSRHWidget() {
	DADSRH *module = new DADSRH();
	setModule(module);
	box.size = Vec(RACK_GRID_WIDTH * 10, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/DADSRH.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(0, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 15, 0)));
	addChild(createScrew<ScrewSilver>(Vec(0, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 15, 365)));

	// generated by svg_widgets.rb
	auto delayParamPosition = Vec(27.08, 33.08);
	auto attackParamPosition = Vec(27.08, 89.08);
	auto decayParamPosition = Vec(27.08, 145.08);
	auto sustainParamPosition = Vec(27.08, 201.08);
	auto releaseParamPosition = Vec(27.08, 257.08);
	auto holdParamPosition = Vec(82.38, 313.08);
	auto attackShapeParamPosition = Vec(77.02, 124.02);
	auto decayShapeParamPosition = Vec(77.02, 180.52);
	auto releaseShapeParamPosition = Vec(77.02, 292.52);
	auto triggerParamPosition = Vec(90.04, 43.04);
	auto modeParamPosition = Vec(119.9, 96.9);
	auto loopParamPosition = Vec(119.9, 146.9);
	auto speedParamPosition = Vec(19.9, 322.9);
	auto retriggerParamPosition = Vec(54.9, 322.9);

	auto triggerInputPosition = Vec(115.0, 40.0);

	auto envOutputPosition = Vec(115.0, 191.0);
	auto invOutputPosition = Vec(115.0, 228.0);
	auto triggerOutputPosition = Vec(115.0, 265.0);

	auto delayLightPosition = Vec(12.0, 76.0);
	auto attackLightPosition = Vec(12.0, 123.0);
	auto decayLightPosition = Vec(12.0, 179.0);
	auto sustainLightPosition = Vec(12.0, 235.0);
	auto releaseLightPosition = Vec(12.0, 291.0);
	auto attackShape1LightPosition = Vec(77.0, 96.0);
	auto attackShape2LightPosition = Vec(77.0, 106.0);
	auto attackShape3LightPosition = Vec(77.0, 116.0);
	auto decayShape1LightPosition = Vec(77.0, 152.5);
	auto decayShape2LightPosition = Vec(77.0, 162.5);
	auto decayShape3LightPosition = Vec(77.0, 172.5);
	auto releaseShape1LightPosition = Vec(77.0, 264.5);
	auto releaseShape2LightPosition = Vec(77.0, 274.5);
	auto releaseShape3LightPosition = Vec(77.0, 284.5);
	// end generated by svg_widgets.rb

	addParam(createParam<Knob38>(delayParamPosition, module, DADSRH::DELAY_PARAM, 0.0, 1.0, 0.0));
	addParam(createParam<Knob38>(attackParamPosition, module, DADSRH::ATTACK_PARAM, 0.0, 1.0, 0.12));
	addParam(createParam<Knob38>(decayParamPosition, module, DADSRH::DECAY_PARAM, 0.0, 1.0, 0.32));
	addParam(createParam<Knob38>(sustainParamPosition, module, DADSRH::SUSTAIN_PARAM, 0.0, 1.0, 0.5));
	addParam(createParam<Knob38>(releaseParamPosition, module, DADSRH::RELEASE_PARAM, 0.0, 1.0, 0.32));
	addParam(createParam<Knob38>(holdParamPosition, module, DADSRH::HOLD_PARAM, 0.0, 1.0, 0.45));
	addParam(createParam<Button9Toggle3>(attackShapeParamPosition, module, DADSRH::ATTACK_SHAPE_PARAM, 1.0, 3.0, 1.0));
	addParam(createParam<Button9Toggle3>(decayShapeParamPosition, module, DADSRH::DECAY_SHAPE_PARAM, 1.0, 3.0, 1.0));
	addParam(createParam<Button9Toggle3>(releaseShapeParamPosition, module, DADSRH::RELEASE_SHAPE_PARAM, 1.0, 3.0, 1.0));
	addParam(createParam<Button18>(triggerParamPosition, module, DADSRH::TRIGGER_PARAM, 0.0, 1.0, 0.0));
	addParam(createParam<CKSS>(modeParamPosition, module, DADSRH::MODE_PARAM, 0.0, 1.0, 1.0));
	addParam(createParam<CKSS>(loopParamPosition, module, DADSRH::LOOP_PARAM, 0.0, 1.0, 1.0));
	addParam(createParam<CKSS>(speedParamPosition, module, DADSRH::SPEED_PARAM, 0.0, 1.0, 1.0));
	addParam(createParam<CKSS>(retriggerParamPosition, module, DADSRH::RETRIGGER_PARAM, 0.0, 1.0, 1.0));

	addInput(createInput<Port24>(triggerInputPosition, module, DADSRH::TRIGGER_INPUT));

	addOutput(createOutput<Port24>(envOutputPosition, module, DADSRH::ENV_OUTPUT));
	addOutput(createOutput<Port24>(invOutputPosition, module, DADSRH::INV_OUTPUT));
	addOutput(createOutput<Port24>(triggerOutputPosition, module, DADSRH::TRIGGER_OUTPUT));

	addChild(createLight<TinyLight<GreenLight>>(delayLightPosition, module, DADSRH::DELAY_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(attackLightPosition, module, DADSRH::ATTACK_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(decayLightPosition, module, DADSRH::DECAY_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(sustainLightPosition, module, DADSRH::SUSTAIN_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(releaseLightPosition, module, DADSRH::RELEASE_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(attackShape1LightPosition, module, DADSRH::ATTACK_SHAPE1_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(attackShape2LightPosition, module, DADSRH::ATTACK_SHAPE2_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(attackShape3LightPosition, module, DADSRH::ATTACK_SHAPE3_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(decayShape1LightPosition, module, DADSRH::DECAY_SHAPE1_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(decayShape2LightPosition, module, DADSRH::DECAY_SHAPE2_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(decayShape3LightPosition, module, DADSRH::DECAY_SHAPE3_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(releaseShape1LightPosition, module, DADSRH::RELEASE_SHAPE1_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(releaseShape2LightPosition, module, DADSRH::RELEASE_SHAPE2_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(releaseShape3LightPosition, module, DADSRH::RELEASE_SHAPE3_LIGHT));
}
