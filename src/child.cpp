#include <os.h>

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

int main() {
    char file_name_child[256];
    PipeRead(0, file_name_child, sizeof(file_name_child));
    std::ofstream out(file_name_child, std::ios::app);
    if (!out.is_open()) {
        std::cout << "Error" << std::endl;
        return 1;
    }
    char buf[256];
    bool ok;
    while(PipeRead(0, &buf, sizeof(buf))) {
        std::string str(buf);
        if (str.back() != '.' && str.back() != ';') {
            out << str << std::endl;
            ok = false;
        } else {
            std::cerr << str << std::endl;
            ok = true;
        }
        PipeWrite(1, &ok, sizeof(ok));
    }
    out.close();
    return 0;
}