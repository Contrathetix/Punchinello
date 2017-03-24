#pragma once

// json includes
#include <fstream>
#include <exception>

// project includes
#include "Interfaces.hpp"
#include "Logging.hpp"
#include "json.hpp"

namespace Punchinello::JSONUtils {

	nlohmann::json EraseObjectKey(nlohmann::json, char *);
	std::string JsonFilePath(char *);

	template <typename T>
	nlohmann::json SetObjectValue(nlohmann::json Object, char *Path, T Value) {
		char *CharP;
		try {
			if ((CharP = strchr(Path, '.')) != NULL) {
				*CharP = '\0';
				Object[Path] = SetObjectValue(Object[Path], CharP + 1, Value);
			} else {
				Object[Path] = Value;
			}
		} catch (std::exception& e) {
			Log_Print("SetObjectValue, Exception (%s), Key (%s)", e.what(), Path);
		} catch (...) {}
		return Object;
	}

	template <typename T>
	T GetObjectValue(nlohmann::json Object, char *Path, T DefaultReturnValue) {
		char *CharP;
		try {
			if ((CharP = strchr(Path, '.')) != NULL) {
				*CharP = '\0';
				return GetObjectValue(Object[Path], CharP + 1, DefaultReturnValue);
			} else if (Object != NULL && Object[Path] != NULL) {
				return Object[Path];
			}
		} catch (std::exception& e) {
			Log_Print("GetObjectValue, Exception (%s), Key (%s)", e.what(), Path);
		} catch (...) {}
		return DefaultReturnValue;
	}

}

namespace Punchinello::JSON {

	void EraseKey(char *Filename, char *Path);

	template <typename T>
	void SetValue(char *Filename, char *Path, T Value) {
		static nlohmann::json Data;
		static const std::string Filepath = Punchinello::JSONUtils::JsonFilePath(Filename);
		try {
			std::ifstream InFile(Filepath);
			InFile >> Data;
			InFile.close();
			Data = Punchinello::JSONUtils::SetObjectValue(Data, Path, Value);
			std::ofstream OutFile(Filepath);
			OutFile << std::setw(4) << Data << std::endl;
			OutFile.close();
		} catch (std::exception& e) {
			Log_Print("SetValue, Exception (%s), Filepath (%s), Key (%s)", e.what(), Filepath, Path);
		} catch (...) {}
	}

	template <typename T>
	T GetValue(char *Filename, char *Path, T DefaultReturnValue) {
		static nlohmann::json Data;
		static std::string Filepath = Punchinello::JSONUtils::JsonFilePath(Filename);
		try {
			std::ifstream File(Filepath);
			File >> Data;
			File.close();
			return Punchinello::JSONUtils::GetObjectValue(Data, Path, DefaultReturnValue);
		} catch (std::exception& e) {
			Log_Print("GetValue, Exception (%s), Filepath (%s), Key (%s)", e.what(), Filepath, Path);
		} catch (...) {}
		return DefaultReturnValue;
	}

}
