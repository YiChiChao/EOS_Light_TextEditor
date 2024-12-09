# EOS_Light_TextEditor

## Learning Notes
By default, terminal starts in canonical mode, also called cooked mode.In this mode, keyboard input is only sent to your program when the user presses Enter. Useful because it lets user type in a line of text, which is able to fix errors with Backspace, and finally press Enter to send it to the program.

Therefore, we should set the program to raw mode if we want to build a text editor. Raw mode is achieved by turning off a great many flags in the terminal.
'tcgetattr()' function from <termios.h> is used to get the current terminal attributes into a struct.

### Turn off Canonical Mode
ICANON can let us to turn off the canonical mode, which means that instead of reading the input line-by-line, we read the input byte-by-byte. So when we turn off the ECHO mode and the ICANON mode, the terminal should shut down as long as we press the 'q' without pressing enter.

(stty sane) to recover the default mode of terminal.