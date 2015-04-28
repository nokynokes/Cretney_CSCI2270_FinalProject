
#include "hashTable.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string.h>
#include <vector>
#include <fstream>
using namespace std;

//ctor
hashTable::hashTable()
{
    
}

//dtor
hashTable::~hashTable()
{
    for(int i = 0; i<table_size;i++){
        if(table[i] != NULL){
            delete table[i];
        }
    }
    for(int i = 0; i<table_size; i++){
        if(table2[i] != NULL){
            delete table2[i];
        }
    }

}

void hashTable::insertGame(string name, int rating, string genre, int price)
{   int index = 0;
    index = hashSum(name);
    if(table[index] == NULL){ // no collision
        table[index] = new vector<VideoGame>;
        table[index]->push_back(VideoGame(name,rating,genre,price));
    }
    else{ // collision 
        table[index]->push_back(VideoGame(name,rating,genre,price));


    }

}


void hashTable::printInventory(){ //  prints out the title and price
   for(int i = 0; i< table_size; i++){
        if(table[i] != NULL){
            for(unsigned int j = 0; j<table[i]->size();j++){
                string name = (*table[i])[j].title;
                int price = (*table[i])[j].price;
                cout<<name<<"-" <<" $"<<price<<endl;
            }
        }
    }

}

void hashTable::readFile(){ //read in two files. first file contains video game scores and prices. second file contains esrb rating and info
    ifstream myFile;
    myFile.open("videoGames.txt");
    string line, name, rating, genre, price;
    //reading in the first file
    if(myFile){
        while(getline(myFile, line)){ // using commas as the delimiter
            stringstream iss(line);
            getline(iss,name,',');
            getline(iss,rating,',');
            getline(iss,genre,',');
            getline(iss,price,',');
            insertGame(name, stoi(rating), genre, stoi(price));
        }
        myFile.close();
    }
    ifstream myFile2;
    myFile2.open("GameInfo.txt");
    string line2, title, esrb, info;
    //reading in the second file
    if(myFile2){
        while(getline(myFile2, line2)){ // using dashes as the delimiter 
            stringstream iss2(line2);
            getline(iss2,title,'-');
            getline(iss2,esrb,'-');
            getline(iss2,info,'-');
            insertGameInfo(title, esrb, info);

        }


    }


}

void hashTable::findGame(string name)
{
    string rating, info;
    bool found = false;
    int index = hashSum(name);
    if(table[index] != NULL){
        for(unsigned int i = 0; i<table[index]->size(); i++){
            if((*table[index])[i].title == name){
                cout<<"Score: "<<(*table[index])[i].rating<<" out of 100"<<endl;
                cout<<"Genre: "<<(*table[index])[i].genre<<endl;
                cout<<"Price: $"<<(*table[index])[i].price<<endl;
                found = true;
                int input;
                while(input != 4){ // when the game is found, display menu for adding to cart, getting the rating, getting info
                    displayFindMenu();
                    cin >> input;
                    cin.clear();
                    switch(input){
                        case 1:
                            if((*table[index])[i].added != true){ // checks for duplicates in shopping cart
                                cart.push_back((*table[index])[i]);
                                cout<<(*table[index])[i].title<<" has been added to the shopping cart"<<endl;
                                (*table[index])[i].added = true;
                            }
                            else{
                                cout<<(*table[index])[i].title<<" is already in the shopping cart"<<endl;
                            }
                            
                            break;
                        case 2:
                            info = getInfo((*table[index])[i].title); //returns info form 2nd hashtable
                            cout<<info<<endl;
                            break;
                        case 3:
                            rating = getESRB((*table[index])[i].title); // return esrb raing from second hashtable
                            cout<<"This game is rated: "<<rating<<endl;
                            break;
                        case 4:// goes back to the first menu
                            break;
                        default:
                            cout<<"please enter a valid number between 1-4"<<endl;
                            break;

                    }
                }
                return;

            }
        }
    }
    if(found == false){
        cout<<"game not found"<<endl;
    }
}

