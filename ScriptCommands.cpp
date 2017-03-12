#pragma once
#include "ScriptCommands.hpp"

namespace Punchinello::Commands {

	void RegisterCommands(const ::OBSEInterface* obse) {

		obse->SetOpcodeBase(0x2000);
		obse->RegisterCommand(&kJsonGetStringCommand);

	}

	bool Cmd_JsonGetString_Execute(COMMAND_ARGS) {

		Console_Print("JsonGetString, running...");

		*result = 0;

		//Parameters
		char Filename[512];
		char Key[512];
		char DefaultReturn[512];

		if (!ExtractArgs(PASS_EXTRACT_ARGS, &Filename, &Key, &DefaultReturn)) {
			return true;
		}

		if (strlen(Filename) < 1 || strlen(Key) < 1) {
			Log_Print("JsonGetString(%s, %s, %s) --> unable to read parameters");
			Console_Print("JsonGetString(%s, %s, %s) --> unable to read parameters");
			Punchinello::Interface::GetStringInterface()->Assign(PASS_COMMAND_ARGS, DefaultReturn);
		} else {
			const char* Value = "Some Value From Json";
			Punchinello::Interface::GetStringInterface()->Assign(PASS_COMMAND_ARGS, Value);
		}

		return true;
	}

}
