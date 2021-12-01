//The main file which links all header files together, uses the external json parsing framework, and contains the main function.
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
#include "nlohmann/json.hpp"
using json = nlohmann::json;
#include "convertType.h"
#include "carDef.h"
#include "marketDef.h"
#include "makeDef.h"
#include "builderFunc.h"
#include "mainFuncs.h"
#include "streamFuncs.h"

//The the main function which contains the main menu, the outer game loop and inner day loop, and cod for player inputs within the game.
int main() {
    
    //Loading all variables and setting them to 0 or empty strings. Empty Car and Market objects are created as well.
    bool inMenu = false;
    bool saveLoaded = false;
    char fileChoice = ' ';
    int dayCount = 0;
    int menuChoice = 0;
    int carsBought = 0;
    int carsSell = 0;
    int carsBoughtLimit = 0;
    int carsSellLimit = 0;
    double sellPrice = 0.0;
    double money = 200000.0;
    double lifeTimeProfit = 0.0;
    double moneySpent = 0.0;
    double fixedCost = 500.0;
    Manufacturer mList [9];
    Market demand;
    Market emptyMarket;
    Car usedCars[10];
    Car newCars[10];
    Car invCars[10];
    Car saleCars[10];
    Car emptyCars1[10];
    vector<Car> soldCars;
    vector<Car> emptyCars2;
    srand((unsigned)time(0));
    makeMatch(mList);
    demand.setMarket();
    
    cout << "Welcome to 100 Days. Do you wish to start a new game or load a save file?" << endl;
    cout << "Enter (N/S) for save file or new game." << endl;
    cin >> fileChoice;
    //Either loads save file and fills all variables with json data or starts the game with the empty variables.
    if (fileChoice == 'S') {
        inputFile(soldCars, usedCars, newCars, invCars, saleCars, carsBought, carsSell, carsBoughtLimit, carsSellLimit, money, moneySpent, lifeTimeProfit, demand, dayCount);
        saveLoaded = true;
    }
    else {
        cout << "Starting new game..." << endl;
    }
        
    while (dayCount < 100) {
        
        //Checks if save data was loaded or not. If not, it does typical start-of-day procedure such as adjusting the market demand and generating a new list
        //of used and new cars.
        inMenu = false;
        if (saveLoaded == false) {
            dayCount++;
            demand.resetMarket();
            carsBoughtLimit = 0;
            carsSellLimit = 0;
            //Loop that generates a list of used a new cars for sale.
            for (int x = 0; x < 10; x++) {
                usedCars[x] = build(mList, 1, demand);
                newCars[x] = build(mList, 0, demand);
                if (invCars[x].getMake() != "")
                    expPriceBuild(invCars[x], demand);
                if (saleCars[x].getMake() != "") {
                    expPriceBuild(saleCars[x], demand);
                    ratingBuild(saleCars[x]);
                }
            }
        }
        else {
            saveLoaded = false;
        }
        
        while (inMenu == false) {
            
            //The main menu. The user must enter an integer between 1 and 7 to choose an option.
            cout << "\nDay " << dayCount << endl;
            cout << "--------------------------------------------" << endl;
            cout << "1: See used car offers." << endl;
            cout << "2: Search for brand new cars for sale." << endl;
            cout << "3: Check out your inventory." << endl;
            cout << "4: See your cars for sale and their ratings." << endl;
            cout << "5: Ask a specialist for a market analysis." << endl;
            cout << "6: End the day." << endl;
            cout << "7: Save and end game.\n" << endl;
            cout << "Cash: " << fixed << setprecision(2) << money << endl;
            cout << endl;
            cin >> menuChoice;
            
            switch (menuChoice) {
                //Choice 1 loads a list of the generated used cars and the player can choose any of the 10 cars to buy if they have enough money and room
                //in their inventory.
                case 1:
                    displayList(usedCars, money, menuChoice);
                    cin >> menuChoice;
                    
                    if (carsBoughtLimit < 3) {
                        if (menuChoice == 0)
                            continue;
                        else if (menuChoice <= 10 && menuChoice > 0) {
                            if (money >= usedCars[menuChoice - 1].getBuyPrice()) {
                                for (int x = 0; x < 10; x++) {
                                    if (invCars[x].getMake() == "") {
                                        if (usedCars[menuChoice - 1].getMake() == "") {
                                            cout << "\nInvalid option.\n";
                                            break;
                                        }
                                        
                                        money -= usedCars[menuChoice - 1].getBuyPrice();
                                        moneySpent += usedCars[menuChoice - 1].getBuyPrice();
                                        invCars[x].transfer(usedCars[menuChoice - 1]);
                                        cout << "\nYou bought car number " << menuChoice << ". You have " << money << " in cash left.\n" << endl;
                                        carsBought++;
                                        carsBoughtLimit++;
                                        break;
                                    }
                                    else if (x == 9)
                                        cout << "\nYou don't have room in your inventory to buy a car.\n" << endl;
                                }
                            }
                            else
                                cout << "\nYou don't have enough money to buy that car.\n" << endl;
                        }
                        else
                            cout << "Invalid input." << endl;
                            cin.clear();
                            cin.ignore();
                            continue;
                        break;
                    }
                    else
                        cout << "\nYou already bought 3 cars today. Try again tomorrow.\n" << endl;
                        break;
                case 2:
                    //Choice 2 loads a list of the generated new cars and the player can choose any of the 10 cars to buy if they have enough money and room
                    //in their inventory.
                    displayList(newCars, money, menuChoice);
                    cin >> menuChoice;
                    
                    if (carsBoughtLimit < 3) {
                        if (menuChoice == 0)
                            continue;
                        else if (menuChoice <= 10 && menuChoice > 0) {
                            if (money >= newCars[menuChoice - 1].getBuyPrice()) {
                                for (int x = 0; x < 10; x++) {
                                    if (invCars[x].getMake() == "") {
                                        if (newCars[menuChoice - 1].getMake() == "") {
                                            cout << "\nInvalid option.\n";
                                            break;
                                        }
                                        
                                        money -= newCars[menuChoice - 1].getBuyPrice();
                                        moneySpent += newCars[menuChoice - 1].getBuyPrice();
                                        invCars[x].transfer(newCars[menuChoice - 1]);
                                        cout << "\nYou bought car number " << menuChoice << ". You have " << money << " in cash left.\n" << endl;
                                        carsBought++;
                                        carsBoughtLimit++;
                                        break;
                                    }
                                    else if (x == 9)
                                        cout << "\nYou don't have room in your inventory to buy a car.\n" << endl;
                                }
                            }
                            else
                                cout << "\nYou don't have enough money to buy that car.\n" << endl;
                        }
                        else
                            cout << "Invalid input." << endl;
                            cin.clear();
                            cin.ignore();
                            continue;
                        break;
                    }
                    else
                        cout << "\nYou already bought 3 cars today. Try again tomorrow.\n" << endl;
                        break;
                case 3:
                    //Choice 3 loads a list of your cars that were bought but not put up for sale yet. Here, the player can choose a car to put up for sale
                    //and choose a price to sell it for.
                    displayList(invCars, money, menuChoice);
                    cin >> menuChoice;
                    
                    if (carsSellLimit < 3) {
                        if (menuChoice == 0)
                            continue;
                        else if (menuChoice <= 10 && menuChoice > 0) {
                            for (int x = 0; x < 10; x++) {
                                if (saleCars[x].getMake() == "") {
                                    if (invCars[menuChoice - 1].getMake() == "") {
                                        cout << "\nInvalid option.\n";
                                        break;
                                    }
                                    
                                    cout << "\nFor how much will you be selling this car for?" << endl;
                                    cout << "Original buyer selling price was " << invCars[menuChoice - 1].getBuyPrice() << ".\n" << endl;
                                    cin >> sellPrice;
                                    if (sellPrice > 0) {
                                        invCars[menuChoice - 1].setSelPrice(sellPrice);
                                        ratingBuild(invCars[menuChoice - 1]);
                                        saleCars[x].transfer(invCars[menuChoice - 1]);
                                        cout << "\nYou put car number " << menuChoice << " for sale for " << saleCars[x].getSelPrice() << ".\n" << endl;
                                        carsSellLimit++;
                                    }
                                    else {
                                        cout << "Invalid input." << endl;
                                        cin.clear();
                                        cin.ignore();
                                    }
                                    break;
                                }
                                else if (x == 9)
                                    cout << "\nYou can't put up anymore cars for sale.\n" << endl;
                            }
                        }
                        else
                            cout << "Invalid input." << endl;
                            cin.clear();
                            cin.ignore();
                            continue;
                        break;
                    }
                    else
                        cout << "\nYou already put 3 cars up for sale today. Try again tomorrow.\n" << endl;
                        break;
                case 4:
                    //Choice 4 loads a list of your cars put up for sale. Here, each car up for sale is given a rating based on the best possible combination
                    //of profit margin and chance of sale. The best price to sell a car for is 50% of its market price. This is because this gives you the
                    //most profit while not sacrificing too much of your chance to sell. The player also has the option to remove cars from sale and return
                    //them to their inventory to resale it for a new price.
                    displayList(saleCars, money, menuChoice);
                    cin >> menuChoice;
                    
                    if (menuChoice == 0)
                        continue;
                    else if (menuChoice <= 10 && menuChoice > 0) {
                        for (int x = 0; x < 10; x++) {
                            if (invCars[x].getMake() == "") {
                                if (saleCars[menuChoice - 1].getMake() == "") {
                                    cout << "\nInvalid option.\n";
                                    break;
                                }
                                
                                invCars[x].transfer(saleCars[menuChoice - 1]);
                                cout << "\nYou removed car number " << menuChoice << " from sale.\n" << endl;
                                break;
                            }
                            else if (x == 9)
                                cout << "\nYou don't have room in your inventory to remove a car from sale.\n" << endl;
                        }
                    }
                    else
                        cout << "Invalid input." << endl;
                        cin.clear();
                        cin.ignore();
                        continue;
                    break;
                case 5:
                    //Choice 5 loads the market analyst screen. Go to mainFuncs.h for more details.
                    marketAnalysis(demand, money, moneySpent);
                    break;
                case 6:
                    //Choice 6 ends the day by setting inMenue to true which causes the game to exit the inner loop and increase the day count, generate new
                    //used and new cars, adjust market demand, adjust expected prices and ratings of your inventory and sale cars, and reset the cars bought
                    //and cars put up for sale limit since the most a player can buy/put up for sale a car is 3 times per day.
                    inMenu = true;
                    break;
                case 7:
                    //Choice 7 causes the game to export the game data to a json file and exit the program.
                    outputFile(soldCars, usedCars, newCars, invCars, saleCars, carsBought, carsSell, carsBoughtLimit, carsSellLimit, money,  moneySpent, lifeTimeProfit, demand, dayCount);
                    cout << "Saving and ending game..." << endl;
                    exit(0);
                    break;
                default:
                    //Error handling for main menu options.
                    cout << "Invalid input." << endl;
                    cin.clear();
                    cin.ignore();
                    break;
            }
            
        }
        
        //End of day duties which include subtracting maintenance costs from player money and ending the game if player's money is set to 0 or below.
        //If the player still has money left after maintenance costs, the game checks if any of the player's cars put up for sale were sold and
        //increases the players money accordingly.
        checkCosts(invCars, saleCars, money, moneySpent, fixedCost);
        if (money <= 0) {
            cout << "You have gone bankrupt. The game is over. Saving and ending..." << endl;
            exit(0);
        }
        checkCarsSold(saleCars, soldCars, money, lifeTimeProfit, carsSell);
    
    }
    
    //Final lines of code once the player ends day 100. It exports a save file with empty data so that the next time the game is loaded the player won't load a
    //save file of the previous game. The game then ends as the program reaches the end.
    cout << "You earned " << lifeTimeProfit << " in profit over your run." << endl;
    cout << "Now ending the game..." << endl;
    outputFile(emptyCars2, emptyCars1, emptyCars1, emptyCars1, emptyCars1, 0, 0, 0, 0, 0.0, 0.0, 0.0, emptyMarket, 0);
    
    return 0;
}
