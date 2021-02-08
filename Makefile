##
## EPITECH PROJECT, 2018
## nmobjdump
## File description:
## Makefile
##

MY_MAKE		= $(MAKE)
TARGETS		= core \
		graphicals \
		games

all:	$(TARGETS)

core:
	$(MY_MAKE) -C ./core && cp ./core/arcade arcade

graphicals:
	$(MY_MAKE) -C ./lib/sfml
	$(MY_MAKE) -C ./lib/sdl2
	$(MY_MAKE) -C ./lib/libcaca

games:
	$(MY_MAKE) -C ./games/nibbler
	$(MY_MAKE) -C ./games/centipede

clean:
	$(MY_MAKE) -C core clean
	$(MY_MAKE) -C ./lib/sfml clean
	$(MY_MAKE) -C ./lib/sdl2 clean
	$(MY_MAKE) -C ./lib/libcaca clean
	$(MY_MAKE) -C ./games/nibbler clean
	$(MY_MAKE) -C ./games/centipede clean

fclean:
	$(MY_MAKE) -C core fclean
	$(MY_MAKE) -C ./lib/sfml fclean
	$(MY_MAKE) -C ./lib/sdl2 fclean
	$(MY_MAKE) -C ./lib/libcaca fclean
	$(MY_MAKE) -C ./games/nibbler fclean
	$(MY_MAKE) -C ./games/centipede fclean
	$(RM) arcade

re: fclean all

.PHONY: all core clean fclean re games graphicals
