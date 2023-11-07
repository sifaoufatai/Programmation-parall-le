#include <iostream>
#include <fstream>
#include "Bord.h"
#include "Piece.h"
#include <vector>
#include <thread>
#include <atomic>

#include <chrono>

using namespace std;
char bordcolor; atomic <bool> trouve(false);

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
    

   

bool Bord::sequentielle(int x, int y, Bord b) {
        
        
        
    if(trouve ) return true;
    
    if(y==col){
       x +=1;
        y=0;
    }
    if(x==col){
        trouve = true;
        display(b.bord);
        return true ;
    
                   }

    
    else{
     
               


    for (int i = 0; i < col * row; i++) {
        if (b.usedliste[i]== false) {
            if(verifbor( x , y , i)){
           b. bord[x][y] = b.listPieces[i];
           
          b. usedliste[i]= true;
             
          
            if (sequentielle(x, y+1, b)) {
                return true;
            }

          b. usedliste[i] = false;
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
bool Bord::verifbor(int x ,int y ,int i){
    if(!usedliste[i]){

if(x==0){
    if (y==0) {
        return listPieces[i].left==listPieces[i].top;
    }
    else if(y<col-1) {
        return (listPieces[i].left==bord[x][y-1].right && listPieces[i].top== bord[x][y-1].top);
    }
    else  {
       return  (listPieces[i].left==bord[x][y-1].right && listPieces[i].top== bord[x][y-1].top && listPieces[i].right==listPieces[i].top);
    }   
} 

else if(y==0){
   

          
        
    if(x<col-1) {

    return (listPieces[i].left==bord[x-1][y].left && listPieces[i].top==bord[x-1][y].bot);
   }
   else {

   return      (listPieces[i].left==bord[x-1][y].left && listPieces[i].top==bord[x-1][y].bot && listPieces[i].bot==listPieces[i].left);
   }

}
else if(x==col-1)
    {
       
    if(y==0) {  
         return      (listPieces[i].left==bord[x-1][y].left && listPieces[i].top==bord[x-1][y].bot && listPieces[i].bot==listPieces[i].left);

    }
    else if(y<col-1){

        return (listPieces[i].left==bord[x][y-1].right &&listPieces[i].top==bord[x-1][y].bot &&listPieces[i].bot==bord[x][y-1].bot);
    }
    else {

        return (listPieces[i].left==bord[x][y-1].right &&listPieces[i].top==bord[x-1][y].bot &&listPieces[i].bot==bord[x][y-1].bot &&listPieces[i].right==listPieces[i].bot);
    }

    }
else if(y==col-1){
    if(x==0){
      return   (listPieces[i].left==bord[x][y-1].right && listPieces[i].top==bord[x][y-1].top && listPieces[i].right==listPieces[i].top);
    }
    else if(x<col-1){

        
      return   (listPieces[i].left==bord[x][y-1].right && listPieces[i].top==bord[x-1][y].bot && listPieces[i].right==bord[x-1][y].right);
    }
    else {

        
      return   (listPieces[i].left==bord[x][y-1].right && listPieces[i].top==bord[x-1][y].bot && listPieces[i].right==bord[x-1][y].right && listPieces[i].bot==listPieces[i].right);
    }
}

else return (listPieces[i].left ==bord[x][y-1].right && listPieces[i].top == bord[x-1][y].bot);
    
}
return false ;

}

bool Bord::backtrackparelle(int x, int y) {
    if (y== col) {
             cout<<"thread  done "<<x <<endl;
      display(bord);
       
        return true;
    }
    else{
    for (int i = 0; i < col *row; i++) {
        if (usedliste[i]== false) {
          // if(isposible(bord , x , y , i)){

            if(verifbor( x , y , i)){
            bord[x][y] = listPieces[i];
           usedliste[i]= true;
             
          
                   
            if (backtrackparelle(x, y+1)) {
                return true;
            }

           usedliste[i]= false;
        }
    }}
    cout<< "thread fail"<< x <<endl;
    return false;
    }
}

void  Bord::startparralle() {
   for (int i = 0; i <= col; i++) {
    thread t([&]{backtrackparelle(i, 0);});
    t.join();
  
}
//display(bord);
}
void Bord:: creatBortool(char * filname){


   char left , top , bot , right;
   int row , col;
  
   ifstream file(filname);
   if(file){
    file>>row>>col;
  this->row=row;
  this->col=col;
     for(int i=0; i<col*row ; i++){

    file>>left>>top>>right>>bot ;
    
    Piece P (left, top, right , bot );
    listPieces.push_back(P);
    usedliste.push_back(false);
                                }

            }        

     file.close();
cout <<row;

Piece** bord = new Piece*[row];
for (int i = 0; i < row; i++) {
    bord[i] = new Piece[col];
}
this->bord=bord;
}


vector<Piece>  Bord:: getvector(vector<Piece> t, int i ){
vector<Piece >k ;   int n = col* row;


k= t;
k[i]=t[n-i];
k[n-i]=t[i];



return k ;


}
void Bord::Backtrakparralllepool() {
    vector<thread> threadvector;

    for (int i = 0; i < col * row; i++) {
        Bord b;
        b.bord = bord;
        b.listPieces = getvector(listPieces, i);
        b.usedliste = usedliste;
        
        
        thread t([&,b]() {
            sequentielle(0, 0, b);
        });

        
       threadvector.push_back(move(t));
    }

    for (auto &t : threadvector) {
        t.join();
    }
}





int main(int c , char *argv[]) {



Bord b;
b.creatBortool(argv[1]);
//b.sequentielle(0,0);
//b.startparralle();
b.Backtrakparralllepool();

 std::vector<std::thread> threads;

   

//destructeur de bord 
for (int i = 0; i < b.row; i++) {
    delete[]b. bord[i];
}
delete[] b.bord;

    return 0;
}
