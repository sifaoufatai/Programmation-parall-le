  #ifndef BORD_H
#define BORD_H
  #include<iostream>
  #include <stdio.h>
  #include <vector>
  #include "Piece.h"
    using namespace std ;


class Bord { 
public:
    int row , col;
    vector <Piece> listPieces;
    vector< bool>usedliste ;
    Piece  **bord;
    

   Bord(){};
  // Bord(const Bord& other);
       
    //Bord( Piece** bord , int col, int row  );
    Bord(Piece **bord, int col, int row, vector<Piece> listPieces, vector<bool> usedliste);
    bool isposible(Piece **bord, int x, int y, int position);
    bool sequentielle(int x, int y,Bord b);
    bool possible(int x , int y , int i);
    bool  isbordcolor(int x, int y , int i);
    bool verifbor(int x, int y, int i);
   
    bool backtrackparelle(int x, int y);
    void startparralle();
    void creatBortool(char *filname);
    void threadPool();
    bool checkifbordvalide(Piece **bord);
    void display(Piece **bord);
    vector<Piece> getvector(vector<Piece> v, int i );

    void Backtrakparralllepool();

    Piece **putfirstPiece(Bord b, int i);


    // bool sequentielle(){}
};
#endif