NAME	= lib_arcade_pacman.so

CC	= g++

CP = mv

RM	= rm -f

SRCS	= ./src/entry.cpp \
		./src/classes/Pacman.cpp \
		./src/classes/Ghost.cpp \
		./src/shared_header/Scoreboard.cpp \
		./src/shared_header/Scale.cpp \

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./src/pp
CPPFLAGS += -W -Wall -Wextra -lpthread --std=c++11 -g -O2
CPPFLAGS += -fPIC

LDFLAGS += -lncurses -shared --std=c++11

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	 $(CP) $(NAME) ../

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
