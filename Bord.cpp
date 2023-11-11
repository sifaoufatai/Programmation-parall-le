#include <iostream>
#include <fstream>
#include "Bord.h"
#include "Piece.h"
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;

char bordcolor;
atomic<bool> trouve(false);
atomic<int> nbthread;

vector<int> task;
atomic<bool> afficher(false);
int T = 2;
mutex m;

Bord::Bord(vector<vector<Piece>> bord, int col, int row, vector<Piece> listPieces, vector<bool> usedliste)
{
    this->bord = bord;
    this->col = col;
    this->row = row;
    this->listPieces = listPieces;
    this->usedliste = usedliste;
}

bool Bord::isposible(vector<vector<Piece>> bord, int x, int y, int position)
{
    if (usedliste[position] == false)
    {
        if (x == 0 && y == 0)
        {
            if (listPieces[position].left == listPieces[position].top)
            {
                bordcolor = listPieces[position].left;

                return true;
            }
            return false;
        }

        else if (possible(x, y, position) && isbordcolor(x, y, position))
            return true;
    }
    return false;
}

bool Bord::sequentielle(int x, int y, Bord &b)
{

    // if(b.bord[0][0].left !=  b.bord[0][0].top){cout<< "pas besoins de me traiter aucun n'interet "<< endl; nbthread--;return false ;}
    
    
    if (trouve)
        return true;

    if (y == col)
    {
        x += 1;
        y = 0;
    }
    if (x == col)
    {
        m.lock();
        std::cout << "__________________  *Bingo *________________________" << endl;
        trouve = true;

        if (!afficher)
        {
            afficher = true;
            display(b.bord);
        }
        m.unlock();
        return true;
    }
    else
    {

        for (int i = 0; i < col * row; i++)
        {
            if (b.usedliste[i] == false)
            {
                // if (isposible(b.bord, x, y, i))
                if (verifbor(x, y, i))
                {
                    b.bord[x][y] = b.listPieces[i];

                    b.usedliste[i] = true;

                    if (sequentielle(x, y + 1, b))
                    {
                        return true;
                    }

                    b.usedliste[i] = false;
                    // b.bord[x][y] = Piece();
                }
            }
        }
        

        return false;
    }
}

void Bord::display(vector<vector<Piece>> bords)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << "   " << bords[i][j].top << "   ";
        }
        cout << endl;
        for (int j = 0; j < col; j++)
        {
            cout << " " << bords[i][j].left << "   " << bords[i][j].right << " ";
        }
        cout << endl;
        for (int j = 0; j < this->col; j++)
        {
            cout << "   " << bords[i][j].bot << "   ";
        }
        cout << endl;
        cout << endl;
    }
}

bool Bord::possible(int x, int y, int i)
{
    if (x == 0)
    {
        return (listPieces[i].left == bord[x][y - 1].right);
    }
    else if (y == 0)
    {

        return (listPieces[i].top == bord[x - 1][y].bot);
    }
    else
        return ((listPieces[i].left == bord[x][y - 1].right) && (listPieces[i].top == bord[x - 1][y].bot));
}

