#include<iostream>
#include<random>
#include<string>
#include<fstream>
#include"header.h"

using namespace std;

void fill_hex_table(char **hex_table, int size){
    // first all elements of 2D array are empty
    for(int i = 0; i<size ; i++){
        for(int j = 0; j< size;j++){
            hex_table[i][j] = empty;
        }
    }
}
void print_hex_table(char **hex_table, int size){
  
    cout << "\n\t\t";
    
    for(char c='a'; c-'a'<size; c++) cout << ' ' << c ;
    
    cout << endl;
    
    for(int i=0; i< size; i++){
        cout << "\t\t";
    if(i < 9) 
        for(int k=0; k < i; k++) cout << ' ';      
    else 
        for(int k=0; k < i-1; k++) cout << ' ';
        
        cout << i+1 << ' ';
        for(int j=0; j<size ; j++){
           cout << hex_table[i][j] << ' ';
        }
        cout << endl;
    }
}
void game(char **hex_table,int size, int choice){

    if(choice == 1){ // user to user
        user_to_user(hex_table,size);

    }
    if(choice == 2){ // user to computer
        user_to_computer(hex_table,size);
    }   
}
void user_to_user(char **hex_table,int size){
 
        decltype(hex_table) temp_board = new char*[size]; for(int i = 0; i<size;i++) temp_board[i] = new char[size];
        auto playing_user = get_user();
         
        int win_flag = false,move_counter_x = 0, move_counter_o = 0;
        // if there is no winner or not filled board then loop going to continue
        cin.clear();
        cin.ignore();
        while(true){
            
            if(playing_user == 1){
                print_hex_table(hex_table,size);
                cout << "User1(x) Plays\n";
                get_input(hex_table,size,playing_user);
                playing_user=2;
                move_counter_x++;
            }
            // check x won or not
            if(move_counter_x >= size){
                // copy hex board to temp board for sending to function
                copy_array(hex_table,temp_board,size);

                for(int i=0 ;i<size ;i++) win_flag = win_flag || check_winner(temp_board,0+i,0,size,x);
            }
            // if x won break the loop and finish the game which user won
            if(win_flag == true){
                cout << "\n\t\tUSER_1(x) WON\n";
                print_hex_table(temp_board,size);
                break;
            }
            if(playing_user == 2){
               print_hex_table(hex_table,size);
               cout << "User2(o) Plays\n";
               get_input(hex_table,size,playing_user);
               playing_user=1;
               move_counter_o++;
            // check o won or not
            }
            if(move_counter_o >= size){
                copy_array(hex_table,temp_board,size);
                for(int i=0 ;i<size ;i++) win_flag = win_flag || check_winner(temp_board,0,0+i,size,o);
            }
            if(win_flag == true){
                cout << "\n\t\tUSER_2(o) WON\n";
                print_hex_table(temp_board,size);
                break;
            }
            if(move_counter_x + move_counter_o == size * size){
                cout << "Hex Board is filled!!\n";
                break;
            }
            
        }
}
void user_to_computer(char **hex_table,int size){
        char **temp_board = new char*[size];
        for(int i = 0; i<size;i++) temp_board[i] = new char[size];
        location loc;
        cout << "\n\t\t User will be x and try to go horizontal\n";
        
        int win_flag = 0,move_counter_x = 0, move_counter_o = 0;
        int playing_user = 1; // x will be start and this is user
        // if there is no winner or not filled board then loop going to continue
        cin.clear();
        cin.ignore();
        while(true){
                        
            if(playing_user == 1){
                print_hex_table(hex_table,size);
                cout << "User Plays\n";
                loc = get_input(hex_table,size,playing_user);
                playing_user=2;
                move_counter_x++;
              
            }
            // check x won or not
            if(move_counter_x >= size){
                // copy hex board to temp board for sending to function
                copy_array(hex_table,temp_board,size);
                for(int i=0 ;i<size ;i++) win_flag = win_flag || check_winner(temp_board,0+i,0,size,x);
            }
            // if x won break the loop and finish the game which user won
            if(win_flag == true){
                cout << "\n\t\tUSER WON\n";
                print_hex_table(temp_board,size);
                break;
            }
            if(playing_user == 2){
                smart_move(hex_table,(loc.row)-1,(loc.column) -'a',size);// this is computer 
                playing_user=1;
                move_counter_o++;
            }
            // check o won or not
            if(move_counter_o >= size){
                copy_array(hex_table,temp_board,size);
                for(int i=0 ;i<size ;i++) win_flag = win_flag || check_winner(temp_board,0,0+i,size,o);
            }
            if(win_flag == true){
                cout << "\n\t\tCOMPUTER WON\n";
                print_hex_table(temp_board,size);
                break;
            }
            if(move_counter_x + move_counter_o == size * size){
                cout << "Hex Board is filled!!\n";
                break;
            }
        }
}
int move(char **hex_table,int size,int row,char column, int user){
    
    int l_flag = false;
        // check if the inputted location is empty then return true else return false
        if(row >=1 && row <= size && column >= 'a' && column < size + 'a' ){
            if(hex_table[row-1][column-'a'] == empty && hex_table[row-1][column-'a'] != x && hex_table[row-1][column-'a'] != o){
                l_flag=true;
                if (user == 1){ 
                    hex_table[row-1][column-'a'] = x;
                }
                if(user ==2){
                    hex_table[row-1][column-'a'] = o;
                }
            }
            else{
                cout << "\nInputted location is not empty!\n";
                l_flag=false;
            }
        }
        else{
            cout << "\nThere is no inputted location!\n";
            l_flag = false;
        }
    
    return l_flag;
}

