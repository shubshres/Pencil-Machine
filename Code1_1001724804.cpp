//Shubhayu Shrestha 1001724804
//Coding Assignment 1: Pencil Machine (due 24 Sept.)
#include <iostream>
#include <string.h>

//defining pencil price
#define pencilPrice 60

using namespace std;

//declaring enum class
enum class Status
{
    SOLDWITHCHANGE, 
    SOLDWITHEXACT,
    NOINVENTORY,
    NOCHANGE,
    INSUFFICIENTFUNDS
};

//function that converts from cents to dollars (to string)
string moneyConversion(long moneyIn)
{
    string dollars {to_string(moneyIn / 100)};
    string cents {to_string(abs(moneyIn % 100))}; 
    
    string price{"$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents}; 

    return price; 
}

//function that prints out menu and takes in user choice
void printMenu(int& menuChoice)
{    
    //asking user for input
    cout << "\n\nPlease choose from the following options\n" << endl; 

    //Printing out options to user
    cout << "0. No pencils for me today" << endl;
    cout << "1. Purchase pencils" << endl;
    cout << "2. Check inventory level" << endl;
    cout << "3. Check change level\n" << endl;

    cout << "Choice: "; 

    //utilizing if statement utilizing ors and fail flags for error handling user input
    cin >> menuChoice;

    //checking if input is a letter, and if it is, ask user to reenter
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout << "\ninput must be numeric, please reenter ";
        cin >> menuChoice;
    }
}


//function used to buy pencils 
bool buyPencils(Status& definition, long payment, long totalPrice, int& inventory, long& change, int numberOfPencils)
{
    //initializing local boolean
    bool passFail; 
    //checking inventory level
    if(inventory < numberOfPencils)
    {
        passFail = false; 
        definition = Status::NOINVENTORY; 
        
    }
    else //goes here if inventory was fine
    {
        //checking if exact payment was entered or not
        if(totalPrice == payment)
        {
            passFail = true;
            definition = Status::SOLDWITHEXACT;  
            inventory = (inventory - numberOfPencils); 
        }
        else if(payment > totalPrice) //checking if payment is greater than total price
        {
            if(change >= (payment-totalPrice)) // checking if we have enough change to give back
            {
                passFail = true; 
                definition = Status::SOLDWITHCHANGE;
                inventory = (inventory - numberOfPencils); 
                change = (change - (payment-totalPrice));
            }
            else
            {
                definition = Status::NOCHANGE; 
                passFail = false; 
            }
            
        }
        else if(payment<totalPrice) //checking if there is insufficient funds
        {
            definition = Status::INSUFFICIENTFUNDS; 
            passFail = false; 
        }
    }
    
    return passFail; 
}


int main(void)
{
    //declaring variables
    int menuChoice{}; 
    int numberOfPencils{};
    long totalPrice{};
    long payment{};     
    long change{500}; 
    int inventory{100}; 
    int runSwitch{0}; 
    bool workFailBool{}; 
    Status definition;  

    //printing welcome message 
    cout << "\nWelcome to my Pencil Machine" << endl; 

    //assigning menuChoice to choice returned by printMenu function
    do
    {
        //printing menu
        printMenu(menuChoice); 
        //creating switch statement to follow allong with menu choice
        
        //switch statement with user menu choice
        switch(menuChoice)
        {
            case 0 : // No pencils for me today
            {
                runSwitch--; 
                break; 
            }
            case 1 : //purchase pencils
            {  
                if(inventory > 0)
                {
                    cout << "\nA pencil costs " << moneyConversion(pencilPrice) << endl; 
                    cout << "\nHow many pencils would you like to purchase? "; 
                    cin >> numberOfPencils;
                    
                    //checking if user inputted more than one pencil
                    if(numberOfPencils <= 0)
                    {
                        cout << "\nYou must purchase at least one pencil";                             
                    } 
                    else if(numberOfPencils > inventory)
                    {
                        cout << "\n\nThere are not enough pencils to sell. \n\nThere are currently " << inventory << " pencils" << endl;
                    }
                    else if(numberOfPencils <= inventory)
                    {
                        //checking if user inputted a letter                
                        while(cin.fail())
                        {
                            cin.clear();
                            cin.ignore(100,'\n');
                            cout << "\ninput must be numeric, please reenter ";
                            cin >> numberOfPencils;
                        }
        
                        totalPrice = (numberOfPencils * pencilPrice); //calculating total price
                        cout << "\nYour total is " << moneyConversion(totalPrice) << endl; 
                        cout << "\nEnter your payment (in cents) "; //asking user to input payment
                        cin >> payment; 

                        //checking to see if user inputted letter instead of number
                        while(cin.fail())
                        {
                            cin.clear();
                            cin.ignore(100,'\n');
                            cout << "\ninput must be numeric, please reenter ";
                            cin >> payment;
                        }
                        
                        //assigning return boolean from buyPencil function 
                        bool workFailBool = buyPencils(definition, payment, totalPrice, inventory, change, numberOfPencils);
                    
                


                        //boolean statement to print output of transaction to user
                        if((workFailBool))
                        {
                            switch(definition)
                            {
                                case Status::SOLDWITHCHANGE : 
                                {
                                    cout << "\nHere are your pencils with the change of " << moneyConversion((payment-totalPrice)) << endl;
                                    break; 
                                }
                                case Status::SOLDWITHEXACT : 
                                {
                                    cout << "\nHere are your pencils. Thank you for providing the exact payment!" << endl;
                                    break; 
                                }
                                default:
                                {
                                    cout << "\nunknown error occured"; 
                                }
                            }
                        }
                        else
                        {
                            switch(definition)
                            {
                                case Status::NOINVENTORY : 
                                {
                                    cout << "\nNot enough inventory to complete purchase" << endl;
                                    cout << "\nThere are currently " << inventory << " pencils left in the machine available to purchase" << endl;
                                    break; 
                                }
                                case Status::NOCHANGE : 
                                {
                                    cout << "\nThis Pencil Dispenser does not have enough change and cannot accept your payment\n\nSorry..." << endl;
                                    break; 
                                }
                                case Status::INSUFFICIENTFUNDS : 
                                {
                                    cout << "\nYou did not enter a sufficient payment. No pencils for you." << endl;
                                    break; 
                                }
                                default:
                                {
                                    cout << "\nunknown error occured"; 
                                }
                            }
                        }
                }
                }
                else
                {
                    cout << "\nThere are no more pencils left to purchase";
                }
                
                break; 
            }
            case 2 :  //Check inventory level
            {
                cout << "\nThere are currently " << inventory << " pencils left in the machine" << endl; 
                break; 
            }
            case 3 : //check change level
            { 
                cout << "\nThe current change level is " << moneyConversion(change) << endl; 
                break;
            }
            default : 
                cout << "\nInvalid menu choice. Please choose again." << endl; 
        }
    } 
    while(runSwitch == 0);
    return 0; 
}
