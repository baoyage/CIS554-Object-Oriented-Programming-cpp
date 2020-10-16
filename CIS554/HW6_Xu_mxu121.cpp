//HW6 by Mingyang Xu
//SU Net ID: mxu121  SUID: 841104584
//CIS554 HW6   Due: 11:59PM, Friday, Nov. 8.
#include <iostream>
#include <memory>
#include <math.h>

using namespace std;

class node {
public:
	int value;
	shared_ptr<node> right;
	shared_ptr<node> l_child;
	shared_ptr<node> r_child;
	node() {}
	node(int i) { value = i; }
};

class tree {
public:
	shared_ptr<node> root;
	int level;
	tree() { level = 0; }

	//Implement all member functions below
	tree(int n);//constructor for n-level tree
	//and initilize values as shown in the diagram; 0, 1, 2, ...
	//Note that root node is at level 1 and its value will be initialized to 0

	tree(const tree& T);//copy constructor
	~tree();//destructor
	tree(tree&& T); //move constructor

	tree(const initializer_list<int>& V);//The first number in V is tree level;
	//the rest are values from top to bottom and from left to right
	//For example, to create the tree with n=3 in the diagram,
	//tree T1 = {3, 0,1,2,3,4,5,6}; //where the first 3 is tree level, and the rest are values

	void operator= (const tree& R);//L-value operator=
	void operator= (tree&& R); //R-value operator=


	tree ThreeTimes(); //return a tree with all node value being three times
	friend ostream& operator<<(ostream& str, const tree& T);

	int sum(shared_ptr<node> p);//sum of node values in sub-tree rooted at p
	void delete_level(int i); // Delete nodes at level i. Some nodes at level(s) higher
	//than i will also be deleted accordingly. As described in class.  (Also see the
	//example in the main function.)

	shared_ptr<node> find(int i); //find the first node with value i and return
	//its address; if not found, return nullptr;

};
int tree::sum(shared_ptr<node> p)
{
	auto high = 0;
	auto stage = 0;
	auto stageptr = root;
	while (stageptr != p)
	{
		stageptr = stageptr->right;
		stage++;
	}
	if (stage == 0)
	{
		high = 1;
	}
	else
	{
		high = log(stage + 1) / log(2) + 1;
	}
	int step = level - high;
	auto q = root;
	auto s = p->value;
	int k = 1;
	int n = pow(2, k) - 1;
	while (step != 0)
	{
		n = pow(2, k) - 1;
		p = p->l_child;
		q = p;
		s = s + p->value;
		while (n != 0)
		{
			p = p->right;
			s = s + p->value;
			n--;
		}
		p = q;
		step--;
		k++;

	}
	return s;
}

