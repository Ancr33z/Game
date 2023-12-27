#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <windows.h>

#include "Header.h"

using namespace std;

bool gameOver, playerValueRecorded, playerInTopThree, fruitSpawned, restartTheGame = true, fruitSpawnedMys, fruitPlased, headPlased;
int width = 35;
int height = 15;
int x, y, score, choose, timeCounter, timeBeforeSpawn, variantMysteryFruit, increaseCounter, timeCounterMys, gameMode, fruitQuantity;
int fruit[20];
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

bool FruitAtSnake() {
	for (int i = 0; i < fruitQuantity * 2; i += 2) {
		if (fruit[i] == x && fruit[i + 1] == y) {
			return true;
		}
		int j = 0;
		do {
			if (fruit[i] == tailX[j] && fruit[i + 1] == tailY[j]) {
				return true;
			}
			++j;
		} while (j < nTail);
	}
	return false;
}

bool FruitAtFruit() {
	for (int i = 0; i < fruitQuantity * 2 - 2; i += 2) {
		for (int j = 0; j < fruitQuantity * 2 - 2; j += 2) {
			if (fruit[i] == fruit[i + 2] && fruit[i + 1] == fruit[i + 3])
				return true;
		}
	}
	return false;
}

void Setup() {
	srand(time(NULL));
	headPlased = false;
	fruitSpawned = false;
	fruitSpawnedMys = false;
	playerValueRecorded = true;
	playerInTopThree = false;
	gameOver = false;
	timeCounter = 0;
	timeCounterMys = 0;
	timeBeforeSpawn = 0;
	increaseCounter = 0;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	nTail = 0;
	fruitQuantity = 3;
	for (int i = 0; i < fruitQuantity * 2; i += 2) {
		fruit[i] = rand() % (width - 1);
		fruit[i + 1] = rand() % (height - 1);
		
	}
	for (int i = 0; i < fruitQuantity * 2; i += 2) {
		while (FruitAtSnake() && FruitAtFruit()) {
			fruit[i] = rand() % (width - 1);
			fruit[i + 1] = rand() % (height - 1);
		}
	}

	score = 0;
	cout << "Please enter your nickname" << endl;
	cin >> playerName;
}



void FieldDecreaser() {
	if (increaseCounter >= 5) {
		width--;
		height--;
		increaseCounter -= 5;
		fruitQuantity++;
		fruit[fruitQuantity*2-2] = rand() % (width - 2);
		fruit[fruitQuantity*2-1] = rand() % (height - 2);
	}
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

void ArraySort() {
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

				if (i == y && j == x) {
					cout << "0";
				}
				else
				{
					bool print = false;

					for (int k = 0; k < nTail; k++) {
						if (tailX[k] == j && tailY[k] == i) {
							print = true;
							cout << "o";
						}
					}

					for (int f = 0; f < fruitQuantity * 2; f += 2) {
						if (j == fruit[f] && i == fruit[f + 1]) {
							print = true;
							cout << "F";
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
					if (i == 5 && j > 10 && j < 25) {
						cout << startTheGame[j - 11];

					}
					else {
						if (!print && !headPlased) {
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
			if (i == 5 && j > 12 && j < 22)
				cout << gameEnd[j - 13];
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
	srand(time(NULL));
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
		gameOver = true;
	else if (x < 0)
		gameOver = true;
	if (y >= height)
		gameOver = true;
	else if (y < 0)
		gameOver = true;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	for (int i = 0; i < fruitQuantity * 2; i += 2) {
		if (x == fruit[i] && y == fruit[i + 1]) {
			score++;
			increaseCounter++;
			nTail++;
			do {
				fruit[i] = rand() % (width - 1);
				fruit[i + 1] = rand() % (height - 1);
			} while (FruitAtSnake() && FruitAtFruit());
		}
	}

	FieldDecreaser();
}


void LeaderBoardUpdate() {
	ArraySort();
	ofstream Lead;
	Lead.open("LeaderBoard.txt", ofstream::out);
	Lead.clear();
	for (int i = 0; i < 3; i++) {
		Lead << leadersName[i] << " " << leadersScore[i] << '\n';
	}
	Lead.close();
}
void DrawLeaderBoard() {
	cout << leadersName[0] << " " << leadersScore[0] << " score" << endl;
	cout << leadersName[1] << " " << leadersScore[1] << " score" << endl;
	cout << leadersName[2] << " " << leadersScore[2] << " score" << endl;
}

int main()
{
	GetLeaderBoard();

	while (restartTheGame) {

		system("cls");
		cout << "1. Play" << endl << "2. Leader board" << endl << "3. Developers" << endl << "4. How to play" << endl << "5. Exit" << endl;
		cin >> choose;

		switch (choose) {
		case 1:

			system("cls");
			Setup();
			system("cls");
			cout << playerName << " enter game mode: 1 - Hard mode, 2 - Easy mode\n\n";
			cout << "Hard mode is the mode when the playing field decreases when reaching 5 points, and which has only 3 normal fruits\n";
			cout << "Easy mode is when the field increases when you reach 10 points and there are 3 different fruits in this mode \n";
			cin >> gameMode;
			switch (gameMode)
			{
			case 1:			
				Draw();
				gameOver = false;
				while (!gameOver) {
					Draw();
					Input();
					Logic();
					Sleep(100 - 3 * nTail);
				}
				LeaderBoard();
				if (playerInTopThree)
					LeaderBoardUpdate();
				break;
			case 2:
				easyGameMode();
				break;
			default:
				break;
			}

			cout << endl << "1. Back to main menu " << endl << "0. Exit" << endl;
			cin >> restartTheGame;

			break;
		case 2:
			system("cls");
			DrawLeaderBoard();

			system("pause");
			break;
		case 3:
			system("cls");
			cout << "1. Borisov Nikita 1-9 PI\n";
			cout << "2. Darkovich Dinis 1-9 PI\n";
			cout << "3. Ermolenko Stanislav 1-9 PI\n";
			cout << "4. Volod'kov Dima 1-9 PI\n";
			cout << "5. Amanov Artur 1-9 PI\n\n";
			system("pause");
			break;
		case 4:
			system("cls");
			cout << "Use 'w', 'a', 's', 'd' to control your snake\n\n";
			cout << "'F' - usual fruit can give you +1 score +1 tail\n\n";
			cout << "'S' - special fruit can give you +5 score -1 tail and his size 2x2 unlike others\n\n";
			cout << "'?' - mysterios fruit can give you 1 of 3 bonuses: \n1. +1 tail +1 score \n2. -1 tail -1 score \n3. +5 score\n\n";

			system("pause");
			break;
		case 5:
			restartTheGame = false;
			break;
		default:
			break;
		}
	}
	return 0;
}