#include <iostream>
#include <time.h>
using namespace std;

//Route class Defenition
class Route {
	char from[30];
	char to[30];
	char stop[20][30];
public:
	int route_no;
};

//Bus class Defenition
class bus {
	char bus_name[20];
	int seat[10][4];
	int route_no;
public:
	int bus_no;
};

//Traveller class Defenition
class traveller {
	int route_no;
	int bus_no;
};

int main(){

    return 0;
}
