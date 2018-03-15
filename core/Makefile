NAME	= program

CC	= g++

RM	= rm -f

SRCS	= ./classes/DLLoader.cpp \
	  ./classes/LibAnalyzer.cpp \
	  ./main.cpp  \
	  ./src/shared_header/PixelBox.cpp \

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./pp
CPPFLAGS += -W -Wall -Wextra -g -std=c++11

LDFLAGS += -ldl -std=c++11

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
