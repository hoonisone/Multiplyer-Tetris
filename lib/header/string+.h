#pragma once
#include <vector>
#include <string>

#define ALIGN_LEFT		0
#define ALIGN_MIDDLE	1
#define ALIGN_RIGHT		2


std::vector<std::string> split(std::string s, std::string key) {
	int pos1 = 0, pos2;
	std::vector<std::string> tokens;
	while ((pos2 = s.find(key, pos1)) != -1) {
		tokens.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + key.size();
	}
	pos2 = s.size();
	tokens.push_back(s.substr(pos1, pos2 - pos1));
	return tokens;
}
