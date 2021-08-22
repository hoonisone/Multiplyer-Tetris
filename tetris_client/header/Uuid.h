#pragma once
#pragma comment(lib, "rpcrt4.lib")
#include <iostream>
#include "string+.h"
class Uuid {
public:
	static string getID() {
		UUID uuid;
		UuidCreate(&uuid);
		char* str;
		UuidToStringA(&uuid, (RPC_CSTR*)&str);
		string s(str);
		RpcStringFreeA((RPC_CSTR*)&str);
		return s;
	}
};