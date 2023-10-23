#include <iostream>
#include <fstream>
#include "Bord.h"
#include "Piece.h"
#include <vector>
#include <thread>
#include<mutex>
mutex m;

#include <chrono>

using namespace std;
char bordcolor; 
Bord::Bord(Piece** bord, int col ,int row) {
    this->bord= bord;
    this->col= col;
    this->row = row ;

}

bool Bord::isposible(Piece** bord, int x, int y, int position) {
    if (usedliste[position ]== false) {
        if(x==0 && y==0){
            if (listPieces[position].left==listPieces[position].top){
                bordcolor=listPieces[position].left;

             return true;
            }  
                 return false ;

        }  
               
            
           
        
      else if(possible(x, y ,position )&& isbordcolor(x, y , position)) return true ;
    
   
    }
       return false;  
}    
    

   

bool Bord::sequentielle(int x, int y) {
    
    if(y==col){
       x +=1;
        y=0;
    }
    if(x==col){
        display(bord);
        return true ;
    
                   }

    
    else{
     
               


    for (int i = 0; i < col * row; i++) {
        if (usedliste[i]== false) {
            if(isposible(this->bord , x , y , i)){
            bord[x][y] = listPieces[i];
           usedliste[i]= true;
             
          
            if (sequentielle(x, y+1)) {
                return true;
            }

            usedliste[i] = false;
        }
    }}
    
       return false;
    }
}

void Bord::display(Piece** bord) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << "   " << bord[i][j].top << "   ";
        }
        cout << endl;
        for (int j = 0; j < col; j++) {
            cout << " " << bord[i][j].left << "   " << bord[i][j].right << " ";
        }
        cout << endl;
        for (int j = 0; j < this->col; j++) {
            cout << "   " << bord[i][j].bot << "   ";
        }
        cout << endl;
        cout << endl;
    }
}



 bool Bord:: possible(int x , int y , int i){
if(x==0){
             return (listPieces[i].left ==bord[x][y-1].right);
}
else if(y==0){

    return(listPieces[i].top==bord[x-1][y].bot);
}
else return ((listPieces[i].left ==bord[x][y-1].right) && (listPieces[i].top==bord[x-1][y].bot));
}



bool Bord :: isbordcolor(int x, int y , int i) {
                if(x==0 && y!=col-1 ) return listPieces[i].top==bordcolor ;

                else if(x==col-1 && y !=col-1) return listPieces[i].bot==bordcolor ;
                else if (y==col-1 && x!=col-1) return listPieces[i].right==bordcolor ;
                    //last angle 
                else if((x==col-1) && (y==col-1)) return (listPieces[i].right==bordcolor && listPieces[i].bot==bordcolor) ;
                    //second angle 
                else   if(x==0 && y==col-1) return (listPieces[i].right==bordcolor && listPieces[i].top==bordcolor) ;
                    //third one clear
                else  if(y==0 && x==col-1 ) return listPieces[i].bot==bordcolor  && listPieces[i].left==bordcolor;
                 else return true;
   
}

 

bool Bord::backtrackparelle(int x, int y) {
    if (y== col) {
       
    display(this->bord);
      
        return true;
    }
    else{
    for (int i = 0; i < col *row; i++) {
    
        if (usedliste[i]== false) {
      
           if(isposible(this->bord , x , y , i)){
            bord[x][y] = listPieces[i];
           usedliste[i]= true;
            
            
          
                   
            if (backtrackparelle(x, y+1)) {
                return true;
            }

           usedliste[i]= false;
        }
    }}
    
    return false;
    }
}

void  Bord::startparralle() {

    for (int x = 0; x < col; x++) {
    thread t([&]{backtrackparelle(x, 0);});
    t.join();
  
}
}
   



int main(int c , char *argv[]) {
   char left , top , bot , right;
   int row , col;
   vector<bool>liste_state;
   vector< Piece>liste_Piece;
   ifstream file(argv[1]);
   if(file){
    file>>row;
    file>>col;
     for(int i=0; i<col*row ; i++){

    file>>left;
    file>>top;
    file>>right;
    file>>bot ;
    Piece P (left, top, right , bot );
    liste_Piece.push_back(P);
    liste_state.push_back(false);
                                }

            }        

     file.close();

cout<< row << endl;


Piece** bord = new Piece*[row];
for (int i = 0; i < row; i++) {
    bord[i] = new Piece[col];
}







Bord b(bord,row, col );
b.listPieces=liste_Piece;
b.usedliste= liste_state;

 std::vector<std::thread> threads;






   

auto start = std::chrono::high_resolution_clock::now();


//cout<<b.sequentielle(0, 0);


 b.startparralle();


auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

int minutes = duration.count() / 60;
int seconds = duration.count() % 60;

std::cout << "Temps d'exécution : " << minutes << " minutes et " << seconds << " secondes" << std::endl;


//cldestructeur de bord 
for (int i = 0; i < row; i++) {
    delete[] bord[i];
}
delete[] bord;

    return 0;
}


