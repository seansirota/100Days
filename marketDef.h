//Header file defining the market class.
#ifndef marketDef_h
#define marketDef_h

class Market {
    
    //Private member variables that decide which car attributes are popular and unpopular in the current moment.
    private:
        string makeUp;
        string makeDown;
        string sizeUp;
        string sizeDown;
        string typeUp;
        string typeDown;
    //Contains constructors, getters, setters, setMarket, resetMarket, and priceImpact functions.
    public:
        Market() {
            makeUp = "";
            makeDown = "";
            sizeUp = "";
            sizeDown = "";
            typeUp = "";
            typeDown = "";
        }
        Market(string mu, string md, string su, string sd, string tu, string td) {
            makeUp = mu;
            makeDown = md;
            sizeUp = su;
            sizeDown = sd;
            typeUp = tu;
            typeDown = td;
        }
        
        string getMakeUp()
            {return makeUp;}
        string getMakeDown()
            {return makeDown;}
        string getSizeUp()
            {return sizeUp;}
        string getSizeDown()
            {return sizeDown;}
        string getTypeUp()
            {return typeUp;}
        string getTypeDown()
            {return typeDown;}
        
        void setMakeUp(string mu)
            {makeUp = mu;}
        void setMakeDown(string md)
            {makeDown = md;}
        void setSizeUp(string su)
            {sizeUp = su;}
        void setSizeDown(string sd)
            {sizeDown = sd;}
        void setTypeUp(string tu)
            {typeUp = tu;}
        void setTypeDown(string td)
            {typeDown = td;}
        
        //Used at the start of the game to assign each market variable a value based on randomness.
        void setMarket() {
            
            int randHolder;
            
            randHolder = rand() % 8;
            makeUp = makeIDMatch(randHolder);
            do {
                randHolder = rand() % 8;
                makeDown = makeIDMatch(randHolder);
            } while (makeUp == makeDown);
            randHolder = rand() % 3 + 1;
            sizeUp = sizeIDMatch(randHolder);
            do {
                randHolder = rand() % 3 + 1;
                sizeDown = sizeIDMatch(randHolder);
            } while (sizeUp == sizeDown);
            randHolder = rand() % 5 + 1;
            typeUp = typeIDMatch(randHolder);
            do {
                randHolder = rand() % 5 + 1;
                typeDown = typeIDMatch(randHolder);
            } while (typeUp == typeDown);
            
        }
        
        //Used at the start of each day to check if the market gets adjusted.
        void resetMarket() {
            
            double randChance;
            int randHolder;
            double changeChance = 0.1;
            
            //Loop that goes through all six market variables. Each market variable gets a 10% chance to have its value adjusted. Checks to make sure
            //no market variable is the same and that the adjusted market variable is not equal to the previous.
            for (int x = 0; x < 6; x++) {
                randChance = (rand() % 100 + 1) * 0.01;
                if (randChance <= changeChance) {
                    switch (x + 1) {
                        case 1:
                            do {
                                randHolder = rand() % 8;
                            } while (makeDown == makeIDMatch(randHolder) || makeUp == makeIDMatch(randHolder));
                            makeUp = makeIDMatch(randHolder);
                            break;
                        case 2:
                            do {
                                randHolder = rand() % 8;
                            } while (makeDown == makeIDMatch(randHolder) || makeUp == makeIDMatch(randHolder));
                            makeDown = makeIDMatch(randHolder);
                            break;
                        case 3:
                            do {
                                randHolder = rand() % 3 + 1;
                            } while (sizeDown == sizeIDMatch(randHolder) || sizeUp == sizeIDMatch(randHolder));
                            sizeUp = sizeIDMatch(randHolder);
                            break;
                        case 4:
                            do {
                                randHolder = rand() % 3 + 1;
                            } while (sizeDown == sizeIDMatch(randHolder) || sizeUp == sizeIDMatch(randHolder));
                            sizeDown = sizeIDMatch(randHolder);
                            break;
                        case 5:
                            do {
                                randHolder = rand() % 5 + 1;
                            } while (typeDown == typeIDMatch(randHolder) || typeUp == typeIDMatch(randHolder));
                            typeUp = typeIDMatch(randHolder);
                            break;
                        case 6:
                            do {
                                randHolder = rand() % 5 + 1;
                            } while (typeDown == typeIDMatch(randHolder) || typeUp == typeIDMatch(randHolder));
                            typeDown = typeIDMatch(randHolder);
                            break;
                        default:
                            break;
                    }
                }
                    
            }
            
        }
        
    
        //Function that returns the adjusted price impact for each market attribute should the car have any of the low or high demand market attributes.
        double priceImpact(Car &temp, int mode) {
            
            double impact = 0.0;
            int sign = 0;
            
            //Mode index is based on the three market attributes. If the car matches any of these attributes, its price increases, decreases, or stays the same.
            //Each market attribute can increase or decrease the price by a certain percent. Each attribute has their own percent range. Make can change by
            //up to +/-5% to 15%, size can change by up to +/-15% to 25%, and type can change by up to +/-25% to 35%.
            switch (mode) {
                case 1:
                    if (makeUp == temp.getMake())
                        sign = 1;
                    else if (makeDown == temp.getMake())
                        sign = -1;
                    impact = (rand() % (3 + 1)) * 0.05 * sign;
                    break;
                case 2:
                    if (sizeUp == temp.getSize())
                        sign = 1;
                    else if (sizeDown == temp.getSize())
                        sign = -1;
                    impact = (rand() % (3 + 1) + 2) * 0.05 * sign;
                    break;
                case 3:
                    if (typeUp == temp.getType())
                        sign = 1;
                    else if (typeDown == temp.getType())
                        sign = -1;
                    impact = (rand() % (3 + 1) + 4) * 0.05 * sign;
                    break;
                default:
                    break;
            }
            
            return impact;
            
        }
    
};

#endif
