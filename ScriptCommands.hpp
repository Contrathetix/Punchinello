// obse includes
#include "obse/PluginAPI.h"

// project includes
#include "Logging.hpp"
#include "Interface.hpp"


namespace Punchinello::Commands {

	void RegisterCommands(const ::OBSEInterface* obse);

	// input = Filename:string, Key:string, DefaultReturn:string
	// output = the specified json string value, DefaultReturn if error
	bool Cmd_JsonGetString_Execute(COMMAND_ARGS);
	static ParamInfo kParams_JsonGetString[3] = {
		{ "Filename", kParamType_String, 0 },
		{ "Key", kParamType_String, 0 },
		{ "DefaultReturn", kParamType_String, 0 }
	};
	static CommandInfo kJsonGetStringCommand = {
		"JsonGetString",
		"",
		0,
		"Fetch string value from JSON, returns DefaultReturn if unable to fetch value",
		0,
		3,
		kParams_JsonGetString,
		Cmd_JsonGetString_Execute
	};

}
