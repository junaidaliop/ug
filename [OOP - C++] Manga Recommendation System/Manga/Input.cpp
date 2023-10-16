#include "Input.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Header.h"
#include "Manga.h"
#include "Action.h"
#include "Romance.h"
#include "Comedy.h"
#include "Fantasy.h"
#include "Mystery.h"
#include <algorithm>
#include <time.h>
#include <stdlib.h>
using namespace std;
void Input::fileChecker()
{
	// Our file checker function works through every one of the .txt files and firstly finds the anime/manga names(if any) and then recommends them.
	Action::checkManga();
	Manga::counterCheck();
	counter = 0;
	Manga::others.clear();
	otherLines = 0;
	Romance::checkManga();
	Manga::counterCheck();
	counter = 0;
	Manga::others.clear();
	otherLines = 0;
	Comedy::checkManga();
	Manga::counterCheck();
	counter = 0;
	Manga::others.clear();
	otherLines = 0;
	Fantasy::checkManga();
	Manga::counterCheck();
	counter = 0;
	Manga::others.clear();
	otherLines = 0;
	Mystery::checkManga();
	Manga::counterCheck();
	counter = 0;
	Manga::others.clear();
	otherLines = 0;
	// If the counter hasn't yet reached the value 3. then we have not found 3 matching manga names
	// For then we say that the entered manga's are either correct or are not a part of our manga list
	// we recommend some of our favorite manga's under the "special.txt" file then.
	if (recommendation.size() < 3)
	{
		validInput = false;
		string specialS;
		fstream special;
		special.open("special.txt");
		// Counter = recommendation.size()-3;
		if (recommendation.size() == 2)
		{
			counter = 1;
		}
		if (recommendation.size() == 1 || recommendation.size() == 0)
		{
			counter = 3;
		}
		while (getline(special, specialS))
		{
			// Makes sure that the input is not added into the recommendations.
			if (inputString[0] != specialS && inputString[1] != specialS && inputString[2] != specialS)
			{
				switch (recommendation.size())
				{
					// This switch makes sure that the manga we're going to recommend isn't already recommended by us or entered by the user.
				case (0):
				{
					others.push_back(specialS);
					otherLines++;
					break;
				}
				case (1):
				{
					if (recommendation[0] != specialS)
					{
						others.push_back(specialS);
						otherLines++;
					}
					break;
				}
				case (2):
				{
						if (recommendation[0] != specialS && recommendation[1] != specialS)
						{
							others.push_back(specialS);
							otherLines++;
						}
						break;
					}
				}
			}
		}
		Manga::counterCheck();
	}
	// If the password is correct, the .txt file for that user name will get our recommendations in the input. otherwise it won't.
	if (correctPass == true) 
	{
		fstream file;
		file.open(filename, ios::app);
		file << "\n\t--------Our Manga Recommendation System is going to recommend you the following mangas.--------" << endl;
		file << "\n\t\t\t We Feel Like You Would Like These Mangas \t\t\t" << endl;
		for (int i = 0; i < recommendation.size(); i++)
		{
			file <<"\n\t\t\t " << recommendation[i] << endl;
		}
	}
}