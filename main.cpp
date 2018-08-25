#include <iostream>
#include <fstream>
//#include <conio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
using namespace std;

void clrscr(){}

//Route class Defenition
class Route {
	char stop[20][30];
public:
	int route_no;
	char from[30];
	char to[30];
	void getDetails();
	void getRouteNo();
	void showDetails();
};

/////////////////////////////////////////////////
//Member functions of class Route
////////////////////////////////////////////////

void Route :: showDetails() {
	cout << route_no << '\t' << from << '\t' << to << '\n';
}

void Route :: getDetails() {
	fstream file;
	Route r;
	int flag;
	file.open("routes.dat", ios :: app | ios :: binary);
	int no;
	do {
		no = 100;
		flag = 0;
		cout << "Enter the details of the route : " << '\n';
	 	cout << '\t' << "From : ";
		cin.ignore();
		cin.getline(from, 30);
		cout << '\t' << "To: ";
		cin.getline(to, 30);
		while(file){
			no+=1;
			file.read((char *) &r, sizeof(r));
			if(!strcmp(r.from, from) && !strcmp(r.to, to))
				flag = 1;
		}
	} while(flag);
	route_no = no;
	file.close();
	cout<<route_no<<" "<<from<< " "<<to;
}

//Bus class Defenition
class Bus {
	char bus_name[20];
	int seat[10][4];
	int route_no;
public:
	int bus_no;
	void getNewBusNo();
	void getRouteNo();
	void getDetails();
};

/////////////////////////////////////////////////
//Member functions of class bus
////////////////////////////////////////////////

void Bus :: getNewBusNo() {
	int no = 1000;
	fstream file;
	file.open("busses.dat",ios::app | ios :: binary);
	file.seekg(0, ios :: end);
	no+= (file.tellg() / sizeof(Bus));
	bus_no = no;
	file.close();
}

void Bus :: getRouteNo() {
	fstream file;
	char from[30];
	char to[30];
	int flag = 0;
	Route r;
	file.open("routes.dat",ios :: app | ios :: binary);
	do {
		cout << "Enter the route details : " << '\n';
		cout << '\t' << "From : ";
		cin.ignore();
		cin.getline(from, 30);
		cout << '\t' << "To : ";
		cin.getline(to, 30);
		file.seekg(0, ios :: beg);
		while(file) {
			file.read((char *) &r, sizeof(r));
			if(!strcmp(r.from, from) && !strcmp(r.to, to)){
				route_no = r.route_no;
				flag = 1;
				break;
			}
		}
	} while(!flag);
	file.close();
}


void Bus :: getDetails() {
	cout << "Enter the details of the bus :" << '\n';
	cout << '\t' << "Name : ";
	cin.ignore();
	cin.getline(bus_name, 20);
	getNewBusNo();
	getRouteNo();
}

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
	if(bfile.write((char *)&b, sizeof(b)))
		cout << "New bus has been successfully added." << '\n';
	bfile.close();
}

//Function to add new route
void addNewRoute() {
	fstream rfile;
	rfile.open("routes.dat", ios::app | ios:: binary);
	Route r;
	r.getDetails();
	if(rfile.write((char *)&r, sizeof(r)))
		cout << "New route has been successfully added." << '\n';
	rfile.close();
}

//Function to show all bus routes
void showAllRoutes() {
		fstream file;
		Route r;
		file.open("routes.dat", ios::app | ios :: binary);
		cout << "Route no." << '\t' << "From" << '\t' << "To" << '\n';
		while(file) {
			file.read((char *) &r, sizeof(r));
			cout << "-----------------------------------------------------------------------" << '\n';
			r.showDetails();
			cout << "-----------------------------------------------------------------------" << '\n';
		}
		file.close();
}

//Admin Controls
void adminControl() {
	int opt;
	do {
		opt = 0;
		cout << "Choose a correct option: " << '\n';
		cout << '\t' << "- Add new bus [ 1 ]" << '\n';
		cout << '\t' << "- Add new route [ 2 ]" << '\n';
		cout << '\t' << "- Show all routes [ 3 ]" << '\n';
		cout << '\t' << "- Exit [ 4 ]" << '\n';
		cin>>opt;
		clrscr();

		if(opt == 1)
			addNewBus();
		else if(opt == 2)
			addNewRoute();
		else if(opt == 3)
			showAllRoutes();
		else if(opt == 4)
			break;
	} while(opt != 1 || opt != 2 || opt != 3 || opt !=4);
}

//Client Area
void clientArea() {

}

int main() {
	int opt;
	do {
		opt = 0;
		cout << '\t' << "- Admin Control [ 1 ]" << '\n';
		cout << '\t' << "- Client Area [ 2 ]" << '\n';
		cout << '\t' << "- Exit [ 3 ]" << '\n';
		cin>>opt;
		clrscr();

		if(opt == 1)
			adminControl();
		else if(opt == 2)
			clientArea();
		else if(opt == 3)
			break;
	} while(opt != 1 || opt != 2 || opt != 3);
	adminControl();
	return 0;
}
