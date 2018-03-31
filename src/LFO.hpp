#pragma once

#include "bogaudio.hpp"
#include "dsp/oscillator.hpp"

using namespace bogaudio::dsp;

extern Model* modelLFO;

namespace bogaudio {

struct LFO : Module {
	enum ParamsIds {
		FREQUENCY_PARAM,
		SLOW_PARAM,
		SAMPLE_PARAM,
		PW_PARAM,
		OFFSET_PARAM,
		SCALE_PARAM,
		NUM_PARAMS
	};

	enum InputsIds {
		SAMPLE_INPUT,
		PW_INPUT,
		OFFSET_INPUT,
		SCALE_INPUT,
		PITCH_INPUT,
		RESET_INPUT,
		NUM_INPUTS
	};

	enum OutputsIds {
		RAMP_UP_OUTPUT,
		RAMP_DOWN_OUTPUT,
		SQUARE_OUTPUT,
		TRIANGLE_OUTPUT,
		SINE_OUTPUT,
		NUM_OUTPUTS
	};

	enum LightsIds {
		SLOW_LIGHT,
		NUM_LIGHTS
	};

	const int modulationSteps = 100;
	const float frequencyExponent = 1.9385f;
	const float maxFrequency = 1000.0f;
	const float minFrequency = 1.0f;
	const float slowModeFactor = 0.01f;
	const float amplitude = 5.0f;

	int _modulationStep = 0;
	bool _slowMode = false;
	int _sampleSteps = 1;
	int _sampleStep = 0;
	float _offset = 0.0f;
	float _scale = 0.0f;
	SchmittTrigger _resetTrigger;

	Phasor _phasor;
	SineTableOscillator _sine;
	TriangleOscillator _triangle;
	SawOscillator _ramp;
	SquareOscillator _square;

	float _sineSample = 0.0f;
	float _triangleSample = 0.0f;
	float _rampUpSample = 0.0f;
	float _rampDownSample = 0.0f;
	float _squareSample = 0.0f;

	bool _sineActive = false;
	bool _triangleActive = false;
	bool _rampUpActive = false;
	bool _rampDownActive = false;
	bool _squareActive = false;

	LFO()
	: Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS)
	, _phasor(engineGetSampleRate(), 1.0f)
	, _sine(0.0f, 0.0f)
	, _triangle(0.0f, 0.0f)
	, _ramp(0.0f, 0.0f)
	, _square(0.0f, 0.0f)
	{
		onReset();
	}

	virtual void onReset() override;
	virtual void onSampleRateChange() override;
	virtual void step() override;
	void updateOutput(Phasor& wave, bool useSample, bool invert, Output& output, float& sample, bool& active);
};

} // namespace bogaudio