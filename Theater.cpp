/****************************************************************************
 * 
 * Proj.03: Theater Seating Chart
 *  
 * File Name: Theater.cpp
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

int main() {
    //define variables and arrays
    int RowSize=80, ColumnSize=80, Exit=0, PriceSum=0,TicketSum=0,Wipe=0;
    double TheaterPrices[ROW][COLUMN];
    char TheaterSeating[ROW][COLUMN];
    
    //get theater information from user
    ConfigArray(RowSize,ColumnSize,TheaterPrices);
    
    //loop to set theater seats to avaliable
    for(int i=0; i<RowSize; i++) {
        for(int a=0; a<ColumnSize; a++) {
            TheaterSeating[i][a]='^';
        }
    }
    
    //loop to output menu and interact with theater
    do {
        Choice(Menu(),Exit,TheaterPrices,TheaterSeating,RowSize,ColumnSize,PriceSum,TicketSum);
    } while (Exit==0);
    
 return 0;
}