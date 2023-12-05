NAME = philo

NAME_BONUS = philo_bonus

SRCS = ft_creat_arg.c		\
	   ft_creat_philo.c		\
	   ft_util_philo.c		\
	   ft_libft.c			\
	   ft_get_time.c		\
	   ft_philo_state.c		\
	   main.c

SRCS_BONUS = ft_creat_arg.c		\
			 ft_creat_philo.c	\
			 ft_util_philo.c	\
	  		 ft_libft.c			\
			 ft_get_time.c		\
	  		 ft_philo_state.c	\
	  		 main.c

SRCS_DIR = philo_srcs/

BONUS_DIR = philo_bonus_srcs/

SRCS_OK = $(addprefix $(SRCS_DIR), $(SRCS))

BONUS_OK = $(addprefix $(BONUS_DIR), $(SRCS_BONUS))

OBJ = $(SRCS_OK:.c=.o)

OBJ_BONUS = $(BONUS_OK:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
RM = rm -f
AR = ar rcs

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

bonus : $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) $(CFLAGS) -o $(NAME_BONUS)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -I. -c $< -o ${<:.c=.o}

clean :
	$(RM) $(OBJ)
	$(RM) $(OBJ_BONUS)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re : fclean all

.PHONY:	all clean fclean re bonus
