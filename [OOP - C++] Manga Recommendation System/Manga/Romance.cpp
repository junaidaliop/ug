#include "Romance.h"
#include "Header.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
void Romance::checkManga()
{
	string shoujoString;
	fstream shoujo("Romance.txt");
	while (getline(shoujo, shoujoString))
	{
		for (int i = 0; i < 3; i++)                             // We know that we're inputting 3 strings into the vector
		{
			if (inputString[i] == shoujoString)
			{
				counter++;
			}
		}
		// If the input strings aren't equal to the shounen names we have in our .txt file
		if (inputString[0] != shoujoString && inputString[1] != shoujoString && inputString[2] != shoujoString)
		{
			others.push_back(shoujoString);                  // Others contains all the vectors not being a part of the input String
			otherLines++;
		}
	}
}