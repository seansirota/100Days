//Header file that defines the Car class.
#ifndef carDef_h
#define carDef_h

class Car {
    
    //Private members variables that include all Car object attributes.
    private:
        string make;
        string model;
        string condition;
        int mileage;
        double expPrice;
        double buyPrice;
        double selPrice;
        double selChance;
        string rating;
        string size;
        string type;
    //Public functions which includes constructors, getters, setters, and the transfer function.
    public:
        Car() {
            make = "";
            model = "";
            condition = "";
            mileage = 0;
            expPrice = 0.0;
            buyPrice = 0.0;
            selPrice = 0.0;
            selChance = 0.0;
            rating = "";
            size = "";
            type = "";
        }
        Car(string mk, string md, string cn, int ml, double ep, double bp, double sp, double sc, string r, string s, string t) {
            make = mk;
            model = md;
            condition = cn;
            mileage = ml;
            expPrice = ep;
            buyPrice = bp;
            selPrice = sp;
            selChance = sc;
            rating = r;
            size = s;
            type = t;
        }
        
        string getMake()
            {return make;}
        string getModel()
            {return model;}
        string getCondition()
            {return condition;}
        int getMileage()
            {return mileage;}
        double getExpPrice()
                {return expPrice;}
        double getBuyPrice()
                {return buyPrice;}
        double getSelPrice()
                {return selPrice;}
        double getSelChance()
            {return selChance;}
        string getRating()
            {return rating;}
        string getSize()
            {return size;}
        string getType()
            {return type;}
        
        void setMake(string mk)
            {make = mk;}
        void setModel(string md)
            {model = md;}
        void setCondition(string cn)
            {condition = cn;}
        void setMileage(int ml)
            {mileage = ml;}
        void setExpPrice(double ep)
            {expPrice = ep;}
        void setBuyPrice(double bp)
            {buyPrice = bp;}
        void setSelPrice(double sp)
            {selPrice = sp;}
        void setSelChance(double sc)
            {selChance = sc;}
        void setRating(string r)
            {rating = r;}
        void setSize(string s)
            {size = s;}
        void setType(string t)
            {type = t;}
    
        //This function, when called, will transfer the contents from the Car object in the parameter into the Car object that is calling this function.
        //This function is used mainly to transfer a car between car lists and filling its previous place with an empty Car object.
        Car transfer(Car &old) {
            make = old.getMake();
            model = old.getModel();
            condition = old.getCondition();
            mileage = old.getMileage();
            expPrice = old.getExpPrice();
            buyPrice = old.getBuyPrice();
            selPrice = old.getSelPrice();
            selChance = old.getSelChance();
            rating = old.getRating();
            size = old.getSize();
            type = old.getType();
            
            old.setMake("");
            old.setModel("");
            old.setCondition("");
            old.setMileage(0);
            old.setExpPrice(0.0);
            old.setBuyPrice(0.0);
            old.setSelPrice(0.0);
            old.setSelChance(0.0);
            old.setRating("");
            old.setSize("");
            old.setType("");
            
            return old;
        }
    
};

#endif
