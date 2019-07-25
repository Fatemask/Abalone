#include <iostream>
#include <string>
#include <vector>
using namespace std;

class abalone
{
	// data members
	vector<vector<int>> board;
	int noOfWhites;
	int noOfBlacks;

	// member functions
	vector<int> getPair(string s); // gets the indices of an RD pair
	vector<vector<int>> getCoordinates(string s); // gets the coordinate list of a string
	bool mod(vector<vector<int>> coor); // returns true if total marbles selected is valid

	/*

	TODO

	void move();
	bool isValid();			will call all validation functions
	bool isStringValid();		string is properly entered
	bool isPosValid();		entered coordinates exist on board
	bool winner();			two players are 0 and 1
	int getWhites();
	int getBlacks();

	*/
public:
	abalone();
	void display(); // display in game format
	void disp(); // display in memory format
};

abalone::abalone()
{
	board = {
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

bool abalone::mod(vector<vector<int>> coor)
{
	// true if no of marbles is 1-3
	return (coor.size() >= 1 && coor.size() <= 3) ? true : false;
}

vector<int> abalone::getPair(string s)
{
	vector<int> xy; // indices of respective input board coordinates
	xy.push_back(s[0] - 65);
	if (s[0] >= 'A' && s[0] <= 'D') xy.push_back(s[0] + s[1] - 118);
	else xy.push_back(s[1] - 49);
	return xy;
}

vector<vector<int>> abalone::getCoordinates(string s)
{
	// Input Format: R1D1 R2D2 Dn
	// R: Row D: Diagonal
	vector<vector<int>> coordinates;
	vector<int> x1y1 = getPair(s.substr(0, 2)); // Initial RD board indices
	vector<int> x2y2 = getPair(s.substr(3, 2)); // Final RD board indices
	if (s[0] == s[3]) // marbles lie along the same row
	{
		for (int i = x1y1[1]; i <= x2y2[1]; i++)
		{
			coordinates.push_back(x1y1);
			x1y1[1]++;
		}
	}
	else if (s[1] == s[4]) // marbles lie along same diagonal
	{
		for (int i = x1y1[0]; i <= x2y2[0]; i++)
		{
			coordinates.push_back(x1y1);
			x1y1[0]++;
		}
	}
	else // marbles aligned along NE direction
	{
		if (s[4] - s[1] == s[0] - s[3])  // checking if they lie properly along the NE direction
		{
			for (int i = s[1]; i <= s[4]; i++)
			{
				coordinates.push_back(x1y1);
				x1y1[0]--;	x1y1[1]++;
			}
		}
	}
	return coordinates;
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
	system("pause");
}
