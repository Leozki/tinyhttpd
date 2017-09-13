#include <iostream>
#include "master.h"

int main(int argc,char* argv[])
{
	Master master;
    std::cout << "---- tinyhttpd run in 0.0.0.0:8000 ----" << std::endl;
    if (!master.StartMaster())
		return -1;

    std::cout << "---- ByeBye ----" << std::endl;
	return 0;
}
