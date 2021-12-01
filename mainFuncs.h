//This header file contains most of the functions used by the main function. These functions often call functions from other header files as well.
#ifndef mainFuncs_h
#define mainFuncs_h

//Function used to match the make ID to its make name. Also calls the namingStyle Manufacturer member function to so that every manufacturer keeps a consistent
//naming style for all their models.
void makeMatch(Manufacturer *M) {
    
    for(int x = 0; x < 9; x++) {
        M[x].setMakeName(makeIDMatch(x));
        M[x].namingStyle();
    }
    
}

//Function used to display a list of cars depending on which car list the player chose to load.
void displayList(Car carList[], double money, int menuChoice) {
    
    string typePrice;
    string ratingCheck = "";
    string extraDashes = "";
    
    //Switch case conditional statement that gives the player instruction based on their main menu choice.
    switch (menuChoice) {
        case 1:
            cout << "\nChoose a used car to buy if you can afford it. You may buy up to 3 cars per day." << endl;
            typePrice = "Buyer ";
            break;
        case 2:
            cout << "\nChoose a new car to buy if you can afford it. You may buy up to 3 cars per day." << endl;
            typePrice = "Buyer ";
            break;
        case 3:
            cout << "\nChoose a car to put up for sale." << endl;
            typePrice = "Bought ";
            break;
        case 4:
            cout << "\nThese are your cars currently up for sale. Choose a car to remove from sale." << endl;
            typePrice = "Sell ";
            ratingCheck = "Rating";
            extraDashes = "-------";
        default:
            break;
    }
    
    //Loads the tables, including the columns containing the car attribute and autogenerated rows as indices for each car and the number to enter when
    //choosing a car from the list.
    cout << "Enter 0 to go back to the main menu.\n" << endl;
    cout << "Choice    Make\t\t     Model\t  Type\t\t    Size\t   Condition    Mileage   " << typePrice << "Price   " << ratingCheck << endl;
    cout << "----------------------------------------------------------------------------------------------" << extraDashes << endl;
    for (int x = 0; x < 10; x++) {
        cout << left << setw(10) << x + 1;
        cout << left << setw(15) << carList[x].getMake();
        cout << left << setw(9) << carList[x].getModel();
        cout << left << setw(14) << carList[x].getType();
        cout << left << setw(11) << carList[x].getSize();
        cout << left << setw(13) << carList[x].getCondition();
        cout << left << setw(10) << carList[x].getMileage();
        switch (menuChoice) {
            //Used, New, and Inventory cars all show the price a seller was selling or sold its car to you for. Sale cars instead show the price
            //you the put the car up for sale and an additional column, its rating, based on the sale price.
            case 1:
                cout << fixed << setprecision(2) << left << setw(13) << carList[x].getBuyPrice() << endl;
                break;
            case 2:
                cout << fixed << setprecision(2) << left << setw(13) << carList[x].getBuyPrice() << endl;
                break;
            case 3:
                cout << fixed << setprecision(2) << left << setw(13) << carList[x].getBuyPrice() << endl;
                break;
            case 4:
                cout << fixed << setprecision(2) << left << setw(13) << carList[x].getSelPrice();
                cout << left << setw(6) << carList[x].getRating() << endl;
                break;
            default:
                break;
        }
    }
    //Displays the players current money which they can see to make decisions.
    cout << endl;
    cout << "Cash: " << money << endl;
    
}

//Function that checks if any cars are sold at the end of the day.
void checkCarsSold(Car S[], vector<Car> &D, double &money, double &lifeTimeProfit, int &carsSell) {
    
    Car emptyCar;
    double randomChance;
    double sellPrice;
    
    //Loops through each car in the sale cars list. If a car in the list has data, then it checks if the car was sold based on its sell chance
    //and then appends the players money and life time profit as well as adding the sold car's data to the sold cars vector.
    for (int x = 0; x < 10; x++) {
        if (S[x].getMake() != "") {
            randomChance = (rand() % 100 + 1) * 0.01;
            if (randomChance <= S[x].getSelChance()) {
                sellPrice = S[x].getSelPrice();
                money += sellPrice;
                lifeTimeProfit += sellPrice;
                cout << "You sold a " << S[x].getMake() << " " << S[x].getModel() << " for " << sellPrice << "." << endl;
                cout << "You now have " << money << ".\n" << endl;
                carsSell++;
                D.push_back(S[x]);
                S[x].transfer(emptyCar);
            }
        }
    }
    
}

//Function that handles the market analyst. Player can choose to spend 5000 to get a hint on the market demand.
void marketAnalysis(Market &D, double &money, double &moneySpent) {
    
    string decision;
    string up;
    string down;
    double fee = 5000.0;
    int mode;
    
    //Player inputs whether they want to spend 5000 on advice from a market analyst.
    cout << "\nYou can purchase the service of a market analyst to give you a tip on market trends." << endl;
    cout << "His fee is " << fee << ". Will you purchase his services? (Y/N)" << endl;
    cin >> decision;
    
    //If the player chooses yes, the game checks if the player has enough money to spend on the market analyst's advice. If not, the player gets booted back
    //to the main menu. If they have enough money, the game chooses a market attribute at random and displays which is in high demand and which is low.
    //The game then subtracts the fee from the player's money.
    if (decision == "Y") {
        if (money >= fee) {
            mode = rand() % 3 + 1;
            switch (mode) {
                case 1:
                    up = D.getMakeUp();
                    down = D.getMakeDown();
                    break;
                case 2:
                    up = D.getSizeUp();
                    down = D.getSizeDown();
                    break;
                case 3:
                    up = D.getTypeUp();
                    down = D.getTypeDown();
                    break;
                default:
                    break;
            }
            money -= fee;
            moneySpent += fee;
            cout << "\nThe analyst says " << up << " is very popular nowadays. " << down << " not so much." << endl;
            cout << "You now have " << money << ".\n" << endl;
        }
        else
            cout << "You don't have enough money to purchase his services.\n" << endl;
    }
    
}

//Function that executes at the end of every day and forces the player to pay in maintenance and operational fees.
void checkCosts (Car I[], Car S[], double &money, double &moneySpent, double fixedCost) {
    
    double variableCost = 0;
    double totalCost = 0;
    
    //The fixed cost is always 500 which includes expenses such as building rent, utilities, tools, and equipment.
    totalCost += fixedCost;
    //The variable cost is calculated by taking the expected price of a car and dividing it by 100. It includes the costs needed to maintain the car while it is being stored
    //inside the building or put out for sale. More expensive cars cost more to maintain.
    for (int x = 0; x < 10; x++) {
        if (I[x].getMake() != "") {
            variableCost = I[x].getExpPrice() / 100;
            totalCost += variableCost;
        }
    }
    for (int x = 0; x < 10; x++) {
        if (S[x].getMake() != "") {
            variableCost = S[x].getExpPrice() / 100;
            totalCost += variableCost;
        }
    }
    
    //The fixed cost combined with the variable cost for each car is the total cost. The total cost is subtracted from the player's money and the game displays how much
    //was taken from the player. If the player's money reaches 0 or negative, they lose the game.
    money -= totalCost;
    moneySpent += totalCost;
    cout << "You spent " << totalCost << " in maintenance and operational costs." << endl;
    cout << "You now have " << money << ".\n" << endl;
    
}

#endif
