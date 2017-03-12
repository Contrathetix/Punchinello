#include <iostream>
#include <exception>
#include <fstream>
#include "json.hpp"

namespace Punchinello::JSON {

	template <typename T>
	void SetValue(const std::string Filename, const std::string Key, T Value) {

		nlohmann::json Data;

		try {
			std::ifstream File(Filename);
			File >> Data;
			File.close();
		} catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		Data[Key] = Value;

		try {
			std::ofstream file(Filename);
			file << std::setw(4) << Data << std::endl;
			file.close();
		} catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		} catch (...) {}
	}

	template <typename T>
	T GetValue(const std::string Filename, const std::string Key, T DefaultReturnValue) {

		nlohmann::json Data;

		try {
			std::ifstream File(Filename);
			File >> Data;
			File.close();
			DefaultReturnValue = Data[Key];
		} catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		} catch (...) {}

		return DefaultReturnValue;
	}

}
