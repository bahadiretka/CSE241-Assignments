#ifndef header
#define header
void fill_hex_table(char **hex_table,int size);
void print_hex_table(char **hex_table, int size);
void game(char **hex_table,int size, int choice);
int check_winner_x(char **hex_table,int row,int column, int size);
int check_winner_o(char **hex_table,int row,int column, int size);
void user_to_user(char **hex_table,int size);
void user_to_computer(char **hex_table,int size);
int move(char **hex_table,int size,int row,char column, int user);
void smart_move(char **hex_table,int row,int column,int size);
void copy_array(char **source, char **target, int size);
#endif
