
#include "Nsgt.hpp"

void Nsgt::onReset() {
	_modulationStep = modulationSteps;
}

void Nsgt::onSampleRateChange() {
	float sampleRate = engineGetSampleRate();
	_detector.setSampleRate(sampleRate);
	_attackSL.setParams(sampleRate, 150.0f);
	_releaseSL.setParams(sampleRate, 600.0f);
	_modulationStep = modulationSteps;
}

void Nsgt::step() {
	if (!(outputs[LEFT_OUTPUT].isConnected() || outputs[RIGHT_OUTPUT].isConnected())) {
		return;
	}

	++_modulationStep;
	if (_modulationStep >= modulationSteps) {
		_modulationStep = 0;

		_thresholdDb = params[THRESHOLD_PARAM].getValue();
		if (inputs[THRESHOLD_INPUT].isConnected()) {
			_thresholdDb *= clamp(inputs[THRESHOLD_INPUT].getVoltage() / 10.0f, 0.0f, 1.0f);
		}
		_thresholdDb *= 30.0f;
		_thresholdDb -= 24.0f;

		float ratio = params[RATIO_PARAM].getValue();
		if (inputs[RATIO_INPUT].isConnected()) {
			ratio *= clamp(inputs[RATIO_INPUT].getVoltage() / 10.0f, 0.0f, 1.0f);
		}
		if (_ratioKnob != ratio) {
			_ratioKnob = ratio;
			_ratio = powf(_ratioKnob, 1.5f);
			_ratio = 1.0f - _ratio;
			_ratio *= M_PI;
			_ratio *= 0.25f;
			_ratio = tanf(_ratio);
			_ratio = 1.0f / _ratio;
		}

		_softKnee = params[KNEE_PARAM].getValue() > 0.97f;
	}

	float leftInput = inputs[LEFT_INPUT].getVoltage();
	float rightInput = inputs[RIGHT_INPUT].getVoltage();
	float env = _detector.next(leftInput + rightInput);
	if (env > _lastEnv) {
		env = _attackSL.next(env, _lastEnv);
	}
	else {
		env = _releaseSL.next(env, _lastEnv);
	}
	_lastEnv = env;

	float detectorDb = amplitudeToDecibels(env / 5.0f);
	float compressionDb = _noiseGate.compressionDb(detectorDb, _thresholdDb, _ratio, _softKnee);
	_amplifier.setLevel(-compressionDb);
	if (outputs[LEFT_OUTPUT].isConnected()) {
		outputs[LEFT_OUTPUT].setVoltage(_saturator.next(_amplifier.next(leftInput)));
	}
	if (outputs[RIGHT_OUTPUT].isConnected()) {
		outputs[RIGHT_OUTPUT].setVoltage(_saturator.next(_amplifier.next(rightInput)));
	}
}

struct NsgtWidget : ModuleWidget {
	static constexpr int hp = 6;

	NsgtWidget(Nsgt* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

		{
			SVGPanel *panel = new SVGPanel();
			panel->box.size = box.size;
			panel->setBackground(SVG::load(asset::plugin(pluginInstance, "res/Nsgt.svg")));
			addChild(panel);
		}

		addChild(createWidget<ScrewSilver>(Vec(0, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 15, 365)));

		// generated by svg_widgets.rb
		auto thresholdParamPosition = Vec(26.0, 52.0);
		auto ratioParamPosition = Vec(26.0, 135.0);
		auto kneeParamPosition = Vec(39.5, 199.5);

		auto leftInputPosition = Vec(16.0, 244.0);
		auto rightInputPosition = Vec(50.0, 244.0);
		auto thresholdInputPosition = Vec(16.0, 280.0);
		auto ratioInputPosition = Vec(50.0, 280.0);

		auto leftOutputPosition = Vec(16.0, 320.0);
		auto rightOutputPosition = Vec(50.0, 320.0);
		// end generated by svg_widgets.rb

		addParam(createParam<Knob38>(thresholdParamPosition, module, Nsgt::THRESHOLD_PARAM, 0.0, 1.0, 0.8));
		addParam(createParam<Knob38>(ratioParamPosition, module, Nsgt::RATIO_PARAM, 0.0, 1.0, 0.552));
		addParam(createParam<SliderSwitch2State14>(kneeParamPosition, module, Nsgt::KNEE_PARAM, 0.95, 1.0, 1.0));

		addInput(createInput<Port24>(leftInputPosition, module, Nsgt::LEFT_INPUT));
		addInput(createInput<Port24>(rightInputPosition, module, Nsgt::RIGHT_INPUT));
		addInput(createInput<Port24>(thresholdInputPosition, module, Nsgt::THRESHOLD_INPUT));
		addInput(createInput<Port24>(ratioInputPosition, module, Nsgt::RATIO_INPUT));

		addOutput(createOutput<Port24>(leftOutputPosition, module, Nsgt::LEFT_OUTPUT));
		addOutput(createOutput<Port24>(rightOutputPosition, module, Nsgt::RIGHT_OUTPUT));
	}
};

Model* modelNsgt = createModel<Nsgt, NsgtWidget>("Bogaudio-Nsgt", "Nsgt", "noise gate", DYNAMICS_TAG);