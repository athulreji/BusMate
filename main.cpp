#include <iostream>
#include <fstream>
//#include <conio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
using namespace std;

void clrscr(){}

struct Time {
	int hour, min, sec;
} curr_time;

struct Date {
	int day, mon, year;
} curr_date;

//Function to get corrent date and time
void getCurrentDateAndTime() {
	time_t tt;

	// Declaring variable to store return value of
	// localtime()
	struct tm * ti;

	// Applying time()
	time (&tt);

	// Using localtime()
	ti = localtime(&tt);

	curr_time.hour = ti -> tm_hour;
	curr_time.min = ti -> tm_min;
	curr_time.sec = ti -> tm_sec;

	curr_date.day = ti -> tm_mday;
	curr_date.mon = ti -> tm_mon+1;
	curr_date.year = ti -> tm_year+1900;
}

Time getTime() {
	Time t;
	cout << '\t' << "Hour : ";
	cin >> t.hour;
	cout << '\t' << "Minute : ";
	cin >> t.min;
	cout << '\t' << "Second : ";
	cin >> t.sec;
	return t;
}

Date getDate() {
	Date d ;
	cout << '\t' << "Day : ";
	cin >> d.day;
	cout << '\t' << "Month : ";
	cin >> d.mon;
	cout << '\t' << "Year : ";
	cin >> d.year;
	return d;
}

void showDate(Date d) {
	cout << d.day << '/' << d.mon << '/' << d.year;
}

void showTime(Time t) {
	cout << t.hour << ':' << t.min << ':' << t.sec;
}

//Route class Defenition
class Route {
public:
	int route_no;
	char from[30];
	char to[30];
	void getDetails();
	void getRouteDetails();
	void showDetails();
};

//Bus class Defenition
class Bus {
	char bus_name[20];
	int seat[10][4];
	Time departure;
	Time arrival;
	float price;
public:
	char from[30];
	char to[30];
	int route_no;
	int bus_no;
	void getNewBusNo();
	void getRouteDetails();
	void getDetails();
	void showDetails();
	void showAvailSeats();

};

//Traveller class Defenition
class Traveller {
	int bus_no;
	int seats_booked;
	int seat_no[6];
	char name[30];
	char pwd[20];
public:
	char u_name[20];
	void getRouteDetails();
	void getBusNo();
	void getDetails();
	void getSignUpDetails();
	int checkLoginDetails(char *, char *);
};

/////////////////////////////////////////////////
//Member functions of class Route
////////////////////////////////////////////////

void Route :: showDetails() {
	cout << route_no << "\t\t\t" << from << "\t\t\t" << to << '\n';
}


void Route :: getDetails() {
	fstream file;
	Route r;
	int flag;
	file.open("routes.dat", ios :: app | ios :: in | ios :: binary);
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
		while(file.read((char *) &r, sizeof(r))){
			no+=1;
			if(!strcmp(r.from, from) && !strcmp(r.to, to))
				flag = 1;
		}
	} while(flag);
	route_no = no;
	file.close();
}


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