shared_ptr<node> tree::find(int i)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	auto j = root;
	while (j->value != i)
	{
		j = j->right;
		if (j->right == nullptr)
		{
			break;
		}
	}
	if (j->value == i)
	{
		return j;
	}
	else {
		return nullptr;
	}
}
void tree::delete_level(int i)
{
	if (root == nullptr)
	{
		return;
	}
	if (i > level)
	{
		return;
	}
	if (i == level)
	{
		int h = pow(2, level - 1) - 1;
		auto g = root;
		while (h != 1)
		{
			g = g->right;
			h--;
		}
		g->right = root;
		level--;
		return;
	}
	if (i == 1)
	{
		root = root->l_child;
		auto p = root, q = root;
		while (p->r_child != nullptr)
		{
			q = q->l_child;
			p->right = q;
			p = p->r_child;
		}
		p->right = root;
		level--;
		return;

	}
	if (root != nullptr)
	{
		auto q = root;
		int start = pow(2, i - 2) - 1;
		int times = pow(2, i - 2);
		auto times1 = times;
		while (start != 0)
		{
			q = q->right;
			start--;
		}
		auto temp = q;
		auto del = root;
		auto delr = root;
		auto deld = root;

		int u = level - i;
		int slevel = 0;
		int s = pow(2, slevel);
		while (times != 0)
		{

			if (level - i > 1)
			{
				del = q->l_child->r_child;
				delr = q->l_child->r_child;
				deld = q->l_child->r_child;
				slevel = 0;
				s = pow(2, slevel);
				while (slevel < u)
				{

					delr = delr->right;
					deld = deld->l_child;
					while (s != 0)
					{
						del->right = nullptr;
						del->l_child = nullptr;
						del->r_child = nullptr;
						del = delr;
						delr = delr->right;
						s--;
					}

					del = deld;
					delr = deld;
					slevel++;
					s = pow(2, slevel);
				}

				slevel = 0;
				s = pow(2, slevel);
				del = q->r_child->r_child;
				delr = q->r_child->r_child;
				deld = q->r_child->r_child;
				while (slevel < u)
				{

					delr = delr->right;
					deld = deld->l_child;
					while (s != 0)
					{
						del->right = nullptr;
						del->l_child = nullptr;
						del->r_child = nullptr;
						del = delr;
						delr = delr->right;
						s--;
					}

					del = deld;
					delr = deld;
					slevel++;
					s = pow(2, slevel);
				}

			}
			q->l_child = q->l_child->l_child;

			q->r_child = q->r_child->l_child;
			q = q->right;
			times--;
		}

		auto f = root;
		int ftimes = pow(2, i - 1) - 2;
		if (ftimes != 1)
		{
			while (ftimes != 0)
			{
				f = f->right;
				ftimes--;
			}
		}
		q = temp;

		int k = i - 2;

		int n = pow(2, k);

		while (level - i != 0)
		{
			n = pow(2, k);
			while (n != 0)
			{
				f->right = q->l_child;
				f = f->right;
				f->right = q->r_child;
				f = f->right;
				q = q->right;

				n--;
			}
			i++;
			k++;
		}
		f->right = root;
		level--;
	}
}
tree tree::ThreeTimes()
{
	tree T;
	auto i = root;
	auto j = T.root;
	if (i == nullptr)
	{
		return T;
	}
	j = make_shared<node>(0);
	j->right = T.root;
	T.root = j;
	i = i->right;

	while (i != root)
	{
		j = make_shared<node>(0);
		j->right = T.root;
		T.root = j;
		i = i->right;
	}
	while (j->right != nullptr)
	{
		j = j->right;
	}
	j->right = T.root;

	i = root;
	j = T.root;
	j->value = i->value * 3;
	i = i->right;
	j = j->right;
	if (root->right == root)
	{
		return T;
	}
	while (i != root)
	{
		j->value = i->value * 3;
		i = i->right;
		j = j->right;
	}
	T.level = level;
	int n = level;
	int x = pow(2, n - 1);
	int m = 0;
	shared_ptr<node> current = T.root;
	shared_ptr<node> a = T.root; auto b = 0;
	if (x == 2)
	{
		auto l = 2 * m + 1;
		auto r = 2 * m + 2;
		a = root; b = 0;
		while (b != l)
		{
			a = a->right;
			b++;
		}
		current->l_child = a;
		a = root; b = 0;
		while (b != r)
		{
			a = a->right;
			b++;
		}
		current->r_child = a;
		current = current->right;
		return T;
	}
	while (m != x)
	{
		auto l = 2 * m + 1;
		auto r = 2 * m + 2;
		a = T.root; b = 0;
		while (b != l)
		{
			a = a->right;
			b++;
		}
		current->l_child = a;
		a = T.root; b = 0;
		while (b != r)
		{
			a = a->right;
			b++;
		}
		current->r_child = a;
		current = current->right;
		m++;
	}

	return T;



}

