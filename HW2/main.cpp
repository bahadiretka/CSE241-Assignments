#include<iostream>
#include"header.h"
using namespace std;

int main(){

    int size;
    cout << "\t\t ^^^ Welcome to Hex Game ^^^\n";
    cout << "\nPlease enter size of Hex Game Table (SxS) (The range is 6 to 12) :";
    
    cin >> size;

    if(size <= 12 && size >=6){
        // allocate memory for 2D character array
        char **hex_table = new char*[12];
            for(int i=0; i< 12; ++i)
                hex_table[i] = new char[12];
                
        fill_hex_table(hex_table,size);
        
        cout << "\nAre you playing with computer or user?\nPlease select(User:1 Computer:2) -> ";
        int choice;
            
            cin >> choice;
    
            if(choice == 1 || choice == 2) 
                game(hex_table,size,choice);
            else
                cerr << "Your input is invalid!";
                exit(-1);
        
    }
       else{ 
        cerr << "Invalid size inputted!\n";
        exit(-1);
    }
    return 0;
}

