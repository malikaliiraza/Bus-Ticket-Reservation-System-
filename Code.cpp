#include <iostream>
using namespace std;

const int max_buses = 10;
const int max_routes = 10;
const int max_reservations = 10;
struct Bus
{
    int busNumber;
    int totalSeat;
    char driverName[50];
};

struct Route //ROUTE DETAILS
{ 
    char departure[50]; 
    char arrival[50]; 
    int distance;
    int duration;
    char stops[5][50]; 
};

struct Reservation //RESERVATION DETAILS
{
    char passengerName[50];  
    char seatNumber[10];
    int fare;
    char tripType[20]; 
    bool discountApplied;
};

struct Trip // TRIP DETAILS
{
    char tripType[20];
    Route route;
    Bus bus;
    Reservation reservations[max_reservations];
    int reservationCount;
};

Bus buses[max_buses];
Route routes[max_routes];
Reservation reservations[max_reservations];
int busCount = 0;
int routeCount = 0;
int reservationCount = 0;

void displaySeatLayout(int totalSeats)
{
    cout << "Seat Layout:\n";
    for(int i = 1; i <= totalSeats; i++)
	{
        cout<<"Seat"<<i<<(i%10==0?"\n":"\t");
    }
    cout<<"\n";
}

int applyDiscount(int fare, const char *userType)
{
	if (userType == "Student")
    {
        return fare - (fare * 20 / 100);
    }
    else if (userType == "Faculty")
    {
        return fare - (fare * 15 / 100);
    }
    else if (userType == "Staff")
    {
        return fare - (fare * 10 / 100);
    }
    return fare;
}

void addBus()
{
    if (busCount >= max_buses)
	{
        cout<<"Cannot add more buses. Maximum limit reached.\n";
        return;
    }
    Bus bus;
    cout<<"Enter Bus Number : ";
    cin>>bus.busNumber;
    cout<<"Enter Seat Capacity : ";
    cin>>bus.totalSeat;
    cout<<"Enter Driver Name : ";
    cin>>bus.driverName;
	buses[busCount++] = bus;
    cout << "Bus added successfully!\n";
}

void addRoute()
{
    if(routeCount >= max_routes)
	{
        cout<<"Cannot add more routes. Maximum limit reached.\n";
        return;
    }
    Route route;
    cout<<"Enter Departure : ";
    cin>>route.departure;
    cout << "Enter Arrival : ";
    cin>>route.arrival;
    cout<<"Enter Distance (in km) : ";
    cin>>route.distance;
    cout<<"Enter Duration (in minutes) : ";
    cin>>route.duration;
    cout<<"Enter Stops (Enter 'done' to stop) :\n";
    int stopCount = 0;
    while (true)
	{
        cin>>route.stops[stopCount];
        if(strcmp(route.stops[stopCount], "done") == 0 || stopCount >= 5)
		break;
        stopCount++;
    }

    routes[routeCount++] = route;
    cout<<"Route added successfully!\n";
}

void displayRoutes()
{
    cout<<"Available Routes:\n";
    for (int i=0; i<routeCount; i++)
	{
        cout<<i+1<<". "<<routes[i].departure<<" to "<<routes[i].arrival<<" | Distance: "<<routes[i].distance<<" km | Duration: "<<routes[i].duration<<" min\n";
    }
}

void bookTicket()
{
    displayRoutes();
    int routeIndex;
    cout<<"Enter route number to book a ticket: ";
    cin>>routeIndex;

    if (routeIndex<1 || routeIndex>routeCount)
	{
        cout<<"Invalid route number.\n";
        return;
    }

    Route selectedRoute = routes[routeIndex-1];
    cout<<"Selected Route: "<<selectedRoute.departure<<" to "<<selectedRoute.arrival<<"\n";
    displaySeatLayout(10);
    char seatNumber[10];
    cout<<"Enter Seat Number (1-10): ";
    cin>>seatNumber;
    char userType[20];
    cout<<"Enter User Type (Student/Faculty/Staff): ";
    cin>>userType;
    int fare = selectedRoute.distance*10;
    int finalFare = applyDiscount(fare, userType);
    if (reservationCount >= max_reservations)
	{
        cout<<"Reservation limit reached!\n";
        return;
    }
    Reservation reservation;
    cout<<"Enter Passenger Name: ";
    cin>>reservation.passengerName;
	strcpy(reservation.seatNumber, seatNumber);
    reservation.fare = finalFare;
    strcpy(reservation.tripType, "One-Day Trip"); 
    reservation.discountApplied = true;
    reservations[reservationCount++] = reservation;
    cout<<"Ticket Booked! Seat Number: "<<seatNumber<<", Fare: "<<finalFare<<"\n";
}

void adminMenu()
{
    int choice;
    for (;choice!=3;)
    {
        cout<<"\nAdmin Menu:\n";
        cout<<"1. Add Bus\n";
        cout<<"2. Add Route\n";
        cout<<"3. Display Routes\n";
        cout<<"4. Display Buses\n";
        cout<<"5. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch (choice)
		{
            case 1:
                addBus();
                break;
            case 2:
                addRoute();
                break;
            case 3:
                displayRoutes();
                break;
            case 4:
                for(int i=0; i<busCount; i++)
				{
                    cout<<"Bus "<<buses[i].busNumber<<" | Driver: "<<buses[i].driverName<<endl;
                }
                break;
            case 5:
                cout<<"Exiting Admin Menu...\n";
                break;
            default:
                cout<<"Invalid choice! Please Try Again.\n";
        }
    }
}

void mainMenu()
{
    int choice;
    for (;choice!=3;)
	{
		cout<<"\nDAWOO Bus Reservation System\n";
        cout<<"1. Admin Menu\n";
        cout<<"2. Book Ticket\n";
        cout<<"3. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch (choice)
        {
            case 1:
                adminMenu();
                break;
            case 2:
                bookTicket();
                break;
            case 3:
                cout << "Exiting system...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n"; 
        }
    }
	
}

int main()
{
    mainMenu();
    return 0;
}
