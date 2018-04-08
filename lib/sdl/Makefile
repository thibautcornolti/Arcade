NAME	= lib_arcade_sdl.so

CC	= g++

CP = mv

RM	= rm -f

SRCS	= ./src/entry.cpp \
			./src/classes/SdlGraphicLib.cpp \

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./src/pp
CPPFLAGS += -W -Wall -Wextra --std=c++11 -g 
CPPFLAGS += -fPIC

LDFLAGS += -lSDL2 -lSDL2_ttf -shared --std=c++11

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
