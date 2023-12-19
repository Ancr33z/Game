#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOverMode, playerValueRecordedMode, playerInTopThreeMode, fruitSpawnedMode, restartTheGameMode = true, fruitSpawnedMysMode;
int widthMode = 35;
int heightMode = 17;
int xMode, yMode, fruitXMode, fruitYMode, mysteriosFruitXMode, mysteriosFruitYMode, scoreMode, chooseMode, timeCounterMode, timeBeforeSpawnMode, variantMysteryFruitMode, increaseCounterMode, timeCounterMysMode, gameModeMode;
string playerNameMode;
int tailXMode[100], tailYMode[100];
int specialFruitXMode[2];
int specialFruitYMode[2];

int nTailMode = 0;
string startTheGameMode = "Start the game";
string gameEndMode = "Game over";
int leadersScoreMode[4];
string leadersNameMode[4];
FILE* LeadMode;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dirMode;

	void SetupMode() {
		srand(time(NULL));
		fruitSpawnedMode = false;
		fruitSpawnedMysMode = false;
		playerValueRecordedMode = true;
		playerInTopThreeMode = false;
		gameOverMode = false;
		timeCounterMode = 0;
		timeCounterMysMode = 0;
		timeBeforeSpawnMode = 0;
		increaseCounterMode = 0;
		dirMode = STOP;
		xMode = widthMode / 2 - 1;
		yMode = heightMode / 2 - 1;
		nTailMode = 0;
		fruitXMode = rand() % (widthMode - 1);
		fruitYMode = rand() % (heightMode - 1);
		specialFruitXMode[0] = -10;
		specialFruitYMode[0] = -10;
		specialFruitXMode[1] = -10;
		specialFruitYMode[1] = -10;
		mysteriosFruitXMode = -10;
		mysteriosFruitYMode = -10;


		scoreMode = 0;
	}

	bool FruitAtSnakeMode() {
		if (fruitXMode == xMode && fruitYMode == yMode) {
			return true;
		}

		int i = 0;
		do {
			if (fruitXMode == tailXMode[i] && fruitYMode == tailYMode[i] || (tailXMode[i] == specialFruitXMode[0] && tailYMode[i] == specialFruitYMode[0] && tailXMode[i] == specialFruitXMode[1] && tailYMode[i] == specialFruitYMode[1])) {
				return true;
			}
			++i;
		} while (i < nTailMode);

		return false;
	}

	bool FruitAtFruitMode() {
		if (fruitXMode == specialFruitXMode[0] && fruitYMode == specialFruitYMode[0] || fruitXMode == specialFruitXMode[1] && fruitYMode == specialFruitYMode[1] || fruitXMode == specialFruitXMode[1] && fruitYMode == specialFruitYMode[0] || fruitXMode == specialFruitXMode[0] && fruitYMode == specialFruitYMode[1])
			return true;
		if (mysteriosFruitXMode == specialFruitXMode[0] && mysteriosFruitYMode == specialFruitYMode[0] || mysteriosFruitXMode == specialFruitXMode[1] && mysteriosFruitYMode == specialFruitYMode[1] || mysteriosFruitXMode == specialFruitXMode[1] && mysteriosFruitYMode == specialFruitYMode[0] || mysteriosFruitYMode == specialFruitXMode[0] && fruitYMode == specialFruitYMode[1])
			return true;
		if (fruitXMode == mysteriosFruitXMode && fruitYMode == mysteriosFruitYMode)
			return true;

		return false;
	}

	void FieldIncreaserMode() {
		if (increaseCounterMode >= 10) {
			widthMode++;
			heightMode++;
			increaseCounterMode -= 10;
		}
	}

	void GetLeaderBoardMode() {
		ifstream Lead;
		Lead.open("LeaderBoard.txt");
		int i = 0;
		while (!Lead.eof()) {
			Lead >> leadersNameMode[i] >> leadersScoreMode[i];
			i++;
		}

		Lead.close();
	}

	void ArraySortMode() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4 - i; j++) {
				if (leadersScoreMode[j] < leadersScoreMode[j + 1]) {
					int temp = leadersScoreMode[j];
					leadersScoreMode[j] = leadersScoreMode[j + 1];
					leadersScoreMode[j + 1] = temp;
				}
			}
		}
		for (int i = 0; i < 3; i++) {
			if (playerValueRecordedMode) {
				if (leadersScoreMode[i] == scoreMode) {
					leadersNameMode[i] = playerNameMode;
					playerValueRecordedMode = false;
				}
			}
		}
	}

	void DrawMode() {
		system("cls");

		if (dirMode != 0) {
			for (int i = 0; i < widthMode + 1; i++)
				cout << "#";
			cout << endl;
			for (int i = 0; i < heightMode; i++) {
				for (int j = 0; j < widthMode; j++) {
					if ((j == 0) || (j == widthMode - 1))
						cout << "#";
					if (i == yMode && j == xMode)
						cout << "0";
					else if (i == fruitYMode && j == fruitXMode)
						cout << "F";
					else if (i == mysteriosFruitYMode && j == mysteriosFruitXMode)
						cout << "?";
					else if (i == specialFruitYMode[0] && j == specialFruitXMode[0] || i == specialFruitYMode[1] && j == specialFruitXMode[1] || i == specialFruitYMode[0] && j == specialFruitXMode[1] || i == specialFruitYMode[1] && j == specialFruitXMode[0])
						cout << "S";
					else {
						bool print = false;
						for (int k = 0; k < nTailMode; k++) {
							if (tailXMode[k] == j && tailYMode[k] == i) {
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
			for (int i = 0; i < widthMode + 1; i++)
				cout << "#";
			cout << endl;
			for (int i = 0; i < heightMode; i++) {
				for (int j = 0; j < widthMode; j++) {
					if ((j == 0) || (j == widthMode - 1))
						cout << "#";
					if (i == yMode && j == xMode)
						cout << "0";
					else {
						bool print = false;
						for (int k = 0; k < nTailMode; k++) {
							if (tailXMode[k] == j && tailYMode[k] == i) {
								print = true;
								cout << "o";
							}
						}
						if (i == 5 && j > 14 && j < 29) {
							cout << startTheGameMode[j - 15];

						}
						else {
							if (!print) {
								cout << " ";
								print = false;
							}
						}
					}
					if (i == 7 && j == widthMode) {

					}
				}
				cout << endl;
			}
		}

		for (int i = 0; i < widthMode + 1; i++)
			cout << "#";
		cout << endl;
		cout << "Score: " << scoreMode << endl;
	}

	void LeaderBoardMode() {
		system("cls");

		for (int i = 0; i < widthMode + 1; i++)
			cout << "#";
		cout << endl;
		for (int i = 0; i < heightMode; i++) {
			for (int j = 0; j < widthMode; j++) {

				if ((j == 0) || (j == widthMode - 1))
					cout << "#";
				if (i == 5 && j > 16 && j < 26)
					cout << gameEndMode[j - 17];
				else if (i == yMode && j == xMode)
					cout << "0";
				else {
					bool print = false;
					for (int k = 0; k < nTailMode; k++) {
						if (tailXMode[k] == j && tailYMode[k] == i) {
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
		for (int i = 0; i < widthMode + 1; i++)
			cout << "#";

		leadersScoreMode[3] = scoreMode;
		if (leadersScoreMode[3] > leadersScoreMode[0] || leadersScoreMode[3] > leadersScoreMode[1] || leadersScoreMode[3] > leadersScoreMode[2]) {
			cout << endl << playerNameMode << " You are in top 3" << endl;
			playerInTopThreeMode = true;
		}

		cout << endl;
		cout << "Score: " << scoreMode << endl;

	}

	void FruitSpawnMode() {
		timeBeforeSpawnMode = (rand() % 10) + 30;

		if (!fruitSpawnedMysMode) {
			if (timeCounterMysMode >= timeBeforeSpawnMode + (rand() % 10)) {
				do {
					mysteriosFruitXMode = (rand() % (widthMode - 1));
					mysteriosFruitYMode = (rand() % (widthMode - 1));
				} while (FruitAtSnakeMode() && FruitAtFruitMode());
				fruitSpawnedMysMode = true;
			}
		}
		if (timeCounterMysMode >= timeBeforeSpawnMode + 50 + (rand() % 50)) {
			mysteriosFruitXMode = -10;
			mysteriosFruitYMode = -10;
			fruitSpawnedMysMode = false;
			timeCounterMysMode = 0;
		}
		if (!fruitSpawnedMode) {
			if (timeCounterMode >= timeBeforeSpawnMode) {
				do {
					specialFruitXMode[0] = (rand() % (widthMode - 2) + 1);
					specialFruitYMode[0] = (rand() % (heightMode - 2) + 1);
					specialFruitXMode[1] = specialFruitXMode[0] - 1;
					specialFruitYMode[1] = specialFruitYMode[0] - 1;
				} while (FruitAtSnakeMode() && FruitAtFruitMode());
				fruitSpawnedMode = true;
			}
		}
		if (timeCounterMode >= timeBeforeSpawnMode + 30 + (rand() % 50)) {
			specialFruitXMode[0] = -10;
			specialFruitYMode[0] = -10;
			specialFruitXMode[1] = -10;
			specialFruitYMode[1] = -10;
			fruitSpawnedMode = false;
			timeCounterMode = 0;
		}
		timeCounterMode++;
		timeCounterMysMode++;
	}


	void InputMode() {
		if (_kbhit()) {
			switch (_getch())
			{
			case 'a':
				if (dirMode != RIGHT) {
					dirMode = LEFT;
				}
				break;
			case 'd':
				if (dirMode != LEFT) {
					dirMode = RIGHT;
				}
				break;
			case 'w':
				if (dirMode != DOWN) {
					dirMode = UP;
				}
				break;
			case 's':
				if (dirMode != UP) {
					dirMode = DOWN;
				}
				break;
			case 'x':
				gameOverMode = true;
				break;
			}

		}
	}

	void LogicMode() {
		srand(time(NULL));
		int prevX = tailXMode[0];
		int prevY = tailYMode[0];
		tailXMode[0] = xMode;
		tailYMode[0] = yMode;
		int prev2X, prev2Y;

		for (int i = 1; i < nTailMode; i++) {
			prev2X = tailXMode[i];
			prev2Y = tailYMode[i];
			tailXMode[i] = prevX;
			tailYMode[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}

		switch (dirMode) {
		case LEFT:
			xMode--;
			break;
		case RIGHT:
			xMode++;
			break;
		case UP:
			yMode--;
			break;
		case DOWN:
			yMode++;
			break;
		}

		if (xMode >= widthMode - 1)
			xMode = 0;
		else if (xMode < 0)
			xMode = widthMode - 2;
		if (yMode >= heightMode)
			yMode = 0;
		else if (yMode < 0)
			yMode = heightMode;

		for (int i = 0; i < nTailMode; i++) {
			if (tailXMode[i] == xMode && tailYMode[i] == yMode)
				gameOverMode = true;
		}

		if (xMode == fruitXMode && yMode == fruitYMode) {
			scoreMode++;
			increaseCounterMode++;
			nTailMode++;
			do {
				fruitXMode = rand() % (widthMode - 2);
				fruitYMode = rand() % (heightMode - 2);
			} while (FruitAtSnakeMode() && FruitAtFruitMode());
		}

		if (yMode == specialFruitYMode[0] && xMode == specialFruitXMode[0] || yMode == specialFruitYMode[1] && xMode == specialFruitXMode[1] || yMode == specialFruitYMode[0] && xMode == specialFruitXMode[1] || yMode == specialFruitYMode[1] && xMode == specialFruitXMode[0]) {
			scoreMode += 5;
			increaseCounterMode += 5;
			specialFruitXMode[0] = -10;
			specialFruitYMode[0] = -10;
			specialFruitXMode[1] = -10;
			specialFruitYMode[1] = -10;
		}
		if (yMode == mysteriosFruitYMode && xMode == mysteriosFruitXMode) {
			variantMysteryFruitMode = rand() % 3;
			switch (variantMysteryFruitMode) {
			case 0:
				scoreMode += 5;
				increaseCounterMode += 5;
				mysteriosFruitXMode = -10;
				mysteriosFruitYMode = -10;
				break;
			case 1:
				nTailMode++;
				scoreMode++;
				increaseCounterMode++;
				mysteriosFruitXMode = -10;
				mysteriosFruitYMode = -10;
				break;
			case 2:
				nTailMode--;
				scoreMode--;
				mysteriosFruitXMode = -10;
				mysteriosFruitYMode = -10;
				break;
			default:
				nTailMode += 100;
			}
		}
		FruitSpawnMode();
		FieldIncreaserMode();
	}


	void LeaderBoardUpdateMode() {
		ArraySortMode();
		ofstream Lead;
		Lead.open("LeaderBoard.txt", ofstream::out);
		Lead.clear();
		for (int i = 0; i < 3; i++) {
			Lead << leadersNameMode[i] << " " << leadersScoreMode[i] << '\n';
		}
		Lead.close();
	}
	void DrawLeaderBoardMode() {
		cout << leadersNameMode[0] << " " << leadersScoreMode[0] << " score" << endl;
		cout << leadersNameMode[1] << " " << leadersScoreMode[1] << " score" << endl;
		cout << leadersNameMode[2] << " " << leadersScoreMode[2] << " score" << endl;
	}

	void easyGameMode()
	{
		GetLeaderBoardMode();

		while (restartTheGameMode) {
			system("cls");
			SetupMode();
			DrawMode();
			gameOverMode = false;
			while (!gameOverMode) {
				DrawMode();
				InputMode();
				LogicMode();
				Sleep(100 - 3 * nTailMode);
			}
			LeaderBoardMode();
			if (playerInTopThreeMode)
				LeaderBoardUpdateMode();
			break;

		}
	}
