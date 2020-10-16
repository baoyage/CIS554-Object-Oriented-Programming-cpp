//HW2 by Mingyang Xu
//SU Net ID: mxu121  SUID: 841104584
//CIS554 HW2 Second 
//Due: 11:59PM Tuesday ( October 22 )
/*
-   Implement the functions reverse of the DoublyLinkedList class which is sorted in frequency.
The description of the reverse function is given in the class.
-   In the implementation reverse, you are not allowed to modify values of nodes.
You only can modify pointers of nodes.
-   Again, you are not allowed to create new nodes in your implementation.  No external structures (such as arrays,
linked list, map, etc.) are allowed.  You can use some temporary pointes or variables for your
implementation.
-   In implementaing reverse, you are not allowed to do sorting from scratch.

When you submit your code, do not modify main function.

Do not introduce new functions
In-place implementation is required.  (This means all operations should directly performed on the list.)
*/
#include <iostream>
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
	DoublyLinkedList(const std::initializer_list<int>& V);
	void printForward();
	void printBackward();


	void reverse();
	/*
	Given an already sorted DoublyLinkedList in frequency (i.e., the result of HW1), make
	the numbers with the same frequency be sorted in decending order.
	For example, 4 9 33 7 7 12 12 6 6 6 will be re-arranged into 33 9 4 12 12 7 7 6 6 6
	*/

};


DoublyLinkedList::DoublyLinkedList(const std::initializer_list<int>& V) {
	head = tail = nullptr;
	for (auto& value : V) {
		Node* p1 = new Node(value);
		p1->previous = tail;
		if (tail != nullptr)
			tail->next = p1;
		tail = p1;
		if (head == nullptr)
			head = p1;
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

void DoublyLinkedList::reverse() {
	if (head == nullptr && tail == nullptr) return;
	Node* p = head;
	int same = 0;
	while (p->next != nullptr)
	{
		if (p->value != p->next->value)
		{
			same++;
		}
		p = p->next;
	}
	if (same == 0) return;
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

			if (b1->value > b2->value)
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


	int k = 0;
	//num = 5;
	int num1 = num;
	int  b = 1, c = 1;
	int m = 1;

	Node* q1 = head; Node* q2 = head->next;
	Node* q3 = nullptr, * q4 = nullptr;
	Node* q5 = head;

	//num = 5;

	while (c < num1)
	{
		while (q2 != nullptr && c < num1) //&& q2->next != nullptr
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
					break;
				}
				else
				{
					if (q2->next == nullptr)
					{
						q1 = q2->previous;
						q2->previous = nullptr;
						q2->next = head;
						head->previous = q2;
						head = q2;
						q1->next = nullptr;
						tail = q1;
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
		if (c == num1)
		{
			break;
		}
		if (q2 == nullptr && q1->value != q1->previous->value)
		{
			if (c == 1)
			{
				q2 = q1;
				q1 = q1->previous;
				q2->previous = nullptr;
				q2->next = head;
				head->previous = q2;
				head = q2;
				q1->next = nullptr;
				tail = q1;
				c = num1;
			}
		}

		c++;
		q1 = head;
		q2 = head->next;
	}

	Node* temp = tail;
	Node* p2 = tail;
	Node* p3 = p2->previous;
	Node* T = tail->next;
	Node* p6 = tail;
	Node* p4 = nullptr, * p5 = tail;
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




int main() {

	DoublyLinkedList d{ 1,9,15,2,2,8,8,0,0,0,0,3,3,3,3,3,19,19,19,19,19,11,11,11,11,11,4,4,4,4,4,4,4 };
	d.reverse();

	d.printForward();
	d.printBackward();

	DoublyLinkedList d1{ 1,9,9,9 };
	d1.reverse();

	d1.printForward();
	d1.printBackward();

	DoublyLinkedList d2{ 0,0,3,3,3,4,4,4 };
	d2.reverse();

	d2.printForward();
	d2.printBackward();

	DoublyLinkedList d3{ 8,8,9,9,13,13 };
	d3.reverse();

	d3.printForward();
	d3.printBackward();

	DoublyLinkedList d4{ };
	d4.reverse();

	d4.printForward();
	d4.printBackward();

	DoublyLinkedList d5{ 13,13,13,13,13 };
	d5.reverse();

	d5.printForward();
	d5.printBackward();

	getchar();
	getchar();
	return 0;
}