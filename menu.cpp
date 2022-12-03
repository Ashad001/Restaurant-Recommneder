#include <iostream>
#include <windows.h> // for sleep()
#include <conio.h>
#include <cstdlib>
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto


using namespace std;
void loadname();
void loader();
void ccolor(int);
void userinput();
void showcredits();
void dname();
void gotoXY(int,int);
void mainmenu();
void timingmenu();
void reservmenu();
void budgetmenu();
void cuisinemenu();
string userbudget,userreserv,usertiming,usercuisine;
int main()
{
	
	loader();
    loadname();
    ccolor(15);   
    cout<<endl<<endl;
	showcredits(); 
	system("cls");
	dname();  
    userinput();

    return 0;
}
void gotoXY(int x, int y) 
{ 
	CursorPosition.X = x; 
	CursorPosition.Y = y; 
	SetConsoleCursorPosition(console,CursorPosition); 
}
void dname(){
	ccolor(4);
	cout<<"\t\t\t\t\tD E L I S H \tA D V O C A C Y";
	ccolor(15);
}
void ccolor(int clr){

	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, clr);

}
void userinput(){
	
	cout<<endl<<endl<<"\t\t\t\t\t\tWelcome User !";
	Sleep(1000);
	system("cls");
	dname();
	cout<<endl<<endl<<"\t\tJust Answer A Few Questions And We Will Pick Out The Perfect Restraunt For You !!";
	Sleep(5000);
	system("cls");
	dname();
	mainmenu();
}
void loader(){
	ccolor(26);
    std::cout << '-' << std::flush;
    for (int i=0;i<20;i++) {
        Sleep(10);
        std::cout << "\b\\" << std::flush;
        Sleep(10);
        std::cout << "\b|" << std::flush;
        Sleep(10);
        std::cout << "\b/" << std::flush;
        Sleep(10);
        std::cout << "\b-" << std::flush;
    }
ccolor(4);
   

}
void loadname(){
	
		Sleep(100);;
		std::cout << "\bD" << std::flush;
        Sleep(100);;
        std::cout << " E" << std::flush;
        Sleep(100);;
        std::cout << " L" << std::flush;
        Sleep(100);;
        std::cout << " I" << std::flush;
        Sleep(100);;
        std::cout << " S" << std::flush;
        Sleep(100);;
        std::cout << " H" << std::flush;
        Sleep(100);;
        std::cout << "\t";
        std::cout << " A" << std::flush;
        Sleep(100);;
        std::cout << " D" << std::flush;
        Sleep(100);;
        std::cout << " V" << std::flush;
        Sleep(100);;
        std::cout << " O" << std::flush;
        Sleep(100);;
        std::cout << " C" << std::flush;
        Sleep(100);;
        std::cout << " A" << std::flush;
        Sleep(100);;
        std::cout << " C" << std::flush;
        Sleep(100);;
        std::cout << " Y" << std::flush;
}
void showcredits() {
	cout<<"by ";
	ccolor(10);
	cout << "Ashad";
	Sleep(1000);;
	cout<<" ";
	ccolor(12);
	cout << "Haseeb";
	Sleep(1000);;
	cout<<" ";
	ccolor(14);
	cout << "Tahir";
	Sleep(1000);;
	ccolor(15);
}
void budgetmenu(){
	int menu_item=0, run, x=7;
	bool running = true;
	
	gotoXY(45,5); cout << "What Is Your Budget";
	gotoXY(45,7); cout << "->";
	
	while(running)
	{
        gotoXY(47,7);  cout << "1) Above 5000 rupees";
		gotoXY(47,8); cout << "2) Below 5000 rupees";
		gotoXY(47,9); cout << "3) Go Back To Main Menu";
		system("pause>nul"); // the >nul bit causes it the print no message
		
		if(GetAsyncKeyState(VK_DOWN) && x != 9) //down button pressed
			{
				gotoXY(45,x); cout << "  ";
				x++;
				gotoXY(45,x); cout << "->";
				menu_item++;
				continue;
				
			}
			
		if(GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
			{
				gotoXY(45,x); cout << "  ";
				x--;
				gotoXY(45,x); cout << "->";
				
				menu_item--;
				continue;
			}
			
			
			
		if(GetAsyncKeyState(VK_RETURN)){ // Enter key pressed
			
			switch(menu_item){
				
				case 0: {
					system("cls");
					dname();
					userbudget="above 5k";
					gotoXY(20,21);cout<<userbudget<<userreserv<<usertiming<<usercuisine;
					running = false;
					break;
				}	
				case 1: {
					system("cls");
					dname();
					userbudget="below 5k";
					gotoXY(20,21);cout<<userbudget<<userreserv<<usertiming<<usercuisine;
					running = false;
					break;
				}
				case 2: {
					running = false;
					system("cls");
					dname();
					mainmenu();
					break;
				}
			}
				
		}		
		
	}
	
	gotoXY(20,21);
	
	
}
void reservmenu(){
	int menu_item=0, run, x=7;
	bool running = true;
	
	gotoXY(45,5); cout << "What You Prefer Reservation";
	gotoXY(45,7); cout << "->";
	
	while(running)
	{
        gotoXY(47,7);  cout << "1) Yes";
		gotoXY(47,8); cout << "2) No";
		gotoXY(47,9); cout << "3) Go Back To Main Menu";
		system("pause>nul"); // the >nul bit causes it the print no message
		
		if(GetAsyncKeyState(VK_DOWN) && x != 9) //down button pressed
			{
				gotoXY(45,x); cout << "  ";
				x++;
				gotoXY(45,x); cout << "->";
				menu_item++;
				continue;
				
			}
			
		if(GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
			{
				gotoXY(45,x); cout << "  ";
				x--;
				gotoXY(45,x); cout << "->";
				
				menu_item--;
				continue;
			}
			
			
			
		if(GetAsyncKeyState(VK_RETURN)){ // Enter key pressed
			
			switch(menu_item){
				
				case 0: {
					system("cls");
					dname();
					timingmenu();
					running = false;
					break;
				}	
				case 1: {
					system("cls");
					dname();
					userreserv="Yes";
					timingmenu();
					running = false;
					break;
				}
				case 2: {
					running = false;
					system("cls");
					dname();
					userreserv="No";
					mainmenu();
					break;
				}
			}
				
		}		
		
	}
	
	gotoXY(20,21);
	
	
}
void timingmenu(){
	int menu_item=0, run, x=7;
	bool running = true;
	
	gotoXY(45,5); cout << "What Timing Would You Prefer";
	gotoXY(45,7); cout << "->";
	
	while(running)
	{
        gotoXY(47,7);  cout << "1) Lunch";
		gotoXY(47,8); cout << "2) Dinner";
		gotoXY(47,9); cout << "3) Go Back to Main Menu";
		system("pause>nul"); // the >nul bit causes it the print no message
		
		if(GetAsyncKeyState(VK_DOWN) && x != 9) //down button pressed
			{
				gotoXY(45,x); cout << "  ";
				x++;
				gotoXY(45,x); cout << "->";
				menu_item++;
				continue;
				
			}
			
		if(GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
			{
				gotoXY(45,x); cout << "  ";
				x--;
				gotoXY(45,x); cout << "->";
				
				menu_item--;
				continue;
			}
			
			
			
		if(GetAsyncKeyState(VK_RETURN)){ // Enter key pressed
			
			switch(menu_item){
				
				case 0: {
					system("cls");
					dname();
					usertiming="Lunch";
					budgetmenu();
					running = false;
					break;
				}	
				case 1: {
					system("cls");
					dname();
					usertiming="Dinner";
					budgetmenu();
					running = false;
					break;
				}
				case 2: {
					running = false;
					system("cls");
					dname();
					mainmenu();
					break;
				}
			}
				
		}		
		
	}
	
	gotoXY(20,21);
	
	
}
void cuisinemenu(){
	int menu_item=0, run, x=7;
	bool running = true;
	
	gotoXY(45,5); cout << "What Cuisine Would You Prefer";
	gotoXY(45,7); cout << "->";
	
	while(running)
	{
        gotoXY(47,7);  cout << "1) American ";
		gotoXY(47,8); cout << "2) Desi";
		gotoXY(47,9); cout << "3) Main Menu";
		system("pause>nul"); // the >nul bit causes it the print no message
		
		if(GetAsyncKeyState(VK_DOWN) && x != 9) //down button pressed
			{
				gotoXY(45,x); cout << "  ";
				x++;
				gotoXY(45,x); cout << "->";
				menu_item++;
				continue;
				
			}
			
		if(GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
			{
				gotoXY(45,x); cout << "  ";
				x--;
				gotoXY(45,x); cout << "->";
				
				menu_item--;
				continue;
			}
			
			
			
		if(GetAsyncKeyState(VK_RETURN)){ // Enter key pressed
			
			switch(menu_item){
				
				case 0: {
					system("cls");
					dname();
					usercuisine="American";
					reservmenu();
					running = false;
					break;
				}	
				case 1: {
					system("cls");
					dname();
					usercuisine="Desi";
					reservmenu();
					running = false;
					break;
				}
				case 2: {
					running = false;
					system("cls");
					dname();
					mainmenu();
					break;
				}
			}
				
		}		
		
	}
	
	gotoXY(20,21);
	
	
}
void mainmenu(){
	int menu_item=0, run, x=7;
	bool running = true;
	
	gotoXY(50,5); cout << "Main Menu";
	gotoXY(45,7); cout << "->";
	
	while(running)
	{
        gotoXY(47,7);  cout << "1) Find A Resturaunt !";
		gotoXY(47,8); cout << "2) Quit Program";

		system("pause>nul"); // the >nul bit causes it the print no message
		
		if(GetAsyncKeyState(VK_DOWN) && x != 8) //down button pressed
			{
				gotoXY(45,x); cout << "  ";
				x++;
				gotoXY(45,x); cout << "->";
				menu_item++;
				continue;
				
			}
			
		if(GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
			{
				gotoXY(45,x); cout << "  ";
				x--;
				gotoXY(45,x); cout << "->";
				
				menu_item--;
				continue;
			}
			
			
			
		if(GetAsyncKeyState(VK_RETURN)){ // Enter key pressed
			
			switch(menu_item){
				
				case 0: {
					
					gotoXY(47,16);
					cout << "Finding Restraunts !";
					Sleep(100);
					cout<<" \b.";
					for(int i=0;i<3;i++){
					Sleep(100);
					cout<<" \b.";
					}
					system("cls");
					dname();
					cuisinemenu();
					break;
				}	
				case 1: {
					gotoXY(47,16);
					cout << "The program has now terminated!!";
					exit(0);
					running = false;
				}
				
			}
				
		}		
		
	}
	
	gotoXY(20,21);
	
	
}
