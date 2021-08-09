.PHONY:	all clean fclean re

NAME_CONTAINERS = ft_containers
NAME_STL_CONTAINERS = stl_containers

CPP_CONTAINERS = main.cpp
CPP_STL_CONTAINERS = main_stl.cpp

HPP_CONTAINERS = containers/*.hpp iterators/*.hpp other/*.hpp

OBJ_CONTAINERS = main.o
OBJ_STL_CONTAINERS = main_stl.o

FLAGS = -Wall -Wextra -Werror

all:	$(NAME_CONTAINERS) $(NAME_STL_CONTAINERS)

$(NAME_CONTAINERS):	$(CPP_CONTAINERS) $(HPP_CONTAINERS)
	clang++ $(FLAGS) -c $(CPP_CONTAINERS)
	clang++ $(FLAGS) $(OBJ_CONTAINERS) -o $(NAME_CONTAINERS)

$(NAME_STL_CONTAINERS):	$(CPP_STL_CONTAINERS)
	clang++ $(FLAGS) -c $(CPP_STL_CONTAINERS)
	clang++ $(FLAGS) $(OBJ_STL_CONTAINERS) -o $(NAME_STL_CONTAINERS)

clean:
	rm -f $(OBJ_CONTAINERS) $(OBJ_STL_CONTAINERS)

fclean:	clean
	rm -f $(NAME_CONTAINERS) $(NAME_STL_CONTAINERS)

re:	fclean all
