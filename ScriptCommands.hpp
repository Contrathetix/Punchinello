#pragma once

// obse includes
#include "obse/GameForms.h"
#include "obse/ModTable.h"
#include "obse/ScriptUtils.h"
#include "obse/PluginAPI.h"
#include "obse/GameAPI.h"
#include "obse/GameData.h"

// project includes
#include "Logging.hpp"
#include "Interfaces.hpp"
#include "JsonProxy.hpp"

namespace Punchinello::ScriptCommands {

	extern CommandInfo kCommandInfo_JsonGetString;
	extern CommandInfo kCommandInfo_JsonSetString;

	extern CommandInfo kCommandInfo_JsonGetFloat;
	extern CommandInfo kCommandInfo_JsonSetFloat;

	extern CommandInfo kCommandInfo_JsonGetInt;
	extern CommandInfo kCommandInfo_JsonSetInt;

	extern CommandInfo kCommandInfo_JsonGetForm;
	extern CommandInfo kCommandInfo_JsonSetForm;

	extern CommandInfo kCommandInfo_JsonEraseKey;

}
