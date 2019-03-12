// DataStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "LinkedList.h"

int main();
void LLTests();

int main()
{
	LLTests();
	return 0;
}


void LLTests()
{
	LinkedList::UnorderedList<int> testList = LinkedList::UnorderedList<int>();
	UnorderedListTest::test1(testList);
	std::cout << "----------------------" << std::endl;
	UnorderedListTest::test2(testList);
	std::cout << "----------------------" << std::endl;
	UnorderedListTest::test3(testList);
	std::cout << "----------------------" << std::endl;
	UnorderedListTest::test4(testList);

	LinkedList::OrderedList oTestList = LinkedList::OrderedList();
	std::cout << "----------------------" << std::endl;
	OrderedListTest::test1(oTestList);
}
