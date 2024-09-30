#include "plugin.hpp"


char *strip_quotes(const char *str) {
    size_t len = strlen(str);

    // Check for empty string
    if (len < 2) {
        return NULL; // Return NULL if the string is too short
    }

    // Check if the first and last characters are quotes
    if (str[0] == '"' && str[len - 1] == '"') {
        // Allocate memory for new string (length - 2 for the quotes + 1 for null terminator)
        char *result = (char *)malloc(len - 1);
        if (result) {
            strncpy(result, str + 1, len - 2); // Copy without quotes
            result[len - 2] = '\0'; // Null-terminate the new string
        }
        return result;
    }

    return NULL; // Return NULL if the string does not start and end with quotes
}


struct BD_cnCt : Module {
	enum ParamId {
		// Param Knobs
		KNOB_ZERO_PARAM,
		KNOB_ONE_PARAM,
		KNOB_TWO_PARAM,
		KNOB_THREE_PARAM,
		KNOB_FOUR_PARAM,
		KNOB_FIVE_PARAM,
		KNOB_SIX_PARAM,
		KNOB_SEVEN_PARAM,
		KNOB_EIGHT_PARAM,
		KNOB_NINE_PARAM,
		KNOB_TEN_PARAM,
		KNOB_ELEVEN_PARAM,
		KNOB_TWELVE_PARAM,
		KNOB_THIRTEEN_PARAM,
		KNOB_FOURTEEN_PARAM,
		KNOB_FIFTEEN_PARAM,
		// Offset Knobs
		OFFSET_KNOB_ZERO_PARAM,
		OFFSET_KNOB_ONE_PARAM,
		OFFSET_KNOB_TWO_PARAM,
		OFFSET_KNOB_THREE_PARAM,
		OFFSET_KNOB_FOUR_PARAM,
		OFFSET_KNOB_FIVE_PARAM,
		OFFSET_KNOB_SIX_PARAM,
		OFFSET_KNOB_SEVEN_PARAM,
		OFFSET_KNOB_EIGHT_PARAM,
		OFFSET_KNOB_NINE_PARAM,
		OFFSET_KNOB_TEN_PARAM,
		OFFSET_KNOB_ELEVEN_PARAM,
		OFFSET_KNOB_TWELVE_PARAM,
		OFFSET_KNOB_THIRTEEN_PARAM,
		OFFSET_KNOB_FOURTEEN_PARAM,
		OFFSET_KNOB_FIFTEEN_PARAM,
		// Mult Knobs
		MULT_KNOB_ZERO_PARAM,
		MULT_KNOB_ONE_PARAM,
		MULT_KNOB_TWO_PARAM,
		MULT_KNOB_THREE_PARAM,
		MULT_KNOB_FOUR_PARAM,
		MULT_KNOB_FIVE_PARAM,
		MULT_KNOB_SIX_PARAM,
		MULT_KNOB_SEVEN_PARAM,
		MULT_KNOB_EIGHT_PARAM,
		MULT_KNOB_NINE_PARAM,
		MULT_KNOB_TEN_PARAM,
		MULT_KNOB_ELEVEN_PARAM,
		MULT_KNOB_TWELVE_PARAM,
		MULT_KNOB_THIRTEEN_PARAM,
		MULT_KNOB_FOURTEEN_PARAM,
		MULT_KNOB_FIFTEEN_PARAM,
		// Local Port Knobs
		PORT_KNOB_ZERO_PARAM,
		PORT_KNOB_ONE_PARAM,
		PORT_KNOB_TWO_PARAM,
		PORT_KNOB_THREE_PARAM,
		// etc
		// TEST_ENABLE_BUTTON_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		CLOCK_INPUT,
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
		NEW_USER_OUTPUT,
		OUTPUTS_LEN
	};

	//std::vector<float> user_vals = std::vector<float>(16, 0.f);
	float clock_prev = 0.f;

