#include <iostream>
#include <windows.h>
#include <unistd.h>

#include <cstdlib>
#include <ctime>

using namespace std;

const int width = 29;
const int height = 29;

int calGrid[width][height];
int disGrid[width][height];


int endSim = 0;

void ClearScreen(){	
	COORD cursorPosition;
	cursorPosition.X = 0;
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void drawGrid(){
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			if (disGrid[x][y] == 1){
				cout << "■ ";
			}else{
				cout <<"□ ";
			}
		}
		cout << endl;
	}
}

int sumCells(int x, int y){
	int cellNumber = 0;
	cellNumber =   (disGrid[x+1][y] + disGrid[x][y+1] +
					disGrid[x-1][y] + disGrid[x][y-1] +
					disGrid[x+1][y+1] + disGrid[x+1][y-1] +
					disGrid[x-1][y-1] + disGrid[x-1][y+1]);
	//cout << endl << cellNumber;
	return(cellNumber);
}

void checkCells(){
	for (int y = 1; y < height-1; y++){
	 	for (int x = 1; x < width-1; x++){
	 		if (disGrid[x][y] == 1){
	 			if (sumCells(x, y) == 3 || sumCells(x, y) == 2){
	 				calGrid[x][y] = 1;
	 			}else{
	 				calGrid[x][y] = 0;
	 			}
	 		}else{
	 			if (sumCells(x, y) == 3){
	 				calGrid[x][y] = 1;
	 			}
	 		}
	 	}
	 }

	for (int y = 1; y < height-1; y++){
		for (int x = 1; x < width-1; x++){
			disGrid[x][y] = calGrid[x][y];
		}
	}

	//if (sumCells(5, 5))
	//cout << sumCells(5, 5) << endl;
}

int main () {
	ShowConsoleCursor(false);
	SetConsoleOutputCP(CP_UTF8);

	srand(time(0));
	
	fill(calGrid[0] + 0, calGrid[0]+ (width*height), 0);

	// calGrid[4][5] = 1;
	// calGrid[5][5] = 1;
	// calGrid[6][5] = 1;
	// calGrid[5][4] = 1;

	for (int y = 1; y < height-1; y++){
		for(int x = 1; x < width-1; x++){
			int r;
			r = rand() % 11;

			if (r > 5){
				calGrid[x][y] = 1;
			}
		}
	}

	for (int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			disGrid[x][y] = calGrid[x][y];
		}
	}

	drawGrid();

	while (endSim != 1){
		usleep(5000);
		ClearScreen();

		checkCells();

		drawGrid();
	}
	return 0;
}