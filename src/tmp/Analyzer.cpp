
#include "Analyzer.hpp"

#define RANGE_DB_KEY "range_db"

void Analyzer::onReset() {
	_modulationStep = modulationSteps;
	_core.resetChannels();
}

void Analyzer::onSampleRateChange() {
	_modulationStep = modulationSteps;
	_core.resetChannels();
}

json_t* Analyzer::dataToJson() {
	json_t* root = json_object();
	json_object_set_new(root, RANGE_DB_KEY, json_real(_rangeDb));
	return root;
}

void Analyzer::dataFromJson(json_t* root) {
	json_t* jrd = json_object_get(root, RANGE_DB_KEY);
	if (jrd) {
		_rangeDb = clamp(json_real_value(jrd), 80.0f, 140.0f);
	}
}

void Analyzer::step() {
	++_modulationStep;
	if (_modulationStep >= modulationSteps) {
		_modulationStep = 0;

		float range = params[RANGE2_PARAM].getValue();
		_rangeMinHz = 0.0f;
		_rangeMaxHz = 0.5f * engineGetSampleRate();
		if (range < 0.0f) {
			range *= 0.9f;
			_rangeMaxHz *= 1.0f + range;
		}
		else if (range > 0.0f) {
			range *= range;
			range *= 0.8f;
			_rangeMinHz = range * _rangeMaxHz;
		}

		const float maxTime = 0.5;
		float smooth = params[SMOOTH_PARAM].getValue() * maxTime;
		smooth /= _core.size() / (_core._overlap * engineGetSampleRate());
		int averageN = std::max(1, (int)roundf(smooth));

		AnalyzerCore::Quality quality = AnalyzerCore::QUALITY_GOOD;
		if (params[QUALITY_PARAM].getValue() > 2.5) {
			quality = AnalyzerCore::QUALITY_ULTRA;
		}
		else if (params[QUALITY_PARAM].getValue() > 1.5) {
			quality = AnalyzerCore::QUALITY_HIGH;
		}

		AnalyzerCore::Window window = AnalyzerCore::WINDOW_KAISER;
		if (params[WINDOW_PARAM].getValue() > 2.5) {
			window = AnalyzerCore::WINDOW_NONE;
		}
		else if (params[WINDOW_PARAM].getValue() > 1.5) {
			window = AnalyzerCore::WINDOW_HAMMING;
		}

		_core.setParams(averageN, quality, window);
	}

	for (int i = 0; i < 4; ++i) {
		_core.stepChannel(i, inputs[SIGNALA_INPUT + i]);
		outputs[SIGNALA_OUTPUT + i].setVoltage(inputs[SIGNALA_INPUT + i].getVoltage());
	}

	lights[QUALITY_ULTRA_LIGHT].value = _core._quality == AnalyzerCore::QUALITY_ULTRA;
	lights[QUALITY_HIGH_LIGHT].value = _core._quality == AnalyzerCore::QUALITY_HIGH;
	lights[QUALITY_GOOD_LIGHT].value = _core._quality == AnalyzerCore::QUALITY_GOOD;
	lights[WINDOW_NONE_LIGHT].value = _core._window == AnalyzerCore::WINDOW_NONE;
	lights[WINDOW_HAMMING_LIGHT].value = _core._window == AnalyzerCore::WINDOW_HAMMING;
	lights[WINDOW_KAISER_LIGHT].value = _core._window == AnalyzerCore::WINDOW_KAISER;
}

struct RangeDbMenuItem : MenuItem {
	Analyzer* _module;
	const float _rangeDb;

	RangeDbMenuItem(Analyzer* module, const char* label, float rangeDb)
	: _module(module)
	, _rangeDb(rangeDb)
	{
		this->text = label;
	}

	void onAction(EventAction &e) override {
		_module->_rangeDb = _rangeDb;
	}

	void step() override {
		rightText = _module->_rangeDb == _rangeDb ? "✔" : "";
	}
};

struct AnalyzerWidget : ModuleWidget {
	static constexpr int hp = 20;

	AnalyzerWidget(Analyzer* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

		{
			auto panel = new SVGPanel();
			panel->box.size = box.size;
			panel->setBackground(SVG::load(asset::plugin(pluginInstance, "res/Analyzer.svg")));
			addChild(panel);
		}

		{
			auto inset = Vec(10, 25);
			auto size = Vec(box.size.x - 2*inset.x, 230);
			auto display = new AnalyzerDisplay(module, size, true);
			display->box.pos = inset;
			display->box.size = size;
			addChild(display);
		}

		addChild(createWidget<ScrewSilver>(Vec(15, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 30, 0)));
		addChild(createWidget<ScrewSilver>(Vec(15, 365)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 30, 365)));

