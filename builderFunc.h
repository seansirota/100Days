//Header file that stores all function that are related to generating cars.
#ifndef builderFunc_h
#define builderFunc_h

//Function that returns a string that will be used as the model name for a Car object.
string modelString(int styleID, Car &temp) {
    
    //Char variables that will be used to create the model string.
    char firstPrefix = ' ';
    char secondPrefix = ' ';
    int middle = 0;
    char suffix = ' ';
    int rangeLower = 0;
    string modelName;
    
    //First checks the Car object's size to decide what numerical naming range it will use. The rangeLower variable serves as a base for model names with numbers.
    //For example, a large size car that uses style 1 will have a numerical minimum value of 7. Possible combinations with these parameters include: M9, G7, H8, etc.
    if (temp.getSize() == "Compact") {
        rangeLower = 0;
    }
    else if (temp.getSize() == "Midsize") {
        rangeLower = 3;
    }
    else if (temp.getSize() == "Large") {
        rangeLower = 6;
    }
    
    //The switch case statement that randomly generates a model string by using the style and size parameters and then concatenating each number and letter together.
    switch (styleID) {
        case 1:
            firstPrefix = (rand() % 25 + 1) + 65;
            middle = (rand() % 3 + 1) + rangeLower;
            modelName = string() + firstPrefix + to_string(middle);
            break;
        case 2:
            firstPrefix = (rand() % 25 + 1) + 65;
            secondPrefix = (rand() % 25 + 1) + 65;
            middle = ((rand() % 3 + 1) + rangeLower) * 100;
            modelName = string() + firstPrefix + secondPrefix + to_string(middle);
            break;
        case 3:
            firstPrefix = (rand() % 25 + 1) + 65;
            secondPrefix = (rand() % 25 + 1) + 65;
            modelName = string() + firstPrefix + secondPrefix;
            break;
        case 4:
            middle = ((rand() % 3 + 1) + rangeLower) * 5;
            suffix = (rand() % 25 + 1) + 65;
            modelName = string() + to_string(middle) + suffix;
            break;
        case 5:
            firstPrefix = (rand() % 25 + 1) + 65;
            middle = ((rand() % 3 + 1) + rangeLower) * 100;
            modelName = string() + firstPrefix + '-' + to_string(middle);
            break;
        default:
            break;
    }

    return modelName;
}

//Function that chooses a make ID for the Car object, converts it to correct make name using makeIDMatch, and sets the make string to the Car object.
void makeBuild(Car &temp) {
    
    int makeID = rand() % 8;
    temp.setMake(makeIDMatch(makeID));
    
}

//Function that chooses a size ID for the Car object, converts it to correct size name using sizeIDMatch, and sets the size string to the Car object.
void sizeBuild(Car &temp) {
    
    int sizeID = rand() % 3 + 1;
    temp.setSize(sizeIDMatch(sizeID));
    
}

//The main model building function. Requires both the Car object as a parameter and the Manufacturer object to choose a naming style when creating the model string.
void modelBuild(Car &temp, Manufacturer M[]) {
    
    int styleID = 0;
    
    //Loops through all makes to find the one that matches the Car objects make. Then sets the naming style ID of the Manufacturer object to a variable.
    //Finally, sets the car's model name by building it in the modelString function using the styleID and Car object as parameters.
    for (int x = 0; x < 9; x++) {
        if (M[x].getMakeName() == temp.getMake()) {
            styleID = M[x].getNamingStyleID();
            temp.setModel(modelString(styleID, temp));
            break;
        }
    }
    
}

//Function that chooses a type ID for the Car object, converts it to correct type name using typeIDMatch, and sets the type string to the Car object.
void typeBuild(Car &temp) {
    
    int typeID = rand() % 5 + 1;
    temp.setType(typeIDMatch(typeID));
    
}

//Function that sets the condition and mileage for the car. If the car was bought from the used cars list, it will have a mileage between 12000 and 120000 and will
//have a used condition. If it was bought from the new cars list, it will have 0 mileage and a new condition.
void conMileBuild(Car &temp, int conditionID) {
    
    if (conditionID == 0) {
        temp.setCondition("New");
        temp.setMileage(0);
    }
    else {
        temp.setCondition("Used");
        temp.setMileage((rand() % 108000 + 1) + 12000);
    }
    
}

