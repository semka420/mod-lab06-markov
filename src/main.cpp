#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "textgen.h"

int main() {
    std::ifstream input("result/gen.txt");

    std::vector<std::string> words;
    std::string word;

    while (input >> word) {
        words.push_back(word);
    }

    TextGenerator generator(2);

    generator.Build(words);

    std::string text = generator.Generate(100);

    std::cout << text << std::endl;

    return 0;
}
