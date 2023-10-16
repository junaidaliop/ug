#include "Fantasy.h"
#include "Header.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
void Fantasy::checkManga()
{
	string fantasyString;
	fstream fantasy("Fantasy.txt");
	while (getline(fantasy, fantasyString))
	{
		for (int i = 0; i < 3; i++)                             // We know that we're inputting 3 strings into the vector
		{
			if (inputString[i] == fantasyString)
			{
				counter++;
			}
		}
		// If the input strings aren't equal to the shounen names we have in our .txt file
		if (inputString[0] != fantasyString && inputString[1] != fantasyString && inputString[2] != fantasyString)
		{
			others.push_back(fantasyString);                  // Others contains all the vectors not being a part of the input String
			otherLines++;
		}
	}
}