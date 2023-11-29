#ifndef OBJPOS_H
#define OBJPOS_H

class objPos
{
    public:
        int x;
        int y;
        char symbol;

        // Constructors
        objPos(); // initialize an objPos
        objPos(objPos &o); // copy constructor
        objPos(int xPos, int yPos, char sym); // initialize with values

        // Setters
        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  
        
        // Getters
        void getObjPos(objPos &returnPos);
        char getSymbol();

        // Mutators
        bool isPosEqual(const objPos* refPos); // evaluates if coordinates match ref
        
        char getSymbolIfPosEqual(const objPos* refPos); // returns obj symbol if coordinates match
};

#endif