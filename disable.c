#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {
    struct termios term;

    // 獲取當前終端設置
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("tcgetattr");
        return 1;
    }

    // 恢復終端的標準模式設置
    term.c_lflag |= (ECHO | ICANON); // 開啟回顯和行緩衝模式
    term.c_iflag |= (IXON);          // 開啟軟流控 (Ctrl-S 和 Ctrl-Q)
    term.c_oflag |= (OPOST);         // 開啟輸出處理

    // 設定更新後的終端屬性
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1) {
        perror("tcsetattr");
        return 1;
    }

    printf("終端已恢復正常模式。\n");
    return 0;
}