//Function that builds the market price of the Car object.
void expPriceBuild(Car &temp, Market &D) {
    
    //Size and type price modifiers can range between +/-10%. Mileage ratio is special number that determines how high a car's value is based on how high its mileage is.
    //The mileage ratio can range between 9.5% and 95% for used cars or 100% for new cars. New cars always keep 100% of their potential value since they have 0 mileage.
    double sizePrice = ((rand() % 21) - 10) * 0.01 + 1;
    double typePrice = ((rand() % 21) - 10) * 0.01 + 1;
    double mileageRatio = 1 - (temp.getMileage() * 0.0000079167);
    if (mileageRatio == 0)
        mileageRatio = 1;
    double finalPrice = 0.0;
    
    //Check the car's size to determine the base price based on car size. Then multiply the modifier to the base price.
    if (temp.getSize() == "Compact")
        sizePrice *= 30000;
    else if (temp.getSize() == "Midsize")
        sizePrice *= 50000;
    else if (temp.getSize() == "Large")
        sizePrice *= 70000;
    else
        sizePrice *= 0;
    
    //Check the car's type to determine the additional price that comes with different car style variations. Then multiply the modifier to the base price.
    if (temp.getType() == "Sedan")
        typePrice *= 3000;
    else if (temp.getType() == "Coupe")
        typePrice *= 5000;
    else if (temp.getType() == "SUV")
        typePrice *= 7000;
    else if (temp.getType() == "Hybrid")
        typePrice *= 9000;
    else if (temp.getType() == "Sports Car")
        typePrice *= 11000;
    else
        typePrice *= 0;
    
    //The final price equation is calculated and then set as the expected, or market, price of the car. The way it works is first the base size and base type prices
    //are both multiplied by the market modifiers using the priceImpact Market member function if any attributes match one of the Market object's variables.
    //Then the market-adjusted size and type prices are added together. Then that number is multiplied by a make market modifier using the priceImpact function.
    //Finally, that number is multiplied by the mileage ratio.
    finalPrice = (((sizePrice * (1 + D.priceImpact(temp, 2))) + (typePrice * (1 + D.priceImpact(temp, 3)))) * (1 + D.priceImpact(temp, 1))) * mileageRatio;
    temp.setExpPrice(finalPrice);
    
}

//Function used to determine the buy price which is the price sellers sell you a car for. Can range between +/-20% of the expected price.
void buyPriceBuild(Car &temp) {
    
    double expPrice = temp.getExpPrice();
    double buyPrice = expPrice + expPrice * ((rand() % 41) - 20) * 0.01 + 1;
    temp.setBuyPrice(buyPrice);
    
}


//Function used to build the rating attribute of a car only when it is put up for sale.
void ratingBuild(Car &temp) {
    
    //Sell chance starts at 25% when a car is sold for exactly its exoected price. Sell chance is inversely proportional to the price ratio, which is the percent
    //gain or loss of money you get for selling for a certain price compared to the expected price.
    int ratingID = 0;
    double expPrice = temp.getExpPrice();
    double sellPrice = temp.getSelPrice();
    double sellChance = 0.25;
    double score = 0.0;
    double priceRatio = sellPrice / expPrice - 1;
    
    //Sell chance decreases by 1 point for every 4 point increase in the price ratio. Sell chance and price ratio are set to a minimum bound of 0.
    sellChance -= (priceRatio / 4);
    if (sellChance < 0)
        sellChance = 0;
    if (priceRatio < 0)
        priceRatio = 0;
    
    //The score variable describes the optimization of the priceRatio and sellChance variables. A lower score either means priceRatio or sellChance is too low.
    //Maximum score value can be achieved by having priceRatio equal to 50, which sets sellChance equal to 12.5, and score to 625.
    //Once score is calculated a rating ID is given based on which interval the score falls under.
    score = (priceRatio * 100) * (sellChance * 100);
    if (score <= 0)
        ratingID = 0;
    else if (score <= 67 && score > 0)
        ratingID = 1;
    else if (score <= 133 && score > 67)
        ratingID = 2;
    else if (score <= 200 && score > 133)
        ratingID = 3;
    else if (score <= 267 && score > 200)
        ratingID = 4;
    else if (score <= 333 && score > 267)
        ratingID = 5;
    else if (score <= 400 && score > 333)
        ratingID = 6;
    else if (score <= 433 && score > 400)
        ratingID = 7;
    else if (score <= 467 && score > 433)
        ratingID = 8;
    else if (score <= 500 && score > 467)
        ratingID = 9;
    else if (score <= 533 && score > 500)
        ratingID = 10;
    else if (score <= 567 && score > 533)
        ratingID = 11;
    else if (score <= 600 && score > 567)
        ratingID = 12;
    else if (score <= 625 && score > 600)
        ratingID = 13;
    
    //The ratingID variable is sent to the ratingIDMatch function to determine the letter grade for your sell price. A letter grade of F can mean either your
    //profit is 0 or lower, or that the sell chance is 0. A letter grade of S can be achieved by optimizing the priceRatio and sellChance variables and is
    //considered the most efficient use of both variables. The sell chance and rating are both set for the Car object.
    temp.setSelChance(sellChance);
    temp.setRating(ratingIDMatch(ratingID));
    
}

//This is the build function which literally builds the Car object. Most of the car's attributes are set here.
Car build(Manufacturer M[], int conditionID, Market &D) {
    
    //The build function calls other attribute-level build subfunctions that generate a value for each attribute.
    Car temp;
    makeBuild(temp);
    sizeBuild(temp);
    modelBuild(temp, M);
    typeBuild(temp);
    conMileBuild(temp, conditionID);
    expPriceBuild(temp, D);
    if (conditionID == 0)
        buyPriceBuild(temp);
    else if (conditionID == 1)
        buyPriceBuild(temp);
    
    return temp;

    
}

#endif
