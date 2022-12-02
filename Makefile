NAME=ft_containers

CC=c++

CFLAGS = -Wall -Werror -Wextra -std=c++98 -fsanitize=address -g

HEADERS = utils/equal.hpp\
	utils/iterator_traits.hpp\
	utils/iterator.hpp\
	utils/lexicographical_compare.hpp\
	utils/pair.hpp\
	utils/reverse_iterator.hpp\
	utils/type_traits.hpp\
	utils/vector_iterator.hpp\
	vector/vector.hpp\
	stack/stack.hpp


INCLUDES = -I utils -I vector -I stack

SRC_FILES = ft_container.cpp

OBJ_FILES = $(SRC_FILES:%.cpp=%.o)

all: $(NAME)


$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $< -o $@

run:
	./$(NAME)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -rf $(OBJ_FILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all


