#include "Interfaces.hpp"

namespace Punchinello::Interfaces {

	PluginHandle kPluginHandle = kPluginHandle_Invalid;
	OBSEStringVarInterface *kOBSEStringVar = NULL;
	OBSEArrayVarInterface *kOBSEArrayVar = NULL;
	OBSEScriptInterface *kOBSEScript = NULL;
	const char* kOblivionDirectory = NULL;

}
