﻿#include <iostream>
#include <fstream>

#include <ert/json2xml.hpp>
#include <nlohmann/json.hpp>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: json2xml <json file>" << std::endl;
        return 1;
    }

    std::string argument = argv[1];
    std::string jsonStr;

    std::ifstream ifs(argument);
    std::stringstream ss;
    ss << ifs.rdbuf();
    jsonStr = ss.str();
    if (jsonStr == "") {
        std::cerr << "Cannot read file provided !" << std::endl;
        return 1;
    }

    // Consume json to build xml:
    ert::JsonSaxConsumer consumer(2);
    bool success = nlohmann::json::sax_parse(jsonStr, &consumer);

    if (!success)
        std::cerr << "Conversion error !" << std::endl;

    // output xml
    std::cout << consumer.getXmlString();

    // exit status
    return success ? 0 : 1;
}
