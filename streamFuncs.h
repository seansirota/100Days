//Header file which contains all stream related functions when exporting or importing json data into the game.
#ifndef streamFuncs_h
#define streamFuncs_h

//Function used to automate all Car arrays into the json file.
void carList(ofstream &outFile, Car C[], int carType) {
    
    string carTypeName;
    
    //Matches car list index to the relevant string name.
    switch (carType) {
        case 1:
            carTypeName = "Used";
            break;
        case 2:
            carTypeName = "New";
            break;
        case 3:
            carTypeName = "Inventory";
            break;
        case 4:
            carTypeName = "Sale";
            break;
        default:
            break;
    }
    
    //Loop that builds each Car object into the json file under the relevant car list.
    outFile << "\t\"" << carTypeName << " Cars\":[" << endl;
    for (int x = 0; x < 10; x++) {
        outFile << fixed << setprecision(2);
        outFile << "\t\t{\"Make\":\"" << C[x].getMake() << "\", ";
        outFile << "\"Model\":\"" << C[x].getModel() << "\", ";
        outFile << "\"Condition\":\"" << C[x].getCondition() << "\", ";
        outFile << "\"Mileage\":" << C[x].getMileage() << ", ";
        outFile << "\"Expected Price\":" << C[x].getExpPrice() << ", ";
        outFile << "\"Buy Price\":" << C[x].getBuyPrice() << ", ";
        outFile << "\"Sell Price\":" << C[x].getSelPrice() << ", ";
        outFile << "\"Sell Chance\":" << C[x].getSelChance() << ", ";
        outFile << "\"Rating\":\"" << C[x].getRating() << "\", ";
        outFile << "\"Size\":\"" << C[x].getSize() << "\", ";
        outFile << "\"Type\":\"" << C[x].getType() << "\"}";
        if (x < 9)
            outFile << "," << endl;
        else
            outFile << endl;
    }
    outFile << "\t], " << endl;
    
}

//Function used to export game data into a json file called "SaveFile.json".
void outputFile(vector<Car> Sd, Car U[], Car N[], Car I[], Car S[], int cb, int cs, int cbl, int csl, double money, double ms, double ltp, Market D, int day) {
    
    ofstream outFile;
    
    //Either opens existing "SaveFile.json" or creates a new one if it doesn't exist.
    outFile.open("SaveFile.json");
    
    
    //Starts with the root of the json tree.
    outFile << fixed << setprecision(2);
    outFile << "{\"Save Data\":{" << endl;
    
    //Exports the general stats such as total cars sold, bought, and money at that point in the game.
    outFile << "\t\"General Stats\":{" << endl;
    outFile << "\t\t\"Day\":" << day << "," << endl;
    outFile << "\t\t\"Cars Sold\":" << cs << "," << endl;
    outFile << "\t\t\"Cars Bought\":" << cb << "," << endl;
    outFile << "\t\t\"Cars Sold Today\":" << csl << "," << endl;
    outFile << "\t\t\"Cars Bought Today\":" << cbl << "," << endl;
    outFile << "\t\t\"Money\":" << money << "," << endl;
    outFile << "\t\t\"Money Spent\":" << ms << "," << endl;
    outFile << "\t\t\"Profit\":" << ltp << "" << endl;
    outFile << "\t}, " << endl;
    
    //Exports the current market demand.
    outFile << "\t\"Market Demand\":{" << endl;
    outFile << "\t\t\"Make Up\":\"" << D.getMakeUp() << "\"," << endl;
    outFile << "\t\t\"Make Down\":\"" << D.getMakeDown() << "\"," << endl;
    outFile << "\t\t\"Size Up\":\"" << D.getSizeUp() << "\"," << endl;
    outFile << "\t\t\"Size Down\":\"" << D.getSizeDown() << "\"," << endl;
    outFile << "\t\t\"Type Up\":\"" << D.getTypeUp() << "\"," << endl;
    outFile << "\t\t\"Type Down\":\"" << D.getTypeDown() << "\"" << endl;
    outFile << "\t}, " << endl;
    
    //Exports all four car lists into the json file.
    carList(outFile, U, 1);
    carList(outFile, N, 2);
    carList(outFile, I, 3);
    carList(outFile, S, 4);
    
    //Exports a list of all the cars sold from the vector containing the list into the json file.
    outFile << "\t\"Sold Cars\":[" << endl;
    for (int x = 0; x < Sd.size(); x++) {
        outFile << fixed << setprecision(2);
        outFile << "\t\t{\"Make\":\"" << Sd[x].getMake() << "\", ";
        outFile << "\"Model\":\"" << Sd[x].getModel() << "\", ";
        outFile << "\"Condition\":\"" << Sd[x].getCondition() << "\", ";
        outFile << "\"Mileage\":" << Sd[x].getMileage() << ", ";
        outFile << "\"Expected Price\":" << Sd[x].getExpPrice() << ", ";
        outFile << "\"Buy Price\":" << Sd[x].getBuyPrice() << ", ";
        outFile << "\"Sell Price\":" << Sd[x].getSelPrice() << ", ";
        outFile << "\"Sell Chance\":" << Sd[x].getSelChance() << ", ";
        outFile << "\"Rating\":\"" << Sd[x].getRating() << "\", ";
        outFile << "\"Size\":\"" << Sd[x].getSize() << "\", ";
        outFile << "\"Type\":\"" << Sd[x].getType() << "\"}";
        if (x < Sd.size() - 1)
            outFile << "," << endl;
        else
            outFile << endl;
    }
    outFile << "\t]}" << endl;
    outFile << "}" << endl;
    
    outFile.close();
    
}

