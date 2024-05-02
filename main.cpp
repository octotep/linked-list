#include <iostream>
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

int main(void)
{
	LinkedList<ApplicationData> list{};

	ApplicationData data0 = ApplicationData(100, "test1");
	ApplicationData data1 = ApplicationData(101, "test2");
	ApplicationData data2 = ApplicationData(102, "test3");
	ApplicationData data3 = ApplicationData(103, "test4");

	list.insert(data0, 0);
	list.insert(data1, 1);
	list.emplace(std::move(data2), 2);
	list.insert(data3, 3);
	list.emplace(ApplicationData(104, "test5"), 4);

	std::cout << std::endl;
	std::cout << "Print the whole list forwards" << std::endl;

	for (auto &data : list)
	{
		std::cout << "App data " << data.id << " and description '" << data.description << "'" << std::endl;
	}

	std::cout << std::endl;
	std::cout << "Print the whole list backwards" << std::endl;

	for (auto rit = list.rbegin(); rit != list.rend(); ++rit)
	{
		auto &data = *rit;
		std::cout << "App data " << data.id << " and description '" << data.description << "'" << std::endl;
	}

	return 0;
}
