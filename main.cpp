// obse includes
#include "obse/PluginAPI.h"
#include "obse/GameAPI.h"
#include "obse/ParamInfos.h"

// project includes
#include "Logging.hpp"
#include "Interface.hpp"
#include "ScriptCommands.hpp"

extern "C" {

	bool OBSEPlugin_Query(const OBSEInterface* obse, PluginInfo* info) {

		Log_Print("OBSEPlugin_Query >> running...");

		// fill out the info structure
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "Punchinello";
		info->version = 1;

		if (obse->isEditor) {
			return true;
		}

		if (obse->obseVersion < OBSE_VERSION_INTEGER) {
			_ERROR("OBSEPlugin_Query >> OBSE version too old (got %08X expected at least %08X)", obse->obseVersion, OBSE_VERSION_INTEGER);
			return false;
		}

		#if OBLIVION
		if (obse->oblivionVersion != OBLIVION_VERSION) {
			_ERROR("OBSEPlugin_Query >> incorrect Oblivion version (got %08X need %08X)", obse->oblivionVersion, OBLIVION_VERSION);
			return false;
		}
		#endif

		/*
		if (!JDeposit::OBSEInterface::SetScriptInterface((OBSEScriptInterface*)obse->QueryInterface(kInterface_Script))) {
			_ERROR("OBSEPlugin_Query >> failed to acquire ScriptInterface");
		}
		*/

		if (!Punchinello::Interface::SetStringInterface((OBSEStringVarInterface*)obse->QueryInterface(kInterface_StringVar))) {
			_ERROR("OBSEPlugin_Query >> failed to acquire ScriptInterface");
			return false;
		}

		Log_Print("OBSEPlugin_Query >> version checks passed");

		return true; // version checks passed

	}

	bool OBSEPlugin_Load(const OBSEInterface* obse) {

		Log_Print("OBSEPlugin_Load >> running...");

		Punchinello::Interface::SetPluginHandle(obse->GetPluginHandle());
		Punchinello::Commands::RegisterCommands(obse);

		Log_Print("OBSEPlugin_Load >> finished loading");

		return true;
	}

};
