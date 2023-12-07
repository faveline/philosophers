/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:07:31 by faveline          #+#    #+#             */
/*   Updated: 2023/12/07 16:30:51 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_person
{
	pthread_t	early;
	pid_t		child;
	long		eat_end;
	int			ok;
}				t_person;

typedef struct s_philo
{
	int				nbr_p;
	useconds_t		t_death;
	useconds_t		t_eat;
	useconds_t		t_sleep;
	int				nbr_eat;
	t_person		*pers;
	long			t0;
	sem_t			*sema_fork;
	sem_t			*sema_ok;
	sem_t			*sema_nbr;	
	sem_t			*dead;
	sem_t			*def_eat;
	sem_t			*check;
	sem_t			*print;
	int				inc;
}					t_philo;

char	*ft_itoa_philo(int nbr);
int		ft_atoi_philo(const char *str);
int		ft_creat_struct(int argc, char *argv[], t_philo *philo);
int		ft_creat_philos(t_philo *philo);
void	ft_error_philo(int error);
void	ft_exterminate(t_philo *philo);
int		ft_loop_philo(t_philo *philo);
int		ft_print_time(t_philo *philo, char *x, int i);
void	ft_get_t0(t_philo *philo);
int		ft_check_i_eat(t_philo *philo);
long	ft_get_time(void);
void	ft_print_die(t_philo *philo, int i);

#endif
