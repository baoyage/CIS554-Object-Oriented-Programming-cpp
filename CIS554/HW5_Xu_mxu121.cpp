//HW5 by Mingyang Xu
//SU Net ID: mxu121  SUID: 841104584
//CIS554 HW5 Due: 11:59PM, Nov. 1 (Friday)

#include <iostream>
#include <list>
#include <map>
#include <algorithm>
using namespace std;

bool odd(int i) { return (i % 2 == 1); }
bool even(int i) { return (i % 2 == 0); }
template <class X> int count(list<int> L, X b)
{
	int a = 0;
	auto it = find_if(L.begin(), L.end(), b);
	while (it != L.end())
	{
		a++;
		it++;
		it = find_if(it, L.end(), b);
	}
	return a;

}
class my_comp_class {
public:
	bool operator() (list<int*>* p1, list<int*>* p2) const {
		auto it1 = (*p1).begin();
		auto it2 = (*p2).begin();
		int a = 0, b = 0;

		while (it1 != (*p1).end())
		{
			a = a + (**it1);
			it1++;
		}
		while (it2 != (*p2).end())
		{
			b = b + (**it2);
			it2++;
		}

		//a = 100; b = 10;
		return a < b;
		//return p1 < p2;
	}

}; class my_comp1_class {
public:
	bool operator() (list<int>* p1, list<int>* p2) const {
		auto it1 = (*p1).begin();
		auto it2 = (*p2).begin();
		int a = 0, b = 0;

		while (it1 != (*p1).end())
		{
			a = a + (*it1);
			it1++;
		}
		while (it2 != (*p2).end())
		{
			b = b + (*it2);
			it2++;
		}

		//a = 100; b = 10;
		return a < b;
		//return p1 < p2;
	}

};

bool my_comp2(list<list<int*>*> p1, list<list<int*>*> p2)
{
	int a = 0, b = 0;
	for (auto i : p1)
	{
		for (auto j : *i)
		{
			a = a + *j;
		}
	}
	for (auto m : p2)
	{
		for (auto n : *m)
		{
			b = b + *n;
		}
	}

	return a < b;
}

class my_comp3 {
public:
	bool operator() (list<list<int*>*> p1, list<list<int*>*> p2) const
	{
		int a = 0, b = 0;
		for (auto i : p1)
		{
			for (auto j : *i)
			{
				a = a + *j;
			}
		}
		for (auto m : p2)
		{
			for (auto n : *m)
			{
				b = b + *n;
			}
		}

		return a < b;
	}
}my_comp3;
template <class T> ostream& operator<< (ostream& s, const list<T*>& L) {

	for (auto i : L) { s << *i << " "; }

	return s;
}
template <class T> ostream& operator<< (ostream& s, const list<T>& L) {

	for (auto i : L) { s << i << " "; }

	return s;
}



template <class T> ostream& operator<< (ostream& s, const map<T, int, my_comp_class>& L) {
	for (auto i : L) { s << *i.first << " " << i.second << " "; }
	return s;
}
template <class T> ostream& operator<< (ostream& s, const map<T, int, my_comp1_class>& L) {
	for (auto i : L) { s << *i.first << " " << i.second << " "; }
	return s;
}
//bool my_comp_class(const int a, const int b) { return a<b; }
int main() {
	//Write 3 functions: count, odd, even.
	//The second argument for count is either function odd or even.
	//It will count either the number of odd element in the list, or 
	//the number of even elements in the list.
	list<int> L0{ 14,7,2,6,9,5,8,2,13 };
	cout << count(L0, odd) << endl;
	cout << count(L0, even) << endl;

	//You need to design a class of comparison functions (or functors) to allow map to sort elements.
	//This class is called my_comp_class.  Remember that you need to include const for sorting of map.
	//You also need to overload the needed operator<< to print DB.

	map<list<int*>*, int, my_comp_class> DB{ {new list<int*>{new int{9}, new int{28}, new int{14}}, 7},
	{new list<int*>{new int{19}, new int{18}}, 17} };
	cout << DB << endl;
	//for (auto i : DB) { cout << *i.first << " " << i.second << " "; }
	//You need to design a class of comparison functions (or functors) to allow map to sort elements.
	//This class is called my_comp1_class. Remember that you need to include const for sorting of map.
	//You also need to overload the needed operator<< to print DB1.
	map<list<int>*, int, my_comp1_class> DB1{ {new list<int>{9, 28,14}, 7},
	{new list<int>{19,18}, 17} };
	cout << DB1 << endl;

	list<list<int*>*> L1{ {new list<int*>{new int{15}, new int{7}, new int{22}}},
	{new list<int*>{new int{4}, new int{8}, new int{12}}} };//sum is 68
	list<list<int*>*> L2{ {new list<int*>{new int{5}, new int{6}, new int{2}, new int{11}}},
	{new list<int*>{new int{2}, new int{7}, new int{10}}} }; //sum is 43
	list<list<int*>*> L3{ {new list<int*>{new int{2}, new int{3}, new int{2}, new int{9}}},
	{new list<int*>{new int{2}, new int{7}, new int{4}, new int(3)}} }; //sum is 32

	/*
	For the following sort of L4, L5, and L6, compare the sum of all values for L1, L2, and L3.
	For example, the sums of L1, L2, and L3 are 68, 43, and 32, respectively.
	Implement the comparison functions my_comp2, my_comp3, my_comp4 as stated below.
	You also need to overload the needed operator<< to allow the printing.
	*/

	list< list<list<int*>*>> L4{ L1, L2, L3 };
	cout << L4 << endl;
	L4.sort(my_comp2);//Design the function my_comp2 using regular function implementation.
	cout << L4 << endl;

	list< list<list<int*>*>> L5{ L1, L3, L2 };
	cout << L5 << endl;
	L5.sort(my_comp3); //Design my_comp3 using a functor.
	cout << L5 << endl;

	list< list<list<int*>*>> L6{ L2, L1, L3 };
	cout << L6 << endl;
	L6.sort([](list<list<int*>*> p1, list<list<int*>*> p2)
		{
			int a = 0, b = 0;
			for (auto i : p1)
			{
				for (auto j : *i)
				{
					a = a + *j;
				}
			}
			for (auto m : p2)
			{
				for (auto n : *m)
				{
					b = b + *n;
				}
			}

			return a < b;
		}); //Use lambda Expression.
	cout << L6 << endl;

	cin.get();
	return 0;
}

//The following is a sample display
/*
4
5
19 18  17 9 28 14  7
19 18  17 9 28 14  7
15 7 22  4 8 12   5 6 2 11  2 7 10   2 3 2 9  2 7 4 3
2 3 2 9  2 7 4 3   5 6 2 11  2 7 10   15 7 22  4 8 12
15 7 22  4 8 12   2 3 2 9  2 7 4 3   5 6 2 11  2 7 10
2 3 2 9  2 7 4 3   5 6 2 11  2 7 10   15 7 22  4 8 12
5 6 2 11  2 7 10   15 7 22  4 8 12   2 3 2 9  2 7 4 3
2 3 2 9  2 7 4 3   5 6 2 11  2 7 10   15 7 22  4 8 12

*/