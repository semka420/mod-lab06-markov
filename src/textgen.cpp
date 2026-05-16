// Copyright 2024

#include "textgen.h"

#include <sstream>
#include <string>
#include <vector>

TextGenerator::TextGenerator(int prefixSize)
    : prefixSize_(prefixSize) {}

void TextGenerator::AddWord(const std::string& word) {
    if (prefix_.size() ==
        static_cast<size_t>(prefixSize_)) {
        table_[prefix_].push_back(word);
        prefix_.pop_front();
    }

    prefix_.push_back(word);
}

void TextGenerator::Build(
    const std::vector<std::string>& words) {
    prefix_.clear();
    table_.clear();

    for (const auto& word : words) {
        AddWord(word);
    }
}

std::string TextGenerator::RandomSuffix(
    const std::vector<std::string>& suffixes) const {
    if (suffixes.empty()) {
        return "";
    }

    static std::mt19937 gen(std::random_device{}());

    std::uniform_int_distribution<> dist(
        0,
        static_cast<int>(suffixes.size()) - 1);

    return suffixes[dist(gen)];
}

std::string TextGenerator::Generate(int maxWords) {
    if (table_.empty()) {
        return "";
    }

    Prefix current = table_.begin()->first;

    std::stringstream result;

    for (const auto& word : current) {
        result << word << " ";
    }

    for (int i = 0; i < maxWords; ++i) {
        auto it = table_.find(current);

        if (it == table_.end()) {
            break;
        }

        std::string next =
            RandomSuffix(it->second);

        result << next << " ";

        current.pop_front();
        current.push_back(next);
    }

    return result.str();
}

Prefix TextGenerator::GetPrefix() const {
    return prefix_;
}

StateTab TextGenerator::GetTable() const {
    return table_;
}
