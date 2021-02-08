#
# EPITECH PROJECT, 2018
# libSFML
# File description:
# Makefile
#

detected_OS := $(shell sh -c 'uname -s 2>/dev/null || echo not')
ifeq ($(detected_OS), Darwin)
CXX		= g++-7
else
CXX		= g++
endif

CXXFLAGS	+= -W -Wall -Wextra -Werror -std=c++17 \
			-march=native -O2 -fPIC \
			$(shell pkg-config --cflags --libs sfml-all)

CPPFLAGS	+= -I../../inc  -Iinc

LDFLAGS		+= -ldl $(shell pkg-config --libs sfml-all) -shared

NAME		= ../lib_arcade_sfml.so

SRCS		= src/LibSFML.cpp

OBJS		= $(SRCS:.cpp=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)


re: fclean all

.PHONY: clean fclean re
