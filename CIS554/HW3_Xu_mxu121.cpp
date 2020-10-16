//HW1 by Mingyang Xu
//SU Net ID: mxu121  SUID: 841104584
//CIS554 HW3
//Due: saturday (10/5) at 11:59PM


#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	course() {}
	course(string n, int s, int c) { name = n; section = s; credits = c; }
	//Add additional needed member functions and implement them.
	//You also need to implement some needed functions for overloading operator<< .
};
//Implement the following functions

void add_student(map<int, map<int, list<course*>* > >& DB, int id);
void remove_student(map<int, map<int, list<course*>* > >& DB, int id);
void add_course(map<int, map<int, list<course*>* > >& DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017

void drop_course(map<int, map<int, list<course*>* > >& DB, int semester, int id, course c);
void print_student_semester_courses(map<int, map<int, list<course*>* > >& DB, int semester, int id);
void print_student_all_courses(map<int, map<int, list<course*>* > >& DB, int id);
void print_DB(map<int, map<int, list<course*>* > >& DB);



//For the print funcitons, you need to add more fucntions to overload operator<<.
//for example print_DB is simply cout << DB;
//Courses in a semeste are sorted alphabetically.


ostream& operator<<(ostream& str, map<int, map<int, list<course*>*>>& DB) {
	if (DB.size() == 0) return str;
	else
	{
		map<int, map<int, list<course*>*> >::iterator it1 = DB.begin();
		while (it1 != DB.end())
		{
			if (it1->second.size() != 0)
			{
				str << "student id = " << it1->first << endl;
				map<int, list<course*>*>::iterator it2 = it1->second.begin();
				list<course*>::iterator it3 = it2->second->begin();
				while (it2 != it1->second.end())
				{
					if (it2->second->size() != 0)
					{
						str << "semester = " << it2->first << endl;

						for (int i = 0; i < it2->second->size(); i++) {

							str << (**it3).name << " " << (**it3).section << " " << (**it3).credits << "  ";
							it3++;
						}
						str << endl;
					}
					it2++;
					if (it2 != it1->second.end())
					{
						it3 = it2->second->begin();
					}
				}
			}
			it1++;
		}
		str << endl; str << endl;
		return str;
	}
}

ostream& operator<<(ostream& str, map<int, list<course*>*>& L) {
	map<int, list<course*>*>::iterator it1 = L.begin();
	list<course*>::iterator it2 = it1->second->begin();
	while (it1 != L.end()) {

		str << "semester = " << it1->first << endl;
		for (int i = 0; i < it1->second->size(); i++) {
			str << (**it2).name << " " << (**it2).section << " " << (**it2).credits << "  ";
			it2++;
		}
		str << endl;
		it1++;
		if (it1 != L.end())
		{
			it2 = it1->second->begin();
		}
	}
	str << endl;
	str << endl;
	return str;
}

ostream& operator<<(ostream& str, list<course*>*& V) {

	if (V->size() != 0)
	{
		list<course*>::iterator it1 = V->begin();
		for (int i = 0; i < V->size(); i++)
		{
			str << (**it1).name << " " << (**it1).section << " " << (**it1).credits << "  ";
			it1++;
		}
	}
	str << endl; str << endl;
	return str;
}

int main() {
	//Do not change code for main function
	map<int, map<int, list <course*>*> > DB;
	add_student(DB, 11111);
	course C1("CIS554", 1, 3), C2("CSE674", 1, 3), C3("MAT296", 8, 4), C4("WRT205", 5, 3);


	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111);

	add_course(DB, 20172, 11111, C2);
	add_course(DB, 20172, 11111, C4);
	add_course(DB, 20172, 11111, C3);
	add_course(DB, 20172, 11111, C1);
	print_student_all_courses(DB, 11111);

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C4);
	add_course(DB, 20171, 11112, C3);
	add_course(DB, 20171, 11112, C1);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C2);
	add_course(DB, 20172, 11112, C4);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);
	print_student_all_courses(DB, 11112);
	print_DB(DB);
	remove_student(DB, 11111);
	print_DB(DB);
	getchar();
	getchar();
	return 0;
}

void add_student(map<int, map<int, list<course*>* >>& DB, int id)
{
	if (DB.find(id) != DB.end()) return;
	map<int, list<course*>*> L;
	DB[id] = L;
}

void remove_student(map<int, map<int, list<course*>* >>& DB, int id)
{
	if (DB.size() == 0 || DB.find(id) == DB.end()) return;
	map<int, list<course*>*>::iterator it1 = DB[id].begin();
	list<course*>::iterator it2 = it1->second->begin();
	while (it1 != DB[id].end())
	{
		if (it1->second->size() != 0)
		{
			for (int i = 0; i < it1->second->size(); i++)
			{
				delete (*it2);
				it2++;
			}
			it1->second->clear();
		}
		//delete(it1->second);
		it1++;
		if (it1 != DB[id].end())
		{
			it2 = it1->second->begin();
		}
	}
	DB.erase(id);
}


