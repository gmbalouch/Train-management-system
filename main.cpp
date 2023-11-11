#include <iostream>
#include <mysql.h>
#include<mysqld_error.h>
#include<string>

#include<unistd.h>
#include<conio.h>
#include<iomanip>
using namespace std;

class TrainSystem{
	private:
		MYSQL* conn;
	
	public:	
		TrainSystem(){
			char HOST[]="localhost";
			char USER[]="root";
			char PASS[]="123abcxyzgm";	
				
			
	  		conn=mysql_init(0);	 	
			if(!mysql_real_connect(conn,HOST,USER,PASS, "trainsystem", 3306, NULL,0)){
	 			cout<<"ERROR: Some database info is wrong or do not exit.."<<endl;
				cout<<mysql_error(conn)<<endl;
			}
			else{
				cout<<"\t\t\t\t\tDatabase connected...."<<endl<<endl;
			}
			Sleep(1000);
		}	
		///////////////////end of constructor
	
		void userGuide(){
			system("cls");
			cout<<"\t\t\t\t ========================"<<endl
				<<"\t\t\t\t|       USER'S GUIDE     |"<<endl
				<<"\t\t\t\t ========================"<<endl<<endl
				
				<<"\t\t\t->Please don't use space, use \'_\' instead of space."<<endl
				<<"\t\t\tPress any key to continue...";
				getch();
		}
		
		bool login(){
			string user;
			string password;
			bool condition=false;
			int sellog;
			
			do{
				
				system("cls");
				cout<<"\t\t\t\t\t ============================"<<endl
					<<"\t\t\t\t\t|       SIGN UP OR LOGIN     |"<<endl
					<<"\t\t\t\t\t ============================"<<endl<<endl
					<<"\t\t\t\t\t ============================"<<endl
					<<"\t\t\t\t\t| 1- Create new account      |"<<endl
					<<"\t\t\t\t\t| 2- Login into account      |"<<endl
					<<"\t\t\t\t\t| 3- EXIT                    |"<<endl
					<<"\t\t\t\t\t ============================"<<endl<<endl
					
					<<"\t\t\t\t\tENTER YOUR SELECTION: ";			
					cin>>sellog;
				
				if(sellog==1){
					system("cls");
					cout<<"\t\t\t\t\t ============================"<<endl
						<<"\t\t\t\t\t|        SIGN UP HERE        |"<<endl
						<<"\t\t\t\t\t ============================"<<endl<<endl
					
						<<"\t\t\t\t\tEnter new User Name: ";
					cin>>user;
					cout<<"\t\t\t\t\tEnter new Password:  ";
					cin>>password;
				
					string insertLog="INSERT INTO LOGIN(USER_NAME,PASSWORD) VALUES('"+user+"','"+password+"')";
					
					if(mysql_query(conn,insertLog.c_str())){
						cout<<"Error: "<<mysql_error(conn)<<endl;
						Sleep(1000);
					}
					else{
						Sleep(1000);
						cout<<"Account created successfully, press any key to continue.. "<<endl;
					}					
					sellog=2;
					cout<<"\t\t\tPress any key to continue...";
					getch();
				}	
			
				else if(sellog==2){
					system("cls");
					cout<<"\t\t\t\t\t ============================"<<endl
						<<"\t\t\t\t\t|       LOGIN HERE           |"<<endl
						<<"\t\t\t\t\t ============================"<<endl<<endl;
					cout<<"\t\t\t\t\tEnter User Name: ";
					cin>>user;
					cout<<"\t\t\t\t\tEnter Password:  ";
					cin>>password;
				
					string loginquery="SELECT USER_NAME, PASSWORD FROM LOGIN WHERE USER_NAME='"+user+"' AND PASSWORD='"+password+"'";
					
					if(mysql_query(conn,loginquery.c_str())){
						cout<<"Error: "<<mysql_error(conn)<<endl;
						Sleep(1000);
					}
					else{
						MYSQL_RES* res;
						res=mysql_store_result(conn);
						if(res){
							int row=mysql_num_rows(res);
							if(row==1){
								Sleep(1000);
								cout<<"\t\t\t\t\tYou Login...";
								condition=true;
							}			
						}
					}//end else				
				}
				else if(sellog==3){
				cout<<"\n\n\t\t\t\t\t PROGRAM EXITED...";
				exit(0);
				
				} 
			
				else {
					cout<<"Invalid selection"<<endl;
					cout<<"Press any key to continue.. "<<endl;
					getch();
				} 
				
			}while(sellog!=2 && sellog!=1);
			
			return condition;
		}
		
