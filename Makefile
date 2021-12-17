SHELL = /bin/bash
CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror
SRC = src/main.cpp
NAME = connect_four
all: $(NAME)

$(NAME):
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRC) 

clean:
	/bin/rm -f $(NAME)

fclean: clean

re : fclean all

.PHONY: all clean fclean re test
