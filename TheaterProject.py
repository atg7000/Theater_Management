import os.path

#Global Variables
ROW=80
COLUMN=80
RowSize=0
ColumnSize=0
PriceSum=0
TicketSum=0

#==========================================================================
 # Function: ConfigArray(TheaterPrices)
 # 
 # Precondition: TheaterPrices is a container with a multidimensional array inside   
 # Postcondition: This funtion gets info from a file about the dimensions of the theater.
 #                
 #/
def ConfigArray(TheaterPrices):

    #define variables
    global RowSize
    global ColumnSize
    my_list = list()

    #open file
    if (os.path.isfile("theater.txt")):
        with open("theater.txt","r") as file:               
            my_list=file.readlines()
        try:
            #set sizes
            RowSize=int(my_list[0])
            ColumnSize=int(my_list[1])

            for i in range(0,RowSize):
                TheaterPrices[i]=float(my_list[i+2])
        except IndexError:
            print("Error with file. Creating a new one...")
            GetInfo(TheaterPrices)
    else:
        GetInfo(TheaterPrices)

#==========================================================================
 # Function: GetInto(TheaterPrices)
 # 
 # Precondition: TheaterPrices is a container with a multidimensional array inside   
 # Postcondition: This funtion gets info from the user about the dimensions of the theater.
 #                
 #/
def GetInfo(TheaterPrices):

    #define variables
    global RowSize
    global ColumnSize

    #open file
    with open("theater.txt","w") as file:

        #get rowsize from user
        print("Within the bounds of 80x80, enter the dimentions of your theater.")
        while True:
            try:
                RowSize = input("Enter the number of rows: ")
                RowSize=int(RowSize)
                if RowSize<81 and RowSize>0:
                    break
                else:
                    print("Incorrect input, please try again.")
            except ValueError:
                print("Incorrect input, please try again.")
                

        #get columnsize from user
        while True:
            try:
                ColumnSize = input("Enter the number of columns: ")
                ColumnSize=int(ColumnSize)
                if ColumnSize<81 and ColumnSize>0:
                    break
                else:
                    print("Incorrect input, please try again.")
            except ValueError:
                print("Incorrect input, please try again.")

        #loop to collect row prices
        for i in range(0,RowSize):

            #loop to get input and handle errors
            while True:
                try:
                    Number=input("Enter the price for seats in row {}. (Prices cannot exceed $1000)".format(i+1))
                    Number=float(Number)
                    if (Number>1000 or Number<=0):
                        print("That is not a valid price")
                        continue
                    else:
                        TheaterPrices[i]=Number
                        break
                except ValueError:
                    print("That is not a valid price")

        #write theater information to file
        file.write(str(RowSize))
        file.write("\n")
        file.write(str(ColumnSize))
        file.write("\n")

        for i in range(0,RowSize):
            file.write(str(TheaterPrices[i]))
            file.write("\n")

        

#==========================================================================
 # Function: Menu()
 # 
 # Precondition: None   
 # Postcondition: Outputs a menu in which the user can choose what to do next
 #                
 #/
def Menu():

    while True:
        #output menu
        print()
        print("|---------------------------------|")
        print("| What would you like to do?      |")
        print("|                                 |")
        print("| (C) Display seating chart       |")
        print("| (S) Sell tickets                |")
        print("| (D) Display theater statistics  |")
        print("| (R) Reset the program           |")
        print("| (E) Exit the program            |")
        print("|---------------------------------|")

        #Get input from user
        choice = input("Your Choice: ")
        if choice=='C' or choice=='S' or choice=='D' or choice=='R' or choice=='E':
            break
        else:
            print("Incorrect input. Please try again.")

    #return the user's choice
    return choice

#==========================================================================
 # Function: Choice(choice, &Exit, TheaterPrices,
 # 
 # Precondition: None   
 # Postcondition: Outputs a menu in which the user can choose what to do next
 #                
 #/
def Choice(choice,TheaterPrices,TheaterSeating):
    
    if   choice == 'C':
        DisplayChart(TheaterSeating)
        return True
    elif choice == 'S':
        Sell(TheaterPrices,TheaterSeating)
        return True
    elif choice == 'D':
        Statistics(TicketSum,PriceSum,RowSize,ColumnSize)
        return True
    elif choice == 'R':
        Reset(TheaterPrices,TheaterSeating)
        return True
    elif choice == 'E':
        print("Thank you for using this program to manage your theater!")
        return False

#==========================================================================
 # Function: DisplayChart(TheaterSeating)
 # 
 # Precondition: The first parameter is a multidimensional array
 # Postcondition: Outputs the seating chart that reflects the current status
 #                of the theater.
 #                
 #/
