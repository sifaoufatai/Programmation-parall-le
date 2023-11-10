#include<iostream>
#include<vector>
#include<atomic>
#include <thread>
using namespace std;
atomic_int k;
void f(){
    k+;cout << k <<endl;
}
int main(){

/*vector <int > t ;
for (int i =0; i< 10 ; i++){
    t.push_back(i);
}
while (1){
        int k =-1;
    if(!t.empty()){
         k= t.back();
        t.pop_back();
    }
    if(k!=-1 ){
        cout<<k << endl; 
    }
    if(t.empty()) break;
}
int n = t.size()-1;
 for (int i =0; i<n; i++){
    int a = t[i];
    t[i]=t[n-i];
    t[n-i]=a;
for (int k =0; k<= n ; k++){cout<< t[k]<<"";}
    cout<< endl; 
 }
*/  vector <thread>threadvector;
    for(int i=0; i<100 ; i++){
        threadvector[i]=thread(f);
    }
    for (int i = 0; i< 100; i++) threadvector[i].join();
return 0;
}