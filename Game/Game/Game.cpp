#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver, playerValueRecorded, playerInTopThree, restartTheGame = true;
const int width = 45;
const int height = 20;
int x, y, fruitX, fruitY, score, choose;
string playerName;
int tailX[100], tailY[100];
int nTail = 0;
string startTheGame = "Start the game";
string gameEnd = "Game over";
int leadersScore[4];
string leadersName[4];
FILE* Lead;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

bool fruitAtSnake() {
	if (fruitX == x && fruitY == y) {
		return true;
	}

	int i = 0;
	do {
		if (fruitX == tailX[i] && fruitY == tailY[i]) {
			return true;
		}
		++i;
	} while (i < nTail);

	return false;
}

void Setup() {
	playerValueRecorded = true;
	playerInTopThree = false;
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;

	fruitX = rand() % (width - 1);
	fruitY = rand() % (height - 1);

	score = 0;
	cout << "Please enter your nickname" << endl;
	cin >> playerName;
}




void GetLeaderBoard() {
	ifstream Lead;
	Lead.open("LeaderBoard.txt");
	int i = 0;
	while (!Lead.eof()) {
		Lead >> leadersName[i] >> leadersScore[i];
		i++;
	}

	Lead.close();
}

void arraySort() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4 - i; j++) {
			if (leadersScore[j] < leadersScore[j + 1]) {
				int temp = leadersScore[j];
				leadersScore[j] = leadersScore[j + 1];
				leadersScore[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if (playerValueRecorded) {
			if (leadersScore[i] == score) {
				leadersName[i] = playerName;
				playerValueRecorded = false;
			}
		}
	}
}

void Draw() {
	system("cls");

	if (dir != 0) {
		for (int i = 0; i < width + 1; i++)
			cout << "#";
		cout << endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if ((j == 0) || (j == width - 1))
					cout << "#";
				if (i == y && j == x)
					cout << "0";
				else if (i == fruitY && j == fruitX)
					cout << "F";
				else {
					bool print = false;
					for (int k = 0; k < nTail; k++) {
						if (tailX[k] == j && tailY[k] == i) {
							print = true;
							cout << "o";
						}
					}
					if (!print) {
						cout << " ";
						print = false;
					}
				}
			}
			cout << endl;
		}
	}
	else {
		for (int i = 0; i < width + 1; i++)
			cout << "#";
		cout << endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if ((j == 0) || (j == width - 1))
					cout << "#";
				if (i == y && j == x)
					cout << "0";
				else {
					bool print = false;
					for (int k = 0; k < nTail; k++) {
						if (tailX[k] == j && tailY[k] == i) {
							print = true;
							cout << "o";
						}
					}
					if (i == 5 && j > 14 && j < 29) {
						cout << startTheGame[j - 15];

					}
					else {
						if (!print) {
							cout << " ";
							print = false;
						}
					}
				}
				if (i == 7 && j == width) {

				}
			}
			cout << endl;
		}
	}

	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}

void LeaderBoard() {
	system("cls");

	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			if ((j == 0) || (j == width - 1))
				cout << "#";
			if (i == 5 && j > 16 && j < 26) {
				cout << gameEnd[j - 17];
			}
			else if (i == y && j == x)
				cout << "0";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o";
					}
				}

				if (!print) {
					cout << " ";
					print = false;

				}
			}
		}
		cout << endl;

	}
	for (int i = 0; i < width + 1; i++)
		cout << "#";

	leadersScore[3] = score;
	if (leadersScore[3] > leadersScore[0] || leadersScore[3] > leadersScore[1] || leadersScore[3] > leadersScore[2]) {
		cout << endl << playerName << " You are in top 3" << endl;
		playerInTopThree = true;
	}

	cout << endl;
	cout << "Score: " << score << endl;

}


void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			if (dir != RIGHT) {
				dir = LEFT;
			}
			break;
		case 'd':
			if (dir != LEFT) {
				dir = RIGHT;
			}
			break;
		case 'w':
			if (dir != DOWN) {
				dir = UP;
			}
			break;
		case 's':
			if (dir != UP) {
				dir = DOWN;
			}
			break;
		case 'x':
			gameOver = true;
			break;
		}

	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	int prev2X, prev2Y;

	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	if (x >= width - 1)
		x = 0;
	else if (x < 0)
		x = width - 1;
	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if ((x == fruitX && y == fruitY) || fruitAtSnake()) {
		score++;
		nTail++;
		do {
			fruitX = rand() % (width - 1);
			fruitY = rand() % (height - 1);
		} while (fruitAtSnake());
	}
}


void LeaderBoardUpdate() {
	arraySort();
	ofstream Lead;
	Lead.open("LeaderBoard.txt", ofstream::out);
	Lead.clear();
	for (int i = 0; i < 3; i++) {
		Lead << leadersName[i] << " " << leadersScore[i] << '\n';
	}
	Lead.close();
}


int main()
{
	GetLeaderBoard();
	Setup();

	while (restartTheGame) {
		system("cls");
		cout << "1. Play" << endl << "2. Leader board" << endl << "3. Exit" << endl;
		cin >> choose;

		switch (choose) {
		case 1:
			system("cls");
			while (!gameOver) {
				Draw();
				Input();
				Logic();
				Sleep(100);
			}
			LeaderBoard();
			if (playerInTopThree)
				LeaderBoardUpdate();
			cout << endl << "1. Back to main menu " << endl << "0. Exit" << endl;
			cin >> restartTheGame;
			break;
		case 2:
			system("cls");
			cout << leadersName[0] << " " << leadersScore[0] << " score" << endl;
			cout << leadersName[1] << " " << leadersScore[1] << " score" << endl;
			cout << leadersName[2] << " " << leadersScore[2] << " score" << endl;
			system("pause");
			break;
		case 3:
			restartTheGame = false;

		}
	}

	return 0;
}