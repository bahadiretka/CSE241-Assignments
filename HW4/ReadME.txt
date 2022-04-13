Program compiled and tested many times with g++ 4.8.4.(cse312 virtual machine)
I did not take any error when program is running or compiling.

about test.cpp:
    I wrote test.cpp for testing all instructions that required. First,
    program asks how many Hex object will be created. Then shows all options
    that my program can do. I wrote delete option in the menu because I wanted
    to show what my destructor does. For this also I wrote simple MultipleHexGame
    structure to hold a Hex and it's id (for delete I should handle which game will be deleted).
    The menu will not close when input is not -1.
save load file command:
    while playing game, you can save or load game.
    for load from file LOAD file.txt
    for save to file SAVE file.txt
quit command:
    while playing game, you can quit from into the game(write quit when object's
    function waiting for location for the cell).And you can continue playing where 
    you left off without deleting the object.
pre-undo and post-undo command:
    while playing game, you can use prefix and postfix decrement operator for Hex class.
    like typed as before SAVE LOAD, these new operator commands are pre-undo(calls --obj)
    and post-undo (calls obj--). It seems they are doing same work but they are both overloaded.
note about score public member function:
    I use this member function in playGame member function.
    in every step calculates scores for both users and prints
    which user is better. Also it can be use anywhere like other
    public member functions.
driver test block for new features:
    I wrote a driver test code block bottom of the test.cpp. It is helpful to show what is new
    different from hw3.