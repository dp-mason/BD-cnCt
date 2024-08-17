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
		// Test Knobs
		TEST_KNOB_ZERO_PARAM,
		TEST_KNOB_ONE_PARAM,
		TEST_KNOB_TWO_PARAM,
		TEST_KNOB_THREE_PARAM,
		TEST_KNOB_FOUR_PARAM,
		TEST_KNOB_FIVE_PARAM,
		TEST_KNOB_SIX_PARAM,
		TEST_KNOB_SEVEN_PARAM,
		TEST_KNOB_EIGHT_PARAM,
		TEST_KNOB_NINE_PARAM,
		TEST_KNOB_TEN_PARAM,
		TEST_KNOB_ELEVEN_PARAM,
		TEST_KNOB_TWELVE_PARAM,
		TEST_KNOB_THIRTEEN_PARAM,
		TEST_KNOB_FOURTEEN_PARAM,
		TEST_KNOB_FIFTEEN_PARAM,
		// Local Port Knobs
		PORT_KNOB_ZERO_PARAM,
		PORT_KNOB_ONE_PARAM,
		PORT_KNOB_TWO_PARAM,
		PORT_KNOB_THREE_PARAM,
		// etc
		TEST_ENABLE_BUTTON_PARAM,
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
	enum LightId {
		TEST_LIGHT,
		LIGHTS_LEN
	};

	std::vector<float> user_vals = std::vector<float>(16, 0.f);
	float clock_prev = 0.f;

	BD_cnCt() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configSwitch(TEST_ENABLE_BUTTON_PARAM, 0.f, 1.f, 1.f, "");

		configParam(PORT_KNOB_ZERO_PARAM,  1.f, 9.f, 5.f, "");
		configParam(PORT_KNOB_ONE_PARAM,   0.f, 9.f, 3.f, "");
		configParam(PORT_KNOB_TWO_PARAM,   0.f, 9.f, 0.f, "");
		configParam(PORT_KNOB_THREE_PARAM, 0.f, 9.f, 9.f, "");

		configParam(TEST_KNOB_ZERO_PARAM,     0.f, 10.f, 0.f, "Test 0" );
		configParam(TEST_KNOB_ONE_PARAM,      0.f, 10.f, 0.f, "Test 1" );
		configParam(TEST_KNOB_TWO_PARAM,      0.f, 10.f, 0.f, "Test 2" );
		configParam(TEST_KNOB_THREE_PARAM,    0.f, 10.f, 0.f, "Test 3" );
		configParam(TEST_KNOB_FOUR_PARAM,     0.f, 10.f, 0.f, "Test 4" );
		configParam(TEST_KNOB_FIVE_PARAM,     0.f, 10.f, 0.f, "Test 5" );
		configParam(TEST_KNOB_SIX_PARAM,      0.f, 10.f, 0.f, "Test 6" );
		configParam(TEST_KNOB_SEVEN_PARAM,    0.f, 10.f, 0.f, "Test 7" );
		configParam(TEST_KNOB_EIGHT_PARAM,    0.f, 10.f, 0.f, "Test 8" );
		configParam(TEST_KNOB_NINE_PARAM,     0.f, 10.f, 0.f, "Test 9" );
		configParam(TEST_KNOB_TEN_PARAM,      0.f, 10.f, 0.f, "Test 10");
		configParam(TEST_KNOB_ELEVEN_PARAM,   0.f, 10.f, 0.f, "Test 11");
		configParam(TEST_KNOB_TWELVE_PARAM,   0.f, 10.f, 0.f, "Test 12");
		configParam(TEST_KNOB_THIRTEEN_PARAM, 0.f, 10.f, 0.f, "Test 13");
		configParam(TEST_KNOB_FOURTEEN_PARAM, 0.f, 10.f, 0.f, "Test 14");
		configParam(TEST_KNOB_FIFTEEN_PARAM,  0.f, 10.f, 0.f, "Test 15");

		configParam(OFFSET_KNOB_ZERO_PARAM,     -10.f, 10.f, 0.f, "Offset 0" );
		configParam(OFFSET_KNOB_ONE_PARAM,      -10.f, 10.f, 0.f, "Offset 1" );
		configParam(OFFSET_KNOB_TWO_PARAM,      -10.f, 10.f, 0.f, "Offset 2" );
		configParam(OFFSET_KNOB_THREE_PARAM,    -10.f, 10.f, 0.f, "Offset 3" );
		configParam(OFFSET_KNOB_FOUR_PARAM,     -10.f, 10.f, 0.f, "Offset 4" );
		configParam(OFFSET_KNOB_FIVE_PARAM,     -10.f, 10.f, 0.f, "Offset 5" );
		configParam(OFFSET_KNOB_SIX_PARAM,      -10.f, 10.f, 0.f, "Offset 6" );
		configParam(OFFSET_KNOB_SEVEN_PARAM,    -10.f, 10.f, 0.f, "Offset 7" );
		configParam(OFFSET_KNOB_EIGHT_PARAM,    -10.f, 10.f, 0.f, "Offset 8" );
		configParam(OFFSET_KNOB_NINE_PARAM,     -10.f, 10.f, 0.f, "Offset 9" );
		configParam(OFFSET_KNOB_TEN_PARAM,      -10.f, 10.f, 0.f, "Offset 10");
		configParam(OFFSET_KNOB_ELEVEN_PARAM,   -10.f, 10.f, 0.f, "Offset 11");
		configParam(OFFSET_KNOB_TWELVE_PARAM,   -10.f, 10.f, 0.f, "Offset 12");
		configParam(OFFSET_KNOB_THIRTEEN_PARAM, -10.f, 10.f, 0.f, "Offset 13");
		configParam(OFFSET_KNOB_FOURTEEN_PARAM, -10.f, 10.f, 0.f, "Offset 14");
		configParam(OFFSET_KNOB_FIFTEEN_PARAM,  -10.f, 10.f, 0.f, "Offset 15");

		configParam(MULT_KNOB_ZERO_PARAM,     -2.f, 2.f, 1.f, "Mult 0" );
		configParam(MULT_KNOB_ONE_PARAM,      -2.f, 2.f, 1.f, "Mult 1" );
		configParam(MULT_KNOB_TWO_PARAM,      -2.f, 2.f, 1.f, "Mult 2" );
		configParam(MULT_KNOB_THREE_PARAM,    -2.f, 2.f, 1.f, "Mult 3" );
		configParam(MULT_KNOB_FOUR_PARAM,     -2.f, 2.f, 1.f, "Mult 4" );
		configParam(MULT_KNOB_FIVE_PARAM,     -2.f, 2.f, 1.f, "Mult 5" );
		configParam(MULT_KNOB_SIX_PARAM,      -2.f, 2.f, 1.f, "Mult 6" );
		configParam(MULT_KNOB_SEVEN_PARAM,    -2.f, 2.f, 1.f, "Mult 7" );
		configParam(MULT_KNOB_EIGHT_PARAM,    -2.f, 2.f, 1.f, "Mult 8" );
		configParam(MULT_KNOB_NINE_PARAM,     -2.f, 2.f, 1.f, "Mult 9" );
		configParam(MULT_KNOB_TEN_PARAM,      -2.f, 2.f, 1.f, "Mult 10");
		configParam(MULT_KNOB_ELEVEN_PARAM,   -2.f, 2.f, 1.f, "Mult 11");
		configParam(MULT_KNOB_TWELVE_PARAM,   -2.f, 2.f, 1.f, "Mult 12");
		configParam(MULT_KNOB_THIRTEEN_PARAM, -2.f, 2.f, 1.f, "Mult 13");
		configParam(MULT_KNOB_FOURTEEN_PARAM, -2.f, 2.f, 1.f, "Mult 14");
		configParam(MULT_KNOB_FIFTEEN_PARAM,  -2.f, 2.f, 1.f, "Mult 15");

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

	void process(const ProcessArgs& args) override {
		
		bool test_enabled = params[TEST_ENABLE_BUTTON_PARAM].getValue() > 0.f;

		if (
			!test_enabled &&
			((inputs[CLOCK_INPUT].isConnected() && inputs[CLOCK_INPUT].getVoltage() > 0.1 && clock_prev < 0.1) || 
			 (!inputs[CLOCK_INPUT].isConnected() && args.frame % int64_t(args.sampleRate) == 0))
		) {
			json_t* reqJ = json_object();
			// json_object_set_new(reqJ, "edition", json_string(APP_EDITION.c_str()));
			std::string port  = std::to_string(
				int(params[PORT_KNOB_ZERO_PARAM].getValue() * 1000) +
				int(params[PORT_KNOB_ONE_PARAM].getValue() * 100)   +
				int(params[PORT_KNOB_TWO_PARAM].getValue() * 10)    +
				int(params[PORT_KNOB_THREE_PARAM].getValue())
			);
			DEBUG("PORT: %s", port.c_str());
			json_t* resJ = network::requestJson(network::METHOD_GET, "0.0.0.0:"+port+"/chat-queue", reqJ);
			const char *key;
			json_t *value;
			DEBUG("PRINTING ALL JSON FIELDS BELOW");
			json_object_foreach(resJ, key, value) {
				/* block of code that uses key and value */
				const char* val = json_dumps(value, JSON_ENCODE_ANY);
				DEBUG("%d", atoi(key));

				char *value = strip_quotes(val);
				DEBUG("value %s turns into %f", value, atof(value));
				
				user_vals[atoi(key)] = atof(value);
				// outputs[atoi(key)].setVoltage(atof(value));
				
				free(value);
			}
			json_decref(reqJ);
			json_decref(resJ);
		}
		else {
			// set the user values as the values of the test knobs
			for (size_t i = 0; i < user_vals.size(); i++)
			{
				user_vals[i] = params[(16*2) + i].getValue();
			}
		}

		// apply offset and mult to each input before outputting value
		for (size_t i = 0; i < user_vals.size(); i++)
		{
			outputs[i].setVoltage( 
				clamp( (user_vals[i] + params[i].getValue()) * params[i+16].getValue(), -10.0, 10.0 )
			);
		}
		if (args.frame % 200000 == 0) {
			DEBUG("USER_VALS, test mode:%f", params[TEST_ENABLE_BUTTON_PARAM].getValue());
			for (size_t i = 0; i < user_vals.size(); i++)
			{
				DEBUG("%f", user_vals[i]);
			} 
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
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(116.678, 31.609)), module, BD_cnCt::TEST_ENABLE_BUTTON_PARAM, BD_cnCt::TEST_LIGHT));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(117.557, 48.676)),  module, BD_cnCt::TEST_KNOB_ZERO_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(134.017, 37.179)),  module, BD_cnCt::TEST_KNOB_ONE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(151.085, 47.866)),  module, BD_cnCt::TEST_KNOB_TWO_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(169.85, 39.743)),   module, BD_cnCt::TEST_KNOB_THREE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(116.773, 70.714)),  module, BD_cnCt::TEST_KNOB_FOUR_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(134.666, 59.524)),  module, BD_cnCt::TEST_KNOB_FIVE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(152.059, 70.794)),  module, BD_cnCt::TEST_KNOB_SIX_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(168.898, 60.414)),  module, BD_cnCt::TEST_KNOB_SEVEN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(115.469, 93.25)),   module, BD_cnCt::TEST_KNOB_EIGHT_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(135.586, 81.203)),  module, BD_cnCt::TEST_KNOB_NINE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(152.188, 92.688)),  module, BD_cnCt::TEST_KNOB_TEN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(170.014, 84.513)),  module, BD_cnCt::TEST_KNOB_ELEVEN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(114.808, 114.321)), module, BD_cnCt::TEST_KNOB_TWELVE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(133.81, 106.809)),  module, BD_cnCt::TEST_KNOB_THIRTEEN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(151.828, 116.827)), module, BD_cnCt::TEST_KNOB_FOURTEEN_PARAM));

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
		addParam(createParamCentered<Trimpot>(mm2px(Vec(27.617, 242.641)), module, BD_cnCt::MULT_KNOB_FOUR_PARAM));
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