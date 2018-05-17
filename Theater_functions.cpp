/****************************************************************************
 * 
 * Proj.03: Theater Seating Chart
 *  
 * File Name: Theater_Functions.cpp
 * Name:      Austin Garner
 * Course:    CPTR 141
 * Date:      December 8, 2017
 * 
 */   

#include "Theater.h"
#include <iostream> // for cout and cin
#include <fstream> // for fout and fin
#include <iomanip> // for setw
using namespace std;

/*==========================================================================
 * Function: void ConfigArray(int&,int&,double);
 * 
 * Precondition: The first and second parameters are int variables, and the
 *               third parameter is a multidimensional array
 * Postcondition: Gets seating chart from user or from file
 *                
 */
void ConfigArray(int &RowSize, int &ColumnSize, double TheaterPrices[][COLUMN]) {
    //see if file exists
    ifstream fin;
    fin.open("theater.txt");
    
    //if the file doesn't exist
    if(!fin) {
        GetInfo(RowSize,ColumnSize,TheaterPrices);
    } else {
        //get array size from file
        fin >> RowSize >> ColumnSize;
        //loop to collect row prices from file
        for(int i=0; i<RowSize; i++) {
            for (int a=0; a<ColumnSize; a++) {
                fin >> TheaterPrices[i][a];
            }
        }
    }
}

/*==========================================================================
 * Function: void GetInfo(int&,int&,double[][COLUMN]);
 * 
 * Precondition: The first parameter is an int variable, the second parameter is an int variable,
 *               and the third parameter is an array of type double
 * Postcondition: Gets the theater size and row prices from user, and then outputs this to a file  
 *                
 */
void GetInfo(int &RowSize,int &ColumnSize,double TheaterPrices[][COLUMN]) {
    int Error=0;
    //open the file to putput
        ofstream fout;
        fout.open("theater.txt");
        if( !fout ) {
            cout << "can't open file" << endl;
        } else {
            //ask for theater dimentions
            cout << "Within the bounds of 80x80, enter the dimentions of your theater." << endl;
            
            //loop to collect rows
            do {
                Error=0;
                
                cout << "Enter the number of rows: ";
                cin  >> RowSize;
                //check for errors
                if(!cin || RowSize>ROW) {
                    cin.clear();
                    cin.ignore(1000,'\n');
                    cerr << "Invalid length. Please try again.\n";
                    Error=1;
                }
            } while (Error==1);
            
            //loop to collect columns
            do {
                Error=0;
                
                cout << "Enter the number of columns: ";
                cin  >> ColumnSize;
                //check for errors
                if(!cin || ColumnSize>COLUMN) {
                    cin.clear();
                    cin.ignore(1000,'\n');
                    cerr << "Invalid length. Please try again.\n";
                    Error=1;
                }
            } while (Error==1);
            
            //loop to collect row prices
            for(int i=0; i<RowSize; i++) {
                int Number=0;
                //loop to get prices for the rows
                do {
                    Error=0;
                    cout << "Enter the price for seats in row " << (i+1) << ": ";
                    cin >> Number;
                    
                    //check for errors
                    if(!cin) {
                        cin.clear();
                        cin.ignore(1000,'\n');
                        cerr << "Invalid price. Please try again.\n";
                        continue;
                        Error=1;
                    }
                    //loop to set row prices
                    for(int a=0; a<ColumnSize; a++) {
                        TheaterPrices[i][a]=Number;
                    } 
                } while(Error==1);
            }
            
            //output the array size to file
            fout << RowSize << endl
                 << ColumnSize << endl;
            
            //optput the row prices to file
            for(int i=0; i<RowSize; i++) {
                for(int a=0; a<ColumnSize; a++) {
                    fout << TheaterPrices[i][a] << endl;
                }
            }
            fout.close();
        }
}

/*==========================================================================
 * Function: char Menu();
 * 
 * Precondition: None   
 * Postcondition: Outputs a menu in which the user can choose what to do next
 *                
 */
