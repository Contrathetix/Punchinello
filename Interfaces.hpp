#pragma once

// obse includes
#include "obse/PluginAPI.h"

// project includes
#include "Logging.hpp"

namespace Punchinello::Interfaces {

	extern PluginHandle kPluginHandle;
	extern OBSEScriptInterface *kOBSEScript;
	extern OBSEStringVarInterface *kOBSEStringVar;
	extern OBSEArrayVarInterface *kOBSEArrayVar;
	extern const char *kOblivionDirectory;

}
