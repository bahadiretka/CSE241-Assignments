Program compiled and tested many times with g++ 4.8.4.(cse312 virtual machine)
I did not take any error when program is running or compiling.

note about adapter.h:
    I tried to compile them separately, but when I searched, I saw that
    I could not handle this problem when the template was not in the same header file.
note about main.cpp:
    I created a text file which includes invalid sequence named invalid_sequence.txt
    with globalController function that controls sequence of game.
note about globalController function:
    I wrote a global function in main.cpp that takes pointer array of AbstractHex class 
    and controls the game includes valid sequence or not.