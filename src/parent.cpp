#include <pipe.h>

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <string>

int main() {
    int pipe_to_child[2];
    int pipe_from_child[2];
    PipeCreate(pipe_to_child);
    PipeCreate(pipe_from_child);
    pid_t pid = ProcessCreate();
    if (!pid) {
        PipeClose(pipe_to_child[1]);
        PipeRedirect(pipe_to_child[0], 0);
        PipeClose(pipe_to_child[0]);
        PipeClose(pipe_from_child[0]);
        PipeRedirect(pipe_from_child[1], 1);
        PipeClose(pipe_from_child[1]);
        ProcessExecute("./child", "child");
    }
    PipeClose(pipe_to_child[0]);
    PipeClose(pipe_from_child[1]);
    std::cout << "INPUT FILE ";
    std::string file;
    std::cin >> file;
    PipeWrite(pipe_to_child[1], file.c_str(), file.size() + 1);
    std::string str;
    bool ok;
    while (std::cin >> str) {
        PipeWrite(pipe_to_child[1], str.c_str(), str.size() + 1);
        PipeRead(pipe_from_child[0], &ok, sizeof(ok));
        if (ok) {
            std::cout << "Valid string (printed by child)" << std::endl;
        } else {
            std::cout << "Invalid string (written to file)" << std::endl;
        }
    }
    PipeClose(pipe_to_child[1]);
    PipeClose(pipe_from_child[0]);
    return 0;
}
