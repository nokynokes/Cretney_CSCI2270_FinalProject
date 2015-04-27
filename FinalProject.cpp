
#include "hashTable.h"
#include "hashTable.cpp"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <cstdlib>
using namespace std;

void printMenu();
int main()
{
    //hashTable *v = new hashTable(10);
    hashTable v;

    v.readFile();
    int input;
    string title;
    string rating;
    string genre;
    int budget = false;

    while(input != 6){


        printMenu();
        cin >> input;
        cin.clear();

        switch(input)
        {
            case 1:
                v.printInventory();
                break;
            case 2:
                v.viewShoppingCart();
                break;
            case 3:
                budget = v.getBalance();
                cout<< "$" <<budget<<" remaining"<<endl;
                break;
            case 4:
                cin.ignore(100, '\n');
                cout<<"Enter a title: "<<endl;
                getline(cin,title);
                v.findGame(title);
                break;
            case 5:
                v.checkOut();
                break;
            case 6:
                break;
            default:
                cout<<"Please Enter a valid number between 1-6"<<endl;
                break;



        }
    }

}

void printMenu()
{
    cout << "======Welcome to Nolan's online game store!=====" << endl;
    cout << "1. View Store" << endl;
    cout << "2. View Shopping Cart"<< endl;
    cout << "3. View Balance"<< endl;
    cout << "4. Search"<< endl;
    cout << "5. Checkout" << endl;
    cout << "6. Quit" << endl;
    return;

}