char Menu() {
    //define variables
    char Choice = 'E';
    int Error=0;
    //output the menu
    cout << endl << "What would you like to do?" << endl
         << setw(4) << "(C) Display seating chart" << endl
         << setw(4) << "(S) Sell tickets" << endl
         << setw(4) << "(D) Display theater statistics" << endl
         << setw(4) << "(R) Reset the program" << endl
         << setw(4) << "(E) Save and exit the program" << endl;
         
    do {
        Error=0;
            //ask for a random seed 
        cout << "Your choice: ";
        cin >> Choice;
        cout << endl;
            //check if the input is good
        if(!cin || (Choice!='C' && Choice!='S' && Choice!='D' && Choice!='R' && Choice!='E')) {
            cin.clear();
            cin.ignore(1000,'\n');
            cerr << "Invalid choice. Please try again.\n";
            Error=1;
        }
     } while (Error==1);
     
    return Choice;
}

/*==========================================================================
 * Function: void Choice(char,int&,double[][COLUMN],char[][COLUMN],int&,int&,int&,int&);
 * 
 * Precondition: The first parameter is a char character, the second parameter is an int variable,
 *               the third parabeter is an array of type double, the fourth parameter is an array
 *               of type char, and the fifth through eighth parameters are variables of type int
 * Postcondition: It will run the program of the users choice
 *                
 */
void Choice(char Choice,int &Exit, double TheaterPrices[][COLUMN], char TheaterSeating[][COLUMN], int &RowSize, int &ColumnSize, int &PriceSum, int &TicketSum) {
    
    //switch statement for the different functions
    switch(Choice) {
        case 'C':
        DisplayChart(TheaterSeating,ColumnSize,RowSize);
        break;
        
        case 'S':
        Sell(RowSize,ColumnSize,PriceSum,TicketSum,TheaterPrices,TheaterSeating);
        break;
        
        case 'D':
        Statistics(RowSize,ColumnSize,PriceSum,TicketSum);
        break;
        
        case 'R':
        Reset(RowSize,ColumnSize,PriceSum,TicketSum,TheaterPrices,TheaterSeating);
        break;
        
        case 'E':
            cout << "Thank you for using this program to manage your theater!" << endl;
            Exit=1;
        break;
        
        default:
            cerr << "Invalid Choice";
        break;
    }
}

/*==========================================================================
 * Function: void DisplayChart(char[][COLUMN],int,int);
 * 
 * Precondition: The first parameter is an array of type char, the second parameter
 *               is an int, and the third parameter is an int
 * Postcondition: Outputs a chart that reflects the current status of the theater
 *                
 */
void DisplayChart(char TheaterSeating[][COLUMN],int ColumnSize, int RowSize) {
    //define variables 
    int Sum=ColumnSize, Sum2=0;
    
    //loop for creating variables to be used in creating the chart
    if (Sum>10 && (Sum%10)!=0) {
        while((Sum%10)!=0) {
            Sum--;
            Sum2++;
        }
    }
    //loop to output header column numbers
    cout << "       ";
    for(int i=1, T=0; i<=Sum; i*=10, T++) {
        cout << T << "        ";
    }
    cout << endl;
    
    //loop to output the column numbers
    if((Sum%10)==0 && Sum>=10) {
        cout << "       ";
        for(int f=1; f<=(ColumnSize/10); f++) {
            cout << "1234567890";
        }
        for(int i=0; i<Sum2; i++) {
            cout << (i+1);
        }
    } else {
        cout << setw(8);
        for (int r=0; r<ColumnSize; r++) {
            cout << (r+1);
        }
    }
    cout << endl;
    //loop to create the rows
    for(int i=0; i<RowSize; i++) {
        cout << "Row " << (i+1) << " ";
        if(i<9) {
            cout << " ";
        }
        for(int a=0; a<ColumnSize; a++) {
            cout << TheaterSeating[i][a];
        }
        cout << endl;
    }
}

