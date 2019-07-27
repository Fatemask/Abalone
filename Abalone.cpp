#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <conio.h>
#define invalid 1000
using namespace std;

class abalone
{
	// data members
	vector<vector<int>> board;
	int noOfWhites;
	int noOfBlacks;

public:
	abalone();
	void display(); // display in game format
	void disp(); // display in memory format

	/*

	TODO

	bool isValid();			will call all validation functions
	bool isStringValid();		string is properly entered
	bool isPosValid();		entered coordinates exist on board
	bool winner();			two players are 0 and 1

	*/

	// member functions
	vector<int> getPair(string s); // gets the indices of an RD pair
	vector<vector<int>> getCoordinates(string &r1d1, string &r2d2, string r3d3); // gets the coordinate list of a string
	int mod(string x1y1, string x2y2); // returns true if total marbles selected is valid
	string getDirection(string rdi, string rdf); // calculates the direction to go in
	vector<vector<int>> calcFinalPosition(vector<vector<int>> coor, string dir); // calculates the final position to move to
	void move(vector<vector<int>> initialCoor, vector<vector<int>> finalCoor); // moves pieces from initial to final position
	int getWhites();
	int getBlacks();
};

abalone::abalone()
{
	board = {
			{  -1, -1, -1, -1, -1},

		  {  0,  0,  -1,  -1,  1,  1},

		 {  0,  0,  0,  -1,  1,  1,  1},

	  {  -1,  0,  0,  -1,  -1,  1,  1,  -1},

  {  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},

	  {  -1,  1,  1,  -1,  -1,  0,  0,  -1},

		 {  1,  1,  1,  -1,  0,  0,  0},
		 
		  {  1,  1,  -1,  -1,  0,  0},

		   {  -1,  -1,  -1,  -1,  -1}
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

int abalone::mod(string x1y1, string x2y2)
{
	if (x1y1[0] == x2y2[0]) // marbles are along same row
	{
		return abs(x1y1[1] - x2y2[1]) + 1;
	}
	else if (x1y1[1] == x2y2[1]) // marbles along same diagonal
	{
		return abs(x1y1[0] - x2y2[0]) + 1;
	}
	else // along different row and diagonal
	{
		if (x1y1[0] - x2y2[0] == x2y2[1] - x1y1[1]) // marbles along proper line
		{
			return abs(x1y1[0] - x2y2[0]) + 1;
		}
		else return invalid;
	}
}

vector<int> abalone::getPair(string s)
{
	vector<int> xy; // indices of respective input board coordinates
	xy.push_back(s[0] - 65);
	if (s[0] >= 'A' && s[0] <= 'D') xy.push_back(s[0] + s[1] - 118);
	else xy.push_back(s[1] - 49);
	return xy;
}

vector<vector<int>> abalone::getCoordinates(string &r1d1, string &r2d2, string r3d3)
{
	// R: Row D: Diagonal
	vector<vector<int>> coordinates;
	if (mod(r2d2, r3d3) < mod(r1d1, r3d3) || mod(r1d1, r3d3) == invalid) // x1y1 must be the one closer to x3y3
	{
		swap(r1d1, r2d2);
	}
	if (mod(r1d1, r3d3) != 2) // final position of marble should be within one block of the final marble
	{
		cout << "Invalid Move!" << endl;
		return coordinates;
	}


	if (r1d1[0] == r2d2[0]) // marbles lie along the same row
	{
		if (r1d1[1] < r2d2[1]) // eg: A5, A7
		{
			string i = r1d1;
			for (; i != r2d2; i[1]++)
			{
				coordinates.push_back(getPair(i));
			}
			coordinates.push_back(getPair(i));
		}
		else // eg: A7, A5
		{
			string i = r1d1;
			for (; i != r2d2; i[1]--)
			{
				coordinates.push_back(getPair(i));
			}
			coordinates.push_back(getPair(i));
		}
	}
	else if (r1d1[1] == r2d2[1]) // marbles lie along same diagonal
	{
		if (r1d1[0] < r2d2[0]) // eg: A5, C5
		{
			string i = r1d1;
			for (; i != r2d2; i[0]++)
			{
				coordinates.push_back(getPair(i));
			}
			coordinates.push_back(getPair(i));
		}
		else // eg: C5, A5
		{
			string i = r1d1;
			for (; i != r2d2; i[0]--)
			{
				coordinates.push_back(getPair(i));
			}
			coordinates.push_back(getPair(i));
		}
	}
	else // marbles aligned along NE direction
	{
		if (r2d2[1] - r1d1[1] == r1d1[0] - r2d2[0])  // checking if they lie properly along the NE direction
		{
			if (r1d1[1] < r2d2[1]) // eg: I1, G3
			{
				string i = r1d1;
				for (; i != r2d2; i[0]--, i[1]++)
				{
					coordinates.push_back(getPair(i));
				}
				coordinates.push_back(getPair(i));
			}
			else // eg: G3, I1
			{
				string i = r1d1;
				for (; i != r2d2; i[0]++, i[1]--)
				{
					coordinates.push_back(getPair(i));
				}
				coordinates.push_back(getPair(i));
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

string abalone::getDirection(string rdi, string rdf)
{
	if (rdi[0] == rdf[0]) // along same row
	{
		if (rdi[1] < rdf[1]) return "EE"; // going east
		else return "WW"; // going west
	}
	else if(rdi[1] == rdf[1]) // along same diagonal
	{
		if (rdi[0] < rdf[0]) return "SE";
		else return "NW";
	}
	else // along NE direction
	{
		if (rdi[0] < rdf[0]) return "SW";
		else return "NE";
	}
}

void abalone::move(vector<vector<int>> initialCoor, vector<vector<int>> finalCoor)
{
	for (int i = 0; i < initialCoor.size(); i++)
	{
		// new coordinates will get the current pieces
		board[finalCoor[i][0]][finalCoor[i][1]] = board[initialCoor[i][0]][initialCoor[i][1]];

		// old coordinates will be declared empty
		board[initialCoor[i][0]][initialCoor[i][1]] = -1;
	}
}

vector<vector<int>> abalone::calcFinalPosition(vector<vector<int>> coor, string dir)
{
	vector<vector<int>> finalCoor;
	int deltaX, deltaY;
	/*
		deltaX and deltaY will indicate what to add to the current position
		for west, decrease col; for east increase col....
	*/
	if (dir == "WW") { deltaX = 0;	deltaY = -1; }
	else if (dir == "EE") { deltaX = 0;	deltaY = 1; }
	else if (dir == "NW") { deltaX = -1;	deltaY = 0; }
	else if (dir == "SE") { deltaX = 1;	deltaY = 0; }
	else if (dir == "NE") { deltaX = -1;	deltaY = 1; }
	else if (dir == "SW") { deltaX = 1;	deltaY = -1; }
	for (int i = 0; i < coor.size(); i++)
	{
		finalCoor.push_back({ coor[i][0] + deltaX, coor[i][1] + deltaY });
	}
	return finalCoor;
}

int abalone::getBlacks()
{
	return noOfBlacks;
}

int abalone::getWhites()
{
	return noOfWhites;
}

int main()
{
	abalone a;
	a.display();
	string s;
	// input form : initial marble, final marble, where you want to move the closer marble to
	// max one step further
	getline(cin, s);
	// getting individual points on the board
	string rd1 = s.substr(0, 2), rd2 = s.substr(3, 2), rd3 = s.substr(6, 2);
	vector<vector<int>> iniCoor = a.getCoordinates(rd1, rd2, rd3);
	string dir = a.getDirection(rd1, rd3);
	vector<vector<int>> finCoor = a.calcFinalPosition(iniCoor, dir);
	a.move(iniCoor, finCoor);
	a.display();
	_getch();
}
