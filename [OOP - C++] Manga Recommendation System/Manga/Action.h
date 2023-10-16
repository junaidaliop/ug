#pragma once
#include "Manga.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class Action :
	virtual public Manga
{
public:
	void checkManga();                                 // Goes through Shounen Manga to check for the inputs to match or not
};