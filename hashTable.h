#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <stdlib.h>
#include <vector>

//I use two hash tables, on for the price and score, the other for the rating and info

struct VideoGame{
    std::string title;
    int rating;
    std::string genre;
    int price;
    bool added = false;

    VideoGame(){};

    VideoGame(std::string in_title, int in_rating, std::string in_genre, int in_price){
        title = in_title;
        rating = in_rating;
        genre = in_genre;
        price = in_price;
    }

};

struct GameInfo{
    std::string name;
    std::string esrb;
    std::string descrption;

    GameInfo(){};

    GameInfo(std::string in_name, std::string in_esrb, std::string in_description){
        name = in_name;
        esrb = in_esrb;
        descrption = in_description;

    }
};

class hashTable
{
    public:
        hashTable();
        ~hashTable();
        void readFile();
        void insertGame(std::string name, int rating, std::string genre, int price);
        void insertGameInfo(std::string name, std::string esrb, std:: string info);
        void printInventory();
        void findGame(std::string title);
        void deleteGame(std::string title);
        int getBalance();
        void displayFindMenu();
        void viewShoppingCart();
        void checkOut();
        std::string getESRB(std::string name);
        std::string getInfo(std::string name);
    protected:
    private:
        int hashSum(std::string title);
        int table_size = 10;
        std::vector<VideoGame> *table[10] = {NULL};
        std::vector<VideoGame> cart;
        std::vector<GameInfo> *table2[10] = {NULL};
        int budget = 120;

};
#endif // HASHTABLE_H
