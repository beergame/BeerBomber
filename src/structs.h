#include "defs.h"

typedef struct      Entity
{
    int             type;
    int             speed;
    int             x;
    int             y;
    int             thinkTime;
    SDL_Surface     *sprite;

    void            (*action)(void);

    void            (*draw)(SDL_Surface *, int, int);
}                   Entity;

typedef struct      MapCase
{
    unsigned int    mapType;
    int             inFire;
    int             hasBomb;
    SDL_Surface     *sprite;
    Entity          *entity;
}                   MapCase;

typedef struct      Game
{
    int             score;
    int             status;
    MapCase         **map;
    SDL_Surface     *screen;
    TTF_Font        *font;
    SDL_Joystick    *joystick;
}                   Game;

typedef struct      Sprite
{
    SDL_Surface     *image;
}                   Sprite;

typedef struct      Sound
{
    Mix_Chunk       *effect;
}                   Sound;

typedef struct      Control
{
    int             up;
    int             down;
    int             left;
    int             right;
    int             fire;
}                   Control;

typedef struct      Redefine
{
    int             redefineIndex;
    char            redefineString[255];
}                   Redefine;
