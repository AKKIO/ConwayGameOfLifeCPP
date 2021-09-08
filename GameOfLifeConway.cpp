#include <iostream>
#include <windows.h>
#include <unistd.h>

using namespace std;

const int width = 11;
const int height = 11;

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


int main () {
	ShowConsoleCursor(false);
	SetConsoleOutputCP(CP_UTF8);
	
	fill(disGrid[0] + 0, disGrid[0]+ (width*height), 0);

	drawGrid();
	ClearScreen();

	while (endSim != 1){
		disGrid[width/2][width/2] = !disGrid[width/2][width/2];
		drawGrid();


		ClearScreen();
		usleep(200000);

	}
}
//save