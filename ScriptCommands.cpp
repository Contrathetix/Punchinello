#include "ScriptCommands.hpp"

namespace Punchinello::ScriptCommands {

	// input = Filename:string, Key:string, DefaultReturn:string
	// output = the specified json string value, DefaultReturn if error
	static bool Cmd_Punchinello_JsonGetString_Execute(COMMAND_ARGS) {

		Console_Print("JsonGetString, running...");

		*result = 0;

		//Parameters
		char Filename[512];
		char Key[512];
		char DefaultReturn[512];

		if (!ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &DefaultReturn)) {
			return true;
		}

		Punchinello::Interfaces::kOBSEStringVar->Assign(PASS_COMMAND_ARGS, DefaultReturn);

		if (strlen(Filename) < 1 || strlen(Key) < 1) {

			Log_Print("JsonGetString, %s, %s, %s -> unable to read parameters");
			Console_Print("JsonGetString, %s, %s, %s -> unable to read parameters");

		} else {

			nlohmann::json Data;
			std::string Filepath(Filename);
			Filepath = Punchinello::Interfaces::kOblivionDirectory + Filepath;
			Log_Print("JsonGetString, filepath (%s)", Filepath);

			try {
				std::ifstream File(Filepath);
				File >> Data;
				File.close();
				std::string Value = Data[Key];
				Log_Print("JsonGetString, %s, %s, %s -> %s", Filename, Key, DefaultReturn, Value);
				Punchinello::Interfaces::kOBSEStringVar->Assign(PASS_COMMAND_ARGS, Value.c_str());
				free(&Value);
			} catch (const std::exception& e) {
				Log_Print("JsonGetString, error (%s)", e.what());
			} catch (...) {}

		}

		free(&Filename); free(&Key); free(&DefaultReturn);

		return true;
	}

	ParamInfo kParams_JsonGetString[3] = {
		{ "Filename", kParamType_String, 0 },
		{ "Key", kParamType_String, 0 },
		{ "DefaultReturn", kParamType_String, 0 }
	};

	CommandInfo kCommandInfo_JsonGetString = {
		"JsonGetString",
		"",
		0,
		"Fetch string value from JSON, returns DefaultReturn if unable to fetch value",
		0,
		3,
		kParams_JsonGetString,
		Cmd_Punchinello_JsonGetString_Execute
	};

	

}
