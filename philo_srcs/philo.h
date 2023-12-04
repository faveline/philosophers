/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:07:31 by faveline          #+#    #+#             */
/*   Updated: 2023/12/04 17:17:44 by faveline         ###   ########.fr       */
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
	int				all_ok;
	int				inc;
	long			t0;
	pthread_t		early;
	int				early_end;
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
void	ft_result(t_philo *philo);
int		ft_check_i_eat(t_philo *philo);
//int		ft_check_early(t_philo *philo, int i);
long	ft_get_time(void);
void	ft_print_die(t_philo *philo, int i);
int		ft_creat_malloc(t_philo *philo);

#endif
