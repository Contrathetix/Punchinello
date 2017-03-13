#pragma once

// obse includes
#include "obse/PluginAPI.h"

// project includes
#include "Logging.hpp"
#include "Interfaces.hpp"

// json includes
#include <exception>
#include <fstream>
#include "JsonProxy.hpp"

namespace Punchinello::ScriptCommands {

	extern CommandInfo kCommandInfo_JsonGetString;
	//extern CommandInfo kCommandInfo_JsonSetString;

	extern CommandInfo kCommandInfo_JsonGetFloat;
	//extern CommandInfo kCommandInfo_JsonSetFloat;

	extern CommandInfo kCommandInfo_JsonGetInt;
	//extern CommandInfo kCommandInfo_JsonSetInt;

}
