#include <string>
#include "JsonProxy.hpp"

int main() {

    std::string Filename = "JsonTest.json", TempString;

    TempString = "This is a string.";
    Punchinello::JSON::SetValue(Filename, "StringTest", TempString);

    TempString = "Unseen this one";
    TempString = Punchinello::JSON::GetValue(Filename, "StringTest", TempString);
    std::cout << TempString << std::endl;

    TempString = "DefaultReturn";
    TempString = Punchinello::JSON::GetValue(Filename, "NotHere", TempString);
    std::cout << TempString << std::endl;

    Punchinello::JSON::SetValue(Filename, "IntTest", 12345);
    std::cout << Punchinello::JSON::GetValue(Filename, "IntTest", 54321) << std::endl;

    Punchinello::JSON::SetValue(Filename, "FloatTest", 9.8765);
    std::cout << Punchinello::JSON::GetValue(Filename, "FloatTest", 5.6789) << std::endl;

    return 0;
}