void hashTable::deleteGame(string title){ 
    int index = hashSum(title);
    bool found = false;
    if(table[index] != NULL){ //searching the first hashtable
        for(unsigned int i = 0; i<table[index]->size(); i++){
            if((*table[index])[i].title == title){
                table[index]->erase(table[index]->begin() + i);//deleting fomr 1st hashtable
                found = true;
                if(table2[index] != NULL){//searching the 2nd hashtable
                    for(unsigned int j = 0; j<table2[index]->size(); j++){
                        if((*table2[index])[j].name == title){
                            table2[index]->erase(table2[index]->begin() + j); //deleting from 2nd hashtable
                            break;
                        }
                    } 
                }
                
            }
        }
    }
    if(found == false){
        cout<<"game not found"<<endl;
    }
}

int hashTable::hashSum(string title){
    int sum = 0;
    for(unsigned int i = 0; i< title.length(); i++){
        sum = sum + title[i];

    }
    sum  = sum % table_size;
    return sum;
}

int hashTable::getBalance(){
    return budget;
}

void hashTable::displayFindMenu(){
    cout<<"1. Add to cart"<<endl;
    cout<<"2. See Description"<<endl;
    cout<<"3. See ESRB rating"<<endl;
    cout<<"4. Go back"<<endl;
    return;
}

void hashTable::viewShoppingCart(){
    int total = 0;
    bool isEmpty = true;
    if(cart.empty() == false){
        for(unsigned int i = 0; i<cart.size(); i++){
            cout<<cart[i].title<<"-"<<"$"<<cart[i].price<<endl;
            total = total + cart[i].price;
        }
        isEmpty = false;
    }

    if(isEmpty == false){
        cout<<"Total cost: $"<<total<<endl;
    }
    else{
        cout<<"cart is empty"<<endl;
    }

}

void hashTable::checkOut(){
    bool isEmpty = cart.empty();
    int sum = 0;
    if(isEmpty != true){
        for(unsigned int i = 0; i<cart.size(); i++){ // find the total price
            sum = sum + cart[i].price;
        }
        if(budget >= sum){ // if the budget is less than the total price, then when can delete from the cart
            for(unsigned int j = 0; j<cart.size(); j++){
                deleteGame(cart[j].title); // delete from the inverntory
            }

            budget = budget - sum; // subtract the total from the budget
            cout<<"We hope you enjoy your new games!"<<endl;
            cart.erase(cart.begin(), cart.begin()+cart.size()); // delete
            return;
        }
        else{
            cout<<"insufficient funds"<<endl;
            return;
        }

    }
    else{
        cout<<"cart is empty"<<endl;
        return;
    }

}

void hashTable::insertGameInfo(string name, string esrb, string info){ // same as insertGame function
    int index = 0;
    index = hashSum(name);
    if(table2[index] == NULL){
        table2[index] = new vector<GameInfo>;
        table2[index]->push_back(GameInfo(name,esrb,info));
    }
    else{
        //cout<<"collision"<<endl;
        table2[index]->push_back(GameInfo(name,esrb,info));


    }
}

string hashTable::getESRB(string name)
{
    int index = hashSum(name);
    bool found = false;
    string rating;
    if(table2[index] != NULL){ // searches the 2nd hashtable
        for(unsigned int i = 0; i<table2[index]->size(); i++){
            if((*table2[index])[i].name == name){
                rating = (*table2[index])[i].esrb;
                return rating;
            }
        }
    }
    if(found == false){
        cout<<"game not found"<<endl;
    }
}

string hashTable::getInfo(string name)
{
    int index = hashSum(name);
    bool found = false;
    string info;
    if(table2[index] != NULL){ // searches the 2nd hashtable
        for(unsigned int i = 0; i<table2[index]->size(); i++){
            if((*table2[index])[i].name == name){
                info = (*table2[index])[i].descrption;
                return info;
            }
        }
    }
    if(found == false){
        cout<<"game not found"<<endl;
    }

}

