#include <iostream>
#include <exception>
#include <fstream>
#include "json.hpp"

namespace JSON {

	template <typename T>
	void SetValue(const std::string Filename, const std::string Key, T Value) {

		nlohmann::json Data;

		try {
			std::ifstream File(Filename);
			File >> Data;
			File.close();
		} catch (std::exception& e) {}

		Data[Key] = Value;

		try {
			std::ofstream file(Filename);
			file << std::setw(4) << Data << std::endl;
			file.close();
		} catch (std::exception& e) {}
	}

	template <typename T>
	T GetValue(const std::string Filename, const std::string Key, T DefaultReturnValue) {

		nlohmann::json Data;

		try {
			std::ifstream File(Filename);
			File >> Data;
			File.close();
			DefaultReturnValue = Data[Key];
		} catch (std::exception& e) {}

		return DefaultReturnValue;
	}

}