bool Bord ::isbordcolor(int x, int y, int i)
{
    if (x == 0 && y != col - 1)
        return listPieces[i].top == bordcolor;

    else if (x == col - 1 && y != col - 1)
        return listPieces[i].bot == bordcolor;
    else if (y == col - 1 && x != col - 1)
        return listPieces[i].right == bordcolor;
    // last angle
    else if ((x == col - 1) && (y == col - 1))
        return (listPieces[i].right == bordcolor && listPieces[i].bot == bordcolor);
    // second angle
    else if (x == 0 && y == col - 1)
        return (listPieces[i].right == bordcolor && listPieces[i].top == bordcolor);
    // third one clear
    else if (y == 0 && x == col - 1)
        return listPieces[i].bot == bordcolor && listPieces[i].left == bordcolor;
    else
        return true;
}
bool Bord::verifbor(int x, int y, int i)
{
    // if(!usedliste[i]){

    if (x == 0)
    {
        if (y == 0)
        {
            return listPieces[i].left == listPieces[i].top;
        }
        else if (y < col - 1)
        {
            return (listPieces[i].left == bord[x][y - 1].right && listPieces[i].top == bord[x][y - 1].top);
        }
        else
        {
            return (listPieces[i].left == bord[x][y - 1].right && listPieces[i].top == bord[x][y - 1].top && listPieces[i].right == listPieces[i].top);
        }
    }
    else if (y == 0)
    {

        if (x < col - 1)
        {

            return (listPieces[i].left == bord[x - 1][y].left && listPieces[i].top == bord[x - 1][y].bot);
        }
        else
        {

            return (listPieces[i].left == bord[x - 1][y].left && listPieces[i].top == bord[x - 1][y].bot && listPieces[i].bot == listPieces[i].left);
        }
    }
    else if (x == col - 1)
    {

        if (y == 0)
        {
            return (listPieces[i].left == bord[x - 1][y].left && listPieces[i].top == bord[x - 1][y].bot && listPieces[i].bot == listPieces[i].left);
        }
        else if (y < col - 1)
        {

            return (listPieces[i].left == bord[x][y - 1].right && listPieces[i].top == bord[x - 1][y].bot && listPieces[i].bot == bord[x][y - 1].bot);
        }
        else
        {

            return (listPieces[i].left == bord[x][y - 1].right && listPieces[i].top == bord[x - 1][y].bot && listPieces[i].bot == bord[x][y - 1].bot && listPieces[i].right == listPieces[i].bot);
        }
    }
    else if (y == col - 1)
    {
        if (x == 0)
        {
            return (listPieces[i].left == bord[x][y - 1].right && listPieces[i].top == bord[x][y - 1].top && listPieces[i].right == listPieces[i].top);
        }
        else if (x < col - 1)
        {

            return (listPieces[i].left == bord[x][y - 1].right && listPieces[i].top == bord[x - 1][y].bot && listPieces[i].right == bord[x - 1][y].right);
        }
        else
        {

            return (listPieces[i].left == bord[x][y - 1].right && listPieces[i].top == bord[x - 1][y].bot && listPieces[i].right == bord[x - 1][y].right && listPieces[i].bot == listPieces[i].right);
        }
    }
    else
        return (listPieces[i].left == bord[x][y - 1].right && listPieces[i].top == bord[x - 1][y].bot);

    // }
    return false;
}

bool Bord::backtrackparelle(int x, int y)
{
    if (y == col)
    {
        cout << "thread  done " << x << endl;
        display(bord);

        return true;
    }
    else
    {
        for (int i = 0; i < col * row; i++)
        {
            if (usedliste[i] == false)
            {

                if (verifbor(x, y, i))
                {
                    bord[x][y] = listPieces[i];
                    usedliste[i] = true;

                    if (backtrackparelle(x, y + 1))
                    {
                        return true;
                    }

                    usedliste[i] = false;
                }
            }
        }
        cout << "thread fail" << x << endl;
        return false;
    }
}

void Bord::startparralle()
{
    for (int i = 0; i <= col; i++)
    {
        thread t([&]
                 { backtrackparelle(i, 0); });
        t.join();
    }
    // display(bord);
}
void Bord::creatBortool(char *filname)
{

    char left, top, bot, right;
    int row, col;

    ifstream file(filname);
    if (file)
    {
        file >> row >> col;
        this->row = row;
        this->col = col;
        for (int i = 0; i < col * row; i++)
        {

            file >> left >> top >> right >> bot;

            Piece P(left, top, right, bot);
            listPieces.push_back(P);
            usedliste.push_back(false);
        }
    }

    file.close();
    vector<vector<Piece>> bord;
    bord = vector<vector<Piece>>(row, vector<Piece>(col));
    ;

    for (int i = 0; i < col; i++)
    {

        for (int j = 0; j < col; j++)
        {
            bord[i][j] = Piece();
        }
    }

    this->bord = bord;
}

