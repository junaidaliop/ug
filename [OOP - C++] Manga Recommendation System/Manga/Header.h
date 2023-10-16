#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <assert.h>
using namespace std;

template<class T>
void vectorPr(const vector<T>& vector) {
	copy(vector.begin(), vector.end(),
		ostream_iterator<T>(cout<<"\n\t\t\t\t\t\t", "\n\n\t\t\t\t\t\t"));
}
