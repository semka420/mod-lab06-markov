#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <deque>
#include <map>
#include <random>
#include <string>
#include <vector>

typedef std::deque<std::string> Prefix;
typedef std::map<Prefix, std::vector<std::string>> StateTab;

class TextGenerator {
 public:
    explicit TextGenerator(int prefixSize = 2);

    void AddWord(const std::string& word);

    void Build(const std::vector<std::string>& words);

    std::string Generate(int maxWords);

    Prefix GetPrefix() const;

    StateTab GetTable() const;

    std::string RandomSuffix(
        const std::vector<std::string>& suffixes) const;

 private:
    int prefixSize_;
    Prefix prefix_;
    StateTab table_;
};

#endif  // INCLUDE_TEXTGEN_H_