//Function used to automate populating the four car list with variables for each Car object.
void carImport(json &saveFile, Car C[], int carType) {
    
    //Matches car list index to the relevant string name.
    string carTypeName;
    
    switch (carType) {
        case 1:
            carTypeName = "Used Cars";
            break;
        case 2:
            carTypeName = "New Cars";
            break;
        case 3:
            carTypeName = "Inventory Cars";
            break;
        case 4:
            carTypeName = "Sale Cars";
            break;
        default:
            break;
    }
    
    //Imports and sets Car variables from json file to each Car object within the relevant car list.
    for (int x = 0; x < 10; x++) {
        C[x].setMake(saveFile["Save Data"][carTypeName][x]["Make"]);
        C[x].setModel(saveFile["Save Data"][carTypeName][x]["Model"]);
        C[x].setCondition(saveFile["Save Data"][carTypeName][x]["Condition"]);
        C[x].setMileage(saveFile["Save Data"][carTypeName][x]["Mileage"]);
        C[x].setExpPrice(saveFile["Save Data"][carTypeName][x]["Expected Price"]);
        C[x].setBuyPrice(saveFile["Save Data"][carTypeName][x]["Buy Price"]);
        C[x].setSelPrice(saveFile["Save Data"][carTypeName][x]["Sell Price"]);
        C[x].setSelChance(saveFile["Save Data"][carTypeName][x]["Sell Chance"]);
        C[x].setRating(saveFile["Save Data"][carTypeName][x]["Rating"]);
        C[x].setSize(saveFile["Save Data"][carTypeName][x]["Size"]);
        C[x].setType(saveFile["Save Data"][carTypeName][x]["Type"]);
    }
    
}

//This function handles parsing the json file "SaveFile.json" and setting all game variables and objects to the imported json data.
void inputFile(vector<Car> &Sd, Car U[], Car N[], Car I[], Car S[], int &cb, int &cs, int &cbl, int &csl, double &money, double &ms, double &ltp, Market &D, int &day) {
    
    ifstream inFile;
    
    //Checks if save file exists. If not, it exits the inputFile function and starts the game without loading a save file.
    inFile.open("SaveFile.json");
    if (inFile.is_open() == false) {
        cout << "No save file present. Starting a new game...\n" << endl;
        return;
    }
    //Parses json file and loads it into a json object called saveFile.
    json saveFile = json::parse(inFile);
    //Checks if save file contains empty data. If it does, it exits the inputFile function and starts the game without loading a save file.
    if (saveFile["Save Data"]["General Stats"]["Day"] == 0) {
        cout << "Empty save file detected. Starting a new game...\n" << endl;
        return;
    }
    
    //Loads general stats such as money, cars bought, and cars sold into each variable.
    day = saveFile["Save Data"]["General Stats"]["Day"];
    cs = saveFile["Save Data"]["General Stats"]["Cars Sold"];
    cb = saveFile["Save Data"]["General Stats"]["Cars Bought"];
    csl = saveFile["Save Data"]["General Stats"]["Cars Sold Today"];
    cbl = saveFile["Save Data"]["General Stats"]["Cars Bought Today"];
    money = saveFile["Save Data"]["General Stats"]["Money"];
    ms = saveFile["Save Data"]["General Stats"]["Money Spent"];
    ltp = saveFile["Save Data"]["General Stats"]["Profit"];
    
    //Loads market data into the market demand object.
    D.setMakeUp(saveFile["Save Data"]["Market Demand"]["Make Up"]);
    D.setMakeDown(saveFile["Save Data"]["Market Demand"]["Make Down"]);
    D.setSizeUp(saveFile["Save Data"]["Market Demand"]["Size Up"]);
    D.setSizeDown(saveFile["Save Data"]["Market Demand"]["Size Down"]);
    D.setTypeUp(saveFile["Save Data"]["Market Demand"]["Type Up"]);
    D.setTypeDown(saveFile["Save Data"]["Market Demand"]["Type Down"]);
    
    //Loads carImport function for each car list and loads their data into each Car object.
    carImport(saveFile, U, 1);
    carImport(saveFile, N, 2);
    carImport(saveFile, I, 3);
    carImport(saveFile, S, 4);
    
    //Loads sold cars data into the sold cars Car vector.
    for (int x = 0; x < saveFile["Save Data"]["Sold Cars"].size(); x++) {
        Car emptyCar;
        emptyCar.setMake(saveFile["Save Data"]["Sold Cars"][x]["Make"]);
        emptyCar.setModel(saveFile["Save Data"]["Sold Cars"][x]["Model"]);
        emptyCar.setCondition(saveFile["Save Data"]["Sold Cars"][x]["Condition"]);
        emptyCar.setMileage(saveFile["Save Data"]["Sold Cars"][x]["Mileage"]);
        emptyCar.setExpPrice(saveFile["Save Data"]["Sold Cars"][x]["Expected Price"]);
        emptyCar.setBuyPrice(saveFile["Save Data"]["Sold Cars"][x]["Buy Price"]);
        emptyCar.setSelPrice(saveFile["Save Data"]["Sold Cars"][x]["Sell Price"]);
        emptyCar.setSelChance(saveFile["Save Data"]["Sold Cars"][x]["Sell Chance"]);
        emptyCar.setRating(saveFile["Save Data"]["Sold Cars"][x]["Rating"]);
        emptyCar.setSize(saveFile["Save Data"]["Sold Cars"][x]["Size"]);
        emptyCar.setType(saveFile["Save Data"]["Sold Cars"][x]["Type"]);
        Sd.push_back(emptyCar);
    }
    
    cout << "Loading save file...\n" << endl;
    
}

#endif
