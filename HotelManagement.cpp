// Hotel Management System

#include<iostream>
#include<string.h>
#include<iomanip>
#include<ctime>
using namespace std;

// Creating a class Customer

class Customer
{
    string name;            // Customer Full Name
    string address;         // Customer Address
    string phone;           // Customer phone number
    int days=0;             // Duration of Stay
    float payment_advance;  // Advance payment by customer
    double bill=0;          // Bill Amount
    int booking_id;         // Booking ID
    int room;               // Room ID
    int status;
public:
    Customer()
{
        days=0;
        payment_advance=0;
        bill=0;
        booking_id=0;
        status=0;
        room=0;
}
    void accept();          // Accept Customer Details
    void display();         // Display Customer Details
    friend class room;
    friend class Hotel;
};
void Customer::accept()     // Accepting Customer Details
{
    cout<<"Enter Customer's Name: ";
    getline(cin, name);
    getline(cin, name);
    cout<<"Enter Customer address: ";
    getline(cin,address);
    flag:
    cout<<"Enter Customer's Mobile Number: ";
    cin>>phone;
    for(int i=0;i<(phone.length());i++)
    {
        if(!isdigit(phone[i]))
        {
            cout<<"Phone number has to be in digits.\n";
            goto flag;
        }
    }
    if(phone.length()!=10)       // Phone Length Validation
    {
        cout<<"Phone number should be 10 digits.\n";
        goto flag;
    }
}

void Customer::display()         // Displaying Customer Details
{
    cout<<booking_id<<"\t\t";
    cout<<"| "<<left<<setfill(' ')<<setw(30)<<name;
    cout<<"| "<<phone<<"\t\t\t";
    cout<<"| "<<left<<setfill(' ')<<setw(30)<<address;
    cout<<"| "<<room<<"\t\t\t";
    if(status==1){cout<<"|\t\t-\t\t|"<<endl;}
    else{cout<<"|\tChecked Out.\t\t|"<<endl;}
}

// Creating a Class 'Room'
// Will Store All Room Data

class Room
{
    char type;              // Deluxe or Normal
    char stype;             // Small Sized or Big Sized Room
    char ac;                // AC or NON AC
    int roomNumber;         // ROOM NUMBER
    double rent;            // Daily Tariff of room
    int status=0;           // Room is booked or not
public:
    friend class Hotel;
    void acceptroom(int rno);   //Add rooms in Hotel Database
    void displayroom();         //Display Rooms
    Room()                     //Default Constructor
    {
        type='\0';
        stype='\0';
        ac='\0';
        roomNumber=0;
        rent=0;
        status=0;
    }
};

void Room::acceptroom(int rno)          // Accepting all room details
{
    roomNumber=rno; //Room Number
    cout<<"Type AC/Non-AC (A/N): ";
    cin>>ac;
    while(ac!='A'&& ac!='N')            // Validating the Input
    {
        cout<<"Please Re-Enter type: AC/Non-AC (A/N) : ";
        cin>>ac;
    }
    cout<<"Enter room type - Deluxe or Normal (D/N) : ";
    cin>>type;
    while(type!='D' && type!='N')
    {
        cout<<"Please re-enter room type - Deluxe or Normal (D/N) :";
        cin>>type;
    }
    cout<<"Please enter room size - Big or Small(B/S) : ";
    cin>>stype;
    while(stype!='B'&& stype!='S')
    {
        cout<<"Please re-enter room size (B/S) : ";
        cin>>stype;
    }
    cout<<"Daily Tariff: ";
    cin>>rent;
    while(rent<0 || rent>20000)
    {
        cout<<"Please enter valid rent.";
        cin>>rent;
    }
    status=0;       // Booking Status of the Room
    cout<<"\nRoom Added Successfully!"<<endl;
}

void Room::displayroom()
{
    cout<<"| "<<roomNumber<<".\t\t|\t"<<ac<<"\t\t|\t"<<type<<"\t\t|\t"<<stype<<"\t\t|\t"<<rent<<"\t\t|\t";
    if(status==0) {cout<<"Available.\t|";}
    else{cout<<"Booked.\t\t|";}
    cout<<endl;
}

// Class Hotel

