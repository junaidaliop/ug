#pragma once
#include "Action.h"
#include "Romance.h"
#include "Header.h"
#include "Manga.h"
#include "Comedy.h"
#include "Fantasy.h"
#include "Mystery.h"
class Input:public Action, public Romance, public Mystery,public Comedy,public Fantasy
{
	// Input Class
public:
	void fileChecker();                          // Checks all the files
};

