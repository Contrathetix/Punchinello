#include "obse/PluginAPI.h"

namespace Punchinello::Interface {

	bool SetPluginHandle(PluginHandle NewPluginHandle);
	PluginHandle GetPluginHandle();

	//bool SetScriptInterface(OBSEScriptInterface* NewScriptInterface);
	//OBSEScriptInterface* GetScriptInterface();

	bool SetStringInterface(OBSEStringVarInterface* NewStringInterface);
	OBSEStringVarInterface* GetStringInterface();

}