	BD_cnCt() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN);
		// configSwitch(TEST_ENABLE_BUTTON_PARAM, 0.f, 1.f, 1.f, "");

		configParam(PORT_KNOB_ZERO_PARAM,  1.f, 9.f, 5.f, "");
		configParam(PORT_KNOB_ONE_PARAM,   0.f, 9.f, 3.f, "");
		configParam(PORT_KNOB_TWO_PARAM,   0.f, 9.f, 0.f, "");
		configParam(PORT_KNOB_THREE_PARAM, 0.f, 9.f, 9.f, "");

		configParam(KNOB_ZERO_PARAM,     0.f, 10.f, 0.f, "Param 0" );
		configParam(KNOB_ONE_PARAM,      0.f, 10.f, 0.f, "Param 1" );
		configParam(KNOB_TWO_PARAM,      0.f, 10.f, 0.f, "Param 2" );
		configParam(KNOB_THREE_PARAM,    0.f, 10.f, 0.f, "Param 3" );
		configParam(KNOB_FOUR_PARAM,     0.f, 10.f, 0.f, "Param 4" );
		configParam(KNOB_FIVE_PARAM,     0.f, 10.f, 0.f, "Param 5" );
		configParam(KNOB_SIX_PARAM,      0.f, 10.f, 0.f, "Param 6" );
		configParam(KNOB_SEVEN_PARAM,    0.f, 10.f, 0.f, "Param 7" );
		configParam(KNOB_EIGHT_PARAM,    0.f, 10.f, 0.f, "Param 8" );
		configParam(KNOB_NINE_PARAM,     0.f, 10.f, 0.f, "Param 9" );
		configParam(KNOB_TEN_PARAM,      0.f, 10.f, 0.f, "Param 10");
		configParam(KNOB_ELEVEN_PARAM,   0.f, 10.f, 0.f, "Param 11");
		configParam(KNOB_TWELVE_PARAM,   0.f, 10.f, 0.f, "Param 12");
		configParam(KNOB_THIRTEEN_PARAM, 0.f, 10.f, 0.f, "Param 13");
		configParam(KNOB_FOURTEEN_PARAM, 0.f, 10.f, 0.f, "Param 14");
		configParam(KNOB_FIFTEEN_PARAM,  0.f, 10.f, 0.f, "Param 15");

		configParam(OFFSET_KNOB_ZERO_PARAM,     -10.f, 10.f, 0.f, "Param Offset 0" );
		configParam(OFFSET_KNOB_ONE_PARAM,      -10.f, 10.f, 0.f, "Param Offset 1" );
		configParam(OFFSET_KNOB_TWO_PARAM,      -10.f, 10.f, 0.f, "Param Offset 2" );
		configParam(OFFSET_KNOB_THREE_PARAM,    -10.f, 10.f, 0.f, "Param Offset 3" );
		configParam(OFFSET_KNOB_FOUR_PARAM,     -10.f, 10.f, 0.f, "Param Offset 4" );
		configParam(OFFSET_KNOB_FIVE_PARAM,     -10.f, 10.f, 0.f, "Param Offset 5" );
		configParam(OFFSET_KNOB_SIX_PARAM,      -10.f, 10.f, 0.f, "Param Offset 6" );
		configParam(OFFSET_KNOB_SEVEN_PARAM,    -10.f, 10.f, 0.f, "Param Offset 7" );
		configParam(OFFSET_KNOB_EIGHT_PARAM,    -10.f, 10.f, 0.f, "Param Offset 8" );
		configParam(OFFSET_KNOB_NINE_PARAM,     -10.f, 10.f, 0.f, "Param Offset 9" );
		configParam(OFFSET_KNOB_TEN_PARAM,      -10.f, 10.f, 0.f, "Param Offset 10");
		configParam(OFFSET_KNOB_ELEVEN_PARAM,   -10.f, 10.f, 0.f, "Param Offset 11");
		configParam(OFFSET_KNOB_TWELVE_PARAM,   -10.f, 10.f, 0.f, "Param Offset 12");
		configParam(OFFSET_KNOB_THIRTEEN_PARAM, -10.f, 10.f, 0.f, "Param Offset 13");
		configParam(OFFSET_KNOB_FOURTEEN_PARAM, -10.f, 10.f, 0.f, "Param Offset 14");
		configParam(OFFSET_KNOB_FIFTEEN_PARAM,  -10.f, 10.f, 0.f, "Param Offset 15");

		configParam(MULT_KNOB_ZERO_PARAM,     -2.f, 2.f, 1.f, "Param Mult 0" );
		configParam(MULT_KNOB_ONE_PARAM,      -2.f, 2.f, 1.f, "Param Mult 1" );
		configParam(MULT_KNOB_TWO_PARAM,      -2.f, 2.f, 1.f, "Param Mult 2" );
		configParam(MULT_KNOB_THREE_PARAM,    -2.f, 2.f, 1.f, "Param Mult 3" );
		configParam(MULT_KNOB_FOUR_PARAM,     -2.f, 2.f, 1.f, "Param Mult 4" );
		configParam(MULT_KNOB_FIVE_PARAM,     -2.f, 2.f, 1.f, "Param Mult 5" );
		configParam(MULT_KNOB_SIX_PARAM,      -2.f, 2.f, 1.f, "Param Mult 6" );
		configParam(MULT_KNOB_SEVEN_PARAM,    -2.f, 2.f, 1.f, "Param Mult 7" );
		configParam(MULT_KNOB_EIGHT_PARAM,    -2.f, 2.f, 1.f, "Param Mult 8" );
		configParam(MULT_KNOB_NINE_PARAM,     -2.f, 2.f, 1.f, "Param Mult 9" );
		configParam(MULT_KNOB_TEN_PARAM,      -2.f, 2.f, 1.f, "Param Mult 10");
		configParam(MULT_KNOB_ELEVEN_PARAM,   -2.f, 2.f, 1.f, "Param Mult 11");
		configParam(MULT_KNOB_TWELVE_PARAM,   -2.f, 2.f, 1.f, "Param Mult 12");
		configParam(MULT_KNOB_THIRTEEN_PARAM, -2.f, 2.f, 1.f, "Param Mult 13");
		configParam(MULT_KNOB_FOURTEEN_PARAM, -2.f, 2.f, 1.f, "Param Mult 14");
		configParam(MULT_KNOB_FIFTEEN_PARAM,  -2.f, 2.f, 1.f, "Param Mult 15");

		configOutput(ZERO_OUTPUT,     "Output 0" );
		configOutput(ONE_OUTPUT,      "Output 1" );
		configOutput(TWO_OUTPUT,      "Output 2" );
		configOutput(THREE_OUTPUT,    "Output 3" );
		configOutput(FOUR_OUTPUT,     "Output 4" );
		configOutput(FIVE_OUTPUT,     "Output 5" );
		configOutput(SIX_OUTPUT,      "Output 6" );
		configOutput(SEVEN_OUTPUT,    "Output 7" );
		configOutput(EIGHT_OUTPUT,    "Output 8" );
		configOutput(NINE_OUTPUT,     "Output 9" );
		configOutput(TEN_OUTPUT,      "Output 10");
		configOutput(ELEVEN_OUTPUT,   "Output 11");
		configOutput(TWELVE_OUTPUT,   "Output 12");
		configOutput(THIRTEEN_OUTPUT, "Output 13");
		configOutput(FOURTEEN_OUTPUT, "Output 14");
		configOutput(FIFTEEN_OUTPUT,  "Output 15");

		configInput(CLOCK_INPUT, "");
	}

	void calc_output_with_offset_mult(){
		// apply offset and mult to each input before outputting value
		for (size_t i = 0; i < 16; i++)
		{
			// if (i == 0) {
			// 	DEBUG("params[%ld]: %f", i, params[i].getValue());
			// 	DEBUG("params[%ld]: %f", i, params[i+16].getValue());
			// 	DEBUG("params[%ld+16]: %f", i, params[i+32].getValue());
			// }
			outputs[i].setVoltage( 
				clamp( (params[i].getValue() + params[i+16].getValue()) * params[i+32].getValue(), -10.0, 10.0 )
			);
		}
	}

	void process(const ProcessArgs& args) override {
		
		// test mode will allow you to test how user values would effect your patch with the parameter
		// knobs on the right
		// bool test_enabled = params[TEST_ENABLE_BUTTON_PARAM].getValue() > 0.f;

		// if clock is connected, update when the clock triggers
		// if the clock is not connected, update once per 2 seconds
		if (
			// !test_enabled &&
			((inputs[CLOCK_INPUT].isConnected() && inputs[CLOCK_INPUT].getVoltage() > 0.1 && clock_prev < 0.1) || 
			 (!inputs[CLOCK_INPUT].isConnected() && args.frame % int64_t(args.sampleRate) * 2 == 0))
		) {
			std::string port  = std::to_string(
				int(params[PORT_KNOB_ZERO_PARAM].getValue() * 1000) +
				int(params[PORT_KNOB_ONE_PARAM].getValue() * 100)   +
				int(params[PORT_KNOB_TWO_PARAM].getValue() * 10)    +
				int(params[PORT_KNOB_THREE_PARAM].getValue())
			);
			json_t* reqJ = json_object();
			json_t* resJ = network::requestJson(network::METHOD_GET, "0.0.0.0:"+port+"/twitch-queue", reqJ);
			const char *key;
			json_t *value;
			json_object_foreach(resJ, key, value) {
				/* block of code that uses key and value */
				const char* val = json_dumps(value, JSON_ENCODE_ANY);
				DEBUG("%d", atoi(key));

				char *value = strip_quotes(val);
				DEBUG("--- key: %s - value: %s ---", key, value);
				DEBUG("string value %s turns into float value %f", value, atof(value));
				
				// user_vals[atoi(key)] = atof(value);
				params[atoi(key)].setValue(atof(value));
				
				free(value);
			}
			json_decref(reqJ);
			json_decref(resJ);
		}

		// this doesn't NEED to happen every frame
		if(args.frame % 256 == 0) {
			calc_output_with_offset_mult();
		}

		clock_prev =  inputs[CLOCK_INPUT].getVoltage();
	}
};


