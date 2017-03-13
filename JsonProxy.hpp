#include <exception>
#include <fstream>
#include "json.hpp"

namespace Punchinello::JSON {

	template <typename T>
	bool SetValue(const std::string Filename, const std::string Key, T Value) {

		nlohmann::json Data;

		try {
			std::ifstream File(Filename);
			File >> Data;
			File.close();
		} catch (...) {}

		Data[Key] = Value;

		try {
			std::ofstream file(Filename);
			file << std::setw(4) << Data << std::endl;
			file.close();
		} catch (...) {}

	}

	template <typename T>
	T GetValue(char* Filename, char* Key, T DefaultReturnValue) {

		nlohmann::json Data;
		std::string Filepath(Filename);

		if (Filepath.find("..") != std::string::npos) {
			Log_Print("invalid path %s", Filepath);
			return DefaultReturnValue;
		} else {
			Filepath = Punchinello::Interfaces::kOblivionDirectory + Filepath;
			Log_Print("final path %s", Filepath);
		}

		try {
			std::ifstream File(Filepath);
			File >> Data;
			File.close();
			return Data[Key];
		} catch (...) {}

		return DefaultReturnValue;
	}

}
