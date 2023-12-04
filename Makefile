NAME = philo

SRCS = ft_creat_arg.c		\
	   ft_creat_philo.c		\
	   ft_util_philo.c		\
	   ft_libft.c			\
	   ft_get_time.c		\
	   ft_philo_state.c		\
	   main.c

SRCS_DIR = philo_srcs/

SRCS_OK = $(addprefix $(SRCS_DIR), $(SRCS))

OBJ = $(SRCS_OK:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
RM = rm -f
AR = ar rcs

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