struct BD_cnCtWidget : ModuleWidget {
	BGPanel *pBackPanel;
	
	BD_cnCtWidget(BD_cnCt* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/BD_cnCt.svg")));

		// Adapted from https://github.com/netboy3/MSM-vcvrack-plugin/
		pBackPanel = new BGPanel();
		pBackPanel->box.size = box.size;
		pBackPanel->imagePath = asset::plugin(pluginInstance, "res/BD_cnCt.png");
		pBackPanel->visible = false;
		addChild(pBackPanel);
		pBackPanel->visible = true;

		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(12.952, 13.75)), module, BD_cnCt::PORT_KNOB_ZERO_PARAM));
		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(28.388, 13.75)), module, BD_cnCt::PORT_KNOB_ONE_PARAM));
		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(43.823, 13.75)), module, BD_cnCt::PORT_KNOB_TWO_PARAM));
		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(59.259, 13.75)), module, BD_cnCt::PORT_KNOB_THREE_PARAM));

		// addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(116.678, 31.609)), module, BD_cnCt::TEST_ENABLE_BUTTON_PARAM));
		// addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(116.678, 31.609)), module, BD_cnCt::TEST_ENABLE_BUTTON_PARAM, BD_cnCt::TEST_LIGHT));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(117.557, 48.676)),  module, BD_cnCt::KNOB_ZERO_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(134.017, 37.179)),  module, BD_cnCt::KNOB_ONE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(151.085, 47.866)),  module, BD_cnCt::KNOB_TWO_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(169.85, 39.743)),   module, BD_cnCt::KNOB_THREE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(116.773, 70.714)),  module, BD_cnCt::KNOB_FOUR_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(134.666, 59.524)),  module, BD_cnCt::KNOB_FIVE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(152.059, 70.794)),  module, BD_cnCt::KNOB_SIX_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(168.898, 60.414)),  module, BD_cnCt::KNOB_SEVEN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(115.469, 93.25)),   module, BD_cnCt::KNOB_EIGHT_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(135.586, 81.203)),  module, BD_cnCt::KNOB_NINE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(152.188, 92.688)),  module, BD_cnCt::KNOB_TEN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(170.014, 84.513)),  module, BD_cnCt::KNOB_ELEVEN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(114.808, 114.321)), module, BD_cnCt::KNOB_TWELVE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(133.81, 106.809)),  module, BD_cnCt::KNOB_THIRTEEN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(151.828, 116.827)), module, BD_cnCt::KNOB_FOURTEEN_PARAM));

		addParam(createParamCentered<Trimpot>(mm2px(Vec(19.893, 43.597)),  module, BD_cnCt::OFFSET_KNOB_ZERO_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(51.966, 45.073)),  module, BD_cnCt::OFFSET_KNOB_ONE_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(70.326, 44.227)),  module, BD_cnCt::OFFSET_KNOB_TWO_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(98.736, 46.118)),  module, BD_cnCt::OFFSET_KNOB_THREE_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(23.054, 66.001)),  module, BD_cnCt::OFFSET_KNOB_FOUR_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(53.052, 65.537)),  module, BD_cnCt::OFFSET_KNOB_FIVE_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(70.871, 64.454)),  module, BD_cnCt::OFFSET_KNOB_SIX_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(99.71, 64.624)),   module, BD_cnCt::OFFSET_KNOB_SEVEN_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(22.679, 87.711)),  module, BD_cnCt::OFFSET_KNOB_EIGHT_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(52.673, 87.183)),  module, BD_cnCt::OFFSET_KNOB_NINE_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(72.862, 86.482)),  module, BD_cnCt::OFFSET_KNOB_TEN_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(100.847, 85.736)), module, BD_cnCt::OFFSET_KNOB_ELEVEN_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(24.904, 107.186)), module, BD_cnCt::OFFSET_KNOB_TWELVE_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(54.208, 111.029)), module, BD_cnCt::OFFSET_KNOB_THIRTEEN_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(72.333, 108.939)), module, BD_cnCt::OFFSET_KNOB_FOURTEEN_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(98.52, 107.819)),  module, BD_cnCt::OFFSET_KNOB_FIFTEEN_PARAM));
		

		addParam(createParamCentered<Trimpot>(mm2px(Vec(27.505, 52.949)),  module, BD_cnCt::MULT_KNOB_ZERO_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(47.556, 53.128)),  module, BD_cnCt::MULT_KNOB_ONE_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(74.25, 52.922)),   module, BD_cnCt::MULT_KNOB_TWO_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(95.123, 53.87)),   module, BD_cnCt::MULT_KNOB_THREE_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(27.617, 73.177)), module, BD_cnCt::MULT_KNOB_FOUR_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(47.592, 72.928)),  module, BD_cnCt::MULT_KNOB_FIVE_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(77.059, 73.177)),  module, BD_cnCt::MULT_KNOB_SIX_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(96.783, 73.253)),  module, BD_cnCt::MULT_KNOB_SEVEN_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(28.448, 96.547)),  module, BD_cnCt::MULT_KNOB_EIGHT_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(47.317, 96.941)),  module, BD_cnCt::MULT_KNOB_NINE_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(76.945, 94.741)),  module, BD_cnCt::MULT_KNOB_TEN_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(95.004, 94.037)),  module, BD_cnCt::MULT_KNOB_ELEVEN_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(30.175, 116.024)), module, BD_cnCt::MULT_KNOB_TWELVE_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(50.981, 119.031)), module, BD_cnCt::MULT_KNOB_THIRTEEN_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(77.272, 115.789)), module, BD_cnCt::MULT_KNOB_FOURTEEN_PARAM));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(94.364, 114.865)), module, BD_cnCt::MULT_KNOB_FIFTEEN_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(81.99, 13.75)), module, BD_cnCt::CLOCK_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(13.156, 52.627)),  module, BD_cnCt::ZERO_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(40.37, 46.593)),   module, BD_cnCt::ONE_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(63.423, 52.07)),   module, BD_cnCt::TWO_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(88.497, 47.444)),  module, BD_cnCt::THREE_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.42, 73.605)),   module, BD_cnCt::FOUR_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(40.093, 67.379)),  module, BD_cnCt::FIVE_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(65.467, 72.1)),    module, BD_cnCt::SIX_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(90.196, 65.583)),  module, BD_cnCt::SEVEN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(16.336, 95.171)),  module, BD_cnCt::EIGHT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(41.508, 88.675)),  module, BD_cnCt::NINE_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(65.728, 94.304)),  module, BD_cnCt::TEN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(88.706, 86.256)),  module, BD_cnCt::ELEVEN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(18.469, 113.772)), module, BD_cnCt::TWELVE_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(44.476, 112.598)), module, BD_cnCt::THIRTEEN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(66.927, 116.257)), module, BD_cnCt::FOURTEEN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(88.623, 108.348)), module, BD_cnCt::FIFTEEN_OUTPUT));
		
		addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(171.411, 106.658)), module, BD_cnCt::NEW_USER_OUTPUT));
	}
};


Model* modelBD_cnCt = createModel<BD_cnCt, BD_cnCtWidget>("BD_cnCt");