NAME_BONUS = philo_bonus

SRCS_BONUS = ft_creat_arg.c		\
			 ft_creat_philo.c	\
			 ft_util_philo.c	\
	  		 ft_libft.c			\
			 ft_get_time.c		\
	  		 ft_philo_state.c	\
	  		 main.c

OBJ_BONUS = $(SRCS_BONUS:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
AR = ar rcs

all : $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) $(CFLAGS) -o $(NAME_BONUS)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -I. -c $< -o ${<:.c=.o}

clean :
	$(RM) $(OBJ_BONUS)

fclean : clean
	$(RM) $(NAME_BONUS)

re : fclean all

.PHONY:	all clean fclean re
