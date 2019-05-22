
#include "DADSRHPlus.hpp"

struct DADSRHPlusWidget : ModuleWidget {
	static constexpr int hp = 15;

	DADSRHPlusWidget(DADSRHPlus* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

		{
			SVGPanel *panel = new SVGPanel();
			panel->box.size = box.size;
			panel->setBackground(SVG::load(asset::plugin(pluginInstance, "res/DADSRHPlus.svg")));
			addChild(panel);
		}

		addChild(createWidget<ScrewSilver>(Vec(15, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 30, 0)));
		addChild(createWidget<ScrewSilver>(Vec(15, 365)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 30, 365)));

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
		auto modeParamPosition = Vec(120.0, 95.0);
		auto loopParamPosition = Vec(120.0, 145.0);
		auto speedParamPosition = Vec(20.0, 321.0);
		auto retriggerParamPosition = Vec(55.0, 321.0);

		auto delayInputPosition = Vec(152.0, 40.0);
		auto attackInputPosition = Vec(152.0, 96.0);
		auto decayInputPosition = Vec(152.0, 152.0);
		auto sustainInputPosition = Vec(152.0, 208.0);
		auto releaseInputPosition = Vec(152.0, 264.0);
		auto holdInputPosition = Vec(152.0, 320.0);
		auto triggerInputPosition = Vec(115.0, 40.0);

		auto delayOutputPosition = Vec(189.0, 40.0);
		auto attackOutputPosition = Vec(189.0, 96.0);
		auto decayOutputPosition = Vec(189.0, 152.0);
		auto sustainOutputPosition = Vec(189.0, 208.0);
		auto releaseOutputPosition = Vec(189.0, 264.0);
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

		addParam(createParam<Knob38>(delayParamPosition, module, DADSRHPlus::DELAY_PARAM, 0.0, 1.0, 0.0));
		addParam(createParam<Knob38>(attackParamPosition, module, DADSRHPlus::ATTACK_PARAM, 0.0, 1.0, 0.12));
		addParam(createParam<Knob38>(decayParamPosition, module, DADSRHPlus::DECAY_PARAM, 0.0, 1.0, 0.32));
		addParam(createParam<Knob38>(sustainParamPosition, module, DADSRHPlus::SUSTAIN_PARAM, 0.0, 1.0, 0.5));
		addParam(createParam<Knob38>(releaseParamPosition, module, DADSRHPlus::RELEASE_PARAM, 0.0, 1.0, 0.32));
		addParam(createParam<Knob38>(holdParamPosition, module, DADSRHPlus::HOLD_PARAM, 0.0, 1.0, 0.45));
		addParam(createParam<StatefulButton9>(attackShapeParamPosition, module, DADSRHPlus::ATTACK_SHAPE_PARAM, 1.0, 3.0, 1.0));
		addParam(createParam<StatefulButton9>(decayShapeParamPosition, module, DADSRHPlus::DECAY_SHAPE_PARAM, 1.0, 3.0, 1.0));
		addParam(createParam<StatefulButton9>(releaseShapeParamPosition, module, DADSRHPlus::RELEASE_SHAPE_PARAM, 1.0, 3.0, 1.0));
		addParam(createParam<Button18>(triggerParamPosition, module, DADSRHPlus::TRIGGER_PARAM, 0.0, 1.0, 0.0));
		addParam(createParam<SliderSwitch2State14>(modeParamPosition, module, DADSRHPlus::MODE_PARAM, 0.0, 1.0, 1.0));
		addParam(createParam<SliderSwitch2State14>(loopParamPosition, module, DADSRHPlus::LOOP_PARAM, 0.0, 1.0, 1.0));
		addParam(createParam<SliderSwitch2State14>(speedParamPosition, module, DADSRHPlus::SPEED_PARAM, 0.0, 1.0, 1.0));
		addParam(createParam<SliderSwitch2State14>(retriggerParamPosition, module, DADSRHPlus::RETRIGGER_PARAM, 0.0, 1.0, 1.0));

		addInput(createInput<Port24>(delayInputPosition, module, DADSRHPlus::DELAY_INPUT));
		addInput(createInput<Port24>(attackInputPosition, module, DADSRHPlus::ATTACK_INPUT));
		addInput(createInput<Port24>(decayInputPosition, module, DADSRHPlus::DECAY_INPUT));
		addInput(createInput<Port24>(sustainInputPosition, module, DADSRHPlus::SUSTAIN_INPUT));
		addInput(createInput<Port24>(releaseInputPosition, module, DADSRHPlus::RELEASE_INPUT));
		addInput(createInput<Port24>(holdInputPosition, module, DADSRHPlus::HOLD_INPUT));
		addInput(createInput<Port24>(triggerInputPosition, module, DADSRHPlus::TRIGGER_INPUT));

		addOutput(createOutput<Port24>(delayOutputPosition, module, DADSRHPlus::DELAY_OUTPUT));
		addOutput(createOutput<Port24>(attackOutputPosition, module, DADSRHPlus::ATTACK_OUTPUT));
		addOutput(createOutput<Port24>(decayOutputPosition, module, DADSRHPlus::DECAY_OUTPUT));
		addOutput(createOutput<Port24>(sustainOutputPosition, module, DADSRHPlus::SUSTAIN_OUTPUT));
		addOutput(createOutput<Port24>(releaseOutputPosition, module, DADSRHPlus::RELEASE_OUTPUT));
		addOutput(createOutput<Port24>(envOutputPosition, module, DADSRHPlus::ENV_OUTPUT));
		addOutput(createOutput<Port24>(invOutputPosition, module, DADSRHPlus::INV_OUTPUT));
		addOutput(createOutput<Port24>(triggerOutputPosition, module, DADSRHPlus::TRIGGER_OUTPUT));

		addChild(createLight<TinyLight<GreenLight>>(delayLightPosition, module, DADSRHPlus::DELAY_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(attackLightPosition, module, DADSRHPlus::ATTACK_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(decayLightPosition, module, DADSRHPlus::DECAY_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(sustainLightPosition, module, DADSRHPlus::SUSTAIN_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(releaseLightPosition, module, DADSRHPlus::RELEASE_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(attackShape1LightPosition, module, DADSRHPlus::ATTACK_SHAPE1_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(attackShape2LightPosition, module, DADSRHPlus::ATTACK_SHAPE2_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(attackShape3LightPosition, module, DADSRHPlus::ATTACK_SHAPE3_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(decayShape1LightPosition, module, DADSRHPlus::DECAY_SHAPE1_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(decayShape2LightPosition, module, DADSRHPlus::DECAY_SHAPE2_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(decayShape3LightPosition, module, DADSRHPlus::DECAY_SHAPE3_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(releaseShape1LightPosition, module, DADSRHPlus::RELEASE_SHAPE1_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(releaseShape2LightPosition, module, DADSRHPlus::RELEASE_SHAPE2_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(releaseShape3LightPosition, module, DADSRHPlus::RELEASE_SHAPE3_LIGHT));
	}

	void appendContextMenu(Menu* menu) override {
		DADSRHPlus* dadsrhPlus = dynamic_cast<DADSRHPlus*>(module);
		assert(dadsrhPlus);
		menu->addChild(new MenuLabel());
		menu->addChild(new TriggerOnLoadMenuItem(dadsrhPlus, "Resume loop on load"));
	}
};

Model* modelDADSRHPlus = createModel<DADSRHPlus, DADSRHPlusWidget>("Bogaudio-DADSRHPlus", "DADSR(H)+",  "advanced envelope", ENVELOPE_GENERATOR_TAG);