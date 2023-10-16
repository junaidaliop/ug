#include "Action.h"
#include "Header.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
void Action::checkManga()
{
	string shounenString;
	fstream shounen("Action.txt");
	while (getline(shounen, shounenString))
	{
		for (int i = 0; i < 3; i++)                             // We know that we're inputting 3 strings into the vector
		{
			// Counter increases when the input string is the same as a line in our .txt file
			if (inputString[i] == shounenString)
			{
				counter++;
			}
		}
		// If the input strings aren't equal to the shounen names we have in our .txt file
		if (inputString[0] != shounenString && inputString[1] != shounenString && inputString[2] != shounenString)
		{
			others.push_back(shounenString);                  // Others contains all the vectors not being a part of the input String
			otherLines++;
		}
	}
}