#include "pch.h"
#include "gm.h"
#pragma GCC optimize(2)
using namespace std;
extern HANDLE GM_HWND;
extern int NW_GAME;
extern int PID;
extern int ARR_NUM;
extern HWND WIND_HWND;
WCHAR OUT_TEXT[512];
extern int NORMAL_MOUSE_SPEED;
extern int SLOW_MOUSE_SPEED;
void setMouseSpeed()
{
	int k;
	if (GetAsyncKeyState(VK_LSHIFT))
	{
		k = SystemParametersInfo(SPI_SETMOUSESPEED, 0, (void*)SLOW_MOUSE_SPEED, SPIF_SENDCHANGE);
	}
	else
	{
		k = SystemParametersInfo(SPI_SETMOUSESPEED, 0, (void*)NORMAL_MOUSE_SPEED, SPIF_SENDCHANGE);
	}

}

int main()
{
	init();
	if (NORMAL_MOUSE_SPEED == -1)
	{
		MessageBox(NULL, OUT_TEXT, L"Failed to get mouse speed", MB_OK);
		return 0;
	}
	GetGame(GM_HWND, NW_GAME,PID, ARR_NUM);
	init2();
	if (GM_HWND != NULL)
	{
		wsprintf(OUT_TEXT,L"Process PID: %d\nGame ID: %d\nDefault mouse speed: %d\nClosing this program while holding SHIFT may result in your mouse speed setting being overwritten.\nIf that happens, you can set it back to the value you want in the control panel.", PID, Game::allGm[ARR_NUM].num,NORMAL_MOUSE_SPEED);
		MessageBox(NULL, OUT_TEXT, L"Load successful", MB_OK);
		Game& nwGame = Game::allGm[ARR_NUM];
		ios::sync_with_stdio(0);
		while (1){
			setMouseSpeed();
			switch (nwGame.MouseControl())
			{
			case PAUSE_FLAG:
				system("cls");
				cout << "Game paused";
				break;
			case NOT_IN_GAME_FLAG:
				system("cls");
				cout << "Failed to get player coordinates, the game is most likely in the main menu.\n";
				Sleep(16);
				break;
			default:
			case NORMAL_FLAG:
				break;
			}
		}
	}
}
