//HW1 by Mingyang Xu
//SU Net ID: mxu121  SUID: 841104584
//CIS554 HW1
//Due: 11:59PM, Friday ( September 13)
//Do not modify main funaiton.
//Do not introduce new functions
//In-place implementation is required.

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
	void makeRandomList(int m, int n);
	void printForward();
	void printBackward();

	//inplement the following member functions:

	void sort();//sort all values based on frequency in ascending order.
	 //In case of ties, the smaller values will appear earlier
	//Example:  for list with values  7 6 12 4 33 12 6 6 7
	//sorted results: 4 33 7 7 12 12 6 6 6


	//If your algorithm is inefficient, you might lose points.
	//You will not modify L.

};

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

int main() {
	DoublyLinkedList d1;
	d1.makeRandomList(40, 20);
	d1.printForward();
	d1.printBackward();

	d1.sort();
	d1.printForward();
	d1.printBackward();

	getchar();
	getchar();
	return 0;
}