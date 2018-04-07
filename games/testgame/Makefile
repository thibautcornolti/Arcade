NAME	= lib_arcade_testgame.so

CC	= g++

CP = cp

RM	= rm -f

SRCS	= ./src/entry.cpp \
			./src/classes/TestGameLib.cpp \

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./src/pp
CPPFLAGS += -W -Wall -Wextra --std=c++11 -g 
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
