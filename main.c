#include <unistd.h>
#include <termios.h>

#include <errno.h>
#include "simple_func.h"



int main(){
    enableRawMode();
    //Read keypress
    // Read 1 byte from the standard input into the variable c
    while(1){
        editor_ReadKEYPress();
    }
    /*
    while(read(STDIN_FILENO, &c, 1) == 1 && c!= 'q'){
        //check if c is control character
        // ctrl c = 3
        // backspace = 127...
        if(iscntrl(c)){
            printf("%d\n", c);
        }else{
            printf("%d ('%c')\n", c, c);
        }
    };*/
    return 0;
}