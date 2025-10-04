#include<os.h>

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

int main() {
    std::string file;
    std::cin >> file;
    std::ofstream out(file, std::ios::app);
    if (!out.is_open()) {
        std::cerr << "Ошибка открытия файла" << std::endl;
        return 1;
    }
    std::cin.ignore();
    std::string str;
    while (std::cin >> str) {
        if (str.back() == '.' || str.back() == ';') {
            out << str << std::endl;
        } else {
            std::cout << "fails verification" << std::endl;
            break;
        }
    }
    out.close();
    return 0;
}