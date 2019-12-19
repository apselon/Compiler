#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int main(int argc, char *argv[]) {
    
    if (argc == 1) {
        cout << "flag -h to read help text" << endl;
        return 1;
    }
    
    if (argc >= 3) {
        cout << "failed num of arguments" << endl;
        return 2;
    }
    
    if (strcmp(argv[1], "-h") == 0 ||
        strcmp(argv[1], "help") == 0) {
        cout << "Argument is the name of file with assembler code" << endl;
        return 0;
    }
    
    char name_of_input_file[FILENAME_MAX + 1] = {};
    
    strcpy(name_of_input_file, argv[1]);
    
    
    
    //g++ -std=c++14 -I//Users/alex/Desktop/my_libs main.cpp
    
    system("g++ -std=c++14 -I//Users/alex/Desktop/my_libs -o asm /Users/alex/Desktop/Clion/asm/main.cpp");
    
    system("g++ -std=c++14 -I//Users/alex/Desktop/my_libs -o CPU /Users/alex/Desktop/Clion/CPU/main.cpp");
    
    system("g++ -std=c++14 -I//Users/alex/Desktop/my_libs -o disasm /Users/alex/Desktop/Clion/disasm/main.cpp");
    
    char command[PATH_MAX] = "./asm ";
    strcat(command, name_of_input_file);
    
    system(command);
    
    system("rm asm");
    
    system("./CPU");
    
    system("rm CPU");
    
    system("./disasm out.txt");
    
    system("rm disasm");
    
    return 0;
}
