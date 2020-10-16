//HW1 by Mingyang Xu
//SU Net ID: mxu121  SUID: 841104584
//CIS554 HW2
//Due: 11:59PM, Wednesday ( September 25)
/*
-   Implement two member functions, merge and remove, of the DoublyLinkedList class of HW1.
The descriptions of the two member functions are given below.
-   In the implementation of merge and remove, you are not allowed to modify values of nodes.
You only can modify pointers of nodes.
-   Again, you are not allowed to create new nodes in your implementation.  No external structures (such as arrays,
linked list, map, etc.) are allowed.  You can use some temporary pointes or variables for your
implementation.
-   In implementaing merge and remove, you are not allowed to call sort() in HW1


When you submit your code, do not modify main function.

Do not introduce new functions
In-place implementation is required.  (This means all operations should directly performed on the list.)
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node* previous;
	Node(int i) { value = i; next = previous = nullptr; }
	Node() { next = previous = nullptr; }
};

class DoublyLinkedList {
public:
	Node* head;
	Node* tail;
	DoublyLinkedList() { head = tail = nullptr; }
	void makeRandomList(int m, int n);
	void printForward();
	void printBackward();


	void sort();//sort all values based on frequency in ascending order.
	 //In case of ties, the smaller values will appear earlier
	//Example:  for list with values  7 6 12 4 33 12 6 6 7
	//sorted results: 4 33 7 7 12 12 6 6 6



	void merge(DoublyLinkedList& L);
	/*
	Given an already sorted DoublyLinkedList (i.e., the result of HW1) , take
	another unsorted list L as function argument, and merge L into the current
	list to form a single sorted DoublyLinkedList.  The result of merge is a sorted list.
	You are not allowed to invoke sort() in HW1 in your implementation of merge.
	*/

	void remove(int m, int n);
	/*
	Given an already sorted DoublyLinkedList (i.e., the result of the HW1),
	remove n times of value m from the DoublyLinkedList.
	If n is more than the total number of m's in the DoublyLinkedList,
	then remove all m's from the list.
	If m does not exist in the list, then do nothing.
	The result of remove will be a sorted list.
	You are not allowed to invoke sort() in HW1 in your implementation of remove.
	*/
};

void DoublyLinkedList::makeRandomList(int m, int n) {

	for (int i = 0; i < m; i++) {
		Node* p1 = new Node(rand() % n);
		p1->previous = tail;
		if (tail != nullptr) tail->next = p1;
		tail = p1;
		if (head == nullptr) head = p1;
	}
}

void DoublyLinkedList::printForward() {
	cout << endl;
	Node* p1 = head;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void DoublyLinkedList::printBackward() {
	cout << endl;
	Node* p1 = tail;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->previous;
	}
}

