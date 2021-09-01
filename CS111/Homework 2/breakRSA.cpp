#include <iostream> 
#include <unordered_map> //hashmap to map int to chars
#include <utility> //to use pairs
#include <fstream> //for parsing code.txt
#include <vector>
//in vscode just hit ctrl + alt + arrow up/down and another cursor will be created in the line above/below the current one.

int modular_exponentiation(int base, int exponent, int modulus) {
    if (modulus == 1) {
        return 0;
    }
    int c = 1;
    for (int i = 0; i < exponent; i++) {
        c = (c * base)%modulus;
    }
    return c;
}

int main() {
    std::fstream inFile;
    inFile.open("code.txt");
    if (!inFile) {
        std::cout << "Failed to open code.txt." << std::endl;
        return 1;
    }
    int input;
    std::vector<int> inputs;
    while (inFile >> input) {
        inputs.push_back(input);
    }

    for (int i = 0; i < inputs.size(); i++) {
        inputs.at(i) = modular_exponentiation(inputs.at(i), 89, 187);
    }

    std::unordered_map<int, char> codemap;
    for (int i = 3; i <= 28; i++) {
        char ABC = 'A' + i - 3;
        codemap.insert(std::make_pair(i, ABC));
    }
    codemap.insert(std::make_pair(29, ' '));
    codemap.insert(std::make_pair(30, '\"'));
    codemap.insert(std::make_pair(31, '.'));

    for (int i = 0; i < inputs.size(); i++) {
        std::cout << inputs.at(i) << " ";
        //std::cout << codemap.at(inputs.at(i));
    }
    return 0;
}