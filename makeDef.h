//Header file that stores the Manufacturer class definition. This class will establish all model naming styles for each of the manufacturers.
#ifndef makeDef_h
#define makeDef_h

class Manufacturer {
    
    //Private variables for the Manufacturer class.
    private:
        string makeName;
        int namingStyleID;
    //Public member functions for the Manufacturer class including constructors, getters, setters, and the namingStyle function.
    public:
        Manufacturer() {
            makeName = "";
            namingStyleID = 0;
        }
        Manufacturer(string mkN, int nsI) {
            makeName = mkN;
            namingStyleID = nsI;
        }
        
        string getMakeName ()
            {return makeName;}
        int getNamingStyleID ()
            {return namingStyleID;}
        void setMakeName (string mkN)
            {makeName = mkN;}
        void setNamingStyleID (int nsI)
            {namingStyleID = nsI;}
        
        //Function that returns a number between 1 and 5 and is used to set a consistent model naming style for each manufacturer.
        void namingStyle() {
            int styleID = rand() % 5 + 1;
            namingStyleID = styleID;
        }
    
};

#endif
