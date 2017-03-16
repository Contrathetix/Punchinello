// obse includes
#include "obse/PluginAPI.h"

// project includes
#include "Logging.hpp"

namespace Punchinello::Interfaces {

	extern PluginHandle kPluginHandle;
	extern OBSEStringVarInterface* kOBSEStringVar;
	extern const char* kOblivionDirectory;

	std::string JsonFilePath(const char* Filename);

}
