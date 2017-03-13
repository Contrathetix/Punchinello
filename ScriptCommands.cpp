#include "ScriptCommands.hpp"

namespace Punchinello::ScriptCommands {

	static bool Cmd_Punchinello_JsonGetString_Execute(COMMAND_ARGS) {

		*result = 0;
		char Filename[512], Key[512], DefaultReturn[512];

		if (!ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &DefaultReturn)) {
			return true;
		}

		std::string TempStr(DefaultReturn);
		TempStr = Punchinello::JSON::GetValue(Filename, Key, TempStr);
		Punchinello::Interfaces::kOBSEStringVar->Assign(PASS_COMMAND_ARGS, TempStr.c_str());
		free(&TempStr);

		return true;
	}

	static bool Cmd_Punchinello_JsonGetInt_Execute(COMMAND_ARGS) {

		*result = 0;
		char Filename[512], Key[512];
		UInt32 DefaultReturn;

		if (!ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &DefaultReturn)) {
			return true;
		}

		*result = Punchinello::JSON::GetValue(Filename, Key, DefaultReturn);

		return true;
	}

	static bool Cmd_Punchinello_JsonGetFloat_Execute(COMMAND_ARGS) {

		*result = 0;
		char Filename[512], Key[512];
		float DefaultReturn;

		if (!ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &DefaultReturn)) {
			return true;
		}

		*result = Punchinello::JSON::GetValue(Filename, Key, DefaultReturn);

		return true;
	}

	ParamInfo kParams_JsonGetString[3] = {
		{ "Filename", kParamType_String, 0 },
		{ "Key", kParamType_String, 0 },
		{ "Defaultreturn", kParamType_String, 0 }
	};

	ParamInfo kParams_JsonGetInt[3] = {
		{ "Filename", kParamType_String, 0 },
		{ "Key", kParamType_String, 0 },
		{ "Defaultreturn", kParamType_Integer, 0 }
	};

	ParamInfo kParams_JsonGetFloat[3] = {
		{ "Filename", kParamType_String, 0 },
		{ "Key", kParamType_String, 0 },
		{ "Defaultreturn", kParamType_Float, 0 }
	};

	CommandInfo kCommandInfo_JsonGetString = {
		"JsonGetString",
		"",
		0,
		"Fetch string value from JSON, returns Defaultreturn if unable to fetch value",
		0,
		3,
		kParams_JsonGetString,
		Cmd_Punchinello_JsonGetString_Execute
	};

	CommandInfo kCommandInfo_JsonGetInt = {
		"JsonGetInt",
		"",
		0,
		"Fetch int value from JSON, returns Defaultreturn if unable to fetch value",
		0,
		3,
		kParams_JsonGetInt,
		Cmd_Punchinello_JsonGetInt_Execute
	};

	CommandInfo kCommandInfo_JsonGetFloat = {
		"JsonGetFloat",
		"",
		0,
		"Fetch float value from JSON, returns Defaultreturn if unable to fetch value",
		0,
		3,
		kParams_JsonGetFloat,
		Cmd_Punchinello_JsonGetFloat_Execute
	};

}
