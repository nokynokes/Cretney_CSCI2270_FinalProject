# Cretney_CSCI2270_FinalProject
Final project

Project Summary:
My programs is a digital store for video games. The program reads in two files. The first file contains all the Video game titles, ratings, and prices. The second FILE
will contain the ESRB rating of each game and some information about each game. My program stores all of the information from the first file into a hash table and
all the information from the second file into another hashtable (both size 10, this may also change). My programs uses vectors to deal with collisions instead of linked lists
The user will start off with 120$ (this might be changed) and will have the choice of buying games that are read in the from the file by adding them into the shopping cart (another vector)
and then chooses to checkout. My program has one class and two data structs (each struct is for each file).

How to run:
In the terminal, compile with: g++ -std=c++11 FinalProject.cpp -o FinalProject -Wall. To run, type in: ./FinalProject in terminal.
The user will be prompted with a menu. By pressing 1, the program prints all of the games in the hashtable and their prices. By pressing 2,
the program prints out all of the games in the shopping cart. By pressing 3, the program will display the balance. By pressing 4, the program will
prompt the user for a title to search for. If the game exists, the user will be prompted by an other menu in which they can choose to: Add the game to their cart, see the esrb rating, or see the game description.
By pressing 5, the program will checkout. This mean it will add the total prices of all the games in the shopping cart and then see if the user's budget is greater than the total price. After checking out,
the program subtracts the total price from the budget and deletes the games from the shopping cart and the first hashtable (the one where the user searched for the game).

Dependencies:
My program uses no external libraries

System Requriments:
None

Bugs/Glitches:
Early in the cycle, i was using linked lists for collisions but ended up running into to many segmentation faults, so I switched to using vectors instead.


Contributers:
This is a solo project

To-do List:
Make the menu fancier?,
Add more games to txt files,
Sort Alphabectically for collisions,
Add a delete function for shopping cart,









