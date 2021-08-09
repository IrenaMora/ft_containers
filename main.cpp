#include <iostream>
#include "containers/map.hpp"
#include "other/pair.hpp"
#include "containers/stack.hpp"
#include "containers/vector.hpp"
#include "iterators/iterator.hpp"
#include "other/is_integral.hpp"
#include "other/enable_if.hpp"
#include "other/categories.hpp"
#include "other/iterator_traits.hpp"
#include "iterators/reverse_iterator.hpp"
#include <ctime>


int	main(void)
{
	unsigned int	time_first =  clock();
	int	position = 1;
	ft::vector<std::string>	my_vector1;

	std::cout << std::endl << "Add 5 elements" << std::endl << std::endl;
	my_vector1.push_back("String 1");
	my_vector1.push_back("String 2");
	my_vector1.push_back("String 3");
	my_vector1.push_back("String 4");
	my_vector1.push_back("String 5");
	my_vector1.assign(3, "my string");
	std::cout
			<< "Vector: " << std::endl
			<< "\tempty(): " << my_vector1.empty() << std::endl
			<< "\tsize(): " << my_vector1.size() << std::endl
			<< "\tcapacity(): " << my_vector1.capacity() << std::endl
			<< "\tback(): " << my_vector1.front() << std::endl
			<< "\tfront(): " << my_vector1.back() << std::endl
			<< "\tat(1): " << my_vector1.at(1) << std::endl
			<< "\toperator [4]: " << my_vector1[4] << std::endl;

	std::cout << std::endl << "Using iterator:" << std::endl;
	ft::vector<std::string>::iterator	first = my_vector1.begin();
	ft::vector<std::string>::iterator	last = my_vector1.end();
	while (first != last)
	{
		std::cout << "\t[" << position << "]: " << *first << std::endl;
		first++;
		position++;
	}

	std::cout << std::endl << "Using const iterator:" << std::endl;
	position = 1;
	ft::vector<std::string>::const_iterator	cfirst = my_vector1.cbegin();
	ft::vector<std::string>::const_iterator	clast = my_vector1.cend();
	while (cfirst != clast)
	{
		std::cout << "\t[" << position << "]: " << *cfirst << std::endl;
		cfirst++;
		position++;
	}

	std::cout << std::endl << "Using reverse iterator:" << std::endl;
	position = 1;
	ft::vector<std::string>::reverse_iterator	rfirst = my_vector1.rbegin();
	ft::vector<std::string>::reverse_iterator	rlast = my_vector1.rend();
	while (rfirst != rlast)
	{
		std::cout << "\t[" << position << "]: " << *rfirst << std::endl;
		rfirst++;
		position++;
	}

	std::cout
			<< std::endl << "Using pop_back()" << std::endl
			<< "\tCurrent size - " << my_vector1.size() << std::endl
			<< "\tTake last element..." << std::endl;
	my_vector1.pop_back();
	std::cout << "\tNew size is " << my_vector1.size() << std::endl;

	std::cout << std::endl << "Using overload operator[] and get: " << my_vector1[0] << std::endl;

	std::cout << std::endl << "Using copy constructor from my_vector1 to my_vector2 and write all values:" << std::endl;
	ft::vector<std::string>	my_vector2(my_vector1);
	position = 1;
	first = my_vector2.begin();
	last = my_vector2.end();
	while (first != last)
	{
		std::cout << "\t[" << position << "]: " << *first << std::endl;
		first++;
		position++;
	}

	std::cout << std::endl << "Using operator = from my_vector2 to my_vector3 and write all values:" << std::endl;
	ft::vector<std::string>	my_vector3(my_vector1);
	position = 1;
	first = my_vector3.begin();
	last = my_vector3.end();
	while (first != last)
	{
		std::cout << "\t[" << position << "]: " << *first << std::endl;
		first++;
		position++;
	}

	std::cout << std::endl << "Overload operators: ==, !=, >, <, >=, <=" << std::endl;
	std::cout
			<< "\tmy_vector1 == my_vector2? " << (my_vector1 == my_vector2) << std::endl
			<< "\tmy_vector1 != my_vector2? " << (my_vector1 != my_vector2) << std::endl
			<< "\tmy_vector1 > my_vector2? " << (my_vector1 > my_vector2) << std::endl
			<< "\tmy_vector1 < my_vector2? " << (my_vector1 < my_vector2) << std::endl
			<< "\tmy_vector1 >= my_vector2? " << (my_vector1 >= my_vector2) << std::endl
			<< "\tmy_vector1 <= my_vector2? " << (my_vector1 <= my_vector2) << std::endl;

	std::cout	<< std::endl << "Function clear()" << std::endl
				<< "\tmy_vector1 size is " << my_vector1.size() << std::endl
				<< "\tClear my_vector1... ";
	my_vector1.clear();
	std::cout	<< "DONE!" << std::endl
				<< "\tmy_vector1 new size is " << my_vector1.size() << std::endl;


	std::cout << std::endl << "Using swap(my_vector3) and print values of my_vector2:" << std::endl;
	position = 1;
	my_vector3.clear();
	my_vector3.push_back("swap");
	my_vector3.push_back("ok");
	my_vector2.swap(my_vector3);
	first = my_vector2.begin();
	last = my_vector2.end();
	while (first != last)
	{
		std::cout << "\t[" << position << "]: " << *first << std::endl;
		first++;
		position++;
	}

	std::cout << std::endl << "Function get_allocator()" << std::endl;
	my_vector1.get_allocator();
	std::cout << "\tOK" << std::endl;

	std::cout << std::endl << "Functions data()" << std::endl;
	my_vector1.data();
	std::cout << "\tOK" << std::endl;

	std::cout	<< std::endl << "Function reserve() for my_vector1" << std::endl
				<< "\tOld capacity(): " << my_vector1.capacity() << std::endl;
	my_vector1.reserve(100);
	std::cout 	<< "\tNew capacity(): " << my_vector1.capacity() << std::endl;

	std::cout << std::endl << "Erase using" << std::endl;
	my_vector2.erase(my_vector2.begin());
	std::cout << "\tNow vector2.size(): " << my_vector2.size() << std::endl;
	std::cout << "\tValue #1: " << my_vector2.at(0) << std::endl;

	my_vector1.push_back("prePreLast string");
	my_vector1.push_back("preLast string");
	my_vector1.push_back("Last string");
	std::cout << std::endl << "Erase using (prototype #2)" << std::endl;
	std::cout << "\tSize of vector1: " << my_vector1.size() << std::endl;
	my_vector1.erase(my_vector1.begin(), my_vector1.end());
	std::cout << "\tNow size of vector1: " << my_vector1.size() << std::endl;

	std::cout << std::endl << "Function resize() for my_vector1" << std::endl;
	std::cout << "\tOld my_vector1.size() = " << my_vector1.size() << std::endl;
	my_vector1.resize(20, "lol");
	std::cout << "\tNot my_vector1.size() = " << my_vector1.size() << std::endl;

	my_vector1.push_back("hello1!");
	std::cout	<< std::endl << "Using function insert()" << std::endl
				 << "\tOld last element: " << my_vector1.back() << std::endl;
	my_vector1.insert(my_vector1.end(), "i'm replaced successfully");
	std::cout 	<< "\tNew last element: " << my_vector1.back() << " (size = " << my_vector1.size() << ')' << std::endl;

	my_vector1.push_back("hello!");
	std::cout	<< std::endl << "Using function insert() (prototype #2)" << std::endl
				 << "\tOld last element: " << my_vector1.back()
				 << " - with size: " << my_vector1.size() << std::endl;
	my_vector1.insert(my_vector1.begin(), 5, "i'm replaced 5 string successfully");
	std::cout 	<< "\tNew last element: " << my_vector1.back()
				 << " - with size: " << my_vector1.size() << std::endl;

	my_vector1.push_back("String #1");
	my_vector1.push_back("String #2");
	std::cout << std::endl << "Using function insert() (prototype #3)" << std::endl;
	std::cout << "\tOld vector4.size(): " << my_vector1.size() << std::endl;
	my_vector1.insert(my_vector1.begin(), my_vector1.begin(), my_vector1.end());
	std::cout << "\tNew vector4.size(): " << my_vector1.size() << std::endl;
	std::cout << "\tValue #1: " << my_vector1.at(0) << std::endl;
	std::cout << "\tValue #2: " << my_vector1.at(1) << std::endl;

	//Stack

	ft::stack<int>	my_stack1;
	my_stack1.push(123);
	my_stack1.push(321);
	my_stack1.push(18);
	std::cout	<< std::endl
				<< "Stack: " << std::endl
				<< "\tempty(): " << my_stack1.empty() << std::endl
				<< "\tsize(): " << my_stack1.size() << std::endl
				<< "\ttop(): " << my_stack1.top() << std::endl;

	std::cout	<< std::endl << "Push() && top(): " << std::endl
				<< "\tpush 19... ";
	my_stack1.push(19);
	std::cout	<< "Done!" << std::endl;
	std::cout << "\tNew top() is " << my_stack1.top() << std::endl;

	std::cout << std::endl << "Function pop() " << std::endl;
	my_stack1.pop();
	std::cout	<< "\tpop done" << std::endl;
	std::cout	<< "\tNow top is " << my_stack1.top() << std::endl;

	std::cout << std::endl << "Using copy and assign constructor " << std::endl;
	ft::stack<int>	my_stack2(my_stack1);
	std::cout << "\tCopy OK " << std::endl;
	ft::stack<int>	my_stack3 = my_stack1;
	std::cout << "\tAssign OK " << std::endl;

	std::cout << std::endl << "Overload operators: ==, !=, >, <, >=, <=" << std::endl;
	std::cout
			<< "\tmy_stack1 == my_stack2? " << (my_stack1 == my_stack2) << std::endl
			<< "\tmy_stack1 != my_stack2? " << (my_stack1 != my_stack2) << std::endl
			<< "\tmy_stack1 > my_stack2? " << (my_stack1 > my_stack2) << std::endl
			<< "\tmy_stack1 < my_stack2? " << (my_stack1 < my_stack2) << std::endl
			<< "\tmy_stack1 >= my_stack2? " << (my_stack1 >= my_stack2) << std::endl
			<< "\tmy_stack1 <= my_stack2? " << (my_stack1 <= my_stack2) << std::endl;

	//Map

	ft::map<int, std::string>	my_map1;
	my_map1.insert(ft::make_pair(1, "My string 1"));
	my_map1.insert(ft::make_pair(2, "My string 2"));
	my_map1.insert(ft::make_pair(3, "My string 3"));
	std::cout	<< std::endl
				<< "Map: " << std::endl
				<< "\tempty(): " << my_map1.empty() << std::endl
				<< "\tsize(): " << my_map1.size() << std::endl
				<< "\tmax_size(): " << my_map1.max_size() << std::endl
				<< "\tcount(): " << my_map1.count(2) << std::endl
				<< "\tfind(): " << (*my_map1.find(3)).second << std::endl
				<< "\tlower_bound(): " << (*my_map1.lower_bound(2)).second << std::endl
				<< "\tupper_bound(): " << (*my_map1.upper_bound(2)).second << std::endl
				<< "\tequal_range(): " << (*(my_map1.equal_range(2).first)).second << ", " << (*(my_map1.equal_range(2).second)).second << std::endl;

	std::cout	<< std::endl
				<< "Function get_allocator: " << std::endl;
	my_map1.get_allocator();
	std::cout	<< "\tDONE" << std::endl;

	ft::map<int, std::string>	my_map2(my_map1);
	ft::map<int, std::string>	my_map3 = my_map1;
	std::cout	<< std::endl
				<< "Copy and assignment constructors using iterators: " << std::endl;
	ft::map<int, std::string>::iterator iter_first1 = my_map1.begin();
	ft::map<int, std::string>::iterator iter_last1 = my_map1.end();
	std::cout << "\tmy_map1 (iterator):" << std::endl;
	while (iter_first1 != iter_last1)
	{
		std::cout << "\t\t" << (*iter_first1).second << std::endl;
		iter_first1++;
	}
	ft::map<int, std::string>::iterator iter_first2 = my_map2.begin();
	ft::map<int, std::string>::iterator iter_last2 = my_map2.end();
	std::cout << "\tmy_map2 (iterator):" << std::endl;
	while (iter_first2 != iter_last2)
	{
		std::cout << "\t\t" << (*iter_first2).second << std::endl;
		iter_first2++;
	}
	ft::map<int, std::string>::const_iterator const_iter_first1 = my_map3.cbegin();
	ft::map<int, std::string>::const_iterator const_iter_last1 = my_map3.cend();
	std::cout << "\tmy_map3 (const_iterator):" << std::endl;
	while (const_iter_first1 != const_iter_last1)
	{
		std::cout << "\t\t" << (*const_iter_first1).second << std::endl;
		const_iter_first1++;
	}

	std::cout	<< std::endl
				 << "Using reverse_iterator: " << std::endl;
	ft::map<int, std::string>::reverse_iterator reverse_iter_first1 = my_map1.rbegin();
	ft::map<int, std::string>::reverse_iterator reverse_iter_last1 = my_map1.rend();
	std::cout << "\tmy_map1:" << std::endl;
	while (reverse_iter_first1 != reverse_iter_last1)
	{
		std::cout << "\t\t" << (*reverse_iter_first1).second << std::endl;
		reverse_iter_first1++;
	}

	my_map2.clear();
	my_map2.insert(ft::make_pair(14, "string 4"));
	my_map2.insert(ft::make_pair(16, "string 5"));
	std::cout	<< std::endl
				<< "Using function clear() && insert (prototype #2): " << std::endl;
	iter_first1 = my_map2.begin();
	iter_last1 = my_map2.end();
	my_map1.insert(iter_first1, iter_last1);
	iter_first1 = my_map1.begin();
	iter_last1 = my_map1.end();
	while (iter_first1 != iter_last1)
	{
		std::cout << "\t" << (*iter_first1).second << std::endl;
		iter_first1++;
	}

	std::cout	<< std::endl
				 << "Using function erase: " << std::endl;
	std::cout	<< "\tCurrent size is " << my_map1.size() << std::endl;
	my_map1.erase(14);
	std::cout	<< "\tNow size is " << my_map1.size() << std::endl;

	std::cout	<< std::endl
				 << "Using function erase (prototype 2): " << std::endl;
	std::cout	<< "\tCurrent size is " << my_map1.size() << std::endl;
	my_map1.erase(my_map1.begin());
	std::cout	<< "\tNow size is " << my_map1.size() << std::endl;

	std::cout	<< std::endl
				 << "Using function erase (prototype 2): " << std::endl;
	std::cout	<< "\tCurrent size is " << my_map1.size() << std::endl;
	my_map1.erase(my_map1.begin());
	std::cout	<< "\tNow size is " << my_map1.size() << std::endl;

	std::cout	<< std::endl
				 << "Using function erase (prototype 3): " << std::endl;
	std::cout	<< "\tCurrent size is " << my_map1.size() << std::endl;
	my_map1.erase(my_map1.begin(), ++my_map1.begin());
	std::cout	<< "\tNow size is " << my_map1.size() << std::endl;

	my_map2.insert(ft::make_pair(6, "string"));
	my_map2.insert(ft::make_pair(9, "string"));
	std::cout	<< std::endl
				 << "Using function swap " << std::endl;
	std::cout	<< "\tCurrent size is " << my_map1.size() << std::endl;
	my_map1.swap(my_map2);
	std::cout	<< "\tNow size is " << my_map1.size() << std::endl;

	std::cout << std::endl << "Overload operators: ==, !=, >, <, >=, <=" << std::endl;
	std::cout
			<< "\tmy_map1 == my_map2? " << (my_map1 == my_map2) << std::endl
			<< "\tmy_map1 != my_map2? " << (my_map1 != my_map2) << std::endl
			<< "\tmy_map1 > my_map2? " << (my_map1 > my_map2) << std::endl
			<< "\tmy_map1 < my_map2? " << (my_map1 < my_map2) << std::endl
			<< "\tmy_map1 >= my_map2? " << (my_map1 >= my_map2) << std::endl
			<< "\tmy_map1 <= my_map2? " << (my_map1 <= my_map2) << std::endl;

	std::cout	<< std::endl
				 << "Using key_comp() && value_comp(): " << std::endl;
	my_map1.key_comp();
	my_map1.value_comp();
	std::cout	<< "\tDONE" << std::endl;
	unsigned int	time_last = clock();
	std::cout << std::endl << "Working time: " << time_last - time_first << std::endl;
}
