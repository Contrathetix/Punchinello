#include "ScriptCommands.hpp"

// some definitions
#define ARG_MAX_CHARS 512

// convenience definitions for ExtractArgsEx
#define ExtractArgsEx(...) Punchinello::Interfaces::kOBSEScript->ExtractArgsEx(__VA_ARGS__)
#define PASS_EXTRACT_ARGS_EX paramInfo, arg1, opcodeOffsetPtr, scriptObj, eventList

namespace Punchinello::ScriptCommands {

	static bool Cmd_Punchinello_JsonGetString_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS], DefaultReturn[ARG_MAX_CHARS];
		*result = 0;

		if (ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &DefaultReturn)) {
			std::string TempStr(DefaultReturn);
			Punchinello::JsonManager::JsonObject JObject(Filename);
			JObject.Get(Key, TempStr);
			Punchinello::Interfaces::kOBSEStringVar->Assign(PASS_COMMAND_ARGS, TempStr.c_str());
		}

		return true;
	}

	static bool Cmd_Punchinello_JsonSetString_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS], Value[ARG_MAX_CHARS];
		*result = 0;

		if (ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &Value)) {
			Punchinello::JsonManager::JsonObject JObject(Filename);
			JObject.Set(Key, std::string(Value));
			JObject.WriteToDisk();
		}

		return true;
	}

	static bool Cmd_Punchinello_JsonGetInt_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS];
		UInt32 DefaultReturn;

		if (ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &DefaultReturn)) {
			Punchinello::JsonManager::JsonObject JObject(Filename);
			JObject.Get(Key, DefaultReturn);
			*result = DefaultReturn;
		} else {
			*result = 0;
		}

		return true;
	}

	static bool Cmd_Punchinello_JsonSetInt_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS];
		UInt32 Value;
		*result = 0;

		if (ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &Value)) {
			Punchinello::JsonManager::JsonObject JObject(Filename);
			JObject.Set(Key, Value);
			JObject.WriteToDisk();
		}

		return true;
	}

	static bool Cmd_Punchinello_JsonGetFloat_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS];
		float DefaultReturn;

		if (ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &DefaultReturn)) {
			Punchinello::JsonManager::JsonObject JObject(Filename);
			JObject.Get(Key, DefaultReturn);
			*result = DefaultReturn;
		} else {
			*result = 0;
		}

		return true;
	}

	static bool Cmd_Punchinello_JsonSetFloat_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS];
		float Value;
		*result = 0;

		if (ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &Value)) {
			Punchinello::JsonManager::JsonObject JObject(Filename);
			JObject.Set(Key, Value);
			JObject.WriteToDisk();
		}

		return true;
	}

	static bool Cmd_Punchinello_JsonGetForm_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS];
		TESForm *DefaultReturn;
		UInt32 *RefResult = (UInt32 *)result;
		std::string TempStr("");

		if (ExtractArgsEx(PASS_EXTRACT_ARGS_EX, &Filename, &Key, &DefaultReturn)) {
			*RefResult = DefaultReturn->refID;
			Punchinello::JsonManager::JsonObject JObject(Filename);
			JObject.Get(Key, TempStr);
			Punchinello::FormManager::StringToRefID(TempStr, RefResult);
		} else {
			*RefResult = 0;
		}

		return true;
	}

	static bool Cmd_Punchinello_JsonSetForm_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS];
		std::string StringValue;
		TESForm *Value;
		*result = 0;

		if (ExtractArgsEx(PASS_EXTRACT_ARGS_EX, &Filename, &Key, &Value)) {
			Punchinello::JsonManager::JsonObject JObject(Filename);
			JObject.Set(Key, Punchinello::FormManager::FormToString(Value));
			JObject.WriteToDisk();
		}

		return true;
	}

	static bool Cmd_Punchinello_JsonEraseKey_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS];
		*result = 0;

		if (ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key)) {
			Punchinello::JsonManager::JsonObject JObject(Filename);
			JObject.Erase(Key);
			JObject.WriteToDisk();
		}

		return true;
	}

	static bool Cmd_Punchinello_JsonListKeys_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS];
		*result = 0;

		if (ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key)) {
			Punchinello::JsonManager::JsonObject JObject(Filename);
			std::vector<std::string> KeyList;
			JObject.ListKeys(Key, KeyList);
			OBSEArray* OBSEArr = Punchinello::Interfaces::ArrayFromStdVector(KeyList, scriptObj);
			Punchinello::Interfaces::kOBSEArrayVar->AssignCommandResult(OBSEArr, result);
		}

		return true;
	}

	ParamInfo kParams_JsonGetString[3] = {
		{ "Filename", kParamType_String, 0 },
		{ "Key", kParamType_String, 0 },
		{ "Defaultreturn", kParamType_String, 0 }
	};

	ParamInfo kParams_JsonSetString[3] = {
		{ "Filename", kParamType_String, 0 },
		{ "Key", kParamType_String, 0 },
		{ "Value", kParamType_String, 0 }
	};

	ParamInfo kParams_JsonGetInt[3] = {
		{ "Filename", kParamType_String, 0 },
		{ "Key", kParamType_String, 0 },
		{ "Defaultreturn", kParamType_Integer, 0 }
	};

	ParamInfo kParams_JsonSetInt[3] = {
		{ "Filename", kParamType_String, 0 },
		{ "Key", kParamType_String, 0 },
		{ "Value", kParamType_Integer, 0 }
	};

	ParamInfo kParams_JsonGetFloat[3] = {
		{ "Filename", kParamType_String, 0 },
		{ "Key", kParamType_String, 0 },
		{ "Defaultreturn", kParamType_Float, 0 }
	};

	ParamInfo kParams_JsonSetFloat[3] = {
		{ "Filename", kParamType_String, 0 },
		{ "Key", kParamType_String, 0 },
		{ "Value", kParamType_Float, 0 }
	};

	ParamInfo kParams_JsonGetForm[3] = {
		{ "Filename", kParamType_String, 0 },
		{ "Key", kParamType_String, 0 },
		{ "Defaultreturn", kOBSEParamType_Form, 0 }
	};

	ParamInfo kParams_JsonSetForm[3] = {
		{ "Filename", kParamType_String, 0 },
		{ "Key", kParamType_String, 0 },
		{ "Value", kOBSEParamType_Form, 0 }
	};

	ParamInfo kParams_JsonEraseKey[2] = {
		{ "Filename", kParamType_String, 0 },
		{ "Key", kParamType_String, 0 }
	};

	ParamInfo kParams_JsonListKeys[2] = {
		{ "Filename", kParamType_String, 0 },
		{ "KeyPath", kParamType_String, 0 }
	};

	CommandInfo kCommandInfo_JsonGetString = {
		"JsonGetString",
		"",
		0,
		"Read string value from JSON",
		0,
		3,
		kParams_JsonGetString,
		Cmd_Punchinello_JsonGetString_Execute
	};

	CommandInfo kCommandInfo_JsonSetString = {
		"JsonSetString",
		"",
		0,
		"Write string value to JSON",
		0,
		3,
		kParams_JsonSetString,
		Cmd_Punchinello_JsonSetString_Execute
	};

	CommandInfo kCommandInfo_JsonGetInt = {
		"JsonGetInt",
		"",
		0,
		"Read integer value from JSON",
		0,
		3,
		kParams_JsonGetInt,
		Cmd_Punchinello_JsonGetInt_Execute
	};

	CommandInfo kCommandInfo_JsonSetInt = {
		"JsonSetInt",
		"",
		0,
		"Write integer value to JSON",
		0,
		3,
		kParams_JsonSetInt,
		Cmd_Punchinello_JsonSetInt_Execute
	};

	CommandInfo kCommandInfo_JsonGetFloat = {
		"JsonGetFloat",
		"",
		0,
		"Read floating point value from JSON",
		0,
		3,
		kParams_JsonGetFloat,
		Cmd_Punchinello_JsonGetFloat_Execute
	};

	CommandInfo kCommandInfo_JsonSetFloat = {
		"JsonSetFloat",
		"",
		0,
		"Write floating point value to JSON",
		0,
		3,
		kParams_JsonSetFloat,
		Cmd_Punchinello_JsonSetFloat_Execute
	};

	CommandInfo kCommandInfo_JsonGetForm = {
		"JsonGetForm",
		"",
		0,
		"Read form value from JSON",
		0,
		3,
		kParams_JsonGetForm,
		Cmd_Punchinello_JsonGetForm_Execute
	};

	CommandInfo kCommandInfo_JsonSetForm = {
		"JsonSetForm",
		"",
		0,
		"Write form value to JSON",
		0,
		3,
		kParams_JsonSetForm,
		Cmd_Punchinello_JsonSetForm_Execute
	};

	CommandInfo kCommandInfo_JsonEraseKey = {
		"JsonEraseKey",
		"",
		0,
		"Erase key and value from JSON",
		0,
		2,
		kParams_JsonEraseKey,
		Cmd_Punchinello_JsonEraseKey_Execute
	};

	CommandInfo kCommandInfo_JsonListKeys = {
		"JsonListKeys",
		"",
		0,
		"List all keys in a key path in JSON",
		0,
		2,
		kParams_JsonListKeys,
		Cmd_Punchinello_JsonListKeys_Execute
	};

}
