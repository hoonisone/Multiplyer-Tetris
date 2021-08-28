#pragma once

#include <string>
#include <vector>
using namespace std;

class Toast {
public:
	virtual string action(vector<string> question) = 0;
	virtual string action(string question) = 0;
};