#include "dictionary.h"
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <vector>

class DictionaryTest : public ::testing::Test {
protected:
    EnglishRussianDictionary dict;

    void SetUp() override {}

    void TearDown() override {}

    void createTestFile(const std::string& filename, const std::string& content) {
        std::ofstream file(filename);
        file << content;
        file.close();
    }
};

TEST_F(DictionaryTest, AddWordsWithCStrings) {
    dict += std::make_pair("hello", "привет");
    dict += std::make_pair("world", "мир");

    EXPECT_EQ(dict.count(), 2);
    EXPECT_EQ(dict["hello"], "привет");
    EXPECT_EQ(dict["world"], "мир");
}

TEST_F(DictionaryTest, AddWordsWithStdStrings) {
    dict += std::make_pair(std::string("book"), std::string("книга"));
    dict += std::make_pair(std::string("pen"), std::string("ручка"));

    EXPECT_EQ(dict.count(), 2);
    EXPECT_EQ(dict["book"], "книга");
    EXPECT_EQ(dict["pen"], "ручка");
}

TEST_F(DictionaryTest, RemoveWords) {
    dict += std::make_pair("apple", "яблоко");
    dict += std::make_pair("banana", "банан");
    dict += std::make_pair("cherry", "вишня");

    EXPECT_EQ(dict.count(), 3);
    EXPECT_EQ(dict["banana"], "банан");

    dict -= "banana";
    EXPECT_EQ(dict.count(), 2);
    const EnglishRussianDictionary& const_dict = dict;
    EXPECT_EQ(const_dict["banana"], ""); // После удаления должно возвращать пустую строку

    dict -= std::string("apple");
    EXPECT_EQ(dict.count(), 1);
    EXPECT_EQ(dict["cherry"], "вишня");
}

TEST_F(DictionaryTest, SearchTranslation) {
    dict += std::make_pair("cat", "кошка");
    dict += std::make_pair("dog", "собака");

    EXPECT_EQ(dict["cat"], "кошка");
    EXPECT_EQ(dict["dog"], "собака");
    EXPECT_EQ(dict["bird"], "");
}

TEST_F(DictionaryTest, ReplaceTranslation) {
    dict += std::make_pair("house", "дом");
    EXPECT_EQ(dict["house"], "дом");

    // Замена через оператор []
    dict["house"] = "здание";
    EXPECT_EQ(dict["house"], "здание");

    // Добавление нового слова через оператор []
    dict["car"] = "машина";
    EXPECT_EQ(dict["car"], "машина");
    EXPECT_EQ(dict.count(), 2);
}

TEST_F(DictionaryTest, WordCount) {
    EXPECT_EQ(dict.count(), 0);

    dict += std::make_pair("one", "один");
    EXPECT_EQ(dict.count(), 1);

    dict += std::make_pair("two", "два");
    EXPECT_EQ(dict.count(), 2);

    dict += std::make_pair("three", "три");
    EXPECT_EQ(dict.count(), 3);

    dict -= "two";
    EXPECT_EQ(dict.count(), 2);
}

TEST_F(DictionaryTest, LoadFromFile) {
    const std::string filename = "test_dict.txt";
    createTestFile(filename, "apple\nяблоко\nbanana\nбанан\ncherry\nвишня\n");

    EXPECT_TRUE(dict.load(filename));
    EXPECT_EQ(dict.count(), 3);
    EXPECT_EQ(dict["apple"], "яблоко");
    EXPECT_EQ(dict["banana"], "банан");
    EXPECT_EQ(dict["cherry"], "вишня");

    std::remove(filename.c_str());
}

TEST_F(DictionaryTest, LoadFromNonExistentFile) {
    EXPECT_FALSE(dict.load("non_existent_file.txt"));
}

TEST_F(DictionaryTest, ComplexScenario) {
    // Добавляем слова
    dict += std::make_pair("red", "красный");
    dict += std::make_pair("blue", "синий");
    dict += std::make_pair("green", "зеленый");

    // Проверяем добавление
    EXPECT_EQ(dict.count(), 3);
    EXPECT_EQ(dict["red"], "красный");

    // Меняем перевод
    dict["red"] = "рудый";
    EXPECT_EQ(dict["red"], "рудый");

    // Удаляем слово
    dict -= "blue";
    EXPECT_EQ(dict.count(), 2);
    const EnglishRussianDictionary& const_dict = dict;
    EXPECT_EQ(const_dict["blue"], ""); // После удаления должно возвращать пустую строку

    // Добавляем новое слово через оператор []
    dict["yellow"] = "желтый";
    EXPECT_EQ(dict.count(), 3);
    EXPECT_EQ(dict["yellow"], "желтый");
}

TEST_F(DictionaryTest, EmptyDictionary) {
    EXPECT_EQ(dict.count(), 0);
    EXPECT_EQ(dict["anyword"], "");
}

TEST_F(DictionaryTest, RemoveNonExistentWord) {
    dict += std::make_pair("exist", "существует");
    EXPECT_EQ(dict.count(), 1);

    dict -= "nonexist";
    EXPECT_EQ(dict.count(), 1);
    EXPECT_EQ(dict["exist"], "существует");
}

