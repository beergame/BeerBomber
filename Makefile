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
CC =		gcc -std=c99
SRCS =		$(wildcard src/*.c)
OBJS =		$(SRCS:%.c=%.o)
CFLAGS =	-Wall -pedantic -Werror
# SDL 2.0 Flags.
SDLFLAGS = `sdl2-config --libs` `sdl2-config --cflags` \
			-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all:		$(NAME)

$(NAME):	$(OBJS)
		@echo "> Build BeerBomber"
		@$(CC) $(OBJS) $(CFLAGS) $(SDLFLAGS) -o $(NAME)
		@echo "> Done."

clean:
	rm -f $(OBJS)

fclean: clean
	rm $(NAME)

re:	fclean all

.PHONY: fclean all clean
