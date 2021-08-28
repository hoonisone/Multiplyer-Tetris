#pragma once

#include <string>
using namespace std;

class Toast {
public:
	virtual string action(string question) = 0;
};