/*==========================================================================
 * Function: void Sell(int,int,int&,int&,double[][COLUMN],char[][COLUMN]);
 * 
 * Precondition: The first two parameters are ints, the third and fourth parameters 
 *               are variables of type int, the fifth parameter is an array of type
 *               double, and the sixth parameter is an array of type char
 * Postcondition: Sells seats. Gets the seats to sell and edits them in the array
 *                
 */
void Sell(int RowSize, int ColumnSize, int &PriceSum, int &TicketSum, double TheaterPrices[][COLUMN], char TheaterSeating[][COLUMN]) {
    //define variables
    int Error=0, Number=0, N1=0, N2=0, Sum2=0;
    char G='G';
    
    //loop to collect number of seats
    do {
        Error=0;
       
       //output a message
       cout << "Please enter how many seats you would like to sell: ";
       cin  >> Number;
        //error checking
        if(!cin || Number<1 || Number>RowSize) {
            cin.clear();
            cin.ignore(1000,'\n');
            cerr << "Invalid choice. Please try again.\n";
            Error=1;
        }
     } while (Error==1);
     TicketSum+=Number;
    
    //output message to get seats
    cout << "What seats would you like to buy?" << endl
         << "Enter in format \"Row,Column\"" << endl;
         
    //loop to collect seats
    for(int i=0; i<Number; i++) {  
        do {
            Error=0;
       
            cout << "Seat #" << (i+1) << ":";
            cin >> N1 >> G >> N2;
            
            //error checking
            if(!cin) {
                cin.clear();
                cin.ignore(1000,'\n');
                cerr << "Invalid choice. Please try again.\n";
                Error=1;
            } else if (TheaterSeating[N1-1][N2-1]=='*') {
                cerr << "That seat is already taken. Choose another\n";
                Error=1;
            } else if (TheaterSeating[N1-1][N2-1]!='*' && TheaterSeating[N1-1][N2-1]!='^')  {
                cerr << "That seat does not exist, choose another seat" << endl;
                Error=1;
            }
        } while (Error==1);
        //edit arrays and theater info variables
        TheaterSeating[N1-1][N2-1]='*';
        PriceSum+=TheaterPrices[N1-1][N2-1];
        Sum2+=TheaterPrices[N1-1][N2-1];
    }
    //output the total bill
    cout << "Your total is $" << Sum2 << endl;;
}

/*==========================================================================
 * Function: void Statistics(int,int,int,int);
 * 
 * Precondition: All four parameters are integers
 * Postcondition: Outputs the statistics of the theater
 *                
 */
void Statistics(int RowSize,int ColumnSize,int PriceSum,int TicketSum) {
    //outputs the information
    cout << "Tickets sold: " << TicketSum << endl
         << "Total revenue: $" << PriceSum << endl
         << "Seats still available: " << RowSize*ColumnSize-TicketSum << endl;
        
}

/*==========================================================================
 * Function: void Reset(int&,int&,int&,int&,double[][COLUMN],char[][COLUMN]);
 * 
 * Precondition: The first four parameters are variables of type int, the fifth 
 *               parameter is an array of type double, and sisth parameter is an 
 *               array of type char
 * Postcondition: Resets all the variables and arrays, and then gets new information
 *                for the theater
 *                
 */
void Reset(int &RowSize,int &ColumnSize,int &PriceSum,int &TicketSum,double TheaterPrices[][COLUMN],char TheaterSeating[][COLUMN]) {
    //resets the current arrays
    for(int i=0; i<RowSize; i++) {
        for(int a=0; a<ColumnSize; a++) {
            TheaterSeating[i][a]='^';
            TheaterPrices[i][a]=0;
        }
    }
    //resets the variables
    RowSize=80;
    ColumnSize=80;
    PriceSum=0;
    TicketSum=0;
    
    //output message
    cout << "The theater and its statistics have been reset" << endl;
    
    //Call function to get new information
    GetInfo(RowSize,ColumnSize,TheaterPrices);
    
    //set all the new seats to avaliable
    for(int i=0; i<RowSize; i++) {
        for(int a=0; a<ColumnSize; a++) {
            TheaterSeating[i][a]='^';
        }
    }
    
}