#include <iostream>
#include <fstream>

#include "Piece.h"
#include <vector>
#include <thread>
#include <atomic>
#include<mutex>
#include <chrono>
#include<algorithm>
#include<random>

using namespace std;
char bordcolor; atomic <bool> trouve(false); atomic<int>nbthread ;


vector<int>task; int T =36;
mutex m;



/*bool isposible(Piece** bord, int x, int y, int position) {
    if (usedliste[position ]== false, ) {
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
    

   */

/*bool sequentielle(int x, int y, Bord b) {
        
        
    //if(b.bord[0][0].left !=  b.bord[0][0].top){cout<< "pas besoins de me traiter aucun n'interet "<< endl; nbthread--;return false ;}

    /*   if(checkifbordvalide(b.bord) && b.bord[0][0].left != ' ' ){
            display(b.bord);
            return true;
        
        
       
        
    //if( (x==0 && y==0)) {nbthread-- ; cout<<"am faliledksjdfhgkdfhgkldfhgkldfhkgdfkgdfklghdklsmgdklgdkhdfklsdsklghfklghdfklghkldf" <<nbthread<<endl; display(b.bord);return false; };
    
    if(y==col){
       x +=1;
        y=0;
    }
    if(x==col){
        trouve = true;
        display(b.bord);
        return true;
       cout<<"jai trouver"<<endl;
        
                   }

    
  
     
   else{         vector<Piece> t


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
        nbthread--; 

      }   return false;
   } 

*/

void display(vector<vector<Piece>> bords) {
    cout<< "je taffiche le palteau"<<endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << "   " << bords[i][j].top << "   ";
        }
        cout << endl;
        for (int j = 0; j < 4; j++) {
            cout << " " << bords[i][j].left << "   " << bords[i][j].right << " ";
        }
        cout << endl;
        for (int j = 0; j < 4; j++) {
            cout << "   " << bords[i][j].bot << "   ";
        }
        cout << endl;
        cout << endl;
    }
}



/**/



/*bool Bord :: isbordcolor(int x, int y , int i) {
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
bool verifbor(int x ,int y ,int i){
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

else return (listPivector<Piece> t
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
}*/
void creatBortool(char * filname, vector<Piece> & listPieces, vector<vector<Piece>> & board,  vector<bool> & usedliste){

   char left , top , bot , right;
   int row , col;
  
   ifstream file(filname);
   if(file){
    file>>row>>col;
  row=row;
  col=col;
  
     for(int i=0; i<col*row ; i++){

    file>>left>>top>>right>>bot ;
    
    Piece P (left, top, right , bot );
    
    listPieces.push_back(P);
    usedliste.push_back(false);
                                }

            }        

     file.close();



}


