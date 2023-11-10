#include <iostream>
#include "Piece.h"


    
        Piece::Piece() :  left('Q'),  top('R'),  right('S') , bot ('T') {}
    

            
         Piece::  Piece(char left, char top, char right , char bot ) : left(left),  top(top),  right(right) , bot (bot)
         {
        
            
         }
  Piece& Piece::operator=(const Piece& other) {
    if (this != &other) {  
        this->left = other.left;
        this->top = other.top;
        this->right = other.right;
        this->bot = other.bot;
    }
    return *this;
}
