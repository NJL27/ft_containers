#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <utility>

#if STD
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "./map.hpp"
	#include "./stack.hpp"
	#include "./vector.hpp"
#endif


void VectorPrinter(ft::vector<int> inputVector)
{
	std::cout << "FT: " << std::endl;
	std::cout << "Size: " << inputVector.size() << std::endl;
	
	for (unsigned long i = 0; i < inputVector.size(); ++i)
		std::cout << inputVector[i] << std::endl;

	std::cout << std::endl;
}

int main(void)
{
	time_t start = clock();

	ft::vector<int> Vector(5, 8);
	ft::vector<int> Vector2(5, 8);

	std::cout << "Size: " << Vector.size() << std::endl;

	std::cout << Vector.at(2) << std::endl << std::endl;

	std::cout << Vector[4] << std::endl;

	if (Vector >= Vector2)
		std::cout << "True >=" << std::endl;
	else
		std::cout << "False >=" << std::endl;

	if (Vector >= Vector2)
		std::cout << "True >=" << std::endl << std::endl;
	else
		std::cout << "False >=" << std::endl << std::endl;

	std::cout << Vector.front() << std::endl << std::endl;

	VectorPrinter(Vector);

	Vector.resize(4);

	VectorPrinter(Vector);

	Vector.resize(5, 555);

	VectorPrinter(Vector2);


	std::cout << "PUSH_BACK: " << std::endl;

	Vector.clear();

	for (int i = 0; i < 5; ++i)
		Vector.push_back(i + 10);
	
	for (int i = 0; i < 5; ++i)
		Vector.push_back(i + 10);

	VectorPrinter(Vector);

	ft::vector<int> Vector3;

	Vector3.insert(Vector3.end(), 500);
	
	VectorPrinter(Vector3);


	std::cout << "vector4" << std::endl;
	ft::vector<int> vector4;

	vector4.insert(vector4.end(), 42);
	VectorPrinter(vector4);
	vector4.insert(vector4.begin(), 2, 21);
	VectorPrinter(vector4);


	vector4.insert(vector4.begin(), vector4.begin() + 3, vector4.end());
	std::cout << *vector4.insert(vector4.end(), 42) << std::endl;
	VectorPrinter(vector4);

	ft::pair<std::string, int> Temp;
	ft::vector<ft::pair<std::string, int> > PairTest;

	Temp.first = "string";
	Temp.second = 8;
	PairTest.push_back(Temp);

	std::cout << PairTest[0].first << std::endl;
	std::cout << PairTest[0].second << std::endl;

	// std::vector<int>::iterator itrtr;

	ft::stack<int> Stack;
	ft::stack<int> Stack2;

	std::cout << "Empty: " << std::boolalpha << Stack.empty() << std::endl;

	Stack.push(1);
	Stack.push(2);
	Stack.push(3);

	Stack.top();

	std::cout << "Size: " << Stack.size() << std::endl;
	std::cout << "Empty: " << std::boolalpha << Stack.empty() << std::endl;

	Stack.pop();

	std::cout << "Size 1: " << Stack.size() << std::endl;

	Stack.push(1);

	std::cout << "Size 2: " << Stack.size() << std::endl;

	if (Stack == Stack2)
		std::cout << "True ==" << std::endl;
	else
		std::cout << "False ==" << std::endl;

	if (Stack != Stack2)
		std::cout << "True !=" << std::endl;
	else
		std::cout << "False !=" << std::endl;

	if (Stack < Stack2)
		std::cout << "True <" << std::endl;
	else
		std::cout << "False <" << std::endl;

	if (Stack <= Stack2)
		std::cout << "True <=" << std::endl;
	else
		std::cout << "False <=" << std::endl;

	if (Stack > Stack2)
		std::cout << "True >" << std::endl;
	else
		std::cout << "False >" << std::endl;

	if (Stack >= Stack2)
		std::cout << "True >=" << std::endl << std::endl;
	else
		std::cout << "False >=" << std::endl << std::endl;


	ft::map<char, int> Map;

	Map.insert(ft::pair<char, int>('a', 500));
	std::cout << Map.size() << std::endl;
	std::cout << Map.max_size() << std::endl;

	Map.insert(ft::pair<char, int>('b', 600));
	std::cout << Map.size() << std::endl;

	ft::map<char, int> Map2;
	Map2.insert(ft::pair<char, int>('c', 1));
	std::cout << Map2.size() << std::endl;

	Map2.insert(ft::pair<char, int>('d', 2));
	std::cout << Map2.size() << std::endl;

	Map2.swap(Map);
	std::cout << Map.size() << std::endl;
	std::cout << Map2.size() << std::endl << std::endl;


	ft::map<char,int>::iterator it;

	for (it = Map.begin(); it != Map.end(); ++it)
    std::cout << it->first << " => " << it->second << std::endl;


	ft::map<char,int>::iterator it2;

	for (it2 = Map2.begin(); it2 != Map2.end(); ++it2)
    std::cout << it2->first << " => " << it2->second << std::endl;

	std::cout << std::endl;


	ft::map<int, int> Map3;

	for (int i = 1, j = 10; i < 9 && j < 19; ++i && ++j)
		Map3.insert(ft::pair<int, int>(i, j));

	ft::map<int, int>::iterator it3;

	for (it3 = Map3.begin(); it3 != Map3.end(); ++it3)
    	std::cout << it3->first << " => " << it3->second << std::endl;

	std::cout << std::endl;

	std::cout << "lower_bound 0: " << std::endl;
	ft::map<int, int>::iterator lower_bound = Map3.lower_bound(0);
	std::cout << lower_bound->first << " => " << lower_bound->second << std::endl << std::endl;

	std::cout << "upper_bound 7: " << std::endl;
	ft::map<int, int>::iterator upper_bound = Map3.upper_bound(7);
	std::cout << upper_bound->first << " => " << upper_bound->second << std::endl << std::endl;

	std::cout << "find 7: " << std::endl;
	ft::map<int, int>::iterator find = Map3.find(7);
	std::cout << find->first << " => " << find->second << std::endl << std::endl;

	std::cout << "erase 0-5: " << std::endl;
	Map3.erase(Map3.begin(), Map3.lower_bound(5));
	for (it3 = Map3.begin(); it3 != Map3.end(); ++it3)
    std::cout << it3->first << " => " << it3->second << std::endl;

	std::cout << std::endl;

	ft::map<int, int>::reverse_iterator revIT = Map3.rbegin();
    std::cout << revIT->first << " => " << revIT->second << std::endl;

	revIT++;
    std::cout << revIT->first << " => " << revIT->second << std::endl;

	std::cout << std::endl;

	std::cout << "Time Taken: " << (clock() - start) << std::endl << std::endl;

	// system("leaks ft_containers");

	return (0);
}
