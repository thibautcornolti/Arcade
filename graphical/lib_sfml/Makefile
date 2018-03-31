NAME	= lib_sfml.so

CC	= g++

CP = cp

RM	= rm -f

SRCS	= ./src/entry.cpp \
			./src/classes/SfmlGraphicLib.cpp \
			../../shared_header/PixelBox.cpp \
			../../shared_header/TextBox.cpp \
			../../shared_header/Color.cpp \

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./src/pp
CPPFLAGS += -W -Wall -Wextra --std=c++11 -g 
CPPFLAGS += -fPIC

LDFLAGS += -lsfml-graphics -lsfml-window -shared --std=c++11

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
