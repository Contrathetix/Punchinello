#include "Interfaces.hpp"

namespace Punchinello::Interfaces {

	PluginHandle kPluginHandle = kPluginHandle_Invalid;
	OBSEStringVarInterface *kOBSEStringVar = NULL;
	OBSEArrayVarInterface *kOBSEArrayVar = NULL;
	const char* kOblivionDirectory = NULL;

	// helper function for creating an OBSE StringMap from a std::map<std::string, OBSEElement>
	OBSEArray* StringMapFromStdMap(const std::map<std::string, OBSEElement>& data, Script* callingScript) {

		// create empty string map
		OBSEArray* arr = Punchinello::Interfaces::kOBSEArrayVar->CreateStringMap(NULL, NULL, 0, callingScript);

		// add each key-value pair
		for (std::map<std::string, OBSEElement>::const_iterator iter = data.begin(); iter != data.end(); ++iter) {
			Punchinello::Interfaces::kOBSEArrayVar->SetElement(arr, iter->first.c_str(), iter->second);
		}

		return arr;
	}

	// helper function for creating an OBSE Map from a std::map<double, OBSEElement>
	OBSEArray* MapFromStdMap(const std::map<double, OBSEElement>& data, Script* callingScript) {
		OBSEArray* arr = kOBSEArrayVar->CreateMap(NULL, NULL, 0, callingScript);
		for (std::map<double, OBSEElement>::const_iterator iter = data.begin(); iter != data.end(); ++iter) {
			Punchinello::Interfaces::kOBSEArrayVar->SetElement(arr, iter->first, iter->second);
		}
		return arr;
	}

	// helper function for creating OBSE Array from std::vector<OBSEElement>
	OBSEArray* ArrayFromStdVector(const std::vector<OBSEElement>& data, Script* callingScript) {
		OBSEArray* arr = Punchinello::Interfaces::kOBSEArrayVar->CreateArray(&data[0], data.size(), callingScript);
		return arr;
	}

}
