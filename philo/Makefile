NAME = philo

SRCS = ft_creat_arg.c		\
	   ft_creat_philo.c		\
	   ft_util_philo.c		\
	   ft_libft.c			\
	   ft_get_time.c		\
	   ft_philo_state.c		\
	   ft_mutex_1.c			\
	   main.c

OBJ = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread
RM = rm -f

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -I. -c $< -o ${<:.c=.o}

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY:	all clean fclean re