class Hotel
{
    Room a[100];        // Array of Rooms
    Customer c[100];    // Array of Customers
    int nroom=0, ncust=0;   // No. of Rooms and Customers
public:
    void addRooms();        // Add Rooms To Database
    void searchroom();      // Search for a particular room
    void CheckIn();         // For Customer CheckIn
    void searchcust();      // Search stay status of a customer
    void availability();    // Check Availability of Rooms
    void CheckOut();        // Checkout and billing procedures
    void Summary();         // Guest Summary
};
void Hotel::addRooms()
{
    int rno;
    cout<<"Enter number of rooms: ";
    cin>>nroom;             // Accepting number of rooms
    while(nroom<=0)
    {
        cout<<"Invalid. Enter valid number of rooms.";
        cin>>nroom;
    }
    for(int i=0;i<nroom;i++)
    {
        cout<<"ROOM "<<(i+1)<<endl;
        flag:
        cout<<endl<<"Enter room number: ";
        cin>>rno;
        if(rno<=0)          // Validating
        {
            cout<<endl<<"This room number is invalid! Please re-enter the room number: ";
            goto flag;
        }
        for(int i=0; i<nroom;i++)       // Validating for Repetitive Room Numbers
        {
            if(a[i].roomNumber==rno)
            {
                cout<<"Invalid. Repetitive room numbers."<<endl;
                goto flag;
            }
        }
        a[i].acceptroom(rno);
    }
}
void Hotel::availability()          // Checking Availability of the Rooms
{
    if(nroom==0)
    {
        cout<<"Please add rooms."<<endl;
        return;
    }
    cout<<"The list of all available rooms: "<<endl;
    cout<<"| Room No.\t|\tAC/Non-AC\t|\tType\t\t|\tSize\t\t|\tRent\t\t|\tAvailability\t|"<<endl;
    for(int i=0;i<nroom;i++)
    {
        a[i].displayroom();     //Displaying Room Details
    }
}
void Hotel::searchroom()        // Search for a particular type of a room
{
    if(nroom==0)
    {
        cout<<"Please add rooms."<<endl;
        return;
    }
    int flag=0;
    char ac1, type1, stype1;
    cout<<"Do you want AC or Non-AC? (A/N): "<<endl;
    cin>>ac1;
    cout<<"Do you want deluxe or normal room?"<<endl;
    cin>>type1;
    cout<<"Size? (B/S)"<<endl;
    cin>>stype1;
    for(int i=0;i<nroom;i++)
    {
        if(a[i].ac==ac1 && a[i].type==type1 && a[i].stype==stype1)      // Checking all conditions are met
        {
            flag=1;
            cout<<"Room found"<<endl;
            a[i].displayroom();
        }
    }
    if(flag==0)
    {
        cout<<"No such room is available."<<endl;
    }
}
void Hotel::CheckIn()           //Check In process of a Customer
{
    if(nroom==0)
    {
        cout<<"Please add rooms."<<endl;
        return;
    }
    int i, rno;
    if(ncust<=nroom){
        c[ncust].booking_id=ncust+1;
        flag:
        int flag1=0;
        cout<<"Enter room number: ";    // Asking what room number customer wants
        cin>>rno;
        for(i=0;i<nroom; i++){
            if(rno==a[i].roomNumber)
            {
                flag1=1;
                break;
            }
        }
        if(flag1==0){
            cout<<"Invalid room number. Please re-enter room number. \n";
            goto flag;
        }
        if(a[i].status==0)
        {
            char ch2;
            cout<<"Room available."<<endl;
            a[i].displayroom();
            cout<<"Do you wish to continue? Press(Y)";      // Booking Confirmation
            cin>>ch2;
            if(ch2=='Y'||ch2=='y')
            {
                c[ncust].accept();          // Accepting Customer Details
                cout<<"Enter number of days of stay: ";
                cin>>c[ncust].days;
                c[ncust].bill = c[ncust].days*a[i].rent;        // Generates bill of Stay
                cout<<"Your total bill will be approximately Rs. "<<(c[ncust].bill)<<","<<". Min adv payment-"<<c[ncust].bill/4<<"How much do you wish to pay in advance?";
                cin>>c[ncust].payment_advance;
                while(c[ncust].payment_advance<c[ncust].bill/4||c[ncust].payment_advance>c[ncust].bill)
                {
                    cout<<"Enter valid amount.";
                    cin>>c[ncust].payment_advance;
                }
                cout<<"Thank you. Booking confirmed."<<endl;    // Booking Confirmed
                cout<<"--------------------------------------------"<<endl;
                cout<<"Booking Id: "<<c[ncust].booking_id<<"\nName: "<<c[ncust].name<<"\nRoom No.: "<<rno<<"\nDate: ";
                time_t my_time = time(NULL);
                        //ctime() used to give the present time
                printf("%s", ctime(&my_time));
                a[i].status=1;          // Changing room status to booked
                c[ncust].room=rno;      // Alloting room to customer
                c[ncust].status=1;
                ncust++;                       
            }
            else                // If needs to change room number
            {
                goto flag;
            }
        }
        else            // If room is occupied
        {
            cout<<"Room Occupied. Please choose another room."<<endl; 
        }
    }
    else            // Conditions if all rooms are booked
    {
        cout<<"Sorry! Hotel is all booked."<<endl;
    }
}
void Hotel::searchcust()
{
    int id, flag=0;
    cout<<"Enter booking ID of the customer: ";
    cin>>id;
    for(int i=0; i<=ncust;i++)          // Searching for the customer
    {
        if(c[i].booking_id==id)
        {
            cout<<"\t\t\t Name"<<setw(20);
            cout<<"\t\t\t Phone"<<setw(20);
            cout<<"\t\t\t Address"<<setw(20);
            cout<<"\t\t\t Room No: "<<setw(20)<<endl;
            c[i].display();
            flag=1;
        }
    }
    if(flag==0)                     // Case not Found
    {
        cout<<"No Customer Found."<<endl;
    }
}
void Hotel::CheckOut()      // Checking Out
{
    int rno, i, j;
    cout<<"Enter room number: ";
    cin>>rno;
    for(j=0;j<nroom; j++){
        if(rno==a[j].roomNumber)
        {
            break;
        }
    }
    if(a[j].status==0)              // Condition if room is found unoccupied
    {
        cout<<"Invalid."<<endl;
    }
    for(i=0;i<ncust;i++)            // Checking Customer Details
    {
        if(c[i].room==rno)
        {
            cout<<"Checking Out."<<endl;
            c[i].display();         // Customer Details
            cout<<"Your total bill is "<<c[i].bill<<endl;
            cout<<"Advance payment: "<<c[i].payment_advance;
            cout<<endl<<"Hence, Pending Payment = Rs. "<<c[i].bill-c[i].payment_advance;
            cout<<endl<<"Thank You! Visit Again :)"<<endl;
            a[j].status=0;          // Changing Status of room To Unoccupied
            c[i].status=0;          // Checked Out
            break;
        }
    }
}

