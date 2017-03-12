#include "Interface.hpp"

namespace Punchinello::Interface {

	PluginHandle g_pluginHandle = kPluginHandle_Invalid;
	//OBSEScriptInterface* g_scriptInterface = NULL;
	OBSEStringVarInterface* g_stringInterface = NULL;
	//std::string	g_strData;

	bool SetPluginHandle(PluginHandle NewPluginHandle) {
		if (!NewPluginHandle) {
			return false;
		}
		else {
			g_pluginHandle = NewPluginHandle;
			return true;
		}
	}

	PluginHandle GetPluginHandle() {
		return g_pluginHandle;
	}

	/*
	bool SetScriptInterface(OBSEScriptInterface* NewScriptInterface) {
	if (!NewScriptInterface) {
	return false;
	} else {
	g_scriptInterface = NewScriptInterface;
	return true;
	}
	}

	OBSEScriptInterface* GetScriptInterface() {
	return g_scriptInterface;
	}
	*/

	bool SetStringInterface(OBSEStringVarInterface* NewStringInterface) {
		if (!NewStringInterface) {
			return false;
		}
		else {
			g_stringInterface = NewStringInterface;
			return true;
		}
	}

	OBSEStringVarInterface* GetStringInterface() {
		return g_stringInterface;
	}

}
