#include "get_rest.h"
#include "NetCommon.h"
#include <iostream>

int rest_test(void* noUse)
{
	std::string body;
	initializeWinsockIfNecessary();
	int ret = sky_rest::get_rest("http://localhost:3000/cmd", body);
	std::cout << "sky_rest::get_rest return: " << ret << std::endl << "body: " << body;
	uninitializeWinsockIfNecessary();
	return ret;
}