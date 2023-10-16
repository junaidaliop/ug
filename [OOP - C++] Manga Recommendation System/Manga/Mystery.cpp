#include "Mystery.h"
#include "Header.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
void Mystery::checkManga()
{
	string mysString;
	fstream mystery("Mystery.txt");
	while (getline(mystery, mysString))
	{
		for (int i = 0; i < 3; i++)                             // We know that we're inputting 3 strings into the vector
		{
			if (inputString[i] == mysString)
			{
				counter++;
			}
		}
		// If the input strings aren't equal to the shounen names we have in our .txt file
		if (inputString[0] != mysString && inputString[1] != mysString && inputString[2] != mysString)
		{
			others.push_back(mysString);                  // Others contains all the vectors not being a part of the input String
			otherLines++;
		}
	}
}