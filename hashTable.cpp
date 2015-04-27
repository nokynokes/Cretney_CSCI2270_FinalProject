#include "hashTable.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string.h>
#include <vector>
#include <fstream>
using namespace std;

hashTable::hashTable()
{
    /*table_size = size;
    table = new VideoGame*[table_size];
    for(int i = 0; i<table_size;i++){
        table[i] = NULL;
    }*/

}

hashTable::~hashTable()
{
    for(int i = 0; i<table_size;i++){
        if(table[i] != NULL && table2[i] != NULL){
            delete table[i];
            delete table2[i];
        }
    }

}

void hashTable::insertGame(string name, int rating, string genre, int price)
{   int index = 0;
    index = hashSum(name);
    //cout<<index<<endl;
    if(table[index] == NULL){
        table[index] = new vector<VideoGame>;
        table[index]->push_back(VideoGame(name,rating,genre,price));
    }
    else{
        //cout<<"collision"<<endl;
        table[index]->push_back(VideoGame(name,rating,genre,price));


    }

}


void hashTable::printInventory(){
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

void hashTable::readFile(){
    ifstream myFile;
    myFile.open("videoGames.txt");
    string line, name, rating, genre, price;
    if(myFile){
        while(getline(myFile, line)){
            stringstream iss(line);
            getline(iss,name,',');
            getline(iss,rating,',');
            getline(iss,genre,',');
            getline(iss,price,',');
            //cout<<name<<":"<<rating<<endl;
            insertGame(name, stoi(rating), genre, stoi(price));
        }
        myFile.close();
    }
    ifstream myFile2;
    myFile2.open("GameInfo.txt");
    string line2, title, esrb, info;
    if(myFile2){
        while(getline(myFile2, line2)){
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
    //cout<<index<<endl;
    if(table[index] != NULL){
        for(unsigned int i = 0; i<table[index]->size(); i++){
            if((*table[index])[i].title == name){
                cout<<"Score: "<<(*table[index])[i].rating<<" out of 100"<<endl;
                cout<<"Genre: "<<(*table[index])[i].genre<<endl;
                cout<<"Price: $"<<(*table[index])[i].price<<endl;
                found = true;
                int input;
                while(input != 4){
                    displayFindMenu();
                    cin >> input;
                    cin.clear();
                    switch(input){
                        case 1:
                            cart.push_back((*table[index])[i]);
                            cout<<(*table[index])[i].title<<" has been added to the shopping cart"<<endl;
                            break;
                        case 2:
                            info = getInfo((*table[index])[i].title);
                            cout<<info<<endl;
                            break;
                        case 3:
                            rating = getESRB((*table[index])[i].title);
                            cout<<"This game is rated: "<<rating<<endl;
                            break;
                        case 4:
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
    if(table[index] != NULL){
        for(unsigned int i = 0; i<table[index]->size(); i++){
            if((*table[index])[i].title == title){
                table[index]->erase(table[index]->begin() + i);
                found = true;
                break;
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
        /*char a = title.at(i);
        sum = sum + int(a);*/
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
        for(unsigned int i = 0; i<cart.size(); i++){
            sum = sum + cart[i].price;
        }
        if(budget >= sum){
            for(unsigned int j = 0; j<cart.size(); j++){
                deleteGame(cart[j].title);
            }

            budget = budget - sum;
            cout<<"We hope you enjoy your new games!"<<endl;
            cart.erase(cart.begin(), cart.begin()+cart.size());
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

void hashTable::insertGameInfo(string name, string esrb, string info){
    int index = 0;
    index = hashSum(name);
    //cout<<index<<endl;
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
    if(table2[index] != NULL){
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
    if(table2[index] != NULL){
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
