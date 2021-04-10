#include <stdio.h>
#include <iostream>
#include <string>


int main()
{
	int ord;
	std::string name;
	std::string useless;
	while (std::cin>>ord>>useless >> useless >>name){
		printf("#pragma comment(linker, \"/export:%s=libcefNative.%s,@%d\")\n",name.c_str(), name.c_str(), ord);
	}
	return 0;
}