		void newTrain(){
			system("cls");
			string train_no;
			string route;
			string no_of_seats;
			string timings;
			string rent;
			
			cout<<"\t\t\t\t\t ================================"<<endl
				<<"\t\t\t\t\t|       CREATE A NEW TRAIN        |"<<endl
				<<"\t\t\t\t\t ================================"<<endl<<endl;
	
			cout<<"\t\t\t\t\tEnter Train Number:    ";
			cin>>train_no;
			cout<<"\t\t\t\t\tEnter Route:           ";
			cin>>route;
			cout<<"\t\t\t\t\tEnter Number Of Seats: ";
			cin>>no_of_seats;
			cout<<"\t\t\t\t\tEnter Timings:         ";	
			cin>>timings;
			cout<<"\t\t\t\t\tEnter Rent:            ";
			cin>>rent;
			
			string insertTrains="INSERT INTO TRAINS(TRAIN_ID,ROUTE,NO_OF_SEATS,TIMING,RENT) VALUES('"+train_no+"','"+route+"','"+no_of_seats+"','"+timings+"','"+rent+"')";
					
			if(mysql_query(conn,insertTrains.c_str())){
				cout<<"Error: "<<mysql_error(conn)<<endl;
				Sleep(1500);
			}
			else{
				cout<<"\t\t\t\t\tData Inserted Successfuly."<<endl;
				Sleep(1500);
			}				
		
			cout<<endl<<"\n\t\t\t\tPress key to continue....";
			getch();	
		}//end trains
		
		void viewAllTrains(){
			system("cls");
			
			cout<<"\t\t\t ================================"<<endl
				<<"\t\t\t|         CURRENT TRAINS         |"<<endl
				<<"\t\t\t ================================"<<endl;
				
			string showTrainsquery="SELECT * FROM TRAINS";
			if(mysql_query(conn,showTrainsquery.c_str()))
			{
				cout<<"Error:"<<mysql_error(conn);
			}else{
				MYSQL_RES* result=mysql_store_result(conn);
				if(result){
					int num=mysql_num_fields(result);
					MYSQL_ROW row;
					cout<<endl;
					cout<<" ======================================================================================"<<endl;
					cout<<setw(20)<<left<<"|TRAIN ID"<<setw(20)<<"ROUTE"<<setw(20)<<"NO_OF_SEATS"<<setw(20)<<"TIMING"<<setw(20)<<"RENT   |"<<endl;
					cout<<" ======================================================================================"<<endl;
					
					while(row=mysql_fetch_row(result)){
						cout<<"|";
						for(int i=0; i<num; i++){
							if(i<num-1)cout<<setw(20)<<left<<row[i];
							else cout<<setw(6)<<left<<row[i]<<"|";
						}//end for
						cout<<endl;
					}//end while
					cout<<" ======================================================================================"<<endl;
					//Sleep(1500);			
				}//if result
				
			}//else
			
			cout<<endl<<"\n\t\t\t\tPress key to continue....";
			getch();	
		}//trains list
		
	void searhTrain(){
		system("cls");
		cout<<"\t\t\t\t ================================"<<endl
			<<"\t\t\t\t|         SEARCH TRAIN           |"<<endl
			<<"\t\t\t\t ================================"<<endl;
			
		int train_id;
		cout<<"\t\t\t\tENTER TRAIN ID:";
			cin>>train_id;
			
		string searchquery="SELECT * FROM TRAINS WHERE TRAIN_ID='"+to_string(train_id)+"'";
		if(mysql_query(conn,searchquery.c_str()))
		{
			cout<<"Error:"<<mysql_error(conn);
		}else{
			MYSQL_RES* result=mysql_store_result(conn);
			if(result){
				int num=mysql_num_fields(result);
				MYSQL_ROW row;
				cout<<endl;
				cout<<" ======================================================================================"<<endl;
				cout<<setw(20)<<left<<"|TRAIN ID"<<setw(20)<<"ROUTE"<<setw(20)<<"NO_OF_SEATS"<<setw(20)<<"TIMING"<<setw(20)<<"RENT   |"<<endl;
				cout<<" ======================================================================================"<<endl;			
				
				while(row=mysql_fetch_row(result)){
					cout<<"|";
					for(int i=0; i<num; i++){
						if(i<num-1)cout<<setw(20)<<left<<row[i];
						else cout<<setw(6)<<left<<row[i]<<"|";
					}//end for
					cout<<endl;
				}//end while
				cout<<" --------------------------------------------------------------------------------------"<<endl;	
					Sleep(1500);			
			}//if result
				
		}//else
		cout<<endl<<"\n\t\t\t\tPress key to continue....";
		getch();
		
	}//view searchTrain
		
