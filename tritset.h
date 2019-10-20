#include <vector>
#include <map>
#include "trit.h"

class tritset{
private:
    size_t sizeChar;
    size_t sizeTrit;
    static const unsigned char mask = 0b11;
    std::vector<unsigned char> container;

public:

    class reference{

        tritset *trits;
        size_t index;
    
    public:
        reference(tritset *trits, size_t index) : trits(trits), index(index){          
        }

        operator trit() const{
            return this->getTrit();
        }

         trit getTrit() const{
            if(index > trits->sizeTrit)
                return trit::Unknown;

            unsigned char cell = trits->container[index / 4];

            return (trit)((cell & (mask << (6 - 2 * (index % 4)))) >> (6 - 2 * (index % 4)));
        }

        reference &operator=(trit val){
            if(index >= trits->sizeTrit)
                if(val != trit::Unknown){
                    trits->sizeTrit = index + 1;
                    trits->sizeChar = trits->sizeTrit / 4 + 1;
                    trits->container.resize(trits->sizeChar);
                } else {
                    return *this; 
                }

            trits->container[index/4] = (trits->container[index/4] & ~(mask << (6 - 2 * (index % 4))));
            trits->container[index/4] = (trits->container[index/4] | ((unsigned char)val << (6 - 2 * (index % 4))));
            return *this;
        }

        reference &operator=(reference a){
            *this = a.getTrit();
            return *this;
        }
    };

    tritset(size_t size){
        sizeChar = size / 4 + 1;
        sizeTrit = size;
        container.resize(sizeChar);
    };

    reference operator[](int index){
        return reference(this, index);
    }

    size_t getSize(){
        return sizeTrit;
    }

    tritset operator=(tritset b){
        this->container.resize(b.getSize() / 4 + 1);
        this->sizeTrit = b.getSize();
        this->sizeChar = this->sizeTrit / 4 + 1;
        
        size_t i = 0;
        while(i < this->getSize()){
            (*this)[i] = b[i];
            i++;
        }

        return *this;
    }

    size_t cardinality(trit val){
        size_t N = 0;
        for(size_t i = 0; i < this->getSize(); i++){
            if ((*this)[i] == val)
                N++;
        }

        return N;
    }

    std::map<trit, int> cardinality(){
        std::map<trit, int> result{
            {trit::False, 0},
            {trit::Unknown, 0},
            {trit::True, 0},
        };

        for(size_t i = 0; i < this->getSize(); i++){
            if ((*this)[i] == trit::False)
                result[trit::False]++;
            if ((*this)[i] == trit::Unknown)
                result[trit::Unknown]++;
            if ((*this)[i] == trit::True)
                result[trit::True]++;
        }

        return result;
    }

    void shrink(){
        this->sizeTrit = this->length();
        this->sizeChar = this->sizeTrit / 4 + 1;
        this->container.resize(this->sizeChar);
    }

    void trim(size_t lastIndex){
        for(size_t i  = lastIndex; i < this->getSize(); i++){
            (*this)[i] = trit::Unknown;
        }
    }

    size_t length(){
        size_t N = 0;
        for(size_t i = 0; i < this->getSize(); i++){
            if((*this)[i] != trit::Unknown)
                N = i;
        }
        
        return N + 1;
    }

};

tritset operator&(tritset &a, tritset &b){
    tritset c(a.getSize() > b.getSize() ? a.getSize() : b.getSize());

    size_t i = 0;
    while(i < c.getSize()){
        c[i] = a[i] & b[i];
        i++;
    }
    
    return c;
}

tritset operator|(tritset &a, tritset &b){
    tritset c(a.getSize() > b.getSize() ? a.getSize() : b.getSize());

    size_t i = 0;
    while(i < c.getSize()){
        c[i] = a[i] | b[i];
        i++;
    }

    return c;
}

tritset operator~(tritset &a){
    tritset c(a.getSize());

    size_t i = 0;
    while(i < c.getSize()){
        c[i] = ~a[i];
        i++;
    }

    return c;
}