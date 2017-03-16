#pragma once

#include <exception>
#include <fstream>
#include "json.hpp"

namespace Punchinello::JSON {

	template <typename T>
	void SetValue(const char* Filename, const char* Key, T Value) {

		static nlohmann::json Data;
		static const std::string Filepath = Punchinello::Interfaces::JsonFilePath(Filename);

		try {
			std::ifstream File(Filepath);
			File >> Data;
			File.close();
		} catch (...) {}

		Data[Key] = Value;

		try {
			std::ofstream file(Filepath);
			file << std::setw(4) << Data << std::endl;
			file.close();
		} catch (...) {}

	}

	template <typename T>
	T GetValue(char* Filename, char* Key, T DefaultReturnValue) {

		static nlohmann::json Data;
		static std::string Filepath = Punchinello::Interfaces::JsonFilePath(Filename);

		try {
			std::ifstream File(Filepath);
			File >> Data;
			File.close();
			return Data[Key];
		} catch (...) {}

		return DefaultReturnValue;
	}

}
