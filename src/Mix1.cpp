
#include "Mix1.hpp"

void Mix1::onSampleRateChange() {
	_channel.setSampleRate(engineGetSampleRate());
}

void Mix1::step() {
	_channel.next(false, false);
	outputs[OUT_OUTPUT].value = _channel.out;
}

struct Mix1Widget : ModuleWidget {
	static constexpr int hp = 3;

	Mix1Widget(Mix1* module) : ModuleWidget(module) {
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

		{
			SVGPanel *panel = new SVGPanel();
			panel->box.size = box.size;
			panel->setBackground(SVG::load(assetPlugin(plugin, "res/Mix1.svg")));
			addChild(panel);
		}

		addChild(Widget::create<ScrewSilver>(Vec(0, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 15, 365)));

		// generated by svg_widgets.rb
		auto levelParamPosition = Vec(13.5, 18.0);
		auto muteParamPosition = Vec(13.2, 175.7);

		auto muteInputPosition = Vec(10.5, 198.0);
		auto levelInputPosition = Vec(10.5, 233.0);
		auto inInputPosition = Vec(10.5, 268.0);

		auto outOutputPosition = Vec(10.5, 306.0);
		// end generated by svg_widgets.rb

		{
			auto slider = ParamWidget::create<VUSlider151>(
				levelParamPosition,
				module,
				Mix1::LEVEL_PARAM,
				0.0,
				1.0,
				fabsf(MixerChannel::minDecibels) / (MixerChannel::maxDecibels - MixerChannel::minDecibels)
			);
			dynamic_cast<VUSlider*>(slider)->setVULevel(&module->_channel.rms);
			addParam(slider);
		}
		addParam(ParamWidget::create<MuteButton>(muteParamPosition, module, Mix1::MUTE_PARAM, 0.0, 1.0, 0.0));

		addInput(Port::create<Port24>(muteInputPosition, Port::INPUT, module, Mix1::MUTE_INPUT));
		addInput(Port::create<Port24>(levelInputPosition, Port::INPUT, module, Mix1::LEVEL_INPUT));
		addInput(Port::create<Port24>(inInputPosition, Port::INPUT, module, Mix1::IN_INPUT));

		addOutput(Port::create<Port24>(outOutputPosition, Port::OUTPUT, module, Mix1::OUT_OUTPUT));
	}
};

Model* modelMix1 = createModel<Mix1, Mix1Widget>("Bogaudio-Mix1", "MIX1", "fader/amplifier with mute", AMPLIFIER_TAG);