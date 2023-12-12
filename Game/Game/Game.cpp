#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver, playerValueRecorded, playerInTopThree, fruitSpawned, restartTheGame = true, fruitSpawnedMys;
int width = 45;
int height = 20;
int x, y, fruitX, fruitY, mysteriosFruitX, mysteriosFruitY, score, choose, timeCounter, timeBeforeSpawn, variantMysteryFruit, increaseCounter, timeCounterMys;
string playerName;
int tailX[100], tailY[100];
int specialFruitX[2];
int specialFruitY[2];

int nTail = 0;
string startTheGame = "Start the game";
string gameEnd = "Game over";
int leadersScore[4];
string leadersName[4];
FILE* Lead;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;


void Setup() {
	srand(time(NULL));
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

	fruitX = rand() % (width - 1);
	fruitY = rand() % (height - 1);
	specialFruitX[0] = -10;
	specialFruitY[0] = -10;
	specialFruitX[1] = -10;
	specialFruitY[1] = -10;
	mysteriosFruitX = -10;
	mysteriosFruitY = -10;


	score = 0;
	cout << "Please enter your nickname" << endl;
	cin >> playerName;
}

bool FruitAtSnake() {
	if (fruitX == x && fruitY == y) {
		return true;
	}

	int i = 0;
	do {
		if (fruitX == tailX[i] && fruitY == tailY[i] || (tailX[i] == specialFruitX[0] && tailY[i] == specialFruitY[0] && tailX[i] == specialFruitX[1] && tailY[i] == specialFruitY[1])) {
			return true;
		}
		++i;
	} while (i < nTail);

	return false;
}

bool FruitAtFruit() {
	if (fruitX == specialFruitX[0] && fruitY == specialFruitY[0] && fruitX == specialFruitX[1] && fruitY == specialFruitY[1] && fruitX == specialFruitX[1] && fruitY == specialFruitY[0] && fruitX == specialFruitX[0] && fruitY == specialFruitY[1])
		return true;
	if (mysteriosFruitX == specialFruitX[0] && mysteriosFruitY == specialFruitY[0] && mysteriosFruitX == specialFruitX[1] && mysteriosFruitY == specialFruitY[1] && mysteriosFruitX == specialFruitX[1] && mysteriosFruitY == specialFruitY[0] && mysteriosFruitY == specialFruitX[0] && fruitY == specialFruitY[1])
		return true;
	if (fruitX == mysteriosFruitX && fruitY == mysteriosFruitY)
		return true;
	return false;
}

void FieldIncreaser() {
	if (increaseCounter >= 10) {
		width++;
		height++;
		increaseCounter -= 10;
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
				if (i == y && j == x)
					cout << "0";
				else if (i == fruitY && j == fruitX)
					cout << "F";
				else if (i == mysteriosFruitY && j == mysteriosFruitX)
					cout << "?";
				else if (i == specialFruitY[0] && j == specialFruitX[0] || i == specialFruitY[1] && j == specialFruitX[1] || i == specialFruitY[0] && j == specialFruitX[1] || i == specialFruitY[1] && j == specialFruitX[0])
					cout << "S";
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
			if (i == 5 && j > 16 && j < 26)
				cout << gameEnd[j - 17];
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

void FruitSpawn() {
	timeBeforeSpawn = (rand() % 10) + 30;

	if (!fruitSpawnedMys) {
		if (timeCounterMys >= timeBeforeSpawn + (rand() % 10)) {
			do {
				mysteriosFruitX = (rand() % (width - 1));
				mysteriosFruitY = (rand() % (width - 1));
			} while (FruitAtSnake() && FruitAtFruit());
			fruitSpawnedMys = true;
		}
	}
	if (timeCounterMys >= timeBeforeSpawn + 50 + (rand() % 50)) {
		mysteriosFruitX = -10;
		mysteriosFruitY = -10;
		fruitSpawnedMys = false;
		timeCounterMys = 0;
	}
	if (!fruitSpawned) {
		if (timeCounter >= timeBeforeSpawn) {
			do {
				specialFruitX[0] = (rand() % (width - 2) + 1);
				specialFruitY[0] = (rand() % (height - 2) + 1);
				specialFruitX[1] = specialFruitX[0] - 1;
				specialFruitY[1] = specialFruitY[0] - 1;
			} while (FruitAtSnake() && FruitAtFruit());
			fruitSpawned = true;
		}
	}
	if (timeCounter >= timeBeforeSpawn + 30 + (rand() % 50)) {
		specialFruitX[0] = -10;
		specialFruitY[0] = -10;
		specialFruitX[1] = -10;
		specialFruitY[1] = -10;
		fruitSpawned = false;
		timeCounter = 0;
	}
	timeCounter++;
	timeCounterMys++;
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
		x = 0;
	else if (x < 0)
		x = width - 2;
	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if (x == fruitX && y == fruitY) {
		score++;
		increaseCounter++;
		nTail++;
		do {
			fruitX = rand() % (width - 1);
			fruitY = rand() % (height - 1);
		} while (FruitAtSnake() && FruitAtFruit());
	}

	if (y == specialFruitY[0] && x == specialFruitX[0] || y == specialFruitY[1] && x == specialFruitX[1] || y == specialFruitY[0] && x == specialFruitX[1] || y == specialFruitY[1] && x == specialFruitX[0]) {
		score += 5;
		increaseCounter += 5;
		specialFruitX[0] = -10;
		specialFruitY[0] = -10;
		specialFruitX[1] = -10;
		specialFruitY[1] = -10;
	}
	if (y == mysteriosFruitY && x == mysteriosFruitX) {
		variantMysteryFruit = rand() % 3;
		switch (variantMysteryFruit) {
		case 0:
			score += 5;
			increaseCounter += 5;
			mysteriosFruitX = -10;
			mysteriosFruitY = -10;
			break;
		case 1:
			nTail++;
			score++;
			increaseCounter++;
			mysteriosFruitX = -10;
			mysteriosFruitY = -10;
			break;
		case 2:
			nTail--;
			score--;
			mysteriosFruitX = -10;
			mysteriosFruitY = -10;
			break;
		default:
			nTail += 100;
		}
	}
	FruitSpawn();
	FieldIncreaser();
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
			Draw();
			gameOver = false;
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
			DrawLeaderBoard();

			system("pause");
			break;
		case 3:
			system("cls");
			cout << "1. Borisov Nikita 1-9 PI\n";
			cout << "2. Darkovich Dinis 1-9 PI\n";
			cout << "3. Ermolenko Stanislave 1-9 PI\n";
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
		}
	}
	return 0;
}