#pragma once

#include<algorithm>

class Initialization
{
private:
	void InitialALLCombo(HWND hwnd)
	{
		// «аполн€ем выпадающий список с режимом игры
		hGameType = GetDlgItem(hwnd, IDC_GAMETYPE);
		for (size_t i = 0; i < ElementsComboGameType.size(); i++)
		{
			SendMessage(hGameType, CB_ADDSTRING, 0, (LPARAM)ElementsComboGameType[i]);
		}
		// «аполн€ем выпадающий список с уровнем сложности
		hDiffLevel = GetDlgItem(hwnd, IDC_DIFLEVEL);
		for (size_t i = 0; i < ElementsComboDiffLevel.size(); i++)
		{
			SendMessage(hDiffLevel, CB_ADDSTRING, 0, (LPARAM)ElementsComboDiffLevel[i]);
		}
	}

	void InitialWindowsText(HWND hwnd)
	{
		for (size_t i = 0; i < hIDEDIT.size() && i<IDWindows.size(); i++)
		{
			for (size_t j = 0; j < IDWindows[i].size(); j++)
			{
				back_inserter(hIDEDIT[i]) = GetDlgItem(hwnd, IDWindows[i][j]);
			}
		}
	}

	void InitialAllButtonAndText(HWND hwnd)
	{
		hIDSTART = GetDlgItem(hwnd, IDSTART);
		hIDHELP = GetDlgItem(hwnd, IDHELP);
		hIDC_DIFLEVEL = GetDlgItem(hwnd, IDC_DIFLEVEL);
		hIDC_STATIC3 = GetDlgItem(hwnd, IDC_STATIC3);
		hID_BACK = GetDlgItem(hwnd, IDBACK);
		hID_PIC = GetDlgItem(hwnd, ID_PIC);
		ShowWindow(hID_BACK, SW_HIDE);
		ShowWindow(hIDC_STATIC3, SW_HIDE);
		ShowWindow(hIDC_DIFLEVEL, SW_HIDE);
		ShowWindow(hIDSTART, SW_HIDE);
		ShowWindow(hIDHELP, SW_HIDE);

	}

	void InitialIcon(HWND hwnd)
	{
		hIcon1 = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(MAIN_ICON));
		SendMessage(hwnd, WM_SETICON, 1, (LPARAM)hIcon1);
		
	}


	void InitialFont()
	{
		hFont = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS, "Arial");
	}


public:

void Initial(HWND hwnd)
	{
	InitialALLCombo(hwnd);
	InitialWindowsText(hwnd);
	InitialAllButtonAndText(hwnd);
	InitialIcon(hwnd);
	InitialFont();
	
	}

void ShowHiddenButton()
{
	if (selectGameType == 0)
	{
		
		ShowWindow(hID_BACK, SW_SHOW);
		ShowWindow(hIDC_STATIC3, SW_SHOW);
		ShowWindow(hIDSTART, SW_SHOW);
		ShowWindow(hIDHELP, SW_SHOW);
		ShowWindow(hIDC_DIFLEVEL, SW_SHOW);
	}
	
}

void DrawImageAndFont(HWND hwnd)
{
	hdc = BeginPaint(hPic, &ps);
	hdcMem = CreateCompatibleDC(hdc);
	hbmOld = SelectObject(hdcMem, hBitmap);
	GetObject(hBitmap, sizeof(bm), &bm);
	BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
	EndPaint(hPic, &ps);
	for (size_t i = 0; i < hIDEDIT.size() && i<IDWindows.size(); i++)
	{
		for (size_t j = 0; j < IDWindows[i].size(); j++)
		{
			SendDlgItemMessage(hwnd, IDWindows[i][j], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		}
	}
}


void ExitWindow(HWND hwnd,INT_PTR nRezult)
{
	EndDialog(hwnd, nRezult);

}


};

