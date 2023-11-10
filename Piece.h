#include <iostream>
#ifndef PIECE_H
#define PIECE_H
class Piece{
    public :
                char left;
                char  top;
                char  right; 
                char bot;

   
           
            Piece();
                
            
            Piece(char left, char top, char right , char bot ) ;
    
            Piece& operator=(const Piece& other);
};
#endif