int check_winner(char **temp_board,int row,int column, int size,const char user){
    
    if(row >= 0 && row < size && column >= 0 && column < size){ // check it is in grid or not
        
        if(temp_board[row][column] == user){
            if(user == x) temp_board[row][column] = gone_x;
            if(user == o) temp_board[row][column] = gone_o;
            if(user == x && column == size -1) 
                return true;
            if(user == o && row == size -1)
                return true;
            else 
                return check_winner(temp_board,row-1,column+1,size,user) || check_winner(temp_board,row,column+1,size,user) || check_winner(temp_board,row+1,column,size,user) || check_winner(temp_board,row-1,column,size,user)||check_winner(temp_board,row+1,column-1,size,user)|| check_winner(temp_board,row,column-1,size,user);
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
void smart_move(char **hex_table,int row,int column,int size){

    default_random_engine generator;
    uniform_int_distribution<int> distribution(0,size-1);
    int flag = false, temp_r , temp_c;

    if(column + 1 < size && hex_table[row][column+1] == empty && hex_table[row][column+1] != x){
     
            hex_table[row][column+1] = o;
            cout << "\nComputer just moved (" << row+1 << ',' << static_cast<char>(column + 'a' + 1) << ')' << endl;
        
    }
    else if(column -1 >= 0 && hex_table[row][column-1] == empty && hex_table[row][column-1] != x){
            hex_table[row][column-1] = o; 
            cout << "\nComputer just moved (" << row+1 << ',' << static_cast<char>(column + 'a' + -1) << ')' << endl;
    }
    else if(row-1 >= 0 && column + 1 <size && hex_table[row-1][column+1] == empty && hex_table[row-1][column+1] != x){
             hex_table[row-1][column+1] = o;
            cout << "\nComputer just moved (" << row << ',' << static_cast<char>(column + 'a' + 1) << ')' << endl;
    }

    else if(row+1 < size && hex_table[row+1][column] == empty && hex_table[row+1][column] != x){
            hex_table[row+1][column] = o;
            cout << "\nComputer just moved (" << row+2 << ',' << static_cast<char>(column + 'a')<< ')' << endl;
    }

    else if(row-1 >= 0 && hex_table[row-1][column] == empty && hex_table[row-1][column] != x){
            hex_table[row-1][column] = o;
            cout << "\nComputer just moved (" << row << ',' << static_cast<char>(column + 'a')<< ')' << endl;
    }

    else if(row+1 < size && column - 1 >= 0 && hex_table[row+1][column-1] == empty && hex_table[row+1][column-1] != x){
            hex_table[row+1][column-1] = o;
            cout << "\nComputer just moved (" << row+2 << ',' << static_cast<char>(column + 'a' -1) << ')' << endl;
    }
    else{
        while(!flag){
            temp_r = distribution(generator);
            temp_c = distribution(generator);
            if(hex_table[temp_r][temp_c] == empty && hex_table[temp_r][temp_c] != x){
                hex_table[temp_r][temp_c] = o;
                flag = true;
            }
        }
        cout << "\nComputer just moved (" << temp_r << ',' << temp_c << ')' << endl;
    }
}
void copy_array(char **source, char **target, int size){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            target[i][j] = source[i][j];
        }
    }
}
void clean_string(char *str, int size){
    for(int i=0; i<size; i++) str[i] = '\0';
}
location check_location(const char * input){

    location loc;
    int len = len_str(input);
    
    if(len == 3){
        loc.row = (input[0] - '0') * 10 + (input[1] - '0');
        loc.column = input[2];
    }
    else if(len == 2){
        loc.row = (input[0] - '0');
        loc.column = input[1];
    }
    else{
        // assign row and column with invalid location
        loc.row = -1;
        loc.column = 'q';
    }
    return loc;
}
int len_str(const char *input){
    int len = 0;
    for(;input[len] != '\0'; len++);
    
    return len;
}
location get_input(char **hex_table, int& size, int playing_user){
    location loc;
    bool input_flag = false;
    char input[20];
    decltype(input_flag) is_condition = false;
    do{
        cout << "Enter row and column ->";

        cin.getline(input,20);

        if(len_str(input) <= 3){
            loc = check_location(input);
            input_flag=move(hex_table,size,loc.row,loc.column,playing_user);
            is_condition = true;
        }
        else{
            check_condition(hex_table,size,input);
        }
        if(input_flag == false && is_condition == true) cout << "Please enter valid location!\n";
    }while(!input_flag);
    if(is_condition){
        if(playing_user==1) cout << "\nUser1(x) just moved (" << loc.row << ',' << loc.column << ')' <<endl;
        if(playing_user==2) cout << "\nUser2(o) just moved (" << loc.row << ',' << loc.column << ')' <<endl;
    }
    return loc;
}
int get_user(){ 
    int playing_user;   
    
    do{
        cout << "\n\t\tWho will start to game?\n User1(x)(Horizontal) : 1\n User2(o)(Vertical) : 2\n ->";
        cin >> playing_user;
  
        if((playing_user == 1 || playing_user == 2) == false) 
            cout << "Please select user1 or user2!\n";
      
    }while(!(playing_user == 1 || playing_user == 2));   

    return playing_user;
}
void check_condition(char **hex_table, int& size,const char *input){
    string inp = input;
    fstream file;
    size_t found = inp.find("LOAD");
    if(found != string::npos){
    string str;
    str = inp.substr(5,inp.length());
    file.open(str.c_str(),ios::in);
        if(file.is_open()){
            file >> size;
                for(int i=0; i< size ; i++){
                    for(int j=0; j<size; j++){
                            file >> hex_table[i][j];
                        }
                    }
            cout << "\nGame Loaded from " << str << endl;
        }
        else{
            cerr << "File could not opened." << endl;
        }
        file.close();
        
        print_hex_table(hex_table,size);
    }
    found = inp.find("SAVE");
        if(found != string::npos){
            string str;
            str = inp.substr(5,inp.length());
            file.open(str.c_str(),ios::out);
            if(file.is_open()){
                file << size ;
                    for(int i=0; i< size ; i++){
                        for(int j=0; j<size; j++){
                            file << hex_table[i][j];
                        }
                    }
                cout << "\nGame Saved to "<< str << endl;
            }
            else{
                cout << "File could not opened." << endl;
            }
            file.close();
        }
}