void Bus :: getRouteDetails() {
	fstream file;
	char temp_from[30];
	char temp_to[30];
	int flag = 0;
	Route r;
	file.open("routes.dat",ios :: app | ios :: in | ios :: binary);
	do {
		cout << "Enter the route details : " << '\n';
		cout << '\t' << "From : ";
		cin.sync();
		cin.getline(temp_from, 30);
		cout << '\t' << "To : ";
		cin.getline(temp_to, 30);
		file.seekg(0, ios :: beg);
		while(file.read((char *) &r, sizeof(r))) {
			if(!strcmp(r.from, from) && !strcmp(r.to, to)){
				route_no = r.route_no;
				strcpy(from, r.from);
				strcpy(to, r.to);
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
	getRouteDetails();
	departure = getTime();
	arrival = getTime();
	cout << '\t' << "Price : ";
	cin >> price;
}

void Bus :: showDetails() {
	cout << bus_no << "\t" << route_no << "\t" << bus_name << "\t"; showTime(departure);
	cout << "\t\t";
	showTime(arrival);
	cout << "\t" << price;
}

void Bus :: showAvailSeats() {
	cout << "\t\t\t" << "--------------------------------------------------------------------";
}


/////////////////////////////////////////////////
//Member functions of class Traveller
////////////////////////////////////////////////

void Traveller :: getSignUpDetails() {
	int flag;
	fstream file;
	Traveller t;
	file.open("travellers.dat", ios :: in | ios :: app | ios :: binary);
	cout << "Enter your details : " << '\n';
	cout << '\t' << "Name : ";
	cin.ignore();
	cin.getline(name, 30);
	do {
		flag = 0;
		cout << '\t' << "Username : ";
		cin.getline(u_name, 20);
		file.seekg(0, ios :: beg);
		while (file.read((char *) &t, sizeof(t))) {
			if(!strcmp(u_name, t.u_name)) {
					flag = 1;
					cout << "Username already exist";
					break;
			}
		}
	} while(flag);
	if(flag)
		cout << '\n';
	cout << '\t' << "Password : ";
	cin.getline(pwd, 20);
	file.close();
}

int Traveller :: checkLoginDetails(char uname[20], char pass[20]) {
	if(!strcmp(uname, u_name) && !strcmp(pass, pwd))
		return 1;
	else if(!strcmp(uname, u_name))
		return 3;
	else if(strcmp)
		return 0;
}

/////////////////////////////////////////////////
//Global Functions
////////////////////////////////////////////////


//Function to add new bus
void addNewBus() {
	fstream file;
	file.open("busses.dat", ios::app | ios::binary);
	Bus b;
	b.getDetails();
	if(file.write((char *)&b, sizeof(b)))
		cout << "New bus has been successfully added." << '\n';
	file.close();
}

//Function to add new route
void addNewRoute() {
	fstream file;
	file.open("routes.dat", ios::app | ios:: binary);
	Route r;
	r.getDetails();
	if(file.write((char *)&r, sizeof(r)))
		cout << "New route has been successfully added." << '\n';
	file.close();
}

//Function to show all bus routes
void showAllRoutes() {
		fstream file;
		Route r;
		file.open("routes.dat", ios::app | ios :: in | ios :: binary);
		cout << "#######################################################################" << '\n';
		cout << "Route no." << "\t\t" << "From" << "\t\t\t" << "To" << '\n';
		cout << "#######################################################################" << '\n' << '\n';
		while(file.read((char *) &r, sizeof(r))) {
			r.showDetails();
			cout << "-----------------------------------------------------------------------" << '\n';
		}
		file.close();
}

//Function to show details of all busses
void showAllBusses() {
		fstream file;
		Bus b;
		file.open("busses.dat", ios::app | ios :: in | ios :: binary);
		cout << "###################################################################################" << '\n';
		cout << "Bus no." << "\t" << "Route no." << "\t" << "Name" << "\t" << "Departure" << "\t" << "Arrival" << "" << "Price" <<'\n';
		cout << "###################################################################################" << '\n' << '\n';
		while(file.read((char *) &b, sizeof(b))) {
			b.showDetails();
			cout << "-----------------------------------------------------------------------" << '\n';
		}
		file.close();
}

void showAvailBusses(char from[30], char to[30]) {
	fstream file1, file;
	int route_no;
	Route r;
	file1.open("routes.dat", ios :: app | ios :: in | ios :: binary);
	while(file.read((char *) &r, sizeof(r))) {
		if(!strcmp(r.from, from) && !strcmp(r.to, to)){
			route_no = r.route_no;
			break;
		}
	}
	file1.close();
	Bus b;
	file.open("busses.dat", ios :: app | ios :: in | ios :: binary);
	cout << "###################################################################################" << '\n';
	cout << "Bus no." << "\t" << "Route no." << "\t" << "Name" << "\t" << "Departure" << "\t" << "Arrival" << "" << "Price" <<'\n';
	cout << "###################################################################################" << '\n' << '\n';
	while(file.read((char *) &b, sizeof(b))) {
		if(b.route_no == route_no)
			b.showDetails();
		cout << "-----------------------------------------------------------------------" << '\n';
	}
	file.close();
}

void bookTickets() {
	char from[30], to[30];
	Bus b;
	int bus_no, flag;
	Date booking_date;
	cout << "Enter the details : " << '\n';
	cout << '\t' << "From : ";
	cin.ignore();
	cin.getline(from, 30);
	cout << '\t' << "To : ";
	cin.getline(to, 30);
	cout << '\t' << "Departing(From ";
	showDate(curr_date);
	cout << " to the next 31 days";
	cout << ") : " << '\n';
	booking_date = getDate();
	showAvailBusses(from, to);
	fstream file;
	file.open("busses.dat", ios :: in | ios :: binary);
	do {
		flag = 1;
		cout << "Choose a valid Bus no : ";
		cin >> bus_no;
		file.seekg(0, ios :: beg);
		while (file.read((char *) &b, sizeof(b))) {
			if(!strcmp(from, b.from) && !strcmp(to, b.to) && bus_no == b.bus_no) {
					flag = 0;
					cout << "Invalid bus no." << '\n';
					break;
			}
		}
	} while(flag);
	b.showAvailSeats();
}

void ShowAllTickets() {

}

//Client Panel
void clientPanel() {
	int opt;
	int flag = 0;
	do {
		cout << "Choose a correct option: " << '\n';
		cout << '\t' << "- Book Tickets [ 1 ]" << '\n';
		cout << '\t' << "- Show my tickets [ 2 ]" << '\n';
		cout << '\t' << "- Exit [ 3 ]" << '\n';
		cin>>opt;

		switch(opt) {
			case 1:	bookTickets();
							break;
			case 2:	ShowAllTickets();
							break;
			case 3:	flag = 1;
							break;
		}
	}while(!flag);
}

//Function for traveler to signup
void travellerSignUp() {
	Traveller t;
	fstream file;
	file.open("travellers.dat", ios :: app | ios :: binary);
	t.getSignUpDetails();
	if(file.write((char *) &t, sizeof(t)))
		cout << "Your account has been created successfully." << '\n';
	file.close();
}

//Function for traveller to login
int travellerLogin() {
	fstream file;
	Traveller t;
	int temp, flag = 0;
	char u_name[20], pwd[20];
	cout << "Enter login details : " << '\n';
	cout << '\t' << "Username : ";
	cin.ignore();
	cin.getline(u_name, 20);
	cout << '\t' << "Password : ";
	cin.getline(pwd, 20);
	file.open("travellers.dat", ios :: in | ios :: app | ios :: binary);
	while(file.read((char *) &t, sizeof(t))) {
		temp = t.checkLoginDetails(u_name, pwd);
		if(temp == 1) {
			cout << "You have logged in successfully." << '\n';
			flag = 1;
			clientPanel();
			break;
		}
		else if(temp == 3){
			cout << "Incorrect Password." << '\n';
			flag = 1;
			break;
		}
	}
	if(!flag)
		cout << "Username does not exist." << '\n';
	file.close();
}

//Admin Controls
void adminControl() {
	int opt;
	int flag = 0;
	do {
		cout << "Choose a correct option: " << '\n';
		cout << '\t' << "- Add new bus [ 1 ]" << '\n';
		cout << '\t' << "- Add new route [ 2 ]" << '\n';
		cout << '\t' << "- Show all routes [ 3 ]" << '\n';
		cout << '\t' << "- Show all busses [ 4 ]" << '\n';
		cout << '\t' << "- Exit [ 5 ]" << '\n';
		cin>>opt;

		switch(opt) {
			case 1:	addNewBus();
							break;
			case 2:	addNewRoute();
							break;
			case 3:	showAllRoutes();
							break;
			case 4:	showAllBusses();
							break;
			case 5:	flag = 1;
							break;
		}
	}while(!flag);
}

//Client Area
void clientArea() {
	int opt;
	int flag = 0;
	do {
		cout << "Choose a correct option: " << '\n';
		cout << '\t' << "- Login [ 1 ]" << '\n';
		cout << '\t' << "- Create a new account [ 2 ]" << '\n';
		cout << '\t' << "- Exit [ 3 ]" << '\n';
		cin>>opt;

		switch(opt) {
			case 1:	travellerLogin();
							break;
			case 2:	travellerSignUp();
							break;
			case 3:	flag = 1;
							break;
		}
	}while(!flag);
}


int main() {
	getCurrentDateAndTime();
	int opt;
	int flag = 0;
	do {
		cout << '\t' << "- Admin Control [ 1 ]" << '\n';
		cout << '\t' << "- Client Area [ 2 ]" << '\n';
		cout << '\t' << "- Exit [ 3 ]" << '\n';
		cin>>opt;

		switch(opt) {
			case 1:	adminControl();
							break;
			case 2:	clientArea();
							break;
			case 3:	flag = 1;
							break;
		}
	}while(!flag);
	return 0;
}