		// generated by svg_widgets.rb
		auto range2ParamPosition = Vec(30.08, 271.08);
		auto smoothParamPosition = Vec(103.08, 271.08);
		auto qualityParamPosition = Vec(179.02, 306.02);
		auto windowParamPosition = Vec(250.02, 306.02);

		auto signalaInputPosition = Vec(13.5, 323.0);
		auto signalbInputPosition = Vec(86.0, 323.0);
		auto signalcInputPosition = Vec(158.5, 323.0);
		auto signaldInputPosition = Vec(230.5, 323.0);

		auto signalaOutputPosition = Vec(44.5, 323.0);
		auto signalbOutputPosition = Vec(117.0, 323.0);
		auto signalcOutputPosition = Vec(189.5, 323.0);
		auto signaldOutputPosition = Vec(261.5, 323.0);

		auto qualityUltraLightPosition = Vec(170.0, 267.0);
		auto qualityHighLightPosition = Vec(170.0, 281.0);
		auto qualityGoodLightPosition = Vec(170.0, 295.0);
		auto windowNoneLightPosition = Vec(241.0, 267.0);
		auto windowHammingLightPosition = Vec(241.0, 281.0);
		auto windowKaiserLightPosition = Vec(241.0, 295.0);
		// end generated by svg_widgets.rb

		addParam(createParam<Knob38>(range2ParamPosition, module, Analyzer::RANGE2_PARAM, -1.0, 1.0, 0.0));
		addParam(createParam<Knob38>(smoothParamPosition, module, Analyzer::SMOOTH_PARAM, 0.0, 1.0, 0.5));
		addParam(createParam<StatefulButton9>(qualityParamPosition, module, Analyzer::QUALITY_PARAM, 1.0, 3.0, 1.0));
		addParam(createParam<StatefulButton9>(windowParamPosition, module, Analyzer::WINDOW_PARAM, 1.0, 3.0, 1.0));

		addInput(createInput<Port24>(signalaInputPosition, module, Analyzer::SIGNALA_INPUT));
		addInput(createInput<Port24>(signalbInputPosition, module, Analyzer::SIGNALB_INPUT));
		addInput(createInput<Port24>(signalcInputPosition, module, Analyzer::SIGNALC_INPUT));
		addInput(createInput<Port24>(signaldInputPosition, module, Analyzer::SIGNALD_INPUT));

		addOutput(createOutput<Port24>(signalaOutputPosition, module, Analyzer::SIGNALA_OUTPUT));
		addOutput(createOutput<Port24>(signalbOutputPosition, module, Analyzer::SIGNALB_OUTPUT));
		addOutput(createOutput<Port24>(signalcOutputPosition, module, Analyzer::SIGNALC_OUTPUT));
		addOutput(createOutput<Port24>(signaldOutputPosition, module, Analyzer::SIGNALD_OUTPUT));

		addChild(createLight<SmallLight<GreenLight>>(qualityUltraLightPosition, module, Analyzer::QUALITY_ULTRA_LIGHT));
		addChild(createLight<SmallLight<GreenLight>>(qualityHighLightPosition, module, Analyzer::QUALITY_HIGH_LIGHT));
		addChild(createLight<SmallLight<GreenLight>>(qualityGoodLightPosition, module, Analyzer::QUALITY_GOOD_LIGHT));
		addChild(createLight<SmallLight<GreenLight>>(windowNoneLightPosition, module, Analyzer::WINDOW_NONE_LIGHT));
		addChild(createLight<SmallLight<GreenLight>>(windowHammingLightPosition, module, Analyzer::WINDOW_HAMMING_LIGHT));
		addChild(createLight<SmallLight<GreenLight>>(windowKaiserLightPosition, module, Analyzer::WINDOW_KAISER_LIGHT));
	}

	void appendContextMenu(Menu* menu) override {
		Analyzer* a = dynamic_cast<Analyzer*>(module);
		assert(a);

		menu->addChild(new MenuLabel());
		menu->addChild(new RangeDbMenuItem(a, "Amplitude range: to -60dB", 80.0f));
		menu->addChild(new RangeDbMenuItem(a, "Amplitude range: to -120dB", 140.0f));
	}
};

Model* modelAnalyzer = createModel<Analyzer, AnalyzerWidget>("Bogaudio-Analyzer", "Analyzer",  "spectrum analyzer", VISUAL_TAG);