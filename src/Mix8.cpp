
#include "Mix8.hpp"

void Mix8::onSampleRateChange() {
	float sr = engineGetSampleRate();
	_channel1.setSampleRate(sr);
	_channel2.setSampleRate(sr);
	_channel3.setSampleRate(sr);
	_channel4.setSampleRate(sr);
	_channel5.setSampleRate(sr);
	_channel6.setSampleRate(sr);
	_channel7.setSampleRate(sr);
	_channel8.setSampleRate(sr);
	_slewLimiter.setParams(sr, MixerChannel::levelSlewTimeMS, MixerChannel::maxDecibels - MixerChannel::minDecibels);
_rms.setSampleRate(sr);
}

void Mix8::step() {
	bool stereo = outputs[L_OUTPUT].active && outputs[R_OUTPUT].active;
	bool solo =
		params[MUTE1_PARAM].value > 1.5f ||
		params[MUTE2_PARAM].value > 1.5f ||
		params[MUTE3_PARAM].value > 1.5f ||
		params[MUTE4_PARAM].value > 1.5f ||
		params[MUTE5_PARAM].value > 1.5f ||
		params[MUTE6_PARAM].value > 1.5f ||
		params[MUTE7_PARAM].value > 1.5f ||
		params[MUTE8_PARAM].value > 1.5f;
	_channel1.next(stereo, solo);
	_channel2.next(stereo, solo);
	_channel3.next(stereo, solo);
	_channel4.next(stereo, solo);
	_channel5.next(stereo, solo);
	_channel6.next(stereo, solo);
	_channel7.next(stereo, solo);
	_channel8.next(stereo, solo);

	float level = Amplifier::minDecibels;
	if (params[MIX_MUTE_PARAM].value < 0.5f) {
		level = params[MIX_PARAM].value;
		if (inputs[MIX_CV_INPUT].active) {
			level *= clamp(inputs[MIX_CV_INPUT].value / 10.0f, 0.0f, 1.0f);
		}
		level *= MixerChannel::maxDecibels - MixerChannel::minDecibels;
		level += MixerChannel::minDecibels;
	}
	_amplifier.setLevel(_slewLimiter.next(level));

	float mono = 0.0f;
	mono += _channel1.out;
	mono += _channel2.out;
	mono += _channel3.out;
	mono += _channel4.out;
	mono += _channel5.out;
	mono += _channel6.out;
	mono += _channel7.out;
	mono += _channel8.out;
	mono = _amplifier.next(mono);
	mono = _saturator.next(mono);
	_rmsLevel = _rms.next(mono) / 5.0f;

	if (stereo) {
		float left = 0.0f;
		left += _channel1.left;
		left += _channel2.left;
		left += _channel3.left;
		left += _channel4.left;
		left += _channel5.left;
		left += _channel6.left;
		left += _channel7.left;
		left += _channel8.left;
		left = _amplifier.next(left);
		left = _saturator.next(left);
		outputs[L_OUTPUT].value = left;

		float right = 0.0f;
		right += _channel1.right;
		right += _channel2.right;
		right += _channel3.right;
		right += _channel4.right;
		right += _channel5.right;
		right += _channel6.right;
		right += _channel7.right;
		right += _channel8.right;
		right = _amplifier.next(right);
		right = _saturator.next(right);
		outputs[R_OUTPUT].value = right;
	}
	else {
		outputs[L_OUTPUT].value = outputs[R_OUTPUT].value = mono;
	}
}

struct Mix8Widget : ModuleWidget {
	static constexpr int hp = 27;