void DoublyLinkedList::sort()
{
	int d = 0;
	int num = 0;
	Node* n = head;
	while (n)
	{
		n = n->next;
		num++;
	}
	int num2 = num;
	Node* b1 = tail;
	Node* b2 = b1->previous;
	while (d <= num2)
	{
		while (b2 != nullptr)
		{
			if (b1->value < b2->value)
			{
				swap(b1->value, b2->value);
			}
			b1 = b1->previous;
			b2 = b2->previous;
		}
		b1 = tail;
		b2 = b1->previous;
		d++;
	}
	int a = 1;
	Node* p2 = tail;
	Node* temp = tail;
	Node* p3 = p2->previous;
	Node* T = tail->next;
	Node* p6 = tail;
	Node* p4 = nullptr, * p5 = tail;
	int k = 0;
	//num = 5;
	int num1 = num;
	int  b = 1, c = 1;
	int m = 1;

	Node* q1 = head, * q2 = head->next;
	Node* q3 = nullptr, * q4 = nullptr;
	Node* q5 = head;

	//num = 5;
	while (c < num1)
	{
		while (q2 != nullptr && q2->next != nullptr)
		{
			while (q1->value == q2->value && q2->next != nullptr)
			{
				q2 = q2->next;
				b++;
			}
			if (q1->value == q2->value)
			{
				b++;
			}
			if (b > c)
			{
				q1 = q2;
				q2 = q2->next;
				b = 1;
			}
			else
			{
				if (q1 == head)
				{
					q2 = nullptr;
					c = num1;
				}
				else
				{
					if (q2->next == nullptr)
					{
						q2->previous = nullptr;
						q2->next = head;
						q2 = nullptr;
						c = num1;
					}
					else
					{
						q3 = q1->previous;
						q4 = q1->next;
						q1->previous = nullptr;
						q1->next = q5;
						q5->previous = q1;
						q4->previous = q3;
						q3->next = q4;
						while (tail->next != nullptr)
						{
							tail = tail->next;
						}
						while (head->previous != nullptr)
						{
							head = head->previous;
						}
						q2 = nullptr;
						c = num1;
					}
				}
			}
		}



		c++;
		q1 = head;
		q2 = head->next;
	}

	while (num > 1)
	{
		while (p3)
		{
			if (p3->value == p2->value)
			{

				while (p3->value == p2->value)
				{


					p3 = p3->previous;
					a++;
					if (p3 == nullptr)
					{
						return;
					}
				}
				if (num != a)
				{
					p2 = p3;
					p3 = p3->previous;

					a = 1;
				}
				else
				{
					k++;
					if (p2 == temp)
					{
						temp = p3;
						k++;
						p5 = p3->next;
					}
					else
					{
						p4 = p2->next;
						p5 = p3->next;


						if (k == 1)
						{
							p2->next = nullptr;

						}

						if (k > 1)
						{

							p2->next = p6;
							p6->previous = p2;
						}

						p5->previous = temp;
						temp->next = p5;
						p3->next = p4;
						p4->previous = p3;
					}

					p6 = p5;
					temp = p6->previous;

					p2 = p3;
					p3 = p3->previous;
					a = 1;
				}
			}

			else
			{
				p2 = p3;
				p3 = p3->previous;
			}

		}
		num--;
		p2 = p6;
		p3 = p2->previous;
		while (tail->next != nullptr)
		{
			tail = tail->next;
		}
	}

}
//void DoublyLinkedList::sort()

void DoublyLinkedList::merge(DoublyLinkedList& L)
{
	ifstream in("data1.txt");
	int i;
	vector<int> V;
	while (in >> i) { //while not reaching end of file ....

		V.push_back(i);
	}
	in.close();

	for (size_t i = 0; i < V.size(); i++) {
		Node* t1 = new Node(V[i]);
		t1->previous = tail;
		if (tail != nullptr) { tail->next = t1; }
		tail = t1;
		if (head == nullptr) head = t1;
	}

	L.tail->next = head;
	head->previous = L.tail;
	while (head->previous != nullptr)
	{
		head = head->previous;
	}
	int d = 0;
	int num = 0;
	Node* n = head;
	while (n)
	{
		n = n->next;
		num++;
	}
	int num2 = num;
	Node* b1 = tail;
	Node* b2 = b1->previous;
	Node* b3 = nullptr;
	Node* bs1 = nullptr;
	Node* bs2 = nullptr;
	Node* bs3 = nullptr;
	Node* bs4 = nullptr;
	while (d <= num2)
	{
		while (b2 != nullptr)
		{

			if (b1->value < b2->value)
			{
				if (b1 == tail)
				{


					bs1 = b1->next;
					bs2 = b2->previous;

					b1->previous = bs2;
					b1->next = b2;
					b2->previous = b1;
					b2->next = nullptr;
					bs2->next = b1;

				}
				if (b2 == head)
				{
					bs1 = b1->next;
					bs2 = b2->previous;
					b1->previous = nullptr;
					b1->next = b2;
					b2->previous = b1;
					b2->next = bs1;
					bs1->previous = b2;
				}


				if (b1 != tail && b2 != head)
				{
					bs1 = b1->next;
					bs2 = b2->previous;
					b1->previous = bs2;
					b1->next = b2;
					b2->previous = b1;
					b2->next = bs1;
					bs2->next = b1;
					bs1->previous = b2;
				}
				b3 = b1;
				b1 = b2;
				b2 = b3;
			}
			while (tail->next != nullptr)
			{
				tail = tail->next;
			}
			while (head->previous != nullptr)
			{
				head = head->previous;
			}
			b1 = b1->previous;
			b2 = b2->previous;

		}

		b1 = tail;
		b2 = b1->previous;
		d++;
	}
	int a = 1;
	Node* p2 = tail;
	Node* temp = tail;
	Node* p3 = p2->previous;
	Node* T = tail->next;
	Node* p6 = tail;
	Node* p4 = nullptr, * p5 = tail;
	int k = 0;
	//num = 5;
	int num1 = num;
	int  b = 1, c = 1;
	int m = 1;

	Node* q1 = head, * q2 = head->next;
	Node* q3 = nullptr, * q4 = nullptr;
	Node* q5 = head;

	//num = 5;
	while (c < num1)
	{
		while (q2 != nullptr && q2->next != nullptr)
		{
			while (q1->value == q2->value && q2->next != nullptr)
			{
				q2 = q2->next;
				b++;
			}
			if (q1->value == q2->value)
			{
				b++;
			}
			if (b > c)
			{
				q1 = q2;
				q2 = q2->next;
				b = 1;
			}
			else
			{
				if (q1 == head)
				{
					q2 = nullptr;
					c = num1;
				}
				else
				{
					if (q2->next == nullptr)
					{
						q2->previous = nullptr;
						q2->next = head;
						q2 = nullptr;
						c = num1;
					}
					else
					{
						q3 = q1->previous;
						q4 = q1->next;
						q1->previous = nullptr;
						q1->next = q5;
						q5->previous = q1;
						q4->previous = q3;
						q3->next = q4;
						while (tail->next != nullptr)
						{
							tail = tail->next;
						}
						while (head->previous != nullptr)
						{
							head = head->previous;
						}
						q2 = nullptr;
						c = num1;
					}
				}
			}
		}



		c++;
		q1 = head;
		q2 = head->next;
	}

	while (num > 1)
	{
		while (p3)
		{
			if (p3->value == p2->value)
			{

				while (p3->value == p2->value)
				{


					p3 = p3->previous;
					a++;
					if (p3 == nullptr)
					{
						return;
					}
				}
				if (num != a)
				{
					p2 = p3;
					p3 = p3->previous;

					a = 1;
				}
				else
				{
					k++;
					if (p2 == temp)
					{
						temp = p3;
						k++;
						p5 = p3->next;
					}
					else
					{
						p4 = p2->next;
						p5 = p3->next;


						if (k == 1)
						{
							p2->next = nullptr;

						}

						if (k > 1)
						{

							p2->next = p6;
							p6->previous = p2;
						}

						p5->previous = temp;
						temp->next = p5;
						p3->next = p4;
						p4->previous = p3;
					}

					p6 = p5;
					temp = p6->previous;

					p2 = p3;
					p3 = p3->previous;
					a = 1;
				}
			}

			else
			{
				p2 = p3;
				p3 = p3->previous;
			}

		}
		num--;
		p2 = p6;
		p3 = p2->previous;
		while (tail->next != nullptr)
		{
			tail = tail->next;
		}
	}








}

