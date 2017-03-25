#include "JsonProxy.hpp"

namespace Punchinello::JSONUtils {

	nlohmann::json EraseObjectKey(nlohmann::json Object, char *Path) {

		char *Separator;

		try {
			if ((Separator = strchr(Path, '.')) != NULL) {
				*Separator = '\0';
				Object[Path] = EraseObjectKey(Object[Path], Separator + 1);
			} else {
				Object.erase(Path);
			}
		} catch (std::exception& e) {
			Log_Print("EraseObjectKey, Exception (%s), Key (%s)", e.what(), Path);
		} catch (...) {}

		return Object;
	}

	std::string JsonFilePath(char *Filename) {

		std::string Filepath(Filename);
		static const std::string InvalidChars("/*:?\"<>;|"); // borrowed from ConScribe by shademe

		if (Filepath.length() < 5) {
			return std::string("");
		}

		if ((Filepath.find("..") != std::string::npos) || (Filepath.find_first_of(InvalidChars) != std::string::npos)) {
			Log_Print("JsonFilePath, InvalidPathString (%s)", Filepath);
			return std::string("");
		}

		return std::string(Punchinello::Interfaces::kOblivionDirectory) + Filepath;
	}

}

namespace Punchinello::JSON {

	void EraseKey(char *Filename, char *Path) {

		nlohmann::json Data;
		const std::string Filepath = Punchinello::JSONUtils::JsonFilePath(Filename);

		try {
			std::ifstream InFile(Filepath);
			InFile >> Data;
			InFile.close();
			Data = Punchinello::JSONUtils::EraseObjectKey(Data, Path);
			std::ofstream OutFile(Filepath);
			OutFile << std::setw(4) << Data << std::endl;
			OutFile.close();
		} catch (std::exception& e) {
			Log_Print("EraseKey, Exception (%s), Filepath (%s), Key (%s)", e.what(), Filepath, Path);
		} catch (...) {}

	}

}