#pragma warning(disable:4996)
#include "string+.h"
#include <vector>
#include <string>

using namespace std;

vector<string> split(string s, string key) {
	int pos1 = 0, pos2;
	vector<string> tokens;
	while ((pos2 = s.find(key, pos1)) != -1) {
		tokens.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + key.size();
	}
	pos2 = s.size();
	tokens.push_back(s.substr(pos1, pos2 - pos1));
	return tokens;
}
