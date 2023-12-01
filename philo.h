/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:07:31 by faveline          #+#    #+#             */
/*   Updated: 2023/12/01 12:32:22 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_philo
{
	int				nbr_p;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				nbr_eat;
	t_person		*pers;
	pthread_mutex_t	*fork;
	int				all_ok;
}					t_philo;

typedef struct s_person
{
	pthread_t	thread;
	int			alive;
	int			eating;
	int			sleeping;
	int			thinking;
	int			i_eat;
	int			inc;
}				t_person;

char		*ft_itoa_philo(int nbr);
int			ft_atoi_philo(const char *str);
int			ft_creat_struct(int argc, char *argv[], t_philo *philo);
int			ft_creat_philos(t_philo *philo);
void		ft_error_philo(int error);
void		ft_exterminate(t_philo *philo);

#endif
