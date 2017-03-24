// obse includes
#include "obse/PluginAPI.h"
#include "obse/ParamInfos.h"
#include "obse/GameAPI.h"

// project includes
#include "Logging.hpp"
#include "Interfaces.hpp"
#include "ScriptCommands.hpp"

extern "C" {

	bool OBSEPlugin_Query(const OBSEInterface *obse, PluginInfo *info) {

		Log_Print("OBSEPlugin, Query (start)");

		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "Punchinello";
		info->version = 1;

		if (obse->isEditor) {
			Log_Print("OBSEPlugin, Query (editor, skipping version checks)");
			return true;
		}

		if (obse->obseVersion < OBSE_VERSION_INTEGER) {
			Log_Print("OBSEPlugin, Query (OBSE version too old, got %08X, expected >= %08X)", obse->obseVersion, OBSE_VERSION_INTEGER);
			return false;
		}

		if (obse->oblivionVersion != OBLIVION_VERSION) {
			Log_Print("OBSEPlugin, Query (incorrect Oblivion version, got %08X, need %08X)", obse->oblivionVersion, OBLIVION_VERSION);
			return false;
		}

		if ((Punchinello::Interfaces::kOBSEScript = (OBSEScriptInterface*)obse->QueryInterface(kInterface_Script)) == NULL) {
			Log_Print("OBSEPlugin, Query (failed to acquire ScriptInterface)");
			return false; 
		}

		if ((Punchinello::Interfaces::kOBSEStringVar = (OBSEStringVarInterface *)obse->QueryInterface(kInterface_StringVar)) == NULL) {
			Log_Print("OBSEPlugin, Query (failed to acquire StringVarInterface)");
			return false;
		}

		if ((Punchinello::Interfaces::kOBSEArrayVar = (OBSEArrayVarInterface *)obse->QueryInterface(kInterface_ArrayVar)) == NULL) {
			Log_Print("OBSEPlugin, Query (failed to acquire ArrayVarInterface)");
			return false;
		}

		Log_Print("OBSEPlugin, Query (passed)");

		return true; // version checks passed

	}

	bool OBSEPlugin_Load(const OBSEInterface *obse) {

		Log_Print("OBSEPlugin, Load (start)");

		Punchinello::Interfaces::kPluginHandle = obse->GetPluginHandle();

		if (obse->isEditor == false) {
			Punchinello::Interfaces::kOblivionDirectory = obse->GetOblivionDirectory();
			Log_Print("OBSEPlugin, Load (obliviondir %s)", Punchinello::Interfaces::kOblivionDirectory);
		}

		obse->SetOpcodeBase(0x2000);

		obse->RegisterTypedCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonGetString, kRetnType_String);
		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonSetString);

		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonGetFloat);
		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonSetFloat);

		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonGetInt);
		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonSetInt);

		obse->RegisterTypedCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonGetForm, kRetnType_Form);
		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonSetForm);

		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonEraseKey);

		Log_Print("OBSEPlugin, Load (finished)");

		return true;
	}

};
