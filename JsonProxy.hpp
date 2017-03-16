#pragma once

//#include <exception>
#include <fstream>
#include "json.hpp"

namespace Punchinello::Private {

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
		} catch (...) {}
		return DefaultReturnValue;
	}

	std::string JsonFilePath(const char *Filename) {

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

namespace Punchinello::JSON {

	template <typename T>
	void SetValue(char *Filename, char *Path, T Value) {
		static nlohmann::json Data;
		static const std::string Filepath = Punchinello::Private::JsonFilePath(Filename);
		try {
			std::ifstream File(Filepath);
			File >> Data;
			File.close();
		} catch (...) {}
		Data = Punchinello::Private::SetObjectValue(Data, Path, Value);
		try {
			std::ofstream File(Filepath);
			File << std::setw(4) << Data << std::endl;
			File.close();
		} catch (...) {}
	}

	template <typename T>
	T GetValue(char *Filename, char *Path, T DefaultReturnValue) {
		static nlohmann::json Data;
		static std::string Filepath = Punchinello::Private::JsonFilePath(Filename);
		try {
			std::ifstream File(Filepath);
			File >> Data;
			File.close();
			return Punchinello::Private::GetObjectValue(Data, Path, DefaultReturnValue);
		} catch (...) {}
		return DefaultReturnValue;
	}

}
