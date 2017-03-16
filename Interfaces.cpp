#include "Interfaces.hpp"

namespace Punchinello::Interfaces {

	PluginHandle kPluginHandle = kPluginHandle_Invalid;
	OBSEStringVarInterface* kOBSEStringVar	= NULL;
	const char* kOblivionDirectory = NULL;

	std::string JsonFilePath(const char* Filename) {

		static std::string Filepath(Filename);

		if (Filepath.find("..") != std::string::npos) {
			Log_Print("invalid path %s", Filepath);
			return NULL;
		}
		else {
			return Punchinello::Interfaces::kOblivionDirectory + Filepath;
			Log_Print("final path %s", Filepath);
		}

	}

}
