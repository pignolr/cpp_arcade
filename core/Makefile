##
## EPITECH PROJECT, 2018
## nanotekspice
## File description:
## Makefile
##

detected_OS := $(shell sh -c 'uname -s 2>/dev/null || echo not')
ifeq ($(detected_OS), Darwin)
CXX		= g++-7
else
CXX		= g++
endif

CXXFLAGS	+= -W -Wall -Wextra -Werror -std=c++17 -march=native -O2

CPPFLAGS	+= -Iinc

LDFLAGS		+= -ldl

LDLIBS		+=

NAME		=	arcade

SRCS		=\
		src/DynamicLoader.cpp \
		src/Core.cpp \
		src/main.cpp

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM)  $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re
