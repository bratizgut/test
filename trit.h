#include <iostream>

enum class trit{Unknown = 0, False, True};

trit operator&(trit a, trit b){
    if(a == trit::False || b == trit::False)
        return trit::False;

    if(a == trit::True && b == trit::True)
        return trit::True;

    return trit::Unknown;
};

void operator&=(trit &a, trit b){
    a = a & b;
};

trit operator|(trit a, trit b){
    if(a == trit::True || b == trit::True)
        return trit::True;

    if(a == trit::False && b == trit::False)
        return trit::False;

    return trit::Unknown;
};

void operator|=(trit &a, trit b){
    a = a | b;
};

trit operator~(trit a){
    switch (a){
        case(trit::False):
            return trit::True;

        case(trit::True):
            return trit::False;

        default:
            return trit::Unknown;
    }
};

std::ostream& operator<<(std::ostream &out, trit a){
    switch(a){
        case(trit::False):
            out << "False";
            break;
            
        case(trit::True):
            out << "True";
            break;
            
        default:
            out << "Unknown";
            break;
    }

    return out;
}

std::istream& operator >> (std::istream &in, trit &a){
    std::string input;
    in >> input;

    if(input == "False"){
        a = trit::False;
        return in;
    }

    if(input == "Unknown"){
        a = trit::Unknown;
        return in;
    }

    if(input == "True"){
        a = trit::True;
        return in;
    }

    std::cout << "invalid value";
    return in;
}