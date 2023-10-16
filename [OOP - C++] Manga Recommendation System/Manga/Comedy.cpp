#include "Comedy.h"
#include "Header.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
void Comedy::checkManga()
{
	string comedyString;
	fstream comedy("Comedy.txt");
	while (getline(comedy, comedyString))
	{
		for (int i = 0; i < 3; i++)                             // We know that we're inputting 3 strings into the vector
		{
			if (inputString[i] == comedyString)
			{
				counter++;
			}
		}
		// If the input strings aren't equal to the shounen names we have in our .txt file
		if (inputString[0] != comedyString && inputString[1] != comedyString && inputString[2] != comedyString)
		{
			others.push_back(comedyString);                  // Others contains all the vectors not being a part of the input String
			otherLines++;
		}
	}
}