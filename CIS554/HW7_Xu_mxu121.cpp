//HW7 by Mingyang Xu
//SU Net ID: mxu121  SUID: 841104584
#include<iostream>
#include<vector>
using namespace std;

void draw(int n, int x, int y, vector<vector<char>>& array) {
	array[x][y] = 'o';
	array[x - 1][y] = '-';
	array[x + 1][y] = '-';
	array[x - 2][y] = 'o';
	array[x + 2][y] = 'o';
	array[x - 2][y - 1] = '|';
	array[x + 2][y - 1] = '|';
	array[x - 2][y + 1] = '|';
	array[x + 2][y + 1] = '|';
	array[x - 2][y - 2] = 'o';
	array[x + 2][y - 2] = 'o';
	array[x - 2][y + 2] = 'o';
	array[x + 2][y + 2] = 'o';



}
void sep(int n, int x, int y, int row, int column, vector<vector<char>>& array)
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	if (n == 2)
	{
		draw(n - 1, x, y, array);
		return;
	}
	row = row / 2;
	column = column / 2;
	y1 = y + row + 1;
	y2 = y - row - 1;

	x1 = x - row - 1;
	x2 = x + row + 1;
	int k = y2 + 1;
	while (k != y1)
	{
		array[x1][k] = '|';
		k++;
	}
	array[x1][y1] = 'o';
	array[x1][y2] = 'o';
	k = y2 + 1;
	while (k != y1)
	{
		array[x2][k] = '|';
		k++;
	}
	array[x2][y1] = 'o';
	array[x2][y2] = 'o';
	k = x1 + 1;
	while (k != x2)
	{
		array[k][y] = '-';
		k++;
	}
	array[x1][y] = 'o';
	array[x][y] = 'o';
	array[x2][y] = 'o';

	{
		sep(n - 2, x1, y1, row, column, array);

		sep(n - 2, x1, y2, row, column, array);

		sep(n - 2, x2, y2, row, column, array);

		sep(n - 2, x2, y1, row, column, array);
	}
}
void sepd(int n, int x, int y, int row, int column, vector<vector<char>>& array)
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	if (n == 2)
	{
		draw(n - 1, x, y, array);
		return;
	}

	y1 = y + column / 2 + 1;
	y2 = y - column / 2 - 1;


	if (x != y)
	{
		x1 = x;
		x2 = x;
		int k = y2 + 1;
		while (k != y1)
		{
			array[x1][k] = '|';
			k++;
		}
		array[x1][y1] = 'o';
		array[x1][y2] = 'o';
		array[x][y] = 'o';
	}
	else
	{
		x1 = x - row / 2 - 1;
		x2 = x + row / 2 + 1;
		int k = y2 + 1;
		while (k != y1)
		{
			array[x1][k] = '|';
			k++;
		}
		array[x1][y1] = 'o';
		array[x1][y2] = 'o';
		k = y2 + 1;
		while (k != y1)
		{
			array[x2][k] = '|';
			k++;
		}
		array[x2][y1] = 'o';
		array[x2][y2] = 'o';
		k = x1 + 1;
		while (k != x2)
		{
			array[k][y] = '-';
			k++;
		}
		array[x1][y] = 'o';
		array[x][y] = 'o';
		array[x2][y] = 'o';
		row = row / 2;
		column = column / 2;
	}
	if (x1 == x2)
	{
		sep(n - 1, x1, y1, row, column, array);

		//sep(n - 1, x1, y2, row, column, array);

		sep(n - 1, x2, y2, row, column, array);

		//sep(n - 1, x2, y1, row, column, array);
	}
	else
	{
		sep(n - 2, x1, y1, row, column, array);

		sep(n - 2, x1, y2, row, column, array);

		sep(n - 2, x2, y2, row, column, array);

		sep(n - 2, x2, y1, row, column, array);
	}


}


void drawhtree(int n, int x, int y, int row, int column, vector<vector<char>>& array) {
	if (n == 3)
	{
		draw(n, x, y, array);
		return;
	}


	sepd(n - 1, x, y, row, column, array);
	/*
	sep(n-1, x1, y2, array);
	sep(n-1, x2, y2, array);
	sep(n-1, x2, y1, array);*/
}

void print(int row, int column, vector<vector<char>>& array)
{
	int i = 0, j = 0;
	while (i != column)
	{
		j = 0;
		while (j != row)
		{
			cout << array[j][i];
			j++;
		}

		cout << endl;
		i++;
	}

}

int main()
{
	int n = 9;// n is number levels in the binary tree
	int row = 5;
	int column = 5;
	int times = (n - 2) / 2;
	for (; times > 0; times--)
	{
		column = column * 2 + 1;
	}
	row = column;
	if (n % 2 == 0)
	{
		row = (row - 1) / 2;
	}
	vector<char> ro;
	for (int i = column; i > 0; i--)
	{
		ro.push_back({ ' ' });
	}

	vector<vector<char>> array;
	for (int i = column; i > 0; i--)
	{
		array.push_back({ ro });
	}
	int x = row / 2;
	int y = column / 2;
	int x0 = row / 2;
	int y0 = column / 2;
	drawhtree(n, x, y, x0, y0, array);
	print(row, column, array);
	getchar();
	return 0;
}