void add_course(map<int, map<int, list<course*>* >>& DB, int semester, int id, course c)
{

	if (DB.find(id) == DB.end()) return;
	if (DB[id].size() == 0 || DB[id].find(semester) == DB[id].end())
	{
		list<course*>* L = new list<course*>;
		(DB[id][semester]) = L;
		(DB[id])[semester]->push_back(new course(c));
	}
	else
	{
		map<int, list<course*>*>::iterator it1 = DB[id].begin();
		list<course*>::iterator it2 = (DB[id])[semester]->begin();
		for (int i = 0; i < DB[id][semester]->size(); i++)
		{
			if ((**it2).name == c.name)
			{
				return;
			}
			else {
				it2++;
			}
		}
		it2 = (DB[id])[semester]->begin();
		int a = 0;
		char a1;

		int b1;

		char a2;
		int b2;
		for (int i = 0; i < DB[id][semester]->size(); i++)
		{
			a1 = c.name.at(0);

			b1 = a1;

			a2 = (**it2).name.at(0);
			b2 = a2;
			if (b1 < b2)
			{
				DB[id][semester]->insert(it2, new course(c));
				return;
			}
			if (b1 > b2)
			{
				if (i == DB[id][semester]->size() - 1)
				{
					it2++;
					DB[id][semester]->insert(it2, new course(c));
					return;
				}
				else {
					it2++;
				}
			}
			if (b1 == b2)
			{
				a1 = c.name.at(1);

				b1 = a1;

				a2 = (**it2).name.at(1);
				b2 = a2;
				if (b1 < b2)
				{

					DB[id][semester]->insert(it2, new course(c));
					return;
				}
				if (b1 > b2)
				{
					if (i == DB[id][semester]->size() - 1)
					{
						DB[id][semester]->insert(it2, new course(c));
						return;
					}
					else {
						it2++;
					}
				}
				if (b1 == b2)
				{
					a1 = c.name.at(2);

					int b1 = a1;

					a2 = (**it2).name.at(2);
					int b2 = a2;
					if (b1 < b2)
					{
						DB[id][semester]->insert(it2, new course(c));
						return;
					}
					else
					{
						if (i < DB[id][semester]->size())
						{
							it2++;
						}
						else
						{
							it2++;
							DB[id][semester]->insert(it2, new course(c));
							return;
						}
					}
				}
			}
		}
	}
}

void drop_course(map<int, map<int, list<course*>* >>& DB, int semester, int id, course c)
{
	if (DB.find(id) == DB.end() || DB[id].size() == 0) return;
	if (DB[id].find(semester) == DB[id].end()) return;
	map<int, list<course*>*>::iterator it1 = DB[id].begin();
	list<course*>::iterator it2 = it1->second->begin();
	for (int i = 0; i < DB[id][semester]->size(); i++)
	{

		if ((**it2).name == c.name)
		{
			delete(*it2);
			break;
		}
		else {
			it2++;
		}
	}
	DB[id][semester]->erase(it2);
}




void print_student_semester_courses(map<int, map<int, list<course*>* >>& DB, int semester, int id)
{
	if (DB.size() == 0 || DB.find(id) == DB.end()) return;
	if (DB[id].find(semester) == DB[id].end()) return;
	cout << "student id = " << id << endl;
	if (DB[id][semester]->size() != 0)
	{
		cout << "semester = " << semester << endl;
		map<int, list<course*>*>::iterator it1 = DB[id].begin();
		list<course*>::iterator it2 = it1->second->begin();
		for (int i = 0; i < DB[id][semester]->size(); i++)
		{
			cout << (**it2).name << " " << (**it2).section << " " << (**it2).credits << "  ";
			it2++;
		}
	}
	cout << endl; cout << endl;
}

void print_student_all_courses(map<int, map<int, list<course*>* >>& DB, int id)
{
	if (DB.size() == 0 || DB.find(id) == DB.end()) return;
	map<int, list<course*>*>::iterator it1 = DB[id].begin();
	list<course*>::iterator it2 = it1->second->begin();
	cout << "student id = " << id << endl;
	while (it1 != DB[id].end()) {

		cout << "semester = " << it1->first << endl;
		for (int i = 0; i < it1->second->size(); i++) {
			cout << (**it2).name << " " << (**it2).section << " " << (**it2).credits << "  ";
			it2++;
		}
		cout << endl;
		it1++;
		if (it1 != DB[id].end())
		{
			it2 = it1->second->begin();
		}
	}
	cout << endl;
	cout << endl;
}

void print_DB(map<int, map<int, list<course*>* >>& DB)
{
	if (DB.size() == 0) return;
	map<int, map<int, list<course*>*> >::iterator it1 = DB.begin();
	while (it1 != DB.end())
	{
		if (it1->second.size() != 0)
		{
			cout << "student id = " << it1->first << endl;
			map<int, list<course*>*>::iterator it2 = it1->second.begin();
			list<course*>::iterator it3 = it2->second->begin();
			while (it2 != it1->second.end())
			{
				if (it2->second->size() != 0)
				{
					cout << "semester = " << it2->first << endl;

					for (int i = 0; i < it2->second->size(); i++) {

						cout << (**it3).name << " " << (**it3).section << " " << (**it3).credits << "  ";
						it3++;
					}
					cout << endl;
				}
				it2++;
				if (it2 != it1->second.end())
				{
					it3 = it2->second->begin();
				}
			}
		}
		it1++;
	}
	cout << endl; cout << endl;
}
//Some additional functions for overloading operator<<


/*
//Your output needs to keep the identical format
//Sample Screenshot
student id = 11111
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11111
semester = 20171
CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11111
semester = 20171
CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3   MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11111
semester = 20171
CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
*/