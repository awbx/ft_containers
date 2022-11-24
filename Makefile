NAME=ft_containers

CC=c++

CFLAGS = -Wall -Werror -Wextra -g

HEADERS = utils/pair.hpp  utils/type_traits.hpp utils/iterator_traits.hpp
INCLUDES = -I utils

SRC_FILES = ft_container.cpp

OBJ_FILES = $(SRC_FILES:%.cpp=%.o)

all: $(NAME)


$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $< -o $@ -fsanitize=address

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -rf $(OBJ_FILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all


