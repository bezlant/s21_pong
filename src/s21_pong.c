#include "s21_pong.h"

int main() {
    initscr();  // curses start routine
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_CYAN);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    noecho();     // don't show getch() characters on the screen
    curs_set(0);  // remove cursor
    nodelay(stdscr, true);

    obj r2 = {MIN_X + 1, MAX_Y / 2, 0, false, false};
    obj r1 = {MAX_X - 2, MAX_Y / 2, 0, false, false};
    obj ball = {MAX_X / 2, MAX_Y / 2, 0, false, false};

    while (r1.score < 21 && r2.score < 21) {
        clock_t start_t = clock();
        refresh();

        while (clock() < start_t + 100000) {
        }
        // game logic
        if (ball.y == MAX_Y - 1 || ball.y == MIN_Y + 1)
            ball.movY = !ball.movY;
        if (ball.x >= MAX_X - 2 || ball.x <= MIN_X + 2) {
            ball.movX = !ball.movX;
            if (ball.y == r1.y - 1 || ball.y == r2.y - 1) {
                ball.movY = false;
            } else if (ball.y == r1.y + 1 || ball.y == r2.y + 1) {
                ball.movY = true;
            } else if (ball.y != r1.y && ball.y != r2.y) {
                if (ball.x >= MAX_X - 2) {
                    r1.score++;
                } else {
                    r2.score++;
                }
                ball.x = MAX_X / 2;
                ball.y = MAX_Y / 2;
            }
        }

        // ball movement

        if (ball.movX)
            ball.x++;
        else
            ball.x--;
        if (ball.movY)
            ball.y++;
        else
            ball.y--;

        // slide through upper/lower border
        if (r1.y <= MIN_Y + 1)
            r1.y = MAX_Y - 2;
        if (r1.y >= MAX_Y - 1)
            r1.y = MIN_Y + 2;
        if (r2.y <= MIN_Y + 1)
            r2.y = MAX_Y - 2;
        if (r2.y >= MAX_Y - 1)
            r2.y = MIN_Y + 2;

        // key-presses
        int input = getch();
        if (input == 'a')
            r2.y--;
        if (input == 'z')
            r2.y++;
        if (input == 'k')
            r1.y--;
        if (input == 'm')
            r1.y++;
        if (input == 27)
            break;
        clear();

        mvvline(MIN_Y, MAX_X / 2, ACS_VLINE, MAX_Y);
        mvhline(MIN_Y, MIN_X, ACS_HLINE, MAX_X);
        mvhline(MAX_Y, MIN_X, ACS_HLINE, MAX_X);

        attron(COLOR_PAIR(3));
        mvprintw(MIN_Y + 3, MAX_X / 2 - 2, "%d - %d", r1.score, r2.score);
        attroff(COLOR_PAIR(3));

        attron(COLOR_PAIR(2));
        mvprintw(ball.y, ball.x, "O");
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(1));
        for (int i = -1; i < 2; i++) {
            if (r1.y + i == MIN_Y || r1.y + i == MAX_Y) {
                mvprintw(r2.y + i, r2.x, "|");
                continue;
            }
            if (r2.y + i == MIN_Y || r2.y + i == MAX_Y) {
                mvprintw(r1.y + i, r1.x, "|");
                continue;
            }
            mvprintw(r2.y + i, r2.x, "|");
            mvprintw(r1.y + i, r1.x, "|");
        }
        attroff(COLOR_PAIR(1));
    }

    clear();
    refresh();

    if (r1.score == 21) {
        printf("Player on the right WON!");
        return 0;
    }
    if (r2.score == 21) {
        printf("Player on the left WON!");
        return 0;
    }

    endwin();
    return 0;
}
