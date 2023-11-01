#include <iostream>
#include <fstream>

#include <ert/json2xml.hpp>
#include <nlohmann/json.hpp>

using namespace std;
using nlohmann::json;

int check(const string& name_file) { //функция проверяет на наличие нужного файла проверка на путь. Функция которая будет проверять путь.
    try {
        if (std::ifstream(name_file)) {
            return 0;
        }
        else {
            cout << "File not find!!!";
            return -1;
        }
    }
    catch (...) {
        std::cout << "Failed !!!";
        return -1;
    }
}

int convert(const string& name_file) {
    string jsonStr;
    ifstream ifs(name_file);
    stringstream ss;
    ss << ifs.rdbuf();
    jsonStr = ss.str();

        ert::JsonSaxConsumer consumer(2);
        bool success = nlohmann::json::sax_parse(jsonStr, &consumer);

        if (!success) {
            std::cerr << "Conversion error !" << std::endl;
            return -1;
        }
        else {
            std::cout << consumer.getXmlString();
            return 0;
        }
    }





int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: json2xml <json file>" << std::endl;
        return -1;
    }

    else {
        const string name_file(argv[1]);
        if (check(name_file) == -1) {
            return -1;
        }
        else {
            return convert(name_file);
        }
    }
}
