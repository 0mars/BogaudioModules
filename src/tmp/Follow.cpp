
#include "Follow.hpp"

void Follow::onSampleRateChange() {
	_rms.setSampleRate(engineGetSampleRate());
}

void Follow::step() {
	if (inputs[IN_INPUT].isConnected() && outputs[OUT_OUTPUT].isConnected()) {
		float response = params[RESPONSE_PARAM].getValue();
		if (inputs[RESPONSE_INPUT].isConnected()) {
			response *= clamp(inputs[RESPONSE_INPUT].getVoltage() / 10.f, 0.0f, 1.0f);
		}
		_rms.setSensitivity(response);

		float scale = params[SCALE_PARAM].getValue();
		if (inputs[SCALE_INPUT].isConnected()) {
			scale *= clamp(inputs[SCALE_INPUT].getVoltage() / 5.0f, -1.0f, 1.0f);
		}

		outputs[OUT_OUTPUT].setVoltage(scale * 2.0f * _rms.next(inputs[IN_INPUT].getVoltage()));
	}
}

struct FollowWidget : ModuleWidget {
	static constexpr int hp = 3;

	FollowWidget(Follow* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

		{
			SVGPanel *panel = new SVGPanel();
			panel->box.size = box.size;
			panel->setBackground(SVG::load(asset::plugin(pluginInstance, "res/Follow.svg")));
			addChild(panel);
		}

		addChild(createWidget<ScrewSilver>(Vec(0, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 15, 365)));

		// generated by svg_widgets.rb
		auto responseParamPosition = Vec(8.0, 36.0);
		auto scaleParamPosition = Vec(8.0, 142.0);

		auto responseInputPosition = Vec(10.5, 77.0);
		auto scaleInputPosition = Vec(10.5, 183.0);
		auto inInputPosition = Vec(10.5, 233.0);

		auto outOutputPosition = Vec(10.5, 271.0);
		// end generated by svg_widgets.rb

		addParam(createParam<Knob29>(responseParamPosition, module, Follow::RESPONSE_PARAM, 0.0, 1.0, 0.3));
		addParam(createParam<Knob29>(scaleParamPosition, module, Follow::SCALE_PARAM, 0.0, 1.0, 1.0));

		addInput(createInput<Port24>(responseInputPosition, module, Follow::RESPONSE_INPUT));
		addInput(createInput<Port24>(scaleInputPosition, module, Follow::SCALE_INPUT));
		addInput(createInput<Port24>(inInputPosition, module, Follow::IN_INPUT));

		addOutput(createOutput<Port24>(outOutputPosition, module, Follow::OUT_OUTPUT));
	}
};

Model* modelFollow = createModel<Follow, FollowWidget>("Bogaudio-Follow", "Follow",  "envelope follower", ENVELOPE_FOLLOWER_TAG);
