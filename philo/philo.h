/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:07:31 by faveline          #+#    #+#             */
/*   Updated: 2023/12/11 17:13:35 by faveline         ###   ########.fr       */
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

typedef struct s_person
{
	pthread_t	thread;
	long		eat_end;
	int			i_eat;
}				t_person;

typedef struct s_philo
{
	int				nbr_p;
	useconds_t		t_death;
	useconds_t		t_eat;
	useconds_t		t_sleep;
	int				nbr_eat;
	t_person		*pers;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*def_eat;
	int				all_ok;
	int				inc;
	long			t0;
	pthread_mutex_t	wait;
	pthread_mutex_t	wait_i;
	long			*eat_t;
	int				*eat_i;
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
long	ft_get_time(void);
int		ft_print_die(t_philo *philo, int i);
int		ft_creat_malloc(t_philo *philo);
int		ft_ini_mutex(t_philo *philo);
int		ft_mutex_loop1(t_philo *philo, int i);
void	ft_mutex_loop2(t_philo *philo);
int		ft_mutex_philo1(t_philo *philo);
int		ft_mutex_philo2(t_philo *philo, int i);
int		ft_mutex_philo3(t_philo *philo, int i);
int		ft_unlock_fork(t_philo *philo, int i);
int		ft_mutex_loop_philo(t_philo *philo);
void	ft_ini_var(t_philo *philo);

#endif
