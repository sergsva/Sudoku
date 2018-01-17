#include <Windows.h>
#include <WinUser.h>
#include "resource.h"
#include<vector>
#include<list>
#include<stack>
#include<iterator>
#include<algorithm>
#include<iostream>
#include<string>
#include<map>
#include<iomanip>
#include<stack>
#include<ostream>
using namespace std;

#include"MyFun.h"

vector<vector<HWND>> hIDEDIT{ 9 };
vector<vector<string>> ValueFromField{ 9, vector<string>(9, "") };
vector<vector<size_t>> IDWindows = {
	{ IDEDIT_0_0, IDEDIT_0_1, IDEDIT_0_2, IDEDIT_0_3, IDEDIT_0_4, IDEDIT_0_5, IDEDIT_0_6, IDEDIT_0_7, IDEDIT_0_8 },
	{ IDEDIT_1_0, IDEDIT_1_1, IDEDIT_1_2, IDEDIT_1_3, IDEDIT_1_4, IDEDIT_1_5, IDEDIT_1_6, IDEDIT_1_7, IDEDIT_1_8 },
	{ IDEDIT_2_0, IDEDIT_2_1, IDEDIT_2_2, IDEDIT_2_3, IDEDIT_2_4, IDEDIT_2_5, IDEDIT_2_6, IDEDIT_2_7, IDEDIT_2_8 },
	{ IDEDIT_3_0, IDEDIT_3_1, IDEDIT_3_2, IDEDIT_3_3, IDEDIT_3_4, IDEDIT_3_5, IDEDIT_3_6, IDEDIT_3_7, IDEDIT_3_8 },
	{ IDEDIT_4_0, IDEDIT_4_1, IDEDIT_4_2, IDEDIT_4_3, IDEDIT_4_4, IDEDIT_4_5, IDEDIT_4_6, IDEDIT_4_7, IDEDIT_4_8 },
	{ IDEDIT_5_0, IDEDIT_5_1, IDEDIT_5_2, IDEDIT_5_3, IDEDIT_5_4, IDEDIT_5_5, IDEDIT_5_6, IDEDIT_5_7, IDEDIT_5_8 },
	{ IDEDIT_6_0, IDEDIT_6_1, IDEDIT_6_2, IDEDIT_6_3, IDEDIT_6_4, IDEDIT_6_5, IDEDIT_6_6, IDEDIT_6_7, IDEDIT_6_8 },
	{ IDEDIT_7_0, IDEDIT_7_1, IDEDIT_7_2, IDEDIT_7_3, IDEDIT_7_4, IDEDIT_7_5, IDEDIT_7_6, IDEDIT_7_7, IDEDIT_7_8 },
	{ IDEDIT_8_0, IDEDIT_8_1, IDEDIT_8_2, IDEDIT_8_3, IDEDIT_8_4, IDEDIT_8_5, IDEDIT_8_6, IDEDIT_8_7, IDEDIT_8_8 } };
HWND hGameType, hDiffLevel, hIDSTART, hIDHELP, hIDC_DIFLEVEL, hIDC_STATIC3, hID_BACK, hID_PIC, hPic;
HICON hIcon1;
HINSTANCE hInst;
HBITMAP hBitmap;
int selectGameType = -1, selectDiffLevel = -1, enteredStart = 0, enteredReset = 0;
vector<CHAR*> ElementsComboGameType = { "Игра", "Просмотр решения" };
vector<CHAR*>ElementsComboDiffLevel = { "Легкий", "Средний", "Тяжелый" };
size_t token = 0;
BITMAP bm;
PAINTSTRUCT ps;
HDC hdc, hdcMem;
HGDIOBJ hbmOld;
HFONT hFont;

#pragma once

#include<algorithm>

#include"Initialization.h"
#include"CreateGameField.h"
#include"InputValidation.h"
#include"ViewSolution.h"
ViewSolution newgame2;
#include"SimplyGame.h"
SimplyGame newgame;
#include"WorkWithWindow.h"

Initialization Init;


BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPevInstance, LPSTR lpCmdLine, int nCmdShow)//
{
	srand(static_cast<int>(time(NULL)));
	hInst = hInstance;

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DlgProc), 0);
}


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch (uMsg)
	{
	case WM_INITDIALOG:
		hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		hPic = GetDlgItem(hwnd, ID_PIC);
		Init.Initial(hwnd);
		
	break;

	case WM_PAINT:
		
		Init.DrawImageAndFont(hwnd);
		
		break;
	case WM_CTLCOLOREDIT:
		CHAR temp[256];

		for (size_t i = 0; i < hIDEDIT.size() && i<IDWindows.size(); i++)
		{
			for (size_t j = 0; j < IDWindows[i].size(); j++)
			{
				SendMessage(hIDEDIT[i][j], WM_GETTEXT, (WPARAM)255, (LPARAM)temp);
				if ((HWND)lParam == GetDlgItem(hwnd, IDWindows[i][j]) && atoi(temp)>0 && atoi(temp) < 10)
				{

					SetBkColor((HDC)wParam, RGB(135, 206, 250));
					SetTextColor((HDC)wParam, RGB(0, 0, 205));
					return (BOOL)CreateSolidBrush(GetSysColor(COLOR_MENU));
				}
			}
		}
		break;

	case WM_COMMAND:
	{
		 Init.ShowHiddenButton();
		
		switch (LOWORD(wParam))
		{

	//Определяем какой выбрали игровой режим			
		case IDC_GAMETYPE:
		{
	if (HIWORD(wParam)==CBN_SELENDOK)
			{

				selectGameType = SendMessage(hGameType, CB_GETCURSEL, 0, 0);
				if (selectGameType == 0)
				{
					newgame.Start();
				}

				if (selectGameType == 1)
				{
					MessageBox(hwnd, "Установите значения ячеек вручную для вывода решения!", "Информация", MB_OK | MB_ICONINFORMATION);
					WorkWithWindow::ResetGameField();
					ShowWindow(hIDC_STATIC3, SW_HIDE);
					ShowWindow(hIDC_DIFLEVEL, SW_HIDE);
					ShowWindow(hIDSTART, SW_HIDE);
					ShowWindow(hIDHELP, SW_HIDE);
					ShowWindow(hID_BACK, SW_HIDE);

				}
			}
			
		}
		break;

//Определяем какой выбрали уровень сложности
		case IDC_DIFLEVEL:
		{
			if (HIWORD(wParam) == CBN_SELENDOK)
			 {
				 selectDiffLevel = SendMessage(hDiffLevel, CB_GETCURSEL, 0, 0);
			 }
		}
		break;

//Нажатие кнопки Начать
		case IDSTART:
			if (selectDiffLevel == -1)
				{
					MessageBox(hwnd, "Вы не выбрали уровень сложности!", "Информация", MB_OK | MB_ICONINFORMATION);
				}
				else
				{
					++enteredStart;
					enteredReset = 0;
					newgame.StackClear();
					token++;
					newgame.SetDiffLevel(selectDiffLevel);
					newgame.GeneratorFullField();
					newgame.PrepareField();
					WorkWithWindow::EnterInField(newgame.GetGameField());
					token--;
				}	
		break;

//Нажатие кнопки Подсказка
		case IDHELP:
			
			if (selectDiffLevel >= 0 && enteredStart>0 && enteredReset == 0)
			{
				token++;
				if (newgame2.GetCountFillCell(ValueFromField) != 0)
				{
					CoordinateAndValue Temp = newgame.HelpOneCell();
					SendMessage(hIDEDIT[Temp.i][Temp.j], WM_SETTEXT, 0, (LPARAM)Temp.value.c_str());
				}		
				token--;
			}
		break;

//Нажатие кнопки Сброс
		case IDRESET:
		MessageBox(hwnd, "Выполняется сброс значений игрового поля", "Information", MB_OK | MB_ICONINFORMATION);
		WorkWithWindow::ResetGameField();
			enteredReset++;
		break;

//Нажатие кнопки Шаг назад
		case IDBACK:
			if (!newgame.ProgressIsEmpty())
			{
				CoordinateAndValue Step = newgame.StepToBack();
				ValueFromField[Step.i][Step.j] = "";
				SendMessage(hIDEDIT[Step.i][Step.j], WM_SETTEXT, 0, (LPARAM)ValueFromField[Step.i][Step.j].c_str());
			}	
			break;

//Нажатие кнопки Решение
		case IDSOLUTION:
			switch (selectGameType)
			{
			case -1:
				MessageBox(hwnd, "Вы не выбрали игровой режим!", "Информация", MB_OK | MB_ICONINFORMATION);
				break;
			case 0:
				if (selectDiffLevel != -1)
				{
					if (enteredStart>0 && enteredReset == 0)
					{
						token++;
						WorkWithWindow::EnterInField(newgame.ReadSolution());
						token--;
					}
					
				}
				else
				{
					MessageBox(hwnd, "Вы не выбрали уровень сложности!", "Информация", MB_OK | MB_ICONINFORMATION);
				}
				
				break;

			case 1:
					token++;
					newgame2.GetSolution(ValueFromField);
					WorkWithWindow::EnterInField(ValueFromField);
					token--;
					if (newgame2.GetCountFillCell(ValueFromField) != 0)
					{
						MessageBox(hwnd, "Решение не найдено! Введите больше значений!", "Информация", MB_OK | MB_ICONINFORMATION);
					}		
					hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
					hPic = GetDlgItem(hwnd, ID_PIC);
				break;
			}
		break;


//Выход из игры нажатием на кнопку Выход		
		case IDCANCEL:
			Init.ExitWindow(hwnd, 0);
			break;

//Обработка окон ввода
		case IDEDIT_0_0:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(0, 0, hwnd, token);
						   }

		}
			break;
		case IDEDIT_0_1:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(0, 1, hwnd, token);
						   }

		}
			break;
		case IDEDIT_0_2:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(0, 2, hwnd, token);
						   }

		}
			break;
		case IDEDIT_0_3:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(0, 3, hwnd, token);
						   }

		}
			break;
		case IDEDIT_0_4:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(0, 4, hwnd, token);
						   }

		}
			break;
		case IDEDIT_0_5:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(0, 5, hwnd, token);
						   }

		}
			break;
		case IDEDIT_0_6:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(0, 6, hwnd, token);
						   }

		}
			break;
		case IDEDIT_0_7:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(0, 7, hwnd, token);
						   }

		}
			break;
		case IDEDIT_0_8:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(0, 8, hwnd, token);
						   }

		}
			break;
		case IDEDIT_1_0:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(1, 0, hwnd, token);
						   }

		}
			break;
		case IDEDIT_1_1:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(1, 1, hwnd, token);
						   }

		}
			break;
		case IDEDIT_1_2:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(1, 2, hwnd, token);
						   }

		}
			break;
		case IDEDIT_1_3:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(1, 3, hwnd, token);
						   }

		}
			break;
		case IDEDIT_1_4:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(1, 4, hwnd, token);
						   }

		}
			break;
		case IDEDIT_1_5:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(1, 5, hwnd, token);
						   }

		}
			break;
		case IDEDIT_1_6:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(1, 6, hwnd, token);
						   }

		}
			break;
		case IDEDIT_1_7:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(1, 7, hwnd, token);
						   }

		}
			break;
		case IDEDIT_1_8:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(1, 8, hwnd, token);
						   }

		}
			break;
		case IDEDIT_2_0:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(2, 0, hwnd, token);
						   }

		}
			break;
		case IDEDIT_2_1:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(2, 1, hwnd, token);
						   }

		}
			break;
		case IDEDIT_2_2:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(2, 2, hwnd, token);
						   }

		}
			break;
		case IDEDIT_2_3:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(2, 3, hwnd, token);
						   }

		}
			break;
		case IDEDIT_2_4:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(2, 4, hwnd, token);
						   }

		}
			break;
		case IDEDIT_2_5:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(2, 5, hwnd, token);
						   }

		}
			break;
		case IDEDIT_2_6:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(2, 6, hwnd, token);
						   }

		}
			break;
		case IDEDIT_2_7:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(2, 7, hwnd, token);
						   }

		}
			break;
		case IDEDIT_2_8:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(2, 8, hwnd, token);
						   }

		}
			break;
		case IDEDIT_3_0:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(3, 0, hwnd, token);
						   }

		}
			break;
		case IDEDIT_3_1:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(3, 1, hwnd, token);
						   }

		}
			break;
		case IDEDIT_3_2:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(3, 2, hwnd, token);
						   }

		}
			break;
		case IDEDIT_3_3:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(3, 3, hwnd, token);
						   }

		}
			break;
		case IDEDIT_3_4:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(3, 4, hwnd, token);
						   }

		}
			break;
		case IDEDIT_3_5:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(3, 5, hwnd, token);
						   }

		}
			break;
		case IDEDIT_3_6:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(3, 6, hwnd, token);
						   }

		}
			break;
		case IDEDIT_3_7:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(3, 7, hwnd, token);
						   }

		}
			break;
		case IDEDIT_3_8:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(3, 8, hwnd, token);
						   }

		}
			break;
		case IDEDIT_4_0:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(4, 0, hwnd, token);
						   }

		}
			break;
		case IDEDIT_4_1:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(4, 1, hwnd, token);
						   }

		}
			break;
		case IDEDIT_4_2:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(4, 2, hwnd, token);
						   }

		}
			break;
		case IDEDIT_4_3:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(4, 3, hwnd, token);
						   }

		}
			break;
		case IDEDIT_4_4:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(4, 4, hwnd, token);
						   }

		}
			break;
		case IDEDIT_4_5:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(4, 5, hwnd, token);
						   }

		}
			break;
		case IDEDIT_4_6:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(4, 6, hwnd, token);
						   }

		}
			break;
		case IDEDIT_4_7:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(4, 7, hwnd, token);
						   }

		}
			break;
		case IDEDIT_4_8:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(4, 8, hwnd, token);
						   }

		}
			break;
		case IDEDIT_5_0:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(5, 0, hwnd, token);
						   }

		}
			break;
		case IDEDIT_5_1:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(5, 1, hwnd, token);
						   }

		}
			break;
		case IDEDIT_5_2:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(5, 2, hwnd, token);
						   }

		}
			break;
		case IDEDIT_5_3:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(5, 3, hwnd, token);
						   }

		}
			break;
		case IDEDIT_5_4:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(5, 4, hwnd, token);
						   }

		}
			break;
		case IDEDIT_5_5:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(5, 5, hwnd, token);
						   }

		}
			break;
		case IDEDIT_5_6:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(5, 6, hwnd, token);
						   }

		}
			break;
		case IDEDIT_5_7:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(5, 7, hwnd, token);
						   }

		}
			break;
		case IDEDIT_5_8:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(5, 8, hwnd, token);
						   }

		}
			break;
		case IDEDIT_6_0:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(6, 0, hwnd, token);
						   }

		}
			break;
		case IDEDIT_6_1:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(6, 1, hwnd, token);
						   }

		}
			break;
		case IDEDIT_6_2:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(6, 2, hwnd, token);
						   }

		}
			break;
		case IDEDIT_6_3:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(6, 3, hwnd, token);
						   }

		}
			break;
		case IDEDIT_6_4:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(6, 4, hwnd, token);
						   }

		}
			break;
		case IDEDIT_6_5:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(6, 5, hwnd, token);
						   }

		}
			break;
		case IDEDIT_6_6:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(6, 6, hwnd, token);
						   }

		}
			break;
		case IDEDIT_6_7:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(6, 7, hwnd, token);
						   }

		}
			break;
		case IDEDIT_6_8:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(6, 8, hwnd, token);
						   }

		}
			break;
		case IDEDIT_7_0:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(7, 0, hwnd, token);
						   }

		}
			break;
		case IDEDIT_7_1:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(7, 1, hwnd, token);
						   }

		}
			break;
		case IDEDIT_7_2:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(7, 2, hwnd, token);
						   }

		}
			break;
		case IDEDIT_7_3:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(7, 3, hwnd, token);
						   }

		}
			break;
		case IDEDIT_7_4:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(7, 4, hwnd, token);
						   }

		}
			break;
		case IDEDIT_7_5:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(7, 5, hwnd, token);
						   }

		}
			break;
		case IDEDIT_7_6:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(7, 6, hwnd, token);
						   }

		}
			break;
		case IDEDIT_7_7:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(7, 7, hwnd, token);
						   }

		}
			break;
		case IDEDIT_7_8:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(7, 8, hwnd, token);
						   }

		}
			break;
		case IDEDIT_8_0:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(8, 0, hwnd, token);
						   }

		}
			break;
		case IDEDIT_8_1:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(8, 1, hwnd, token);
						   }

		}
			break;
		case IDEDIT_8_2:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(8, 2, hwnd, token);
						   }

		}
			break;
		case IDEDIT_8_3:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(8, 3, hwnd, token);
						   }

		}
			break;
		case IDEDIT_8_4:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(8, 4, hwnd, token);
						   }

		}
			break;
		case IDEDIT_8_5:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(8, 5, hwnd, token);
						   }

		}
			break;
		case IDEDIT_8_6:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(8, 6, hwnd, token);
						   }

		}
			break;
		case IDEDIT_8_7:
		{
						   if (token == 0)
						   {
							   ++token;
							   WorkWithWindow::ProccesingInputText(8, 7, hwnd, token);
						   }

		}
			break;
		case IDEDIT_8_8:
		{
			   if (token == 0)
			   {
			   ++token;
			   WorkWithWindow::ProccesingInputText(8, 8, hwnd, token);
		  }

		}
			break;

		}
	}
	break;

	
//Выход из игры нажатием на крестик		
	case WM_CLOSE:
		Init.ExitWindow(hwnd, 0);
		return FALSE;
	}

	return FALSE;
}