void Hotel::Summary()               // Printing List of All Customers
{
    if(nroom==0)
    {
        cout<<"No customers as of yet."<<endl;
        return;
    }
    cout<<"Guest Summary: "<<endl;
    cout<<"ID\t\t";
    cout<<"|    Name    \t\t";
    cout<<"|    Phone   \t\t";
    cout<<"|    Address \t\t";
    cout<<"|    Room No.  \t";
    cout<<"|    Status  \t\t|"<<endl;
    for(int i=0;i<ncust;i++)
    {
        c[i].display();
    }
}

int main()
{
    Hotel FusionLounge;         // Creating Object of Class Hotel
    char ch;
    cout<<endl<<"----------------------------------------------------WELCOME TO FUSION LOUNGE HOTEL--------------------------------------";
    do
    {               // Menu to use as either Admin or when a Customer checks in
        cout<<endl<<"------------------------------------------------------------------------------------------------------------------------";
        cout<<endl<<"\t\t\t\t\t\t\t\t\t"
                "MENU: \n\t\t\t\t\t\t\t\t"
                "1. OPERATE AS HOTEL ADMIN \n\t\t\t\t\t\t\t\t\t"
                "2. OPERATE FOR CUSTOMER CHECK IN \n\t\t\t\t\t\t\t\t\t"
                "3. EXIT \n\t\t\t\t\t\t\t\t\t"
                "Enter your choice: ";
        cin>>ch;
        switch(ch)
        {
        case '1':
            cout<<"Add database of rooms in the hotel: "<<endl;
            FusionLounge.addRooms();
            cout<<"Database updated. Switching back to main menu."<<endl;
            break;
        case '2':
            char ch1;
            do
            {
                //MENU 2 TO USE WHEN A CUSTOMER WANTS TO CHECK IN
                cout<<endl<<"-----------------------------------------WELCOME TO FUSION LOUNGE HOTEL--------------------------------"<<endl;
                cout<<"\n\t\t\t\t\t\t\t\t"
                        "Menu: \n\t\t\t\t\t\t\t"
                        "1.Check Availability of rooms.\n\t\t\t\t\t\t\t\t\t"
                        "2.Search Rooms.\n\t\t\t\t\t\t\t"
                        "3.Check In\n\t\t\t\t\t\t\t\t"
                        "4.Search Customer.\n\t\t\t\t\t\t\t\t"
                        "5.Guest Summary. \n\t\t\t\t\t\t\t\t"
                        "6.Checkout Process. \n\t\t\t\t\t\t\t\t"
                        "7.Go Back to Main Menu.\n\t\t\t\t\t\t\t\t"
                        "Enter your Choice: ";
                cin>>ch1;
                switch(ch1)
                {
                case '1':
                    FusionLounge.availability();
                    break;
                case '2':
                    FusionLounge.searchroom();
                    break;
                case '3':
                    FusionLounge.CheckIn();
                    break;
                case '4':
                    FusionLounge.searchcust();
                    break;
                case '5':
                    FusionLounge.Summary();
                    break;
                case '6':
                    FusionLounge.CheckOut();
                    break;
                case '7':
                    break;
                default:
                    cout<<"Invalid Choice."<<endl;
                    break;            
                }
            }while(ch!='7');
            break;
        case '3':
            cout<<"Thank you!";
            exit(0);
        default:
            cout<<"Invalid Choice."<<endl;
            break;
        }
    }while(ch!='3');
    return 0;
}
