#include <catch2/catch_test_macros.hpp>
#include "linkedlist.h"

struct ApplicationData
{
    int id{};
    std::string description{};

    // Constructor / Destructor
    ApplicationData(int id, std::string description) : id(id), description(description) {}
    ~ApplicationData() = default;

    ApplicationData(const ApplicationData &copy) : id(copy.id), description(copy.description) {}

    ApplicationData(ApplicationData &&move) : id(std::move(move.id)), description(std::move(move.description)) {}
};

TEST_CASE("Create a linked list and insert one element in it")
{
    LinkedList<ApplicationData> list{};

    list.insert(ApplicationData(101, "This is my description"), 0);

    REQUIRE(list[0].id == 101);
    REQUIRE(list[0].description == "This is my description");
}

TEST_CASE("Create a linked list and emplace one element in it")
{
    LinkedList<ApplicationData> list{};

    list.emplace(ApplicationData(107, "I like lists"), 0);

    REQUIRE(list[0].id == 107);
    REQUIRE(list[0].description == "I like lists");
}

TEST_CASE("Create a linked list and emplace two elements into it at the beginning")
{
    LinkedList<ApplicationData> list{};

    list.emplace(ApplicationData(107, "I like lists"), 0);
    list.emplace(ApplicationData(110, "I like linked lists"), 0);

    REQUIRE(list[0].id == 110);
    REQUIRE(list[0].description == "I like linked lists");

    REQUIRE(list[1].id == 107);
    REQUIRE(list[1].description == "I like lists");
}

TEST_CASE("Create a linked list and insert into the middle")
{
    LinkedList<ApplicationData> list{};

    list.emplace(ApplicationData(107, "I like lists"), 0);
    list.emplace(ApplicationData(110, "I like linked lists"), 0);
    list.emplace(ApplicationData(777, "TEST"), 1);

    REQUIRE(list[0].id == 110);
    REQUIRE(list[0].description == "I like linked lists");

    REQUIRE(list[1].id == 777);
    REQUIRE(list[1].description == "TEST");

    REQUIRE(list[2].id == 107);
    REQUIRE(list[2].description == "I like lists");
}

TEST_CASE("Create a linked list and insert at the end")
{
    LinkedList<ApplicationData> list{};

    list.emplace(ApplicationData(107, "I like lists"), 0);
    list.emplace(ApplicationData(110, "I like linked lists"), 0);
    list.emplace(ApplicationData(777, "TEST"), 2);

    REQUIRE(list[0].id == 110);
    REQUIRE(list[0].description == "I like linked lists");

    REQUIRE(list[1].id == 107);
    REQUIRE(list[1].description == "I like lists");

    REQUIRE(list[2].id == 777);
    REQUIRE(list[2].description == "TEST");

    // Test constant time access too!
    auto rit = list.rbegin();
    REQUIRE((*rit).id == 777);
    REQUIRE((*rit).description == "TEST");
}

TEST_CASE("Iterate forwards")
{
    LinkedList<ApplicationData> list{};

    list.insert(ApplicationData(101, "First"), 0);
    list.emplace(ApplicationData(102, "Second"), 1);
    list.emplace(ApplicationData(103, "Third"), 2);
    list.emplace(ApplicationData(104, "Fourth"), 3);

    auto it = list.begin();

    REQUIRE((*it).id == 101);
    REQUIRE((*it).description == "First");
    ++it;
    REQUIRE((*it).id == 102);
    REQUIRE((*it).description == "Second");
    ++it;
    REQUIRE((*it).id == 103);
    REQUIRE((*it).description == "Third");
    ++it;
    REQUIRE((*it).id == 104);
    REQUIRE((*it).description == "Fourth");
    ++it;

    REQUIRE(!(it != list.end()));
}

TEST_CASE("Iterate backwards")
{
    LinkedList<ApplicationData> list{};

    list.insert(ApplicationData(101, "First"), 0);
    list.emplace(ApplicationData(102, "Second"), 1);
    list.emplace(ApplicationData(103, "Third"), 2);
    list.emplace(ApplicationData(104, "Fourth"), 3);

    auto rit = list.rbegin();

    REQUIRE((*rit).id == 104);
    REQUIRE((*rit).description == "Fourth");
    ++rit;
    REQUIRE((*rit).id == 103);
    REQUIRE((*rit).description == "Third");
    ++rit;
    REQUIRE((*rit).id == 102);
    REQUIRE((*rit).description == "Second");
    ++rit;
    REQUIRE((*rit).id == 101);
    REQUIRE((*rit).description == "First");
    ++rit;

    REQUIRE(!(rit != list.rend()));
}

TEST_CASE("Forwards cursor")
{
    LinkedList<ApplicationData> list{};

    list.insert(ApplicationData(101, "First"), 0);
    list.emplace(ApplicationData(102, "Second"), 1);
    list.emplace(ApplicationData(103, "Third"), 2);
    list.emplace(ApplicationData(104, "Fourth"), 3);

    auto it = list.cursorFrom(1);

    REQUIRE((*it).id == 102);
    REQUIRE((*it).description == "Second");
    ++it;
    REQUIRE((*it).id == 103);
    REQUIRE((*it).description == "Third");
    ++it;
    REQUIRE((*it).id == 104);
    REQUIRE((*it).description == "Fourth");
    ++it;

    REQUIRE(!(it != list.end()));
}

TEST_CASE("Backwards cursor")
{
    LinkedList<ApplicationData> list{};

    list.insert(ApplicationData(101, "First"), 0);
    list.emplace(ApplicationData(102, "Second"), 1);
    list.emplace(ApplicationData(103, "Third"), 2);
    list.emplace(ApplicationData(104, "Fourth"), 3);

    auto rit = list.rcursorFrom(2);

    REQUIRE((*rit).id == 103);
    REQUIRE((*rit).description == "Third");
    ++rit;
    REQUIRE((*rit).id == 102);
    REQUIRE((*rit).description == "Second");
    ++rit;
    REQUIRE((*rit).id == 101);
    REQUIRE((*rit).description == "First");
    ++rit;

    REQUIRE(!(rit != list.rend()));
}