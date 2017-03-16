#include <iostream>
#include <string>
#include <cstring>
#include "json.hpp"

#define STR_MAX_LEN 512

nlohmann::json SetValue(nlohmann::json Object, char *Path, char *Value) {

    char *CharP;

    try {

        if ((CharP = strchr(Path, '.')) != NULL) {
            *CharP = '\0';
            Object[Path] = SetValue(Object[Path], CharP+1, Value);
        } else {
            Object[Path] = Value;
        }

    } catch (...) {}

    return Object;

}

char *GetValue(nlohmann::json Object, char *Path, char *DefaultReturn) {

    char *CharP, *Output;
    std::string TempStr;

    try {

        if ((CharP = strchr(Path, '.')) != NULL) {
            *CharP = '\0';
            return GetValue(Object[Path], CharP+1, DefaultReturn);

        } else if (Object != NULL && Object[Path] != NULL) {
            TempStr = Object[Path];
            if ((Output = (char *)malloc(sizeof(char) * strlen(TempStr.c_str()))) != NULL) {
                strcpy(Output, TempStr.c_str());
                return Output;
            }
        }

    } catch (...) {}

    return DefaultReturn;

}

void main() {

    /*

    nlohmann::json j, t, k, l, m;
    std::array<int, 5> foo = {16, 2, 77, 40, 12071};
    std::map<std::string, int> bar;
    bar["keyyyy"] = 666;
    bar["yyyyek"] = 3333;

    j["aaa"] = 3.12;
    j["bbb"] = "woooooooo";
    t["ccc"] = 12345;
    t["tttt"] = foo;
    t["mmmooooooh"] = bar;
    t["jojojojojoj"] = "ooooooaaaaa";
    j["ddd"] = t;

    l["deepest"] = 123;
    k["second-deepest"] = l;
    m = j["ddd"];
    m["topmost"] = k;

    std::cout << j.dump(4) << std::endl;

    j["ddd"] = m;
    */

    nlohmann::json j;
    j["testing"]["path"]["thingies"] = 123;
    j["testing"]["path"]["dingies"] = "hoho";
    j["testing"]["woot"]["gadgets"] = 3.14;
    j["testing"]["shiny"]["gimmicks"] = 7;

    std::cout << j.dump(4) << std::endl;

    char Testing[STR_MAX_LEN] = "hahahahaha";
    char PathHere[STR_MAX_LEN] = "testing.path.dingies";
    j = SetValue(j, PathHere, Testing);

    char Testing2[STR_MAX_LEN] = "oooooooooooooooo";
    char PathHere2[STR_MAX_LEN] = "aaa.p.wfwf.wiwwwww.2222.iiuhuheuhg.ath.dingies";
    j = SetValue(j, PathHere2, Testing2);

    char Testing3[STR_MAX_LEN] = "pppppppoopopopopop";
    char PathHere3[STR_MAX_LEN] = "trolololololo";
    j = SetValue(j, PathHere3, Testing3);

    std::cout << j.dump(4) << std::endl;

    char Testing4[STR_MAX_LEN] = "trolololo lollolo lollolo lollolo lolololo loo";
    char PathHere4[STR_MAX_LEN] = "definitely not here";
    char *c = GetValue(j, PathHere4, Testing4);
    if (c != NULL) {
        std::cout << c << std::endl;
        free(c);
        std::cout << "freed" << std::endl;
    } else {
        std::cout << "error" << std::endl;
    }

}