tree::tree(int n) //constructor
{
	if (n == 0)
	{
		return;
	}

	level = n;
	int i = 1; int j = pow(2, n);
	root = make_shared<node>(0);
	shared_ptr<node> q = root;
	if (n == 1)
	{
		q->right = root;
		return;
	}
	while (i != j - 1)
	{
		shared_ptr<node> p = make_shared<node>(i);
		q->right = p;
		q = p;
		i++;
	}
	q->right = root;

	j = pow(2, n - 1);
	int m = 0;
	auto current = root;
	auto a = root; auto b = 0;
	if (j == 2)
	{
		auto l = 2 * m + 1;
		auto r = 2 * m + 2;
		a = root; b = 0;
		while (b != l)
		{
			a = a->right;
			b++;
		}
		current->l_child = a;
		a = root; b = 0;
		while (b != r)
		{
			a = a->right;
			b++;
		}
		current->r_child = a;
		current = current->right;
		return;
	}
	while (m != j)
	{
		auto l = 2 * m + 1;
		auto r = 2 * m + 2;
		a = root; b = 0;
		while (b != l)
		{
			a = a->right;
			b++;
		}
		current->l_child = a;
		a = root; b = 0;
		while (b != r)
		{
			a = a->right;
			b++;
		}
		current->r_child = a;
		current = current->right;
		m++;

	}

}

tree::tree(const initializer_list<int>& V)//initializer_list
{

	auto it = V.begin();
	if (*it == 0)
	{
		return;
	}
	int n = *it;
	level = n;
	it++;
	root = make_shared<node>(*it);
	it++;
	auto q = root;
	if (it == V.end())
	{
		q->right = root;
		return;
	}


	while (it != V.end())
	{
		shared_ptr<node> p = make_shared<node>(*it);
		q->right = p;
		q = p;
		it++;
	}
	q->right = root;

	int j = pow(2, n - 1);
	int m = 0;
	shared_ptr<node> current = root;
	shared_ptr<node> a = root; auto b = 0;
	if (j == 2)
	{
		auto l = 2 * m + 1;
		auto r = 2 * m + 2;
		a = root; b = 0;
		while (b != l)
		{
			a = a->right;
			b++;
		}
		current->l_child = a;
		a = root; b = 0;
		while (b != r)
		{
			a = a->right;
			b++;
		}
		current->r_child = a;
		current = current->right;
		return;
	}
	while (m != j)
	{
		auto l = 2 * m + 1;
		auto r = 2 * m + 2;
		a = root; b = 0;
		while (b != l)
		{
			a = a->right;
			b++;
		}
		current->l_child = a;
		a = root; b = 0;
		while (b != r)
		{
			a = a->right;
			b++;
		}
		current->r_child = a;
		current = current->right;
		m++;
	}

}

tree::tree(const tree& T)//copy constructor
{
	level = T.level;
	auto i = T.root;
	auto j = root;
	if (i == nullptr)
	{
		return;
	}
	j = make_shared<node>(0);
	j->right = root;
	root = j;
	i = i->right;

	while (i != T.root)
	{
		j = make_shared<node>(0);
		j->right = root;
		root = j;
		i = i->right;
	}
	while (j->right != nullptr)
	{
		j = j->right;
	}
	j->right = root;

	i = T.root;
	j = root;
	j->value = i->value;
	i = i->right;
	j = j->right;
	if (root->right == root)
	{
		return;
	}
	while (i != T.root)
	{
		j->value = i->value;
		i = i->right;
		j = j->right;
	}
	int n = T.level;
	int x = pow(2, n - 1);
	int m = 0;
	shared_ptr<node> current = root;
	shared_ptr<node> a = root; auto b = 0;
	if (x == 2)
	{
		auto l = 2 * m + 1;
		auto r = 2 * m + 2;
		a = root; b = 0;
		while (b != l)
		{
			a = a->right;
			b++;
		}
		current->l_child = a;
		a = root; b = 0;
		while (b != r)
		{
			a = a->right;
			b++;
		}
		current->r_child = a;
		current = current->right;
		return;
	}
	while (m != x)
	{
		auto l = 2 * m + 1;
		auto r = 2 * m + 2;
		a = root; b = 0;
		while (b != l)
		{
			a = a->right;
			b++;
		}
		current->l_child = a;
		a = root; b = 0;
		while (b != r)
		{
			a = a->right;
			b++;
		}
		current->r_child = a;
		current = current->right;
		m++;
	}

}

