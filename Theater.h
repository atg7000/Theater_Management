/****************************************************************************
 * 
 * Proj.03: Theater Seating Chart
 *  
 * File Name: Theater.h
 * Name:      Austin Garner
 * Course:    CPTR 141
 * Date:      December 8, 2017
 * 
 */   
#ifndef THEATER_H
#define THEATER_H
 
int const COLUMN=80;
int const ROW=80;
 
 /*==========================================================================
 * Function: void ConfigArray(int&,int&,double);
 * 
 * Precondition: The first and second parameters are int variables, and the
 *               third parameter is a multidimensional array
 * Postcondition: Gets seating chart from user or from file
 *                
 */
void ConfigArray(int &RowSize, int &ColumnSize, double TheaterPrices[][COLUMN]);

/*==========================================================================
 * Function: void GetInfo(int&,int&,double[][COLUMN]);
 * 
 * Precondition: The first parameter is an int variable, the second parameter is an int variable,
 *               and the third parameter is an array of type double
 * Postcondition: Gets the theater size and row prices from user, and then outputs this to a file  
 *                
 */
void GetInfo(int &RowSize,int &ColumnSize,double TheaterPrices[][COLUMN]);

/*==========================================================================
 * Function: char Menu();
 * 
 * Precondition: None   
 * Postcondition: Outputs a menu in which the user can choose what to do next
 *                
 */
char Menu();

/*==========================================================================
 * Function: void Choice(char,int&,double[][COLUMN],char[][COLUMN],int&,int&,int&,int&);
 * 
 * Precondition: The first parameter is a char character, the second parameter is an int variable,
 *               the third parabeter is an array of type double, the fourth parameter is an array
 *               of type char, and the fifth through eighth parameters are variables of type int
 * Postcondition: It will run the program of the users choice
 *                
 */
void Choice(char Choice,int &Exit, double TheaterPrices[][COLUMN], char TheaterSeating[][COLUMN], int &RowSize, int &ColumnSize, int &PriceSum, int &TicketSum);

/*==========================================================================
 * Function: void DisplayChart(char[][COLUMN],int,int);
 * 
 * Precondition: The first parameter is an array of type char, the second parameter
 *               is an int, and the third parameter is an int
 * Postcondition: Outputs a chart that reflects the current status of the theater
 *                
 */
void DisplayChart(char TheaterSeating[][COLUMN],int ColumnSize, int RowSize);

/*==========================================================================
 * Function: void Sell(int,int,int&,int&,double[][COLUMN],char[][COLUMN]);
 * 
 * Precondition: The first two parameters are ints, the third and fourth parameters 
 *               are variables of type int, the fifth parameter is an array of type
 *               double, and the sixth parameter is an array of type char
 * Postcondition: Sells seats. Gets the seats to sell and edits them in the array
 *                
 */
void Sell(int RowSize, int ColumnSize, int &PriceSum, int &TicketSum, double TheaterPrices[][COLUMN], char TheaterSeating[][COLUMN]);

/*==========================================================================
 * Function: void Statistics(int,int,int,int);
 * 
 * Precondition: All four parameters are integers
 * Postcondition: Outputs the statistics of the theater
 *                
 */
void Statistics(int RowSize,int ColumnSize,int PriceSum,int TicketSum);

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
void Reset(int &RowSize,int &ColumnSize,int &PriceSum,int &TicketSum,double TheaterPrices[][COLUMN],char TheaterSeating[][COLUMN]);

#endif //THEATER_H