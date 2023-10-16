#include "Manga.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>
#include <stdexcept>
#include <string>
#include <windows.h>
#include "Header.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <windows.h>
int Manga::counter = 0;
int Manga::otherLines = 0;
void Manga::setVector(vector <string> input)
{
	inputString = input;
	if (correctPass == true) {
		fstream file;
		file.open(filename, ios::app);
		file << "\n\t\t\t You entered the following mangas" << endl;
		for (int i = 0; i < inputString.size(); i++)
		{
			file << "\n\t\t\t " <<inputString[i] << endl;
		}
	}
}
void Manga::displayInput()
{
	if (validInput == true)
	{
		vectorPr(inputString);
	}
	else
	{
		vectorPr(inputString);
		cout << "\n\t\t\tSome of the entries are invalid, we'll still recommend you some mangas.\n";
	}
}
void Manga::displayRecommendations()
{
	vectorPr(recommendation);
}
void Manga::counterCheck()
{
	// This randomly generates an anime/manga name depending on the counter from the same file.
	srand(time(NULL));
	if (otherLines > 0)
	{
		int Random = rand() % otherLines;
		if (counter > 0)
		{
			s1 = others[Random];
			recommendation.push_back(s1);
			if (counter == 2 || counter == 3)
			{
				Random = rand() % otherLines;
				while (others[Random] == s1)
				{
					Random = rand() % otherLines;
				}
				s2 = others[Random];
				recommendation.push_back(s2);
				Random = rand() % otherLines;
				while (others[Random] == s1 || others[Random] == s2)
				{
					Random = rand() % otherLines;
				}
				s3 = others[Random];
				recommendation.push_back(s3);
			}
		}
	}
}
string getpassword(const string& input = "Enter password: ")
{
	string passwordstring;

	// No echo, not line buffered input
	DWORD sade, no;
	HANDLE inputh = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE outputh = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleMode(inputh, &sade))
		throw runtime_error(
			"In order to use the program, connect to a console\n"
		);
	SetConsoleMode(inputh, sade & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
	WriteConsoleA(outputh, input.c_str(), input.length(), &no, NULL);
	char c;
	while (ReadConsoleA(inputh, &c, 1, &no, NULL) && (c != '\r') && (c != '\n'))
	{
		if (c == '\b')
		{
			if (passwordstring.length())
			{
				WriteConsoleA(outputh, "\b \b", 3, &no, NULL);
				passwordstring.erase(passwordstring.end() - 1);
			}
		}
		else
		{
			WriteConsoleA(outputh, "*", 1, &no, NULL);
			passwordstring.push_back(c);
		}
	}

	// Restoring Console Mode
	SetConsoleMode(inputh, sade);

	return passwordstring;
}
void Manga::setPass(string pass)
{
	password = pass;
}
string Manga::getUser()
{
	return username;
}
void Manga::setUser(string user)
{

	username = user;
}
string Manga::getPass()
{
	return password;
}
Manga::Manga()
{
	// We just get the user input and output in this case.
	string user;
	string pass1;
	string linee;
	cout << "********************************************************************************************************" << endl;
	cout << "*******************************Welcome to Manga Recommendation System***********************************" << endl;
	cout << "\n\n\t\t\tPlease enter username: ";
	getline(cin, user);
	bool checkEmpty = all_of(user.begin(), user.end(), isspace);
	try {
		if (user == "\0" || checkEmpty == true)
		{
			throw "\n\n\t\t\tError Caught: Empty or Blank UserName";
		}
	}
	catch (const char* e)
	{
		cout << e << endl;
		cout << "\n\n\t\t\tPlease re-enter username: ";
		getline(cin, user);
	}
	setUser(user);
	cout << "\n\n*******We have mailed you our encryption (password) key for using the recommendation system*************" << endl;
	pass1 = getpassword("\n\n\t\t\tPlease enter your password: ");
	cout << endl;
	setPass(pass1);
	filename = user + ".txt";
	txtfile = filename.c_str();                     // Conversion from string to const *char
	checkPass();
	// Loop to make sure the correct password is entered.
	while (correctPass == false)
	{
		cout << "\n\t\t\tForgot Password?" << endl;
		pass1 = getpassword("\n\n\t\t\tRe-enter your password : ");
		setPass(pass1);
		checkPass();
	}
	if (correctPass == true)
	{
		fstream file;
		file.open(filename, ios::app);
		file << "\n\t\t\t ******************** Welcome " << getUser() << "*********************" <<endl;
	}
}
void Manga::checkPass()
{
	// CorrectPass function checks whether the password is the same as the encrypted key we've given to the users.
	string line;
	fstream filed;
	filed.open("passwords.txt");
	while (getline(filed, line) && correctPass == false)
	{
		if (getPass() == line)
		{
			correctPass = true;
			break;
		}
		else
		{
			correctPass = false;
		}
	}
}
Manga::~Manga()
{
	// What our destructor does is. It'll firstly open the .txt file for that subsequent user name.
	// Also it google searches (usually using chrome or default browser) the recommended animes.
	wchar_t textfileopen[MAX_PATH];
	copy(txtfile, txtfile + lstrlenA(txtfile) + 1, textfileopen);
	ShellExecuteW(NULL, L"open", textfileopen, NULL, NULL, SW_SHOW);
	string googleSearch = "https://www.google.com/search?q=";
	for (int i = 0; i < recommendation.size(); i++)
	{
		string URL = googleSearch + recommendation[i];
		const char* url = URL.c_str();
		wchar_t urlGoogle[MAX_PATH];
		copy(url, url + lstrlenA(url) + 1, urlGoogle);
		ShellExecute(NULL, L"open", urlGoogle, NULL, NULL, SW_SHOW);
	}
}