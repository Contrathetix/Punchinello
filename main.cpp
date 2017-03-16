// obse includes
#include "obse/PluginAPI.h"
#include "obse/ParamInfos.h"
#include "obse/GameAPI.h"

// project includes
#include "Logging.hpp"
#include "Interfaces.hpp"
#include "ScriptCommands.hpp"

extern "C" {

	bool OBSEPlugin_Query(const OBSEInterface* obse, PluginInfo* info) {

		Log_Print("Query, running...");

		// fill out the info structure
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "Punchinello";
		info->version = 1;

		if (obse->isEditor) {
			Log_Print("Query, isEditor, skipping version checks");
			return true;
		}

		if (obse->obseVersion < OBSE_VERSION_INTEGER) {
			Log_Print("Query, OBSE version too old (got %08X expected at least %08X)", obse->obseVersion, OBSE_VERSION_INTEGER);
			return false;
		}

		if (obse->oblivionVersion != OBLIVION_VERSION) {
			Log_Print("Query, incorrect Oblivion version (got %08X need %08X)", obse->oblivionVersion, OBLIVION_VERSION);
			return false;
		}

		Punchinello::Interfaces::kOBSEStringVar = (OBSEStringVarInterface*)obse->QueryInterface(kInterface_StringVar);
		if (Punchinello::Interfaces::kOBSEStringVar == NULL) {
			Log_Print("Query, failed to acquire ScriptInterface");
			return false;
		}

		Log_Print("Query, version checks passed");

		return true; // version checks passed

	}

	bool OBSEPlugin_Load(const OBSEInterface* obse) {

		Log_Print("Load, running...");

		Punchinello::Interfaces::kPluginHandle = obse->GetPluginHandle();

		if (obse->isEditor == false) {
			Punchinello::Interfaces::kOblivionDirectory = obse->GetOblivionDirectory();
			Log_Print("Load, oblivion directory (%s)", Punchinello::Interfaces::kOblivionDirectory);
		}

		obse->SetOpcodeBase(0x2000);
		obse->RegisterTypedCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonGetString, kRetnType_String);
		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonSetString);
		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonGetFloat);
		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonSetFloat);
		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonGetInt);
		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonSetInt);

		Log_Print("Load, finished loading");

		return true;
	}

};
