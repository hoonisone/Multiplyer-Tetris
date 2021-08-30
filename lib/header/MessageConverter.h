#pragma once

#include "string+.h"
#include <unordered_map>
#include "error.h"
using namespace std;

class MessageConverter {
	static string toString(unordered_map<string, string> object) {
		string message = "";
		for (auto i = object.begin(); i != object.end(); i++) {
			message.append(i->first);
			message.append(":");
			message.append(i->second);
			message.append("/");
		}
		message.pop_back();
		return message;
	}
	static unordered_map<string, string> toObject(string text) {
		vector<string> tokens = split(text, "/");
		unordered_map<string, string> object;
		for (auto token : tokens) {
			vector<string> elements = split(token, ":");
			try {
				object[elements[0]] = object[elements[1]];
			}catch(...) {
				errorPrint("key duplicated");
			}
		}
		return object;
	}
}