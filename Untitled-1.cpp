
void Bord ::threadPool(){
    int n = row*col;
    for(int i =0; i<n; i++){
        task.push_back(i);
    }
    for(int k = 0 ; k <nbthread; k++){
        Bord b; 
        b.bord= bord ; 
        b.listPieces=listPieces;
        b.usedliste= usedliste ;
       int  current_task=-1;
        if(!task.empty() &&! trouve ){

        current_task =task.back();
        task.pop_back();

        b.bord = putfirstPiece(b , current_task);
        b.usedliste[current_task]=true;
        nbthread++;
        thread t([&,b](){
            sequentielle(0, 1, b);
        });
        t.detach();
    }
    }
    while(1){
        int next_task =-1;
        if(!task.empty() && nbthread<T && ! trouve){
            next_task=task.back();
            task.pop_back();

        }
        if(next_task !=-1){
         Bord b; 
        b.bord= bord ; 
        b.listPieces=listPieces;
        b.usedliste= usedliste ;



        b.bord = putfirstPiece(b , next_task);
        b.usedliste[next_task]=true;
        nbthread++;
        thread t([&,b](){
            sequentielle(0, 1, b);
        });
        t.detach();

        }

    else if(task.empty()|| next_task==-1 || trouve) break;



    }

    
}