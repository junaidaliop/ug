#include <iostream>
#include "Header.h"
#include "Input.h"
#include "Manga.h"
#include "Action.h"
#include "Romance.h"
#include "Comedy.h"
#include "Mystery.h"
#include "Fantasy.h"
#include <vector>
#include <string>
#include <algorithm>
#include <Windows.h>
using namespace std;
int main()
{
	Input I1;
	cout << "\n\n\t\t\tWelcome " << I1.getUser() << endl;
	cout << "\n\n\t\t\tPlease Enter your 3 FAVORITE mangas of all time" << endl;
	vector <string> Input;
	cout << "\n\t\t\t";
	for (int i = 0; i < 3; i++)
	{
		string f;
		getline(cin, f);
		bool checkEmpty = all_of(f.begin(), f.end(), isspace);
		try {
			if (f == "\0"||checkEmpty==true)
			{
				throw "\n\n\t\t\tAn Error occured with your string\n";
			}
		}
		catch (const char*e)
		{
			cout << e << endl;
			cout << "\n\t\t\tAn empty or white spaces only string was entered" << endl;
			cout << "\n\n\t\t\tEnter the name of manga again\n\n\t\t\t";
			getline(cin, f);
		}
		transform(f.begin(), f.end(), f.begin(), ::toupper);         // Capitalizes the input on its own.
		Input.push_back(f);
		cout << "\n\t\t\t";
	}
	I1.setVector(Input);
	I1.fileChecker();
	system("cls");
	const char* url = "https://www.crunchyroll.com/";
	cout << "\n************************************************************************************************************************" << endl;
	cout << "\n\t\t\t----------------------You entered the following mangas----------------------" << endl;
	I1.displayInput();
	cout << "\n\t\t\t----------------------The System Recommends you these-----------------------" << endl;
	I1.displayRecommendations();
	cout << "\n\t\t\t To Watch Your Favorite Anime or To Read your Favorite Manga" << endl;
	cout << "\n\t\t\t Visit " << url << endl;
	cout << "\n\t\t\t Use promo-code \"Ali Ahaha\" to get your first month premium subscription for free" << endl;
	cout << "\n\t\t\t This is the official website to watch animes and mangas for 9.95$ a month" << endl;
	// Opens crunchyroll.com
	wchar_t urlA[MAX_PATH];
	copy(url, url + lstrlenA(url) + 1, urlA);
	ShellExecuteW(NULL, L"open", urlA, NULL, NULL, SW_SHOW);
}