vector<Piece>   getvector(vector<Piece> t, int i ){
vector<Piece >k ;   
k= t;
auto rng = std::default_random_engine {};
std::shuffle(begin(k), end(k), rng);






return k ;


}
/*void Backtrakparralllepool() {
    vector<thread> threadvector;

    for (int i = 0; i < col * row; i++) {
        Bord b1 =  Bord(this.bord, );
        b1.bord = bord;
        b1.listPieces = getvector(listPieces, i);
        b1.usedliste = usedliste;
        
        
        thread t([& ,b1]() {
            sequentielle(0, 0, b1);
        });

        
       threadvector.push_back(move(t));
    }

    for (auto &t : threadvector) {
        t.join();
    }
}

Piece** Bord::putfirstPiece(Bord b , int i){

    b.bord[0][0]=b.listPieces[i];
    b.usedliste[i]= true;
    return b.bord ;
}
*/
/*void Bord ::threadPool(){


int n = row*col;

   

    for(int i =0; i<36; i++){
        task.push_back(i);
    }

     for(int i =0; i<task.size(); i++){
 
    }

    for(int k = 0 ; k <T; k++){
        Bord b; 
        b.bord= bord ; 
        b.listPieces=listPieces;
        b.usedliste= usedliste ;
        int  current_task=-1;
            m.lock();
            
        
        if(!task.empty() && !trouve ){

            current_task =task.back();
            cout<< current_task<<endl;
            task.pop_back();

            m.unlock();
        }

        if(current_task != -1){

            b.bord = putfirstPiece(b , current_task);
            b.usedliste[current_task]=true;
            nbthread++;
            thread t([&,b](){
            sequentielle(0, 1, b);
            });
            t.detach();
                   cout << "le nombre de thread  = " << nbthread << endl;
        }
    }

  while (1) {
    int next_task = -1;
    if(trouve) return ;
    m.lock();
    

    if(!task.empty()){
           

        if (!task.empty() && nbthread < T && !trouve) {

            next_task = task.back();
            task.pop_back();
            nbthread += 1;
        }
        m.unlock();

        if (next_task != -1) {
            Bord b;
            b.bord = bord;
            b.listPieces = listPieces;
            b.usedliste = usedliste;
            cout << next_task << " ici c'est pour le second" << endl;

            b.bord = putfirstPiece(b, next_task);
            b.usedliste[next_task] = true;

            thread h([& , b]() {
                sequentielle(0, 1, b);
            });
            h.detach();
        }

        
    }
    m.lock();
    if (task.empty() || trouve) {
         cout << "Voici " << nbthread << " je suis le nombre de thread " << endl;
     m.unlock();
       
        break;
    }
    

   
}


    
}

   bool Bord::checkifbordvalide(Piece** bord){

    
    // Vérifier les conditions pour la validité du plateau
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == 0 && j == 0) {
                
                if (bord[i][j].left != bord[i][j].top) {
                    return false;
                }
            } else if (i == 0 && j == col - 1) {
               
                if (bord[i][j].left != bord[i][j - 1].right || bord[i][j].top != bord[i][j].right) {
                    return false;
                }
            } else if (i == row - 1 && j == 0) {
                
                if (bord[i][j].left != bord[i - 1][j].bot || bord[i][j].top != bord[i][j].bot) {
                    return false;
                }
            } else if (i == row - 1 && j == col - 1) {
                // Coin inférieur droit
                if (bord[i][j].left != bord[i - 1][j].bot || bord[i][j].top != bord[i][j - 1].right) {
                    return false;
                }
            } else if (i == 0) {
                // Bordure supérieure
                if (bord[i][j].left != bord[i][j - 1].right || bord[i][j].top != bord[i][j].right) {
                    return false;
                }
            } else if (j == 0) {
                // Bordure gauche
                if (bord[i][j].left != bord[i - 1][j].bot || bord[i][j].top != bord[i][j].bot) {
                    return false;
                }
            } else if (i == row - 1) {
                // Bordure inférieure
                if (bord[i][j].left != bord[i - 1][j].bot || bord[i][j].top != bord[i][j - 1].right) {
                    return false;
                }
            } else if (j == col - 1) {
                // Bordure droite
                if (bord[i][j].left != bord[i][j - 1].right || bord[i][j].top != bord[i - 1][j].bot) {
                    return false;
                }
            } else {
                // Au milieu du plateau
                if (bord[i][j].left != bord[i][j - 1].right || bord[i][j].top != bord[i - 1][j].bot ||
                    bord[i][j].right != bord[i][j].top || bord[i][j].bot != bord[i][j].left) {
                    return false;
                }
            }
        }
    }
    return true;
}

    

*/






int main(int c , char *argv[]) {

std::vector<std::vector<Piece>> board(4, std::vector<Piece>(4));

    vector<Piece>  listePieces;
   // vector<vector<Piece>>  board;
    vector<bool> usedliste;

    creatBortool(argv[1], listePieces,board,usedliste);

    for (Piece p: listePieces){
        cout << p.left << endl;
        }

        for(int i=0; i<4; i++){
            for(int j =0; j<4 ; j++){
                    board[i][j]=listePieces[0];
            }
        }
    display(board);



}