void DoublyLinkedList::remove(int m, int n)
{
	if (n == 0)
	{
		return;
	}

	ifstream in("data1.txt");
	int i;
	vector<int> V;
	while (in >> i) { //while not reaching end of file ....

		V.push_back(i);
	}
	in.close();

	for (size_t i = 0; i < V.size(); i++) {
		Node* p1 = new Node(V[i]);
		p1->previous = tail;
		if (tail != nullptr) { tail->next = p1; }
		tail = p1;
		if (head == nullptr) head = p1;
	}
	Node* a, * b, * c, * d, * e, * f, * g;
	a = b = c = d = f = e = f = g = nullptr;
	a = tail;
	int times = 0, remain = 0;
	int remain1, remain2, remain3;
	while (a->value != m)
	{
		if (a->previous == nullptr)
		{
			return;
		}
		a = a->previous;

	}
	if (a->value == m && a->previous != nullptr)
	{

		b = a->next;
		a = a->previous;
		times = 1;
		while (a->value == m && a->previous != nullptr)
		{
			a = a->previous;
			times++;
		}
	}
	if (a->value == m)
	{
		if (times == 0)
		{
			b = a->next;
		}
		a = a->previous;
		times++;
	}
	if (n >= times)
	{
		if (b == nullptr)
		{
			a->next = nullptr;
			tail = a;
		}
		else {
			if (a == nullptr)
			{
				b->previous = nullptr;
				head = b;
			}
			else
			{
				a->next = b;
				b->previous = a;
			}
		}

	}
	if (n < times && n != 0)
	{
		int back = times - n;
		remain = back;
		remain1 = remain;
		remain2 = remain1;
		remain3 = remain2;
		while (back != 0)
		{
			a = a->next;
			back--;
		}
		a->next = b;
		if (b == nullptr)
		{
			a->next = nullptr;
			tail = a;
		}
		else
		{
			a->next = b;
			b->previous = a;
		}
	}
	c = head;
	a = tail;
	b = tail;

	if (remain == 0)
	{
		return;
	}

	if (remain == 1)
	{
		if (a->previous == nullptr)
		{
			return;
		}
		while (a->value != m)
		{
			a = a->previous;
			if (a->previous == nullptr)
			{
				return;
			}
		}
		b = a->next;
		d = a;
		a = a->previous;
		if (c->value == c->next->value)
		{
			d->previous = nullptr;
			d->next = c;
			if (b == nullptr)
			{
				a->next = nullptr;
				tail = a;
			}
			else
			{
				a->next = b;
				b->previous = a;
			}
		}
		else
		{
			while (m > c->value)
			{
				if (c->value == c->next->value)
				{
					e = c->previous;
					d->previous = e;
					e->next = d;
					c->previous = d;
					d->next = c;
					if (b == nullptr)
					{
						a->next = nullptr;
						tail = a;
						return;
					}
					else
					{
						a->next = b;
						b->previous = a;
						return;
					}
				}

				c = c->next;
			}
			e = c->previous;
			d->previous = e;
			e->next = d;
			c->previous = d;
			d->next = c;
			if (b == nullptr)
			{
				a->next = nullptr;
				tail = a;
			}
			else
			{
				a->next = b;
				b->previous = a;
			}
		}
	}
	if (remain > 1)
	{
		while (a->value != m)
		{
			a = a->previous;
			if (a->previous == nullptr)
			{
				return;
			}
		}
		b = a->next;
		e = a;
		while (remain != 0)
		{
			remain--;
			a = a->previous;
		}
		if (a == nullptr)
		{
			return;
		}
		d = a->next;

		int times1 = 1;
		f = c->next;
		while (times1 < remain1)
		{
			while (c->value == f->value)
			{
				f = f->next;
				times1++;
			}
			if (times1 < remain1)
			{
				times1 = 1;
				c = f;
				f = f->next;
			}
		}
		if (times1 > remain1)
		{
			if (c->previous == nullptr)
			{
				c->previous = e;
				e->next = c;
				d->previous = nullptr;
				if (b == nullptr)
				{
					a->next = nullptr;
				}
				else
				{
					a->next = b;
					b->previous = a;
				}
			}
			else
			{
				g = c->previous;
				c->previous = e;
				e->next = c;
				d->previous = g;
				g->next = d;
				if (b == nullptr)
				{
					a->next = nullptr;
				}
				else
				{
					a->next = b;
					b->previous = a;
				}
			}
		}
		if (times1 == remain1)
		{
			if (c->value > m)
			{
				if (c->previous == nullptr)
				{
					c->previous = e;
					e->next = c;
					d->previous = nullptr;
					if (b == nullptr)
					{
						a->next = nullptr;
					}
					else
					{
						a->next = b;
						b->previous = a;
					}
				}
				else
				{
					g = c->previous;
					c->previous = e;
					e->next = c;
					d->previous = g;
					g->next = d;
					if (b == nullptr)
					{
						a->next = nullptr;
						tail = a;
					}
					else
					{
						a->next = b;
						b->previous = a;
					}
				}
			}
			if (c->value < m)
			{
				while (c->value < m)
				{
					c = f;
					while (remain2 > 0)
					{
						f = f->next;
						remain2--;
					}
					remain2 = remain3;
					if (f->previous->value == f->value)
					{
						break;
					}
				}
				if (c->previous == nullptr)
				{
					c->previous = e;
					e->next = c;
					d->previous = nullptr;
					if (b == nullptr)
					{
						a->next = nullptr;
						tail = a;
					}
					else
					{
						a->next = b;
						b->previous = a;
					}
				}
				else
				{
					g = c->previous;
					c->previous = e;
					e->next = c;
					d->previous = g;
					g->next = d;
					if (b == nullptr)
					{
						a->next = nullptr;
						tail = a;
					}
					else
					{
						a->next = b;
						b->previous = a;
					}
				}
			}

		}
	}
}
int main() {
	DoublyLinkedList d0, d1, d2, d3;
	d1.makeRandomList(20, 20);
	//d1.printForward();
	//d1.printBackward();

	d1.sort();
	d1.printForward();
	d1.printBackward();

	d2.makeRandomList(20, 20);
	d2.printForward();
	d2.printBackward();

	d0.merge(d2);
	d0.printForward();
	d0.printBackward();


	d3.remove(7, 1);
	d3.printForward();
	d3.printBackward();

	getchar();
	getchar();
	return 0;
}