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
# Flags for Mac.
OS = $(shell uname)
ifeq ($(OS), Darwin)
    FLAGS = -I/usr/local/include/SDL -L/usr/local/lib -lSDLmain -lSDL \
	-Wl,-framework,Cocoa -lSDL_image -lSDL_mixer -lSDL_ttf
else
    FLAGS = `sdl-config --libs` -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
endif

all:		$(NAME)

$(NAME):	$(OBJS)
		@echo "-> Build BeerBomber"
		$(CC) $(OBJS) $(CFLAGS) $(FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:
	rm $(NAME)

re:	all clean

.PHONY: fclean clean all clean