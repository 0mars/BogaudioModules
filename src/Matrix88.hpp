#pragma once

#include "bogaudio.hpp"
#include "dsp/signal.hpp"

using namespace bogaudio::dsp;

extern Model* modelMatrix88;

namespace bogaudio {

struct Matrix88 : Module {
	enum ParamsIds {
		MIX11_PARAM,
		MIX21_PARAM,
		MIX31_PARAM,
		MIX41_PARAM,
		MIX51_PARAM,
		MIX61_PARAM,
		MIX71_PARAM,
		MIX81_PARAM,
		MIX12_PARAM,
		MIX22_PARAM,
		MIX32_PARAM,
		MIX42_PARAM,
		MIX52_PARAM,
		MIX62_PARAM,
		MIX72_PARAM,
		MIX82_PARAM,
		MIX13_PARAM,
		MIX23_PARAM,
		MIX33_PARAM,
		MIX43_PARAM,
		MIX53_PARAM,
		MIX63_PARAM,
		MIX73_PARAM,
		MIX83_PARAM,
		MIX14_PARAM,
		MIX24_PARAM,
		MIX34_PARAM,
		MIX44_PARAM,
		MIX54_PARAM,
		MIX64_PARAM,
		MIX74_PARAM,
		MIX84_PARAM,
		MIX15_PARAM,
		MIX25_PARAM,
		MIX35_PARAM,
		MIX45_PARAM,
		MIX55_PARAM,
		MIX65_PARAM,
		MIX75_PARAM,
		MIX85_PARAM,
		MIX16_PARAM,
		MIX26_PARAM,
		MIX36_PARAM,
		MIX46_PARAM,
		MIX56_PARAM,
		MIX66_PARAM,
		MIX76_PARAM,
		MIX86_PARAM,
		MIX17_PARAM,
		MIX27_PARAM,
		MIX37_PARAM,
		MIX47_PARAM,
		MIX57_PARAM,
		MIX67_PARAM,
		MIX77_PARAM,
		MIX87_PARAM,
		MIX18_PARAM,
		MIX28_PARAM,
		MIX38_PARAM,
		MIX48_PARAM,
		MIX58_PARAM,
		MIX68_PARAM,
		MIX78_PARAM,
		MIX88_PARAM,
		LEVEL_PARAM,
		NUM_PARAMS
	};

	enum InputsIds {
		IN1_INPUT,
		IN2_INPUT,
		IN3_INPUT,
		IN4_INPUT,
		IN5_INPUT,
		IN6_INPUT,
		IN7_INPUT,
		IN8_INPUT,
		NUM_INPUTS
	};

	enum OutputsIds {
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		OUT3_OUTPUT,
		OUT4_OUTPUT,
		OUT5_OUTPUT,
		OUT6_OUTPUT,
		OUT7_OUTPUT,
		OUT8_OUTPUT,
		NUM_OUTPUTS
	};

	enum LightsIds {
		NUM_LIGHTS
	};

	float _inputs[8] {};
	Saturator _saturators[8];

	Matrix88() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
	}

	void step() override;
};

} // namespace bogaudio
