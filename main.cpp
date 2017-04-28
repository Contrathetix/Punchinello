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

		Log_Print("OBSEPlugin::Query, Start");

		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "Punchinello";
		info->version = 2;

		if (obse->isEditor) {
			Log_Print("OBSEPlugin::Query, Editor >> skip other checks)");
			return true;
		}

		if (obse->obseVersion < OBSE_VERSION_INTEGER) {
			Log_Print("OBSEPlugin::Query, OBSE version too old, got %08X, expected >= %08X", obse->obseVersion, OBSE_VERSION_INTEGER);
			return false;
		}

		if (obse->oblivionVersion != OBLIVION_VERSION) {
			Log_Print("OBSEPlugin::Query, Incorrect Oblivion version, got %08X, need %08X", obse->oblivionVersion, OBLIVION_VERSION);
			return false;
		}

		if ((Punchinello::Interfaces::kOBSEScript = (OBSEScriptInterface*)obse->QueryInterface(kInterface_Script)) == NULL) {
			Log_Print("OBSEPlugin::Query, Failed to acquire ScriptInterface");
			return false; 
		}

		if ((Punchinello::Interfaces::kOBSEStringVar = (OBSEStringVarInterface *)obse->QueryInterface(kInterface_StringVar)) == NULL) {
			Log_Print("OBSEPlugin::Query, Failed to acquire StringVarInterface");
			return false;
		}

		if ((Punchinello::Interfaces::kOBSEArrayVar = (OBSEArrayVarInterface *)obse->QueryInterface(kInterface_ArrayVar)) == NULL) {
			Log_Print("OBSEPlugin::Query, Failed to acquire ArrayVarInterface");
			return false;
		}

		Log_Print("OBSEPlugin::Query, Passed");

		return true; // version checks passed

	}

	bool OBSEPlugin_Load(const OBSEInterface *obse) {

		Log_Print("OBSEPlugin::Load, Start");

		Punchinello::Interfaces::kPluginHandle = obse->GetPluginHandle();

		if (!obse->isEditor) {
			Punchinello::Interfaces::kOblivionDirectory = std::string(obse->GetOblivionDirectory());
			Log_Print("OBSEPlugin::Load, OblivionDir (%s)", Punchinello::Interfaces::kOblivionDirectory.c_str());
		}

		obse->SetOpcodeBase(0x2890); // the plugin was assigned 0x2890 - 289F

		obse->RegisterTypedCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonGetString, kRetnType_String);
		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonSetString);

		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonGetFloat);
		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonSetFloat);

		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonGetInt);
		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonSetInt);

		obse->RegisterTypedCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonGetForm, kRetnType_Form);
		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonSetForm);

		obse->RegisterCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonEraseKey);
		obse->RegisterTypedCommand(&Punchinello::ScriptCommands::kCommandInfo_JsonListKeys, kRetnType_Array);

		Log_Print("OBSEPlugin::Load, Finished");

		return true;
	}

};