def DisplayChart(TheaterSeating):

    #Define variables
    T=0
    Sum=ColumnSize
    Sum2=0

    #loop for creating variables to be used in creating chart
    if(Sum>10 and (Sum%10)!=0):
        while((Sum%10)!=0):
            Sum-=1
            Sum2+=1

    #loop to output header column numbers
    print("        ",end='')
    for i in range(0,Sum+1,10):
        print(T,"        ",end='')
        T+=1

    #loop to output column numbers
    if((Sum%10)==0 and Sum>=10):
        print()
        print("         ",end='')
        for i in range(1,(int(ColumnSize/10)+1)):
            print("1234567890",end='')
        for a in range(0,Sum2):
            print(a+1,end='')
    else:
        print("          ")
        for i in range(0,ColumnSize):
            print(i+1,end='')

    #loop to create the rows
    for i in range(0,RowSize):
        print()
        print("Row ",i+1," ",end='')
        if(i<9):
            print(" ",end='')
        for a in range(0,ColumnSize):
            print(TheaterSeating[i][a],end='')

#==========================================================================
 # Function: Sell(TheaterPrices,TheaterSeating)
 # 
 # Precondition: The first and second conditions are multidimensional arrays
 # Postcondition: Allows manager to sell tickets
 #                
 #/
def Sell(TheaterPrices,TheaterSeating):

    #define variables
    global TicketSum
    global PriceSum
    Sum2=0

    #loop to get how many seats to sell
    while True:
        try:
            Number = input("Please enter how many seats you would like to sell: ")
            Number=int(Number)
            if (type(Number) is not int or Number<1 or Number>RowSize):
                print("Invalid Choice. Please try again")
                continue
            else:
                break
        except ValueError:
            print("Invalid Choice. Please try again")
    TicketSum+=Number

    print("What seats would you like to buy?")

    #sell seats
    for i in range(0,Number):
        while True:
            try:
                print("Seat Row #",i+1,":",end='')
                N1 = input()
                N1=int(N1)

                #error checking
                if (type(N1) is not int):
                    print("Invalid choice. Please try again.")
                    continue
                elif (N1<1 or N1>RowSize):
                    print("That seat # does not exist. Please try again.")
                    continue
            except ValueError:
                print("Invalid choice. Please try again.")
                continue

            try:
                print("Seat Column #",i+1,":",end='')
                N2 = input()
                N2=int(N2)

                #error checking
                if (type(N2) is not int):
                    print("Invalid choice. Please try again.")
                    continue
                elif(N2<1 or N2>ColumnSize):
                    print("That seat # does not exist. Please try again.")
                    continue
                elif(TheaterSeating[N1-1][N2-1]=='*'):
                    print("That seat is already taken. Please try again.")
                    continue
                else:
                    break
            except ValueError:
                print("Invalid choice. Please try again.")

        #set new numbers
        TheaterSeating[N1-1][N2-1]='*'
        PriceSum+=TheaterPrices[N1-1]
        Sum2+=TheaterPrices[N1-1]

    print("Your total is $",Sum2)
        
                
                
 #==========================================================================
 # Function: Statistics(TicketSum,PriceSum,RowSize,ColumnSize)
 # 
 # Precondition: All parameters are integers   
 # Postcondition: Outputs the currect theater statistics
 #                
 #/
def Statistics(TicketSum,PriceSum,RowSize,ColumnSize):
    Seats=(RowSize*ColumnSize)-TicketSum
    print("Tickets sold: ",TicketSum)
    print("Total revenue: $",PriceSum)
    print("Seats still available: ",Seats)

 #==========================================================================
 # Function: Reset(TheaterPrices,TheaterSeating)
 # 
 # Precondition: The first and second conditions are multidimensional arrays
 # Postcondition: Resets everything in the theater
 #                
 #/
def Reset(TheaterPrices,TheaterSeating):

    #define global variables
    global RowSize
    global ColumnSize
    global PriceSum
    global TicketSum

    #reset theater charts
    for i in range(0,RowSize):
        for a in range(0,ColumnSize):
            TheaterSeating[i][a]='#'
            TheaterPrices[i]=0

    #reset global variables
    RowSize=80
    ColumnSize=80
    PriceSum=0
    TicketSum=0

    print("The theater and its statistics have been reset")

    #get new theater information
    GetInfo(TheaterPrices)

    for i in range(0,RowSize):
        for a in range(0,ColumnSize):
            TheaterSeating[i][a]='#'
    

def Main():

    #Define variables
    RowSize=80
    ColumnSize=80
    Exit = True
    PriceSum=0
    TicketSum=0
    Wipe=0
    
    #Define multidimensional arrays
    TheaterPrices  = [0 for x in range(ROW)]
    TheaterSeating = [[0 for x in range(ROW)] for y in range(COLUMN)]

    ConfigArray(TheaterPrices)

    #Set each multidimensional array to empty
    for i in range(0,ROW):
        for a in range(0,COLUMN):
            TheaterSeating[i][a] = '#'
            
    while Exit:
        Exit=Choice(Menu(),TheaterPrices,TheaterSeating)

    
Main()
