////edited for demo by achyuth



#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <string.h>
using namespace std;

#ifdef linux
#define clearscr() system("clear")
#define showPrint() system("gedit ticket_print.txt")
#endif

#ifdef _WIN32
#define clearscr() system("cls")
#define showPrint() system("notepad ticket_print.txt")
#endif

struct Time {
	int hour, min;
};

Time getTime() {
	Time t;
	cout << '\t' << "Hour : ";
	cin >> t.hour;
	cout << '\t' << "Minute : ";
	cin >> t.min;
	return t;
}

void showTime(Time t) {
	cout << t.hour << ':' << t.min << ':' << "00";
}

/////////////////////////////////////////////////
//Classes
////////////////////////////////////////////////

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
	int seat[40];
	float price;
public:
	char from[30];
	char to[30];
	Time departure, arrival;
	int route_no;
	int bus_no;
	Bus() {
		for(int i=0; i<40; i++)
			seat[i] = 0;
	}
	void getNewBusNo();
	void getRouteDetails();
	void getDetails();
	void showDetails();
	void showAvailSeats();
	int bookSeats(int, int []);
};

//User class Defenition
class User {
	int seats_booked;
	int seat_nos[6];
	char from[30];
	char to[30];
	char name[30];
	char pwd[20];
	int bus_no;
public:
	User() {
		seats_booked = 0;
		for(int i=0; i<6; i++)
			seat_nos[i] = 0;
	}
	char u_name[20];
  void printTicket();
	void getRouteDetails();
	void getDetails();
	void getSignUpDetails();
	int checkLoginDetails(char *, char *);
	void clientPanel();
	void bookTickets();
	void showTicket();
};

/////////////////////////////////////////////////
//Global Functions
////////////////////////////////////////////////

//oops

//Function to refresh the window
void refreshScrn() {
	clearscr();
	cout << "##################################################################################" << endl;
	cout << "##############################  BUS BOOKER [v 0.1] ###############################" << endl;
	cout << "##################################################################################" << endl << endl;
}

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
		cout << "##################################################################################" << '\n';
		cout << " Route no." << "\t\t" << "From" << "\t\t\t" << "To" << '\n';
		cout << "##################################################################################" << '\n' << '\n';
		while(file.read((char *) &r, sizeof(r))) {
			r.showDetails();
			cout << "---------------------------------------------------------------------------------" << '\n';
		}
		file.close();
}

//Function to show details of all busses
void showAllBusses() {
		fstream file;
		Bus b;
		file.open("busses.dat", ios::app | ios :: in | ios :: binary);
		cout << "##################################################################################" << '\n';
		cout << " Bus no." << "   " << "Route no." << "\t" << "Name" << "\t\t" << "Departure" << "\t" << "Arrival" << "\t\t" << "Price" <<'\n';
		cout << "##################################################################################" << '\n' << '\n';
		while(file.read((char *) &b, sizeof(b))) {
			b.showDetails();
			cout << "----------------------------------------------------------------------------------" << '\n';
		}
		file.close();
}

void showAvailBusses(char from[30], char to[30]) {
	fstream file;
	Bus b;
	file.open("busses.dat", ios :: app | ios :: in | ios :: binary);
	cout << "###################################################################################" << '\n';
	cout << " Bus no." << "\t" << "Route no." << "\t" << "Name" << "\t\t" << "Departure" << "\t" << "Arrival" << "\t\t" << "Price" <<'\n';
	cout << "###################################################################################" << '\n' << '\n';
	while(file.read((char *) &b, sizeof(b))) {
		if(!strcmp(from, b.from) && !strcmp(to, b.to))
			b.showDetails();
		cout << "---------------------------------------------------------------------------------" << '\n';
	}
	file.close();
}

//Function for traveler to signup
void UserSignUp() {
	User u;
	fstream file;
	file.open("Users.dat", ios :: app | ios :: binary);
	cout << "Enter your details :";
	u.getSignUpDetails();
	if(file.write((char *) &u, sizeof(u)))
		cout << "Your account has been created successfully." << '\n';
	file.close();
}

