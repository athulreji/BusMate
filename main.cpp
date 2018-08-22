#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>
using namespace std;

//Route class Defenition
class Route {
	char from[30];
	char to[30];
	char stop[20][30];
public:
	int route_no;
	void get_details();
};

//Bus class Defenition
class Bus {
	char bus_name[20];
	int seat[10][4];
	int route_no;
public:
	int bus_no;
	void getRouteNo();
	void getDetails();
};

//Traveller class Defenition
class traveller {
	int route_no;
	int bus_no;
	int seat_no;
	char name[30];
public:
	void getRouteNo();
	void getBusNo();
	void getDetails();
};

//Function to add new bus
void addNewBus() {
	fstream bfile;
	bfile.open("busses.dat", ios::app | ios::binary);
	Bus b;
	b.getDetails();
	bfile.write((char *)&b, sizeof(b));
}

//Function to add new route
void addNewRoute() {
	fstream rfile;
	rfile.open("routes.dat", ios::app | ios:: binary);
	Route r;
	r.getDetails();
	rfile.write((char *)&r, sizeof(r));
}

//Admin Controls
void adminControl() {
	int opt;
	do {
		opt = 0;
		cout << "Choose a correct option: " << '\n';
		cout << '\t' << "- Add new bus [ 1 ]" << '\n';
		cout << '\t' << "- Add new route [ 2 ]" << '\n';
		cout << '\t' << "- Exit [ 3 ]" << '\n';
		cin>>opt;
		clrscr();

		if(opt == 1)
			addNewBus();
		else if(opt == 2)
			addNewRoute();
		else if(opt == 3)
			break;
	} while(opt != 1 || opt != 2 || opt != 3);
}

int main() {

    return 0;
}
