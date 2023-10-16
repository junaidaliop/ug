#pragma once
#include <vector>
#include <iostream>
#include <time.h>
#include <string>
#include <stdlib.h>
using namespace std;
class Manga
{
protected:
	vector <string> inputString;                           // The names of input manga's        (3 strings)
	vector <string> recommendation;                        // The manga names we'll recommend  
	static int otherLines;                                 // no. of other variable strings
	vector <string> others;                                // All manga names other than the input ones
	static int counter;                                    // Manga Counter
	string s1, s2, s3;                                     // 3 strings for push_back (easily done)
	bool correctPass;                                      // Checks whether the pass is correct or not
	string username;                                       // Username and Password Strings
	string password;
	string filename;                                       // To create the file based on the user's name
	const char* txtfile;                                   // To open the txt file after the end of the program.
	bool validInput=true;                                  // Checks for valid input
public:
	void setVector(vector <string> input);                 // To set the input vector
	void displayInput();                                   // Displays input string
	void displayRecommendations();                         // Displays Recommended Mangas
	void counterCheck();                                   // Checks counter
	void checkPass();                                      // Correct Password Check
	string getPass();                                      // To get Password
	void setPass(string pass);                             // To set Password
	string getUser();                                      // To get Username
	void setUser(string user);                             // To set Username
	Manga();                                               // Default Constructor
	~Manga();                                              // Destructor (Does Really Cool Stuff)
};