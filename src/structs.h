#include "defs.h"

typedef struct Entity
{
    int active;
    int type;
    int x, y, thinkTime;
    SDL_Surface *sprite;

    void (*action)(void);

    void (*draw)(SDL_Surface *, int, int);
} Entity;

typedef struct MapCase
{
    unsigned int mapType;
    int inFire;
    int hasBomb;
    SDL_Surface *sprite;
    Entity *entity;
} MapCase;

typedef struct Game
{
    int score, status;
    MapCase **map;
    SDL_Surface *screen;
    TTF_Font *font;
    SDL_Joystick *joystick;
} Game;

typedef struct Sprite
{
    SDL_Surface *image;
} Sprite;

typedef struct Sound
{
    Mix_Chunk *effect;
} Sound;

typedef struct Control
{
    int up, down, left, right, fire;
} Control;

typedef struct Redefine
{
    int redefineIndex;
    char redefineString[255];
} Redefine;
