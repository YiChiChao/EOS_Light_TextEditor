
#ifndef SIMPLE_FUNC_H
#define SIMPLE_FUNC_H
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* defines*/
#define CTRL_KEY(k) ((k) & 0x1f)
struct termios origin_termios;

void errorHandler(const char*s){
    fprintf(stderr, "[ERROR] %s: %s (errno: %d)\n", s, strerror(errno), errno);
    exit(1);
}

void disableRawMode(){
    // TCSAFLUSH: Terminal Control Set Attri FLUSH
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &origin_termios);
} 

void enableRawMode(){

    if(tcgetattr(STDIN_FILENO, &origin_termios) == -1){
        errorHandler("tcgetattr function");
        return;
    }

    //disable the raw mode when exit the program
    atexit(disableRawMode);
    struct termios raw = origin_termios;
    printf("Before raw mode: Local flags (c_lflag): 0x%08X\n", raw.c_lflag);
    // turn off the echo and canonical mode 
    // disable ctrlc & ctrl z
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    // Every 1 sec timeout once
    raw.c_cc[VTIME] = 10;
    printf("After Raw Mode: Local flags (c_lflag): 0x%08X\n", raw.c_lflag);
    printf("=====================================================\n");
    //passing the modified struct to tcsetattr() to write the new terminal attributes back out
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


/* how input is process*/
char editorReadKey() {
  int nread;
  char c = '\0';
  // Wait until read 1 character
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) errorHandler("read");
  }

  return c;
}

void editor_ReadKEYPress(){
    char c = editorReadKey();

    if (iscntrl(c)) {
    printf("%d\r\n", c);
    } else {
        printf("%d ('%c')\r\n", c, c);
    }
    // CTRL_KEY : & 00011111
    if (c == CTRL_KEY('q')) exit(0);
}

#endif 