
#include "VU.hpp"

void VU::onSampleRateChange() {
	_lRms.setSampleRate(engineGetSampleRate());
	_rRms.setSampleRate(engineGetSampleRate());
}

void VU::step() {
	float left = 0.0f;
	float right = 0.0f;
	if (inputs[L_INPUT].isConnected()) {
		left = inputs[L_INPUT].getVoltage();
	}
	if (inputs[R_INPUT].isConnected()) {
		right = inputs[R_INPUT].getVoltage();
	}
	else {
		right = left;
	}
	_lLevel = _lRms.next(left) / 5.0f;
	_rLevel = _rRms.next(right) / 5.0f;
	outputs[L_OUTPUT].setVoltage(left);
	outputs[R_OUTPUT].setVoltage(right);
}

struct VUDisplay : OpaqueWidget {
	struct Level {
		float db;
		NVGcolor color;
		Level(float db, const NVGcolor& color) : db(db), color(color) {}
	};

	const NVGcolor bgColor = nvgRGBA(0xaa, 0xaa, 0xaa, 0xff);
	VU* _module;
	std::vector<Level> _levels;

	VUDisplay(VU* module) : _module(module) {
		for (int i = 1; i <= 36; ++i) {
			float db = 12.0f - i*2.0f;
			_levels.push_back(Level(db, decibelsToColor(db)));
		}
	}

	void draw(NVGcontext* vg) override {
		float lDb = _module->_lLevel;
		if (lDb > 0.0f) {
			lDb = amplitudeToDecibels(lDb);
		}
		else {
			lDb = -100.0f;
		}
		float rDb = _module->_rLevel;
		if (rDb > 0.0f) {
			rDb = amplitudeToDecibels(rDb);
		}
		else {
			rDb = -100.0f;
		}

		nvgSave(vg);
		for (int i = 0; i < 180; i += 5) {
			const Level& l = _levels.at(i / 5);

			nvgBeginPath(vg);
			nvgRect(vg, 3, i + 1, 5, 4);
			nvgFillColor(vg, bgColor);
			nvgFill(vg);
			if (lDb > l.db) {
				nvgFillColor(vg, l.color);
				nvgFill(vg);
			}

			nvgBeginPath(vg);
			nvgRect(vg, 10, i + 1, 5, 4);
			nvgFillColor(vg, bgColor);
			nvgFill(vg);
			if (rDb > l.db) {
				nvgFillColor(vg, l.color);
				nvgFill(vg);
			}
		}
		nvgRestore(vg);
	}
};

struct VUWidget : ModuleWidget {
	static constexpr int hp = 3;

	VUWidget(VU* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

		{
			SVGPanel *panel = new SVGPanel();
			panel->box.size = box.size;
			panel->setBackground(SVG::load(asset::plugin(pluginInstance, "res/VU.svg")));
			addChild(panel);
		}

		{
			auto display = new VUDisplay(module);
			display->box.pos = Vec(13.5, 16.5);
			display->box.size = Vec(18, 180);
			addChild(display);
		}

		addChild(createWidget<ScrewSilver>(Vec(0, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 15, 365)));

		// generated by svg_widgets.rb
		auto lInputPosition = Vec(10.5, 203.0);
		auto rInputPosition = Vec(10.5, 238.0);

		auto lOutputPosition = Vec(10.5, 276.0);
		auto rOutputPosition = Vec(10.5, 311.0);
		// end generated by svg_widgets.rb

		addInput(createInput<Port24>(lInputPosition, module, VU::L_INPUT));
		addInput(createInput<Port24>(rInputPosition, module, VU::R_INPUT));

		addOutput(createOutput<Port24>(lOutputPosition, module, VU::L_OUTPUT));
		addOutput(createOutput<Port24>(rOutputPosition, module, VU::R_OUTPUT));
	}
};

Model* modelVU = createModel<VU, VUWidget>("Bogaudio-VU", "VU",  "stereo signal meter", VISUAL_TAG, DUAL_TAG);
