#include <iostream>
#include <vector>
using namespace std;

class abalone
{
	vector<vector<int>> board;

public:
	abalone();
	void display();
	void disp();
};

abalone::abalone()
{
	board = { //more changes
				{  0,  0,  0,  0,  0},

			  {  0,  0,  0,  0,  0,  0},

			{ -1, -1,  0,  0,  0, -1, -1},

		  { -1, -1, -1, -1, -1, -1, -1, -1},

		{ -1, -1, -1, -1, -1, -1, -1, -1, -1},

		  { -1, -1, -1, -1, -1, -1, -1, -1},

			{ -1, -1,  1,  1,  1, -1, -1},

			  {  1,  1,  1,  1,  1,  1},

				{  1,  1,  1,  1,  1}
	};
}

void abalone::display()
{
	char row = 'A';
	int dia = 9;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 3 - i; j >= 0; j--)
		{
			cout << " ";
		}
		cout << row << " ";
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] == -1) cout << "+ ";
			else if (board[i][j] == 0) cout << "O ";
			else cout << "@ ";
		}
		cout << endl;
		row++;
	}
	for (int i = 5; i < 9; i++)
	{
		for (int j = 0; j < i - 4; j++)
		{
			cout << " ";
		}
		cout << row << " ";
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] == -1) cout << "+ ";
			else if (board[i][j] == 0) cout << "O ";
			else cout << "@ ";
		}
		cout << dia << endl;
		row++;
		dia--;
	}
	for (int i = 0; i < 7; i++) cout << " ";
	for (int i = 0; i < 5; i++, dia--) cout << 6 - dia << " ";
	cout << endl;
}

void abalone::move()
{
	/*
		NW - Decrease Row, SE - Increase Row
		NE - Decrease Row Increase Col, SW - Increase Row Decrease Col
		E - Increase Col, W - Decrease Col
	*/
}

void abalone::disp()
{
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
			cout << board[i][j] << " ";
		cout << endl;
	}
}
int main()
{
	abalone a;
	a.display();
	a.disp();
	system("pause");
}
