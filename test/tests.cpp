#include <gtest/gtest.h>

#include <vector>

#include "textgen.h"

TEST(TextGeneratorTest, PrefixFormation) {
    TextGenerator gen(2);

    gen.AddWord("one");
    gen.AddWord("two");

    Prefix p = gen.GetPrefix();

    ASSERT_EQ(p.size(), 2);
    EXPECT_EQ(p[0], "one");
    EXPECT_EQ(p[1], "two");
}

TEST(TextGeneratorTest, PrefixShift) {
    TextGenerator gen(2);

    gen.AddWord("one");
    gen.AddWord("two");
    gen.AddWord("three");

    Prefix p = gen.GetPrefix();

    ASSERT_EQ(p.size(), 2);
    EXPECT_EQ(p[0], "two");
    EXPECT_EQ(p[1], "three");
}

TEST(TextGeneratorTest, TableFormation) {
    TextGenerator gen(2);

    std::vector<std::string> words = {
        "a", "b", "c"
    };

    gen.Build(words);

    StateTab table = gen.GetTable();

    Prefix p = {"a", "b"};

    ASSERT_EQ(table[p].size(), 1);
    EXPECT_EQ(table[p][0], "c");
}

TEST(TextGeneratorTest, SingleSuffixSelection) {
    TextGenerator gen;

    std::vector<std::string> suffixes = {"word"};

    std::string result = gen.RandomSuffix(suffixes);

    EXPECT_EQ(result, "word");
}

TEST(TextGeneratorTest, MultipleSuffixSelection) {
    TextGenerator gen;

    std::vector<std::string> suffixes = {
        "one", "two", "three"
    };

    std::string result = gen.RandomSuffix(suffixes);

    EXPECT_TRUE(
        result == "one" ||
        result == "two" ||
        result == "three");
}

TEST(TextGeneratorTest, GenerateTextNotEmpty) {
    TextGenerator gen(2);

    std::vector<std::string> words = {
        "hello", "world", "again"
    };

    gen.Build(words);

    std::string text = gen.Generate(5);

    EXPECT_FALSE(text.empty());
}

TEST(TextGeneratorTest, EmptyGeneration) {
    TextGenerator gen(2);

    std::string text = gen.Generate(5);

    EXPECT_TRUE(text.empty());
}

TEST(TextGeneratorTest, PrefixSizeThree) {
    TextGenerator gen(3);

    gen.AddWord("a");
    gen.AddWord("b");
    gen.AddWord("c");

    Prefix p = gen.GetPrefix();

    ASSERT_EQ(p.size(), 3);
}

TEST(TextGeneratorTest, TableNotEmptyAfterBuild) {
    TextGenerator gen(2);

    std::vector<std::string> words = {
        "one", "two", "three"
    };

    gen.Build(words);

    EXPECT_FALSE(gen.GetTable().empty());
}

TEST(TextGeneratorTest, GeneratedTextHasWords) {
    TextGenerator gen(2);

    std::vector<std::string> words = {
        "a", "b", "c", "d"
    };

    gen.Build(words);

    std::string text = gen.Generate(10);

    EXPECT_GT(text.size(), 0);
}
