CC= gcc
CFLAGS=-Wall -Wextra -Werror
SRCS= write_to_pipe.c write_to_file.c get_pathname_execve.c \
	helper_functions.c

OBJS= $(patsubst %.c, %.o, $(SRCS))
NAME= pipex
LIB= libpipex.a
LIBFT= libft
MAINF= pipex.c

$(NAME): $(LIB)
	$(CC) -o $(NAME) pipex.o -L. -lpipex -L $(LIBFT)/ -lft -I includes \
	-I $(LIBFT)/includes
$(LIB): $(OBJS) main
	ar rcs $(LIB) $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I includes -I libft/includes
main:
	$(CC) $(CFLAGS) -c pipex.c -o pipex.o -I includes -I libft/includes
	make -C $(LIBFT)

all: $(NAME);
clean:
	rm -rf $(OBJS) pipex.o
fclean: clean
	make -C libft fclean
	rm -rf $(LIB) $(LIBFT)/libft.a $(NAME)
re: fclean all
.PHONY: all clean re fclean main