//Function for User to login
void UserLogin() {
	fstream file;
	User u;
	int temp, flag = 0;
	char u_name[20], pwd[20];
	cout << "Enter login Details :" << endl;
	cout << '\t' << "Username : ";
	cin.ignore();
	cin.getline(u_name, 20);
	cout << '\t' << "Password : ";
	cin.getline(pwd, 20);
	file.open("Users.dat", ios :: in |	ios :: out | ios :: binary);
	while(file.read((char *) &u, sizeof(u))) {
		temp = u.checkLoginDetails(u_name, pwd);
		if(temp == 1) {
			cout << "You have logged in successfully." << '\n';
			u.clientPanel();
			file.seekp(-1 * sizeof(u), ios::cur);
			file.write((char *) &u, sizeof(u));
			flag = 1;
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
	char pwd[10];
	int flag = 0, flag2 = 0;
	cout << "Enter admin password to continue : ";
	cin.ignore();
	cin.getline(pwd, 10);
	if(!strcmp(pwd, "iampwd"))
		flag2 = 1;
	if(flag2)
		do {
			cout << "Choose a correct option: " << '\n';
			cout << '\t' << "- Add new bus [ 1 ]" << '\n';
			cout << '\t' << "- Add new route [ 2 ]" << '\n';
			cout << '\t' << "- Show all routes [ 3 ]" << '\n';
			cout << '\t' << "- Show all busses [ 4 ]" << '\n';
			cout << '\t' << "- Exit [ 5 ]" << '\n';
			cin >> opt;

			refreshScrn();
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
	else
		cout << "Incorrect password" << endl;
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

		refreshScrn();
		switch(opt) {
			case 1:	UserLogin();
							break;
			case 2:	UserSignUp();
							break;
			case 3:	flag = 1;
							break;
		}
	}while(!flag);
}


/////////////////////////////////////////////////
//Member functions of class Route
////////////////////////////////////////////////

//Show details of the route
void Route :: showDetails() {
	cout << ' ' << route_no << "\t\t\t" << from << "\t\t\t" << to << '\n';
}

//Get details of the route
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
	int flag;
	char temp_from[30];
	char temp_to[30];
	Route r;
	file.open("routes.dat",ios :: app | ios :: in | ios :: binary);
	do {
		flag = 0;
		cout << "Enter the route details : " << '\n';
		cout << '\t' << "From : ";
		cin.sync();
		cin.getline(temp_from, 30);
		cout << '\t' << "To : ";
		cin.getline(temp_to, 30);
		file.seekg(0, ios :: beg);
		while(file.read((char *) &r, sizeof(r))) {
			if(!strcmp(r.from, temp_from) && !strcmp(r.to, temp_to)){
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
	cout << "Departure : " << '\n';
	departure = getTime();
	cout << "Arrival : " << '\n';
	arrival = getTime();
	cout << '\t' << "Price : ";
	cin >> price;
}

int Bus :: bookSeats(int n, int sts[6]){
	int flag = 1;
	for(int i=0; i<n; i++){
		if(seat[sts[i]] == 1) {
			cout << "Seat " << sts[i] << "is already booked" << '\n';
			flag = 0;
		}
	}
	if(!flag)
		return 0;
	else {
		for(int i=0; i<n; i++)
			seat[sts[i]] = 1;
		return 1;
	}
}

void Bus :: showDetails() {
	cout << ' ' << bus_no << "\t" << route_no << "\t\t" << bus_name << "\t\t"; showTime(departure);
	cout << "\t\t";
	showTime(arrival);
	cout << "\t\t" << price << endl;
}

void Bus :: showAvailSeats() {
	int temp=0;
	cout <<  "\n\n\n";
	for(int i=1; i<=6; i++) {
		cout << "     ";
		if(i==2 || i==5)
			cout << '(';
		else
			cout << ' ';
		if(i!=3)	{
			cout << '|';
			for(int j=1; j<=8; j++) {
				temp ++;
				cout << '\t' << '|';
				if(seat[temp]==0){
					if(temp<10)
						cout << 0;
					cout << temp;
				}
				else
					cout << "❌";
			}
			cout << "  ";
		}

		else
			cout << '\n';
		if(i==2 || i==5)
			cout <<  '|' << ']';
		else if(i != 3)
			cout << '|';
		cout <<'\n';
	}
	cout << "\n\n\n";
}


/////////////////////////////////////////////////
//Member functions of class User
////////////////////////////////////////////////

void User :: getSignUpDetails() {
	int flag;
	fstream file;
	User u;
	file.open("Users.dat", ios :: in | ios :: app | ios :: binary);
	cout << "Enter your details :" << '\n';
	cout << '\t' << "Name : ";
	cin.ignore();
	cin.getline(name, 30);
	do {
		flag = 0;
		cout << '\t' << "Username : ";
		cin.getline(u_name, 20);
		file.seekg(0, ios :: beg);
		while (file.read((char *) &u, sizeof(u))) {
			if(!strcmp(u_name, u.u_name)) {
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

int User :: checkLoginDetails(char uname[20], char pass[20]) {
	if(!strcmp(uname, u_name) && !strcmp(pass, pwd))
		return 1;
	else if(!strcmp(uname, u_name))
		return 3;
	else if(strcmp)
		return 0;
}

void User :: showTicket() {
	if(seats_booked){
		cout << "From : " << from << endl;
		cout << "To : " << to << endl;
		cout << "Bus No." << bus_no << endl;
		cout << "Seats Booked : " << seats_booked << endl;
		cout << "Seat Nos : ";
		for(int i=0; i<seats_booked; i++)
			cout << seat_nos[i] << ' ';
		cout << endl;
	}
	else
		cout << "Sorry, you haven't booked any tickets yet." << endl;
}

void User :: printTicket() {
  if(seats_booked){
    fstream file;
    file.open("ticket_print.txt", ios :: out);
    file << "\t\t\t\t\tBUS BOOKER \n\n\n\n";
    file << "-Ticket Details-----------------------------------------\n\n";
    file << "Name : " << name << endl <<endl;
    file << "From : " << from <<endl << endl;
    file << "To : " << to << endl << endl;
    file << "Bus no : " << bus_no << endl << endl;
    file << "Seats Booked : " << seats_booked << endl << endl;
    file << "Seat Nos : " << endl;
    for(int i=0; i<seats_booked; i++)
      file << seat_nos[i] << ' ';
    file << "\n\n\n\n";
    file << "\t\t\t\tTHANK YOU FOR BOOKING TICKETS THROUGH BUS BOOKER";
    file.close();
    showPrint();
  }
	else
		cout << "Sorry, you haven't booked any tickets yet." << endl;
}

void User :: bookTickets() {
	char t_from[30], t_to[30];
	Bus b;
	int bus_n, flag;
  cout << "NOTE : Your previous ticket data will be removed.";
	cout << "Enter the details : " << '\n';
	cout << '\t' << "From : ";
	cin.ignore();
	cin.getline(t_from, 30);
	cout << '\t' << "To : ";
	cin.getline(t_to, 30);
	showAvailBusses(t_from, t_to);
	fstream file;
	file.open("busses.dat", ios :: in| ios:: out | ios :: binary);
	do {
		flag = 1;
		cout << "Choose a valid Bus no (0 - exit) : ";
		cin >> bus_n;
		if(bus_n == 0)
			break;
		file.seekg(0, ios :: beg);
		while (file.read((char *) &b, sizeof(b))) {
			if(!strcmp(t_from, b.from) && !strcmp(t_to, b.to) && bus_n == b.bus_no) {
					int no_of_seats, t_seats[6] = {0,0,0,0,0,0}, conf_booking;
					b.showAvailSeats();
					cout << '\n';
					cout << "Enter the no of seats to buy : ";
					cin >> no_of_seats;
					cout << "Enter seat no and press Enter..." << '\n';
					for(int i=0; i<no_of_seats; i++)
						cin >> t_seats[i];
					if(b.bookSeats(no_of_seats, t_seats)) {
						cout << "Booking successful" << '\n';
						bus_no = bus_n;
						seats_booked = no_of_seats;
						strcpy(from, t_from);
						strcpy(to, t_to);
						for(int i=0; i<no_of_seats; i++)
							seat_nos[i] = t_seats[i];
						file.seekp(-1 * sizeof(b), ios :: cur);
						file.write((char *) &b, sizeof(b));
					}
					flag = 0;
					break;
			}
			cout << "Invalid bus no." << '\n';
		}
		cout << endl;
	} while(flag);
}

//Client Panel
void User :: clientPanel() {
	int opt;
	int flag = 0;
	refreshScrn();
	do {
		cout << "Choose a correct option: " << '\n';
		cout << '\t' << "- Book Tickets [ 1 ]" << '\n';
		cout << '\t' << "- Show my tickets [ 2 ]" << '\n';
		cout << '\t' << "- Print Ticket [ 3 ]" << '\n';
		cout << '\t' << "- Exit [ 4 ]" << '\n';
		cin>>opt;

		refreshScrn();
		switch(opt) {
			case 1:	bookTickets();
							break;
			case 2:	showTicket();
							break;
			case 3:	printTicket();
							break;
			case 4:	flag = 1;
							break;
		}
	}while(!flag);
}


int main() {
	int opt;
	int flag = 0;
	refreshScrn();
	do {
		cout << '\t' << "- Admin Control [ 1 ]" << '\n';
		cout << '\t' << "- Client Area [ 2 ]" << '\n';
		cout << '\t' << "- Exit [ 3 ]" << '\n';
		cin>>opt;

		refreshScrn();
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