vector<Piece> Bord::getvector(vector<Piece> t)
{
    vector<Piece> k;
    k = t;
    // generateur de nombres aléatoires
    std::random_device rd;
    // Mersenne Twister Engine pour la randomisation
    std::mt19937 rng(rd());

    std::shuffle(t.begin(), t.end(), rng);
    return k;
}
void Bord::Backtrakparralllepool()
{   
    int r= col*row;
    vector<thread> threadvector(r);

    for (int i = 0; i < col * row; i++)
    {
        auto action = [this,i]()
        {
            vector<Piece> mylistepieces = getvector(listPieces);
            vector<vector<Piece>> bord;

            bord = vector<vector<Piece>>(row, vector<Piece>(col));

            Bord b(bord, col, row, mylistepieces, usedliste);

           b. sequentielle(0, 0, b);
        };

        threadvector[i]=thread(action);
    }

    for (int i = 0; i < col * row; i++)
    {
        threadvector[i].join();
    }
}

vector<vector<Piece>>Bord::putfirstPiece(Bord &b, int i)
{

    b.bord[0][0] = b.listPieces[i];
    b.usedliste[i] = true;
    return b.bord;
}
void Bord:: lunchtask(Bord &b ){
    nbthread++;
    b.sequentielle(0,1, b);
    nbthread--;

}
void Bord ::threadPool()
{

    int n = row * col;

    for (int i = 0; i < n; i++)

    {
            if(listPieces[i].top ==listPieces[i].left)
            {
            task.push_back(i);
            }
    }
     int M = task.size();
        T= M-2;
    vector<thread> threadvector;

    for (int i = 0; i < T; i++)

    {   int k =task.back();
        task.pop_back();
        auto action = [this,k]()
        {
            vector<Piece> mylistepieces = getvector(listPieces);
            vector<vector<Piece>> bord;

            bord = vector<vector<Piece>>(row, vector<Piece>(col));

            Bord b(bord, col, row, mylistepieces, usedliste);
            b.putfirstPiece(b, k);

           b.lunchtask(b);
        };

         threadvector.push_back(thread(action));
    }

    while(!trouve && !task.empty() && nbthread< T)

    {   
            int current_task =-1;
            current_task =task.back();
             task.pop_back();
        
        
             auto f = [this,current_task]()
        {
            vector<Piece> mylistepieces = getvector(listPieces);
            vector<vector<Piece>> bord;

            bord = vector<vector<Piece>>(row, vector<Piece>(col));

            Bord b(bord, col, row, mylistepieces, usedliste);
            b.putfirstPiece(b, current_task);

           b.lunchtask(b);
        };

        threadvector.push_back(thread(f));

        if(trouve || task.empty())
        {
           break;
        }
    }

    for (auto & t: threadvector)  t.join();
    
}



int main(int c, char *argv[])
{

    Bord mybord;
    mybord.creatBortool(argv[1]);
   // mybord.putfirstPiece(mybord, 0);
    
    // cout<< mybord.sequentielle(0, 0, mybord)<<endl;;
    // b.startparralle();
    //  mybord.Backtrakparralllepool();
    // mybord.display(mybord.bord);
   // mybord.threadPool();
  
    int input;
    cout << "choisir le type d'algorithme " << endl;
    cout << "** 1 pour sequentielle " << endl;
    cout << "*** 2 pour le parallesime simple" << endl;
    cout << "*** 3 pour le threadpool" << endl;
    cin >> input;


   auto start = std::chrono::high_resolution_clock::now();

if (input == 1)
{
    start = std::chrono::high_resolution_clock::now();
    mybord.sequentielle(0, 0, mybord);
}
else if (input == 2)
{
    start = std::chrono::high_resolution_clock::now();
    mybord.Backtrakparralllepool();
}
else 
{
        
    start = std::chrono::high_resolution_clock::now();
    mybord.threadPool();
}

auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

int milliseconds = duration.count();
int seconds = milliseconds / 1000;
milliseconds = milliseconds % 1000;

std::cout << "Temps d'exécution : " << seconds << " secondes et " << milliseconds << " millisecondes" << std::endl;

return 0;
}