	void newBooking(){
		system("cls");
		cout<<"\t\t\t\t\t ================================"<<endl
			<<"\t\t\t\t\t|       ENTER NEW BOOKING        |"<<endl
			<<"\t\t\t\t\t ================================"<<endl<<endl;
		string booking_id;
		string passenger_name;
		string no_of_tickets;
		string route;
		string timing;
		string rent;
			
		cout<<"\t\t\t\t\t Enter Booking Id:        ";
		cin>>booking_id;
		cout<<"\t\t\t\t\t Enter Name Of Passenger: ";
		cin>>passenger_name;
		cout<<"\t\t\t\t\t Enter Number Of Tickets: ";
		cin>>no_of_tickets;
		cout<<"\t\t\t\t\t Enter Route:             ";	
		cin>>route;	
			
		string trainquery="SELECT ROUTE, TIMING, RENT FROM TRAINS WHERE ROUTE='"+route+"'";			
		if(mysql_query(conn,trainquery.c_str())){
			cout<<"Error: "<<mysql_error(conn)<<endl;
		}
		else{
			MYSQL_RES* res;
			res=mysql_store_result(conn);
			if(res){		
				int row=mysql_num_rows(res);
				MYSQL_ROW rowfetch=mysql_fetch_row(res);
				timing=rowfetch[1];
				rent=rowfetch[2];
					
				if(row>=1){
					string insertBookings="INSERT INTO BOOKINGS(BOOKING_ID,PASSENGER_NAME,NO_OF_TICKETS,ROUTE,TIMING,RENT) VALUES('"+booking_id+"','"+passenger_name+"','"+no_of_tickets+"','"+route+"','"+timing+"','"+rent+"')";
					if(mysql_query(conn,insertBookings.c_str())){
						cout<<"Error: "<<mysql_error(conn)<<endl;
						Sleep(1500);
					}
					else{
						cout<<"\t\t\t\t\t Enter Timings:           "<<timing<<endl;
						cout<<"\t\t\t\t\t Enter Rent:              "<<rent<<endl<<endl;							
						cout<<"\t\t\t\t\tData Inserted Successfuly."<<endl;
						Sleep(1500);
					}//end else						
				}//end if
								
			}//resquest
						
		}//end else
		cout<<endl<<"\n\t\t\t\tPress key to continue....";
		getch();
			
	}//bookingtickets
		
	void viewBookings(){
		system("cls");
		cout<<"\t\t\t\t ================================"<<endl
			<<"\t\t\t\t|         ALL BOOKINGS           |"<<endl
			<<"\t\t\t\t ================================"<<endl;
		
		string showBookingsquery="SELECT * FROM BOOKINGS";
		if(mysql_query(conn,showBookingsquery.c_str()))
		{
			cout<<"Error:"<<mysql_error(conn);
		}else{
			MYSQL_RES* result=mysql_store_result(conn);
			if(result){
				int num=mysql_num_fields(result);
				MYSQL_ROW row;
				cout<<endl;
				cout<<" =========================================================================================================="<<endl;
				cout<<setw(20)<<left<<"|BOOKING_ID"<<setw(20)<<"PASSENGER_NAME"<<setw(20)<<"NO_OF_TICKETS"<<setw(20)<<"ROUTE"<<setw(20)<<"TIMING"<<setw(10)<<"RENT   |"<<endl;			
				cout<<" =========================================================================================================="<<endl;
				while(row=mysql_fetch_row(result)){
					cout<<"|";
					for(int i=0; i<num; i++){
						if(i<num-1)cout<<setw(20)<<left<<row[i];
						else cout<<setw(6)<<left<<row[i]<<"|";
					}//end for
					cout<<endl;
				}//end while
				cout<<" =========================================================================================================="<<endl;	
					//Sleep(1500);			
			}//if result
				
		}//else
		
		cout<<endl<<"\n\t\t\t\tPress key to continue....";
		getch();
	}//view tickets
	
