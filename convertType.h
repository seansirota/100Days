//Header file containing functions that convert an index of a cae attribute into a string.
#ifndef convertType_h
#define convertType_h

//Converts the make ID index into the make name and returns the string value.
string makeIDMatch(int makeID) {
    
    string makeName = "";
    
    switch (makeID) {
        case 0:
            makeName = "Ventura";
            break;
        case 1:
            makeName = "Spark";
            break;
        case 2:
            makeName = "Avelon";
            break;
        case 3:
            makeName = "Perennial";
            break;
        case 4:
            makeName = "Dragula";
            break;
        case 5:
            makeName = "Ivory Steel";
            break;
        case 6:
            makeName = "Dayto";
            break;
        case 7:
            makeName = "Smarktof";
            break;
        case 8:
            makeName = "Nebula";
            break;
        default:
            break;
    }
    
    return makeName;
    
}

//Converts the size ID index into the size name and returns the value.
string sizeIDMatch(int sizeID) {
    
    string sizeName = "";
    
    switch (sizeID) {
        case 1:
            sizeName = "Compact";
            break;
        case 2:
            sizeName = "Midsize";
            break;
        case 3:
            sizeName = "Large";
            break;
        default:
            break;
    }
    
    return sizeName;
    
}

//Converts the type ID index into the type name and returns the string value.
string typeIDMatch(int typeID) {
    
    string typeName = "";
    
    switch (typeID) {
        case 1:
            typeName = "Sedan";
            break;
        case 2:
            typeName = "Coupe";
            break;
        case 3:
            typeName = "SUV";
            break;
        case 4:
            typeName = "Hybrid";
            break;
        case 5:
            typeName = "Sports Car";
            break;
        default:
            break;
    }
    
    return typeName;
    
}

//Converts the rating ID index into the rating name and returns the string value.
string ratingIDMatch(int ratingID) {
    
    string ratingName = "";
    
    switch (ratingID) {
        case 0:
            ratingName = "F";
            break;
        case 1:
            ratingName = "D-";
            break;
        case 2:
            ratingName = "D";
            break;
        case 3:
            ratingName = "D+";
            break;
        case 4:
            ratingName = "C-";
            break;
        case 5:
            ratingName = "C";
            break;
        case 6:
            ratingName = "C+";
            break;
        case 7:
            ratingName = "B-";
            break;
        case 8:
            ratingName = "B";
            break;
        case 9:
            ratingName = "B+";
            break;
        case 10:
            ratingName = "A-";
            break;
        case 11:
            ratingName = "A";
            break;
        case 12:
            ratingName = "A+";
            break;
        case 13:
            ratingName = "S";
            break;
        default:
            break;
    }
    
    return ratingName;
    
}

#endif
