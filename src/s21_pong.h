#include <curses.h>
#include <time.h>

#define MAX_X 80
#define MIN_X 0
#define MAX_Y 25
#define MIN_Y 0

typedef struct {
    int x;
    int y;
    int score;
    bool movY;
    bool movX;
} obj;
