#pragma once

#include "bogaudio.hpp"
#include "dsp/envelope.hpp"
#include "dsp/signal.hpp"

using namespace bogaudio::dsp;

extern Model* modelAD;

namespace bogaudio {

struct AD : Module {
	enum ParamsIds {
		ATTACK_PARAM,
		DECAY_PARAM,
		LOOP_PARAM,
		LINEAR_PARAM,
		NUM_PARAMS
	};

	enum InputsIds {
		TRIGGER_INPUT,
		ATTACK_INPUT,
		DECAY_INPUT,
		NUM_INPUTS
	};

	enum OutputsIds {
		ENV_OUTPUT,
		EOC_OUTPUT,
		NUM_OUTPUTS
	};

	enum LightsIds {
		ATTACK_LIGHT,
		DECAY_LIGHT,
		LOOP_LIGHT,
		LINEAR_LIGHT,
		NUM_LIGHTS
	};

	const int modulationSteps = 100;
	int _modulationStep = 0;
	bool _loopMode = false;
	bool _linearMode = false;
	Trigger _trigger;
	rack::dsp::PulseGenerator _eocPulseGen;
	bool _on = false;
	ADSR _envelope;
	bogaudio::dsp::SlewLimiter _attackSL;
	bogaudio::dsp::SlewLimiter _decaySL;

	AD() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(AD::ATTACK_PARAM, 0.0, 1.0, 0.12);
		configParam(AD::DECAY_PARAM, 0.0, 1.0, 0.31623);
		configParam(AD::LOOP_PARAM, 0.0, 1.0, 0.0);
		configParam(AD::LINEAR_PARAM, 0.0, 1.0, 0.0);

		onReset();
		onSampleRateChange();
		_envelope.setSustain(0.0f);
		_envelope.setRelease(0.0f);
	}

	void onReset() override;
	void onSampleRateChange() override;
	void process(const ProcessArgs &args) override;
};

} // namespace bogaudio
