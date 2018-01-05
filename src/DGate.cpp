
#include "BogaudioModules.hpp"

struct DGate : Module {
	enum ParamsIds {
		DELAY_PARAM,
		GATE_PARAM,
		LOOP_PARAM,
		TRIGGER_PARAM,
		NUM_PARAMS
	};

	enum InputsIds {
		TRIGGER_INPUT,
		NUM_INPUTS
	};

	enum OutputsIds {
		GATE_OUTPUT,
		END_OUTPUT,
		NUM_OUTPUTS
	};

	enum LightsIds {
		DELAY_LIGHT,
		GATE_LIGHT,
		NUM_LIGHTS
	};

	enum Stage {
		STOPPED_STAGE,
		DELAY_STAGE,
		GATE_STAGE
	};

	SchmittTrigger _trigger;
	PulseGenerator _triggerOuptutPulseGen;
	Stage _stage;
	float _stageProgress;

	DGate() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
		reset();
	}

	virtual void reset() override;
	virtual void step() override;
	bool stepStage(Param& knob);
};

void DGate::reset() {
	_trigger.reset();
	_triggerOuptutPulseGen.process(10.0);
	_stage = STOPPED_STAGE;
	_stageProgress = 0.0;
}

void DGate::step() {
	float envelope = 0.0;
	bool complete = false;
	if (_trigger.process(params[TRIGGER_PARAM].value + inputs[TRIGGER_INPUT].value)) {
		_stage = DELAY_STAGE;
		_stageProgress = 0.0;
	}
	else {
		switch (_stage) {
			case STOPPED_STAGE: {
				break;
			}
			case DELAY_STAGE: {
				if (stepStage(params[DELAY_PARAM])) {
					_stage = GATE_STAGE;
					_stageProgress = 0.0;
				}
				break;
			}
			case GATE_STAGE: {
				if (stepStage(params[GATE_PARAM])) {
					complete = true;
					if (params[LOOP_PARAM].value <= 0.0 || _trigger.isHigh()) {
						_stage = DELAY_STAGE;
						_stageProgress = 0.0;
					}
					else {
						_stage = STOPPED_STAGE;
					}
				}
				else {
					envelope = 1.0;
				}
				break;
			}
		}
	}

	outputs[GATE_OUTPUT].value = envelope * 10.0;
	if (complete) {
		_triggerOuptutPulseGen.trigger(0.001);
	}
	outputs[END_OUTPUT].value = _triggerOuptutPulseGen.process(engineGetSampleTime()) ? 5.0 : 0.0;

	lights[DELAY_LIGHT].value = _stage == DELAY_STAGE;
	lights[GATE_LIGHT].value = _stage == GATE_STAGE;
}

bool DGate::stepStage(Param& knob) {
	float t = clampf(knob.value, 0.0, 1.0);
	t = pow(t, 2);
	t = fmaxf(t, 0.001);
	t *= 10.0;
	_stageProgress += engineGetSampleTime() / t;
	return _stageProgress > 1.0;
}


DGateWidget::DGateWidget() {
	DGate *module = new DGate();
	setModule(module);
	box.size = Vec(RACK_GRID_WIDTH * 3, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/DGATE.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(0, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 15, 365)));

	// generated by svg_widgets.rb
	auto delayParamPosition = Vec(7.5, 32.5);
	auto gateParamPosition = Vec(7.5, 91.5);
	auto loopParamPosition = Vec(15.0, 144.5);
	auto triggerParamPosition = Vec(13.5, 190.0);

	auto triggerInputPosition = Vec(10.5, 213.0);

	auto gateOutputPosition = Vec(10.5, 252.0);
	auto endOutputPosition = Vec(10.5, 287.0);

	auto delayLightPosition = Vec(20.8, 65.0);
	auto gateLightPosition = Vec(20.8, 124.0);
	// end generated by svg_widgets.rb

	addParam(createParam<Knob29>(delayParamPosition, module, DGate::DELAY_PARAM, 0.0, 1.0, 0.0));
	addParam(createParam<Knob29>(gateParamPosition, module, DGate::GATE_PARAM, 0.0, 1.0, 0.32));
	addParam(createParam<SliderSwitch2State14>(loopParamPosition, module, DGate::LOOP_PARAM, 0.0, 1.0, 1.0));
	addParam(createParam<Button18>(triggerParamPosition, module, DGate::TRIGGER_PARAM, 0.0, 1.0, 0.0));

	addInput(createInput<Port24>(triggerInputPosition, module, DGate::TRIGGER_INPUT));

	addOutput(createOutput<Port24>(gateOutputPosition, module, DGate::GATE_OUTPUT));
	addOutput(createOutput<Port24>(endOutputPosition, module, DGate::END_OUTPUT));

	addChild(createLight<TinyLight<GreenLight>>(delayLightPosition, module, DGate::DELAY_LIGHT));
	addChild(createLight<TinyLight<GreenLight>>(gateLightPosition, module, DGate::GATE_LIGHT));
}
