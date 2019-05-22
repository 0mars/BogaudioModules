
#include "Shaper.hpp"

struct ShaperWidget : ModuleWidget {
	static constexpr int hp = 10;

	ShaperWidget(Shaper* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

		{
			SVGPanel *panel = new SVGPanel();
			panel->box.size = box.size;
			panel->setBackground(SVG::load(asset::plugin(pluginInstance, "res/Shaper.svg")));
			addChild(panel);
		}

		addChild(createWidget<ScrewSilver>(Vec(0, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 15, 0)));
		addChild(createWidget<ScrewSilver>(Vec(0, 365)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 15, 365)));

		// generated by svg_widgets.rb
		auto attackParamPosition = Vec(29.08, 33.08);
		auto triggerParamPosition = Vec(89.04, 43.04);
		auto onParamPosition = Vec(29.08, 89.08);
		auto speedParamPosition = Vec(119.0, 96.0);
		auto decayParamPosition = Vec(29.08, 145.08);
		auto loopParamPosition = Vec(119.0, 152.0);
		auto offParamPosition = Vec(29.08, 201.08);
		auto envParamPosition = Vec(82.38, 257.08);
		auto signalParamPosition = Vec(82.38, 313.08);

		auto triggerInputPosition = Vec(114.0, 40.0);
		auto signalInputPosition = Vec(11.5, 320.0);

		auto triggerOutputPosition = Vec(114.0, 208.0);
		auto envOutputPosition = Vec(11.5, 264.0);
		auto invOutputPosition = Vec(40.5, 264.0);
		auto signalOutputPosition = Vec(40.5, 320.0);

		auto attackLightPosition = Vec(12.0, 80.0);
		auto onLightPosition = Vec(12.0, 121.0);
		auto decayLightPosition = Vec(12.0, 189.0);
		auto offLightPosition = Vec(12.0, 237.0);
		// end generated by svg_widgets.rb

		addParam(createParam<Knob38>(attackParamPosition, module, Shaper::ATTACK_PARAM, 0.0, 1.0, 0.12));
		addParam(createParam<Knob38>(onParamPosition, module, Shaper::ON_PARAM, 0.0, 1.0, 0.32));
		addParam(createParam<Knob38>(decayParamPosition, module, Shaper::DECAY_PARAM, 0.0, 1.0, 0.32));
		addParam(createParam<Knob38>(offParamPosition, module, Shaper::OFF_PARAM, 0.0, 1.0, 0.07));
		addParam(createParam<Knob38>(envParamPosition, module, Shaper::ENV_PARAM, 0.0, 1.0, 1.0));
		addParam(createParam<Knob38>(signalParamPosition, module, Shaper::SIGNAL_PARAM, 0.0, 1.0, 0.1));

		addParam(createParam<Button18>(triggerParamPosition, module, Shaper::TRIGGER_PARAM, 0.0, 1.0, 0.0));
		addInput(createInput<Port24>(triggerInputPosition, module, Shaper::TRIGGER_INPUT));

		addParam(createParam<SliderSwitch2State14>(speedParamPosition, module, Shaper::SPEED_PARAM, 0.0, 1.0, 1.0));
		addParam(createParam<SliderSwitch2State14>(loopParamPosition, module, Shaper::LOOP_PARAM, 0.0, 1.0, 1.0));
		addOutput(createOutput<Port24>(triggerOutputPosition, module, Shaper::TRIGGER_OUTPUT));

		addOutput(createOutput<Port24>(envOutputPosition, module, Shaper::ENV_OUTPUT));
		addOutput(createOutput<Port24>(invOutputPosition, module, Shaper::INV_OUTPUT));

		addInput(createInput<Port24>(signalInputPosition, module, Shaper::SIGNAL_INPUT));
		addOutput(createOutput<Port24>(signalOutputPosition, module, Shaper::SIGNAL_OUTPUT));

		addChild(createLight<TinyLight<GreenLight>>(attackLightPosition, module, Shaper::ATTACK_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(onLightPosition, module, Shaper::ON_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(decayLightPosition, module, Shaper::DECAY_LIGHT));
		addChild(createLight<TinyLight<GreenLight>>(offLightPosition, module, Shaper::OFF_LIGHT));
	}

	void appendContextMenu(Menu* menu) override {
		Shaper* shaper = dynamic_cast<Shaper*>(module);
		assert(shaper);
		menu->addChild(new MenuLabel());
		menu->addChild(new TriggerOnLoadMenuItem(shaper, "Resume loop on load"));
	}
};

Model* modelShaper = createModel<Shaper, ShaperWidget>("Bogaudio-Shaper", "Shaper",  "envelope and amplifier", ENVELOPE_GENERATOR_TAG, AMPLIFIER_TAG);