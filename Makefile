NAME =			npuzzle

CC =			g++ $(FLAGS) $(INCLUDES)

INCLUDES =		-I./includes

SRC =			src/main.cpp \
				src/Node.cpp \
				src/isSolvable.cpp \
				src/Map.cpp

OBJ =			$(SRC:%.cpp=%.o)

FLAGS =			-Wall -Wextra -Werror -g -O3

all:			$(NAME)

$(NAME):		$(OBJ) 
				$(CC) $(OBJ) -o $(NAME)

clean:
				rm -f $(OBJ)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

%.o:			%.cpp
				$(CC) -c $< -o $@