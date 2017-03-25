#include "ScriptCommands.hpp"

// some definitions
#define ARG_MAX_CHARS 512
#define MOD_NAME_LENGTH 0x100
#define REF_ID_LENGTH 0x20

// convenience definitions for ExtractArgsEx
#define ExtractArgsEx(...) Punchinello::Interfaces::kOBSEScript->ExtractArgsEx(__VA_ARGS__)
#define PASS_EXTRACT_ARGS_EX paramInfo, arg1, opcodeOffsetPtr, scriptObj, eventList

namespace Punchinello::FormConverter {

	// adapted from GetFormFromMod in Commands_Script.cpp from OBSE
	void StringToRefID(std::string StringValue, UInt32 *ReturnValue) {

		char ModName[MOD_NAME_LENGTH], RefIDString[REF_ID_LENGTH];
		size_t Separator = StringValue.find(':');
		TESForm *Form;
		UInt8 ModIndex = 0xFF;
		UInt32 RefID;

		if (Separator == std::string::npos) {
			Log_Print("StringToRefID, InvalidString (%s)", StringValue.c_str());
			return;
		}

		strcpy(RefIDString, StringValue.substr(0, Separator).c_str());
		strcpy(ModName, StringValue.substr(Separator + 1).c_str());

		if (_stricmp(ModName, "NONE") != 0) { // "NONE" for dynamic refs
			ModIndex = ModTable::Get().GetModIndex(ModName);
			if (ModIndex == 0xFF) {
				return; // mod is not loaded (255?)
			}
		}

		if (sscanf_s(RefIDString, "%x", &RefID) == 1) {
			RefID &= 0x00FFFFFF;
			RefID |= (ModIndex << 24);
			if ((Form = LookupFormByID(RefID)) != NULL) {
				*ReturnValue = (UInt32)RefID;
			}
		}

		return;
	}
	
	// adapted from GetFormIDString in Commands_Script.cpp from OBSE
	std::string FormToString(TESForm *Form) {

		char FormIDString[REF_ID_LENGTH] = { 0 };
		const char *ModName = NULL;
		std::string FormString("");

		if (Form) {
			ModName = (*g_dataHandler)->GetNthModName(Form->GetModIndex());
			sprintf_s(FormIDString, sizeof(FormIDString), "%08X", Form->refID);
			FormString = std::string(FormIDString) + ":" + std::string(ModName);
			free(&ModName);
		}

		return FormString;
	}

}

namespace Punchinello::ScriptCommands {

	static bool Cmd_Punchinello_JsonGetString_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS], DefaultReturn[ARG_MAX_CHARS];
		std::string TempStr;
		*result = 0;

		if (ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &DefaultReturn)) {
			TempStr = std::string(DefaultReturn);
			TempStr = Punchinello::JSON::GetValue(Filename, Key, TempStr);
			Punchinello::Interfaces::kOBSEStringVar->Assign(PASS_COMMAND_ARGS, TempStr.c_str());
		}

		return true;
	}

	static bool Cmd_Punchinello_JsonSetString_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS], Value[ARG_MAX_CHARS];
		std::string TempStr;
		*result = 0;

		if (ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &Value)) {
			TempStr = std::string(Value);
			Punchinello::JSON::SetValue(Filename, Key, TempStr);
		}

		return true;
	}

	static bool Cmd_Punchinello_JsonGetInt_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS];
		UInt32 DefaultReturn;

		if (ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &DefaultReturn)) {
			*result = Punchinello::JSON::GetValue(Filename, Key, DefaultReturn);
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
			Punchinello::JSON::SetValue(Filename, Key, Value);
		}

		return true;
	}

	static bool Cmd_Punchinello_JsonGetFloat_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS];
		float DefaultReturn;

		if (ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &DefaultReturn)) {
			*result = Punchinello::JSON::GetValue(Filename, Key, DefaultReturn);
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
			Punchinello::JSON::SetValue(Filename, Key, Value);
		}

		return true;
	}

	static bool Cmd_Punchinello_JsonGetForm_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS];
		std::string TempStr("");
		TESForm *DefaultReturn;
		UInt32 *RefResult = (UInt32 *)result;

		if (ExtractArgsEx(PASS_EXTRACT_ARGS_EX, &Filename, &Key, &DefaultReturn)) {
			*RefResult = DefaultReturn->refID;
			TempStr = Punchinello::JSON::GetValue(Filename, Key, TempStr);
			Punchinello::FormConverter::StringToRefID(TempStr, RefResult);
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
			StringValue = Punchinello::FormConverter::FormToString(Value);
			Punchinello::JSON::SetValue(Filename, Key, StringValue);
		}

		return true;
	}

	static bool Cmd_Punchinello_JsonEraseKey_Execute(COMMAND_ARGS) {

		char Filename[ARG_MAX_CHARS], Key[ARG_MAX_CHARS];
		*result = 0;

		if (ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key)) {
			Punchinello::JSON::EraseKey(Filename, Key);
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

}
