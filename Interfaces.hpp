// obse includes
#include "obse/PluginAPI.h"

// project includes
#include "Logging.hpp"

namespace Punchinello::Interfaces {

	typedef OBSEArrayVarInterface::Array OBSEArray;
	typedef OBSEArrayVarInterface::Element OBSEElement;

	extern PluginHandle kPluginHandle;
	extern OBSEStringVarInterface *kOBSEStringVar;
	extern OBSEArrayVarInterface *kOBSEArrayVar;
	extern const char *kOblivionDirectory;

	OBSEArray *StringMapFromStdMap(const std::map<std::string, OBSEElement> &, Script *);
	OBSEArray *MapFromStdMap(const std::map<double, OBSEElement> &, Script *);
	OBSEArray *ArrayFromStdVector(const std::vector<OBSEElement> &, Script *);

}
