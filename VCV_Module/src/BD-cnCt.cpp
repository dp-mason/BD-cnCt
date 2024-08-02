#include "plugin.hpp"


struct BD_cnCt : Module {
	enum ParamId {
		KNOB_ZERO_PARAM,
		KNOB_ONE_PARAM,
		KNOB_TWO_PARAM,
		KNOB_THREE_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		INPUTS_LEN
	};
	enum OutputId {
		ZERO_OUTPUT,
		ONE_OUTPUT,
		TWO_OUTPUT,
		THREE_OUTPUT,
		FOUR_OUTPUT,
		FIVE_OUTPUT,
		SIX_OUTPUT,
		SEVEN_OUTPUT,
		EIGHT_OUTPUT,
		NINE_OUTPUT,
		TEN_OUTPUT,
		ELEVEN_OUTPUT,
		TWELVE_OUTPUT,
		THIRTEEN_OUTPUT,
		FOURTEEN_OUTPUT,
		FIFTEEN_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	BD_cnCt() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(KNOB_ZERO_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_ONE_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_TWO_PARAM, 0.f, 1.f, 0.f, "");
		configParam(KNOB_THREE_PARAM, 0.f, 1.f, 0.f, "");
		configOutput(ZERO_OUTPUT, "");
		configOutput(ONE_OUTPUT, "");
		configOutput(TWO_OUTPUT, "");
		configOutput(THREE_OUTPUT, "");
		configOutput(FOUR_OUTPUT, "");
		configOutput(FIVE_OUTPUT, "");
		configOutput(SIX_OUTPUT, "");
		configOutput(SEVEN_OUTPUT, "");
		configOutput(EIGHT_OUTPUT, "");
		configOutput(NINE_OUTPUT, "");
		configOutput(TEN_OUTPUT, "");
		configOutput(ELEVEN_OUTPUT, "");
		configOutput(TWELVE_OUTPUT, "");
		configOutput(THIRTEEN_OUTPUT, "");
		configOutput(FOURTEEN_OUTPUT, "");
		configOutput(FIFTEEN_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
		if (args.frame % 40000 == 0) {
			
			json_t* reqJ = json_object();
			// json_object_set_new(reqJ, "edition", json_string(APP_EDITION.c_str()));
			json_t* resJ = network::requestJson(network::METHOD_GET, "0.0.0.0:4554/chat-queue", reqJ);
			const char *key;
			json_t *value;
			DEBUG("PRINTING ALL JSON FIELDS BELOW");
			json_object_foreach(resJ, key, value) {
 				/* block of code that uses key and value */
				const char* val = json_dumps(value, JSON_ENCODE_ANY);
				DEBUG("%s", key);
				DEBUG("%s", val);
			}
			json_decref(reqJ);
			json_decref(resJ);
		}
	}
};


struct BD_cnCtWidget : ModuleWidget {
	BD_cnCtWidget(BD_cnCt* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/BD-cnCt.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 46.063)), module, BD_cnCt::KNOB_ZERO_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(24.388, 46.063)), module, BD_cnCt::KNOB_ONE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(33.535, 46.063)), module, BD_cnCt::KNOB_TWO_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(42.683, 46.063)), module, BD_cnCt::KNOB_THREE_PARAM));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 81.784)), module, BD_cnCt::ZERO_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24.388, 81.784)), module, BD_cnCt::ONE_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(33.535, 81.784)), module, BD_cnCt::TWO_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(42.683, 81.784)), module, BD_cnCt::THREE_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 90.76)), module, BD_cnCt::FOUR_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24.388, 90.76)), module, BD_cnCt::FIVE_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(33.535, 90.76)), module, BD_cnCt::SIX_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(42.683, 90.76)), module, BD_cnCt::SEVEN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 99.736)), module, BD_cnCt::EIGHT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24.388, 99.736)), module, BD_cnCt::NINE_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(33.535, 99.736)), module, BD_cnCt::TEN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(42.683, 99.736)), module, BD_cnCt::ELEVEN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 108.713)), module, BD_cnCt::TWELVE_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24.388, 108.713)), module, BD_cnCt::THIRTEEN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(33.535, 108.713)), module, BD_cnCt::FOURTEEN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(42.683, 108.713)), module, BD_cnCt::FIFTEEN_OUTPUT));
	}
};


Model* modelBD_cnCt = createModel<BD_cnCt, BD_cnCtWidget>("BD_cnCt");