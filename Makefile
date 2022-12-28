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
	stack/stack.hpp\
	tests/tests.hpp\
	red_black_tree/red_black_tree.hpp\
	red_black_tree/rbt_iterator.hpp\
	map/map.hpp\
	set/set.hpp

TEST_FILES = tests/tests.cpp\
	stack/stack_tests.cpp\
	vector/vector_tests.cpp\
	map/map_tests.cpp

TEST_OBJS = $(TEST_FILES:%.cpp=%.o)


INCLUDES = -I utils -I vector -I stack -I tests -I red_black_tree -I map -I set

SRC_FILES = ft_container.cpp

OBJ_FILES = $(SRC_FILES:%.cpp=%.o)

all: $(NAME)


$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $< -o $@

test: $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -o $@

run:
	./$(NAME)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -rf $(OBJ_FILES) $(TEST_OBJS)

fclean: clean
	rm -rf $(NAME)
	rm -rf test

re: fclean all