	Mix8Widget(Mix8* module) : ModuleWidget(module) {
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

		{
			SVGPanel *panel = new SVGPanel();
			panel->box.size = box.size;
			panel->setBackground(SVG::load(assetPlugin(plugin, "res/Mix8.svg")));
			addChild(panel);
		}

		addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 365)));

		// generated by svg_widgets.rb
		auto level1ParamPosition = Vec(17.5, 32.0);
		auto mute1ParamPosition = Vec(17.2, 185.7);
		auto pan1ParamPosition = Vec(18.5, 223.0);
		auto level2ParamPosition = Vec(61.5, 32.0);
		auto mute2ParamPosition = Vec(61.2, 185.7);
		auto pan2ParamPosition = Vec(62.5, 223.0);
		auto level3ParamPosition = Vec(105.5, 32.0);
		auto mute3ParamPosition = Vec(105.2, 185.7);
		auto pan3ParamPosition = Vec(106.5, 223.0);
		auto level4ParamPosition = Vec(149.5, 32.0);
		auto mute4ParamPosition = Vec(149.2, 185.7);
		auto pan4ParamPosition = Vec(150.5, 223.0);
		auto level5ParamPosition = Vec(193.5, 32.0);
		auto mute5ParamPosition = Vec(193.2, 185.7);
		auto pan5ParamPosition = Vec(194.5, 223.0);
		auto level6ParamPosition = Vec(237.5, 32.0);
		auto mute6ParamPosition = Vec(237.2, 185.7);
		auto pan6ParamPosition = Vec(238.5, 223.0);
		auto level7ParamPosition = Vec(281.5, 32.0);
		auto mute7ParamPosition = Vec(281.2, 185.7);
		auto pan7ParamPosition = Vec(282.5, 223.0);
		auto level8ParamPosition = Vec(325.5, 32.0);
		auto mute8ParamPosition = Vec(325.2, 185.7);
		auto pan8ParamPosition = Vec(326.5, 223.0);
		auto mixParamPosition = Vec(369.5, 32.0);
		auto mixMuteParamPosition = Vec(369.2, 185.7);

		auto cv1InputPosition = Vec(14.5, 255.0);
		auto pan1InputPosition = Vec(14.5, 290.0);
		auto in1InputPosition = Vec(14.5, 325.0);
		auto cv2InputPosition = Vec(58.5, 255.0);
		auto pan2InputPosition = Vec(58.5, 290.0);
		auto in2InputPosition = Vec(58.5, 325.0);
		auto cv3InputPosition = Vec(102.5, 255.0);
		auto pan3InputPosition = Vec(102.5, 290.0);
		auto in3InputPosition = Vec(102.5, 325.0);
		auto cv4InputPosition = Vec(146.5, 255.0);
		auto pan4InputPosition = Vec(146.5, 290.0);
		auto in4InputPosition = Vec(146.5, 325.0);
		auto cv5InputPosition = Vec(190.5, 255.0);
		auto pan5InputPosition = Vec(190.5, 290.0);
		auto in5InputPosition = Vec(190.5, 325.0);
		auto cv6InputPosition = Vec(234.5, 255.0);
		auto pan6InputPosition = Vec(234.5, 290.0);
		auto in6InputPosition = Vec(234.5, 325.0);
		auto cv7InputPosition = Vec(278.5, 255.0);
		auto pan7InputPosition = Vec(278.5, 290.0);
		auto in7InputPosition = Vec(278.5, 325.0);
		auto cv8InputPosition = Vec(322.5, 255.0);
		auto pan8InputPosition = Vec(322.5, 290.0);
		auto in8InputPosition = Vec(322.5, 325.0);
		auto mixCvInputPosition = Vec(366.5, 252.0);

		auto lOutputPosition = Vec(366.5, 290.0);
		auto rOutputPosition = Vec(366.5, 325.0);
		// end generated by svg_widgets.rb

		addSlider(level1ParamPosition, module, Mix8::LEVEL1_PARAM, module->_channel1.rms);
		addParam(ParamWidget::create<SoloMuteButton>(mute1ParamPosition, module, Mix8::MUTE1_PARAM, 0.0, 3.0, 0.0));
		addParam(ParamWidget::create<Knob16>(pan1ParamPosition, module, Mix8::PAN1_PARAM, -1.0, 1.0, 0.0));
		addSlider(level2ParamPosition, module, Mix8::LEVEL2_PARAM, module->_channel2.rms);
		addParam(ParamWidget::create<SoloMuteButton>(mute2ParamPosition, module, Mix8::MUTE2_PARAM, 0.0, 3.0, 0.0));
		addParam(ParamWidget::create<Knob16>(pan2ParamPosition, module, Mix8::PAN2_PARAM, -1.0, 1.0, 0.0));
		addSlider(level3ParamPosition, module, Mix8::LEVEL3_PARAM, module->_channel3.rms);
		addParam(ParamWidget::create<SoloMuteButton>(mute3ParamPosition, module, Mix8::MUTE3_PARAM, 0.0, 3.0, 0.0));
		addParam(ParamWidget::create<Knob16>(pan3ParamPosition, module, Mix8::PAN3_PARAM, -1.0, 1.0, 0.0));
		addSlider(level4ParamPosition, module, Mix8::LEVEL4_PARAM, module->_channel4.rms);
		addParam(ParamWidget::create<SoloMuteButton>(mute4ParamPosition, module, Mix8::MUTE4_PARAM, 0.0, 3.0, 0.0));
		addParam(ParamWidget::create<Knob16>(pan4ParamPosition, module, Mix8::PAN4_PARAM, -1.0, 1.0, 0.0));
		addSlider(level5ParamPosition, module, Mix8::LEVEL5_PARAM, module->_channel5.rms);
		addParam(ParamWidget::create<SoloMuteButton>(mute5ParamPosition, module, Mix8::MUTE5_PARAM, 0.0, 3.0, 0.0));
		addParam(ParamWidget::create<Knob16>(pan5ParamPosition, module, Mix8::PAN5_PARAM, -1.0, 1.0, 0.0));
		addSlider(level6ParamPosition, module, Mix8::LEVEL6_PARAM, module->_channel6.rms);
		addParam(ParamWidget::create<SoloMuteButton>(mute6ParamPosition, module, Mix8::MUTE6_PARAM, 0.0, 3.0, 0.0));
		addParam(ParamWidget::create<Knob16>(pan6ParamPosition, module, Mix8::PAN6_PARAM, -1.0, 1.0, 0.0));
		addSlider(level7ParamPosition, module, Mix8::LEVEL7_PARAM, module->_channel7.rms);
		addParam(ParamWidget::create<SoloMuteButton>(mute7ParamPosition, module, Mix8::MUTE7_PARAM, 0.0, 3.0, 0.0));
		addParam(ParamWidget::create<Knob16>(pan7ParamPosition, module, Mix8::PAN7_PARAM, -1.0, 1.0, 0.0));
		addSlider(level8ParamPosition, module, Mix8::LEVEL8_PARAM, module->_channel8.rms);
		addParam(ParamWidget::create<SoloMuteButton>(mute8ParamPosition, module, Mix8::MUTE8_PARAM, 0.0, 3.0, 0.0));
		addParam(ParamWidget::create<Knob16>(pan8ParamPosition, module, Mix8::PAN8_PARAM, -1.0, 1.0, 0.0));
		addSlider(mixParamPosition, module, Mix8::MIX_PARAM, module->_rmsLevel);
		addParam(ParamWidget::create<MuteButton>(mixMuteParamPosition, module, Mix8::MIX_MUTE_PARAM, 0.0, 1.0, 0.0));

		addInput(Port::create<Port24>(cv1InputPosition, Port::INPUT, module, Mix8::CV1_INPUT));
		addInput(Port::create<Port24>(pan1InputPosition, Port::INPUT, module, Mix8::PAN1_INPUT));
		addInput(Port::create<Port24>(in1InputPosition, Port::INPUT, module, Mix8::IN1_INPUT));
		addInput(Port::create<Port24>(cv2InputPosition, Port::INPUT, module, Mix8::CV2_INPUT));
		addInput(Port::create<Port24>(pan2InputPosition, Port::INPUT, module, Mix8::PAN2_INPUT));
		addInput(Port::create<Port24>(in2InputPosition, Port::INPUT, module, Mix8::IN2_INPUT));
		addInput(Port::create<Port24>(cv3InputPosition, Port::INPUT, module, Mix8::CV3_INPUT));
		addInput(Port::create<Port24>(pan3InputPosition, Port::INPUT, module, Mix8::PAN3_INPUT));
		addInput(Port::create<Port24>(in3InputPosition, Port::INPUT, module, Mix8::IN3_INPUT));
		addInput(Port::create<Port24>(cv4InputPosition, Port::INPUT, module, Mix8::CV4_INPUT));
		addInput(Port::create<Port24>(pan4InputPosition, Port::INPUT, module, Mix8::PAN4_INPUT));
		addInput(Port::create<Port24>(in4InputPosition, Port::INPUT, module, Mix8::IN4_INPUT));
		addInput(Port::create<Port24>(cv5InputPosition, Port::INPUT, module, Mix8::CV5_INPUT));
		addInput(Port::create<Port24>(pan5InputPosition, Port::INPUT, module, Mix8::PAN5_INPUT));
		addInput(Port::create<Port24>(in5InputPosition, Port::INPUT, module, Mix8::IN5_INPUT));
		addInput(Port::create<Port24>(cv6InputPosition, Port::INPUT, module, Mix8::CV6_INPUT));
		addInput(Port::create<Port24>(pan6InputPosition, Port::INPUT, module, Mix8::PAN6_INPUT));
		addInput(Port::create<Port24>(in6InputPosition, Port::INPUT, module, Mix8::IN6_INPUT));
		addInput(Port::create<Port24>(cv7InputPosition, Port::INPUT, module, Mix8::CV7_INPUT));
		addInput(Port::create<Port24>(pan7InputPosition, Port::INPUT, module, Mix8::PAN7_INPUT));
		addInput(Port::create<Port24>(in7InputPosition, Port::INPUT, module, Mix8::IN7_INPUT));
		addInput(Port::create<Port24>(cv8InputPosition, Port::INPUT, module, Mix8::CV8_INPUT));
		addInput(Port::create<Port24>(pan8InputPosition, Port::INPUT, module, Mix8::PAN8_INPUT));
		addInput(Port::create<Port24>(in8InputPosition, Port::INPUT, module, Mix8::IN8_INPUT));
		addInput(Port::create<Port24>(mixCvInputPosition, Port::INPUT, module, Mix8::MIX_CV_INPUT));

		addOutput(Port::create<Port24>(lOutputPosition, Port::OUTPUT, module, Mix8::L_OUTPUT));
		addOutput(Port::create<Port24>(rOutputPosition, Port::OUTPUT, module, Mix8::R_OUTPUT));
	}

	void addSlider(Vec position, Mix8* module, int id, float& rms) {
		auto slider = ParamWidget::create<VUSlider151>(
			position,
			module,
			id,
			0.0,
			1.0,
			fabsf(MixerChannel::minDecibels) / (MixerChannel::maxDecibels - MixerChannel::minDecibels)
		);
		dynamic_cast<VUSlider*>(slider)->setVULevel(&rms);
		addParam(slider);
	}
};

Model* modelMix8 = createModel<Mix8, Mix8Widget>("Bogaudio-Mix8", "Mix8",  "8-channel mixer and panner", MIXER_TAG, PANNING_TAG);
