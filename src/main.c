#include "main.h"

extern void init(char *);

extern void cleanup(void);

extern void getInput(void);

extern void draw(void);

extern void initPlayer(t_case_map **, int, int);

extern void doPlayer(t_case_map **, int, int);

extern void doEntities(void);

extern void loadAllSprites(void);

extern void doCollisions(void);

extern TTF_Font *loadFont(char *, int);

extern void delay(unsigned int);

extern void doRedefine(void);

extern t_case_map **loadMap();

extern void drawMap(t_case_map **);

int main(int argc, char *argv[])
{
    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go;

    /* Start up SDL */

    init("BeerBomber");

    /* Call the cleanup function when the program exits */

    atexit(cleanup);

    go = 1;

    /* Load all the sprites */

    loadAllSprites();

    /* Load the font */

    game.font = loadFont("font/blackWolf.ttf", 16);

    /* Load map */

    game.map = loadMap();

    /* Intialise the player */

    initPlayer(game.map, 1, 1);

    /* Reset the redefine index */

    redefine.redefineIndex = 0;
    redefine.redefineString[0] = '\0';

    /* Loop indefinitely for messages */

    while (go == 1) {
        if (game.status == IN_REDEFINE) {
            /* Handle the key redefining */

            doRedefine();
        } else {
            /* Get the input */

            getInput();

            /* Update the player's position */

            doPlayer(game.map, 1, 1);

            /* Update the entities */

            //doEntities();

            /* Do the collisions */

            //doCollisions();

            /* Draw everything */

            draw();
        }

        /* Sleep briefly to stop sucking up all the CPU time */

        delay(frameLimit);

        frameLimit = SDL_GetTicks() + 16;
    }

    /* Exit the program */

    return (0);
}
