##
## Makefile for BeerBomber in /Users/victorbalssa/BeerBomber
## 
## Made by BALSSA Victor
## Login   <balssa_v@etna-alternance.net>
## 
## Started on  Sun Apr  2 21:36:05 2017 BALSSA Victor
## Last update Sun Apr  2 21:54:18 2017 BALSSA Victor
##

NAME =		beerbomber
CC =		gcc
SRCS =		$(wildcard src/*.c)
OBJS =		$(SRCS:%.c=%.o)
CFLAGS =	-Wall -pedantic -Werror

# OS Flags.
OS = $(shell uname)
ifeq ($(OS), Darwin)
    FLAGS = -I/usr/local/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
else
    FLAGS = `sdl-config --libs` -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
endif

all:		$(NAME)

$(NAME):	$(OBJS)
		@echo "> Build BeerBomber"
		@$(CC) $(OBJS) $(CFLAGS) $(FLAGS) -o $(NAME)
		@echo "> Done."

clean:
	rm -f $(OBJS)

fclean:
	rm $(NAME)

re:	fclean clean all clean

.PHONY: fclean clean