TEST_F(DictionaryTest, AddDuplicateWord) {
    dict += std::make_pair("test", "тест1");
    EXPECT_EQ(dict["test"], "тест1");

    // Добавляем то же слово с другим переводом
    dict += std::make_pair("test", "тест2");
    // Должно заменить перевод
    EXPECT_EQ(dict["test"], "тест2");
    EXPECT_EQ(dict.count(), 1);
}

// НОВЫЕ ТЕСТЫ ДЛЯ УВЕЛИЧЕНИЯ ПОКРЫТИЯ

TEST_F(DictionaryTest, InsertCausesRebalancing) {
    // Тест на вставку, вызывающую перебалансировку
    dict += std::make_pair("m", "м");
    dict += std::make_pair("a", "а");
    dict += std::make_pair("z", "з");
    dict += std::make_pair("b", "б");
    dict += std::make_pair("y", "й");
    dict += std::make_pair("c", "ц");
    dict += std::make_pair("x", "х");

    EXPECT_EQ(dict.count(), 7);
    EXPECT_EQ(dict["a"], "а");
    EXPECT_EQ(dict["z"], "з");
}

TEST_F(DictionaryTest, DeleteCausesRebalancing) {
    // Тест на удаление, вызывающее перебалансировку
    dict += std::make_pair("a", "а");
    dict += std::make_pair("b", "б");
    dict += std::make_pair("c", "ц");
    dict += std::make_pair("d", "д");
    dict += std::make_pair("e", "е");

    dict -= "b";
    dict -= "d";
    dict -= "a";

    EXPECT_EQ(dict.count(), 2);
    const EnglishRussianDictionary& const_dict = dict;
    EXPECT_EQ(const_dict["c"], "ц");
    EXPECT_EQ(const_dict["e"], "е");
}

TEST_F(DictionaryTest, LoadEmptyFile) {
    const std::string filename = "empty_test.txt";
    createTestFile(filename, "");

    EXPECT_TRUE(dict.load(filename));
    EXPECT_EQ(dict.count(), 0);

    std::remove(filename.c_str());
}

TEST_F(DictionaryTest, ConstCharOperations) {
    // Тестирование операций с const char*
    dict += std::make_pair("hello", "привет");
    dict -= "hello";

    const EnglishRussianDictionary& const_dict = dict;
    EXPECT_EQ(const_dict["hello"], "");
}

TEST_F(DictionaryTest, TreeStructureIntegrity) {
    // Тест на целостность структуры дерева после множества операций
    dict += std::make_pair("50", "пятьдесят");
    dict += std::make_pair("25", "двадцать пять");
    dict += std::make_pair("75", "семьдесят пять");
    dict += std::make_pair("10", "десять");
    dict += std::make_pair("30", "тридцать");
    dict += std::make_pair("60", "шестьдесят");
    dict += std::make_pair("80", "восемьдесят");
    dict += std::make_pair("5", "пять");
    dict += std::make_pair("15", "пятнадцать");
    dict += std::make_pair("35", "тридцать пять");

    EXPECT_EQ(dict.count(), 10);

    // Удаляем в разном порядке
    dict -= "25";
    dict -= "75";
    dict -= "10";

    EXPECT_EQ(dict.count(), 7);

    // Проверяем оставшиеся элементы
    const EnglishRussianDictionary& const_dict = dict;
    EXPECT_EQ(dict["50"], "пятьдесят");
    EXPECT_EQ(dict["30"], "тридцать");
    EXPECT_EQ(const_dict["25"], ""); // Удаленный элемент
}

TEST_F(DictionaryTest, MultipleOperationsOnSameWord) {
    // Многократные операции с одним словом
    dict["word"] = "слово1";
    EXPECT_EQ(dict["word"], "слово1");

    dict["word"] = "слово2";
    EXPECT_EQ(dict["word"], "слово2");

    dict += std::make_pair("word", "слово3");
    EXPECT_EQ(dict["word"], "слово3");

    dict -= "word";
    const EnglishRussianDictionary& const_dict = dict;
    EXPECT_EQ(const_dict["word"], "");

    dict["word"] = "слово4";
    EXPECT_EQ(dict["word"], "слово4");
}

TEST_F(DictionaryTest, MixedStringTypes) {
    // Тест с разными типами строк
    std::string eng1 = "hello";
    const char* rus1 = "привет";

    const char* eng2 = "world";
    std::string rus2 = "мир";

    dict += std::make_pair(eng1, rus1);
    dict += std::make_pair(eng2, rus2);

    EXPECT_EQ(dict.count(), 2);
    EXPECT_EQ(dict[eng1], rus1);
    EXPECT_EQ(dict[eng2], rus2);
}

TEST_F(DictionaryTest, StressTest) {
    // Нагрузочный тест
    for (int i = 0; i < 100; ++i) {
        std::string eng = "word" + std::to_string(i);
        std::string rus = "слово" + std::to_string(i);
        dict += std::make_pair(eng, rus);
    }

    EXPECT_EQ(dict.count(), 100);

    // Удаляем каждое второе слово
    for (int i = 0; i < 100; i += 2) {
        std::string eng = "word" + std::to_string(i);
        dict -= eng;
    }

    EXPECT_EQ(dict.count(), 50);

    // Проверяем оставшиеся слова
    for (int i = 1; i < 100; i += 2) {
        std::string eng = "word" + std::to_string(i);
        std::string expected_rus = "слово" + std::to_string(i);
        EXPECT_EQ(dict[eng], expected_rus);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}