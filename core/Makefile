NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= ./classes/DLLoader.cpp \
	  ./classes/LibAnalyzer.cpp \
	  ./classes/Core.cpp \
	  ./classes/Menu.cpp \
	  ./main.cpp  \
	  ../shared_header/Scoreboard.cpp \
	  ../shared_header/Scale.cpp \
	  ../shared_header/PixelBox.cpp \
	  ../shared_header/TextBox.cpp \
	  ../shared_header/Color.cpp \

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./pp
CPPFLAGS += -W -Wall -Wextra -g -std=c++11

LDFLAGS += -ldl -std=c++11 -rdynamic

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