tree::tree(tree&& T)//move constructor
{
	level = T.level;
	root = T.root;
	T.root = nullptr;

}
tree::~tree()
{
	if (root != nullptr)
	{
		auto times = pow(2, level) - 1;
		while (times != 0) {
			auto p = root->right;
			root->right = nullptr;
			root->l_child = nullptr;
			root->r_child = nullptr;
			root = p;
			times--;
		}
		root.reset();
		level = 0;
	}
}
ostream& operator<<(ostream& str, const tree& T)
{
	auto i = T.root;
	if (i == nullptr)
	{
		return str;
	}
	str << i->value << " ";
	i = i->right;
	while (i != T.root)
	{
		str << i->value << " ";
		i = i->right;
	}
	return str;
}
void tree:: operator= (const tree& R)
{
	if (root != nullptr)
	{
		auto times = pow(2, level) - 1;
		while (times != 0) {
			auto p = root->right;
			root->right = nullptr;
			root->l_child = nullptr;
			root->r_child = nullptr;
			root = p;
			times--;
		}
		root.reset();
	}
	level = R.level;
	auto i = R.root;
	auto j = root;
	if (i == nullptr)
	{
		return;
	}
	j = make_shared<node>(0);
	j->right = root;
	root = j;
	i = i->right;
	while (i != R.root)
	{
		j = make_shared<node>(0);
		j->right = root;
		root = j;
		i = i->right;
	}
	while (j->right != nullptr)
	{
		j = j->right;
	}
	j->right = root;
	i = R.root;
	j = root;
	j->value = i->value;
	i = i->right;
	j = j->right;
	if (root->right == root)
	{
		return;
	}
	while (i != R.root)
	{
		j->value = i->value;
		i = i->right;
		j = j->right;
	}
	int n = R.level;
	int x = pow(2, n - 1);
	int m = 0;
	shared_ptr<node> current = root;
	shared_ptr<node> a = root; auto b = 0;
	if (x == 2)
	{
		auto l = 2 * m + 1;
		auto r = 2 * m + 2;
		a = root; b = 0;
		while (b != l)
		{
			a = a->right;
			b++;
		}
		current->l_child = a;
		a = root; b = 0;
		while (b != r)
		{
			a = a->right;
			b++;
		}
		current->r_child = a;
		current = current->right;
		return;
	}
	while (m != x)
	{
		auto l = 2 * m + 1;
		auto r = 2 * m + 2;
		a = root; b = 0;
		while (b != l)
		{
			a = a->right;
			b++;
		}
		current->l_child = a;
		a = root; b = 0;
		while (b != r)
		{
			a = a->right;
			b++;
		}
		current->r_child = a;
		current = current->right;
		m++;
	}


}
void tree:: operator= (tree&& R)
{
	if (root != nullptr)
	{
		auto times = pow(2, level) - 1;
		while (times != 0) {
			auto p = root->right;
			root->right = nullptr;
			root->l_child = nullptr;
			root->r_child = nullptr;
			root = p;
			times--;
		}
		root.reset();
	}

	level = R.level;
	root = R.root;
	R.root = nullptr;
}

int main() {
	tree T1(3);

	cout << T1 << endl; //will print 0 1 2 3 4 5 6

	tree T2 = { 4, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
	cout << T2 << endl; //will print 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24

	tree T3(T2);
	cout << T3 << endl; //will print 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24

	tree T4;
	T4 = T3;
	cout << T4 << endl; //will print 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24

	T4 = T3.ThreeTimes();
	cout << T4 << endl;//will print 30 33 36 39 42 45 48 51 54 57 60 63 66 69 72

	T4.delete_level(3);
	cout << T4 << endl;//will print 30 33 36 51 57 63 69

	cout << T3.sum(T3.find(12)) << endl; //will print 133

	getchar();
	getchar();
	return 0;
}