	void searhBooking(){
		system("cls");
		cout<<"\t\t\t\t ================================"<<endl
			<<"\t\t\t\t|         SEARCH BOOKING           |"<<endl
			<<"\t\t\t\t ================================"<<endl;
			
		int booking_id;
		cout<<"\t\t\t\tENTER BOOKING ID:";
			cin>>booking_id;
		
		string searchquery="SELECT * FROM BOOKINGS WHERE BOOKING_ID='"+to_string(booking_id)+"'";
		if(mysql_query(conn,searchquery.c_str()))
		{
			cout<<"Error:"<<mysql_error(conn);
		}else{
			MYSQL_RES* result=mysql_store_result(conn);
			if(result){
				int num=mysql_num_fields(result);
				MYSQL_ROW row;
				cout<<endl;
				cout<<" =========================================================================================================="<<endl;
				cout<<setw(20)<<left<<"|BOOKING_ID"<<setw(20)<<"PASSENGER_NAME"<<setw(20)<<"NO_OF_TICKETS"<<setw(20)<<"ROUTE"<<setw(20)<<"TIMING"<<setw(10)<<"RENT   |"<<endl;			
				cout<<" ----------------------------------------------------------------------------------------------------------"<<endl;			
				while(row=mysql_fetch_row(result)){
					cout<<"|";
					for(int i=0; i<num; i++){
						if(i<num-1)cout<<setw(20)<<left<<row[i];
						else cout<<setw(6)<<left<<row[i]<<"|";
					}//end for
					cout<<endl;
				}//end while
				cout<<" ----------------------------------------------------------------------------------------------------------"<<endl;	
					//Sleep(1500);			
			}//if result
				
		}//else
		
		cout<<endl<<"\n\t\t\t\tPress key to continue....";
		getch();
	}//search Ticket
			
			
	
	void developer(){
		system("cls");
		cout<<"\t\t\t\t =============================================="<<endl
			<<"\t\t\t\t|  NAME:          GM BALOCH                    |"<<endl
			<<"\t\t\t\t|  ROLL NO:       23SW086                      |"<<endl
			<<"\t\t\t\t|  SEMESTER:      FIRST                        |"<<endl
			<<"\t\t\t\t|  PROJECT:       TRAIN MANAGEMENT SYSTEM      |"<<endl
			<<"\t\t\t\t|  SUBMITTED TO:  SIR SAJJAD                   |"<<endl
			<<"\t\t\t\t =============================================="<<endl;
			
			cout<<endl<<"\n\t\t\t\tPress key to DASHBOARD....";
			getch();
	}
};

int main() {
	TrainSystem trainsys;
	
	trainsys.userGuide();	
	
	do{
		
		if(trainsys.login()){
			int selection;
		
			do{
				system("cls");
				cout<<endl<<endl;
				cout<<"\t\t\t\t    ================================================"<<endl;
				cout<<"\t\t\t\t   |      WELCOME TO TRAIN MANAGEMENT SYSTEM:       |"<<endl;
				cout<<"\t\t\t\t    ================================================"<<endl<<endl;
				cout<<"\t\t\t\t    ================================================"<<endl;
				cout<<"\t\t\t\t   |      1-CREATE NEW TRAIN OPERATION.             |"<<endl;
				cout<<"\t\t\t\t   |      2-VIEW ALL TRAINS.                        |"<<endl;		
				cout<<"\t\t\t\t   |      3-SEARCH A TRAIN.                         |"<<endl;
				cout<<"\t\t\t\t   |      4-NEW BOOKING:                            |"<<endl;
				cout<<"\t\t\t\t   |      5-VIEW BOOKINGS:                          |"<<endl;
				cout<<"\t\t\t\t   |      6-SEARCH BOOKING:                         |"<<endl;
				cout<<"\t\t\t\t   |      7-ABOUT DEVELOPER:                        |"<<endl;
				cout<<"\t\t\t\t   |      8-LOGOUT:                                 |"<<endl;
				cout<<"\t\t\t\t    ================================================"<<endl<<endl;
			
				cout<<"\t\t\t\tENTER SELECTION:";
				cin>>selection;
			
				if(selection==1)trainsys.newTrain();
				if(selection==2)trainsys.viewAllTrains();
				if(selection==3)trainsys.searhTrain();
				if(selection==4)trainsys.newBooking();
				if(selection==5)trainsys.viewBookings();
				if(selection==6)trainsys.searhBooking();
				if(selection==7)trainsys.developer();  
			
			}while(selection!=8);
		}//end login if
		cout<<"\n\t\t\t\t\tINVALID USER OR PASSWORD"<<endl;
		cout<<"\n\n\t\t\t\t\tPress any key to try again....";
		getch();
	}while(true);
	return 0;
}//end main     PF PROJECT
