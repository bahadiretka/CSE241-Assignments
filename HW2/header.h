#ifndef header
#define header
struct location{
    int row;
    char column;
};
enum cell{
    x = 'x',
    o = 'o',
    empty = '-',
    gone_x = 'X',
    gone_o = 'O',
};
void fill_hex_table(char **hex_table,int size); // fills hex board with empty
void print_hex_table(char **hex_table, int size); // shows hex table
void game(char **hex_table,int size, int choice); // starts the hex game with computer or user
int check_winner(char **temp_board,int row,int column, int size,const char user); // checs the required user won or not
void user_to_user(char **hex_table,int size); // starts the game with user
void user_to_computer(char **hex_table,int size); // starts the game with computer
int move(char **hex_table,int size,int row,char column, int user); // puts the user command if it is possible
void smart_move(char **hex_table,int row,int column,int size); // does computer commands
void copy_array(char **source, char **target, int size); // copies array
void clean_string(char *str, int size=20); // cleans character array
location check_location(const char *input); // get the commands from input if it is valid
int len_str(const char *input); // returns character array length
int get_user(); // gets which user will start from the user
location get_input(char **hex_table, int& size, int playing_user); // gets input from the user
void check_condition(char **hex_table, int& size,const char *input); // do save or load operation if input is valid
#endif
