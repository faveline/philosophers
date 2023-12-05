/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:03:05 by faveline          #+#    #+#             */
/*   Updated: 2023/12/05 13:46:32 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_check_early(void *ptr)
{
	t_philo	*philo;
	long	time;
	int		i;

	philo = (t_philo *)ptr;
	i = philo->inc;
	while (philo->pers[i].ok == 1)
	{
		time = ft_get_time();
		if (time - philo->pers[i].eat_end > philo->t_death)
			ft_print_die(philo, i);
	}
	return (NULL);
}

static int	ft_child(t_philo *philo, int i)
{
	int	j;

	j = -1;
	if (pthread_create(&philo->pers[i].early, NULL, ft_check_early, philo) != 0)
		return (-6);
	philo->pers[i].eat_end = ft_get_time();
	while (philo->pers[i].ok == 1)
	{
		sem_wait(philo->sema_fork);
		ft_print_time(philo, "has taken a fork", i);
		ft_print_time(philo, "has taken a fork", i);
		ft_print_time(philo, "is eating", i);
		usleep(philo->t_eat);
		philo->pers[i].eat_end = ft_get_time();
		ft_print_time(philo, "is sleeping", i);
		sem_post(philo->sema_fork);
		if (++j < philo->nbr_eat)
			sem_post(philo->sema_nbr);
		usleep(philo->t_sleep);
		ft_print_time(philo, "is thinking", i);
	}
	return (1);
}

int	ft_creat_philos(t_philo *philo)
{
	int	i;

	philo->pers = (t_person *)malloc(philo->nbr_p * sizeof(t_person));
	if (philo->pers == NULL)
		return (-5);
	i = -1;
	philo->sema_fork = sem_open("semafork", O_CREAT, 00777, philo->nbr_p / 2);
	philo->sema_ok = sem_open("semaok", O_CREAT, 00777, 0);
	if (philo->nbr_eat > 0)
		philo->sema_nbr = sem_open("semanbr", O_CREAT, 00777, 0);
	ft_get_t0(philo);
	while (++i < philo->nbr_p)
	{
		philo->pers[i].eat_end = 9223372036854775807;
		philo->pers[i].ok = 1;
		philo->pers[i].child = fork();
		if (philo->pers[i].child < 0)
			return (-9);
		else if (philo->pers[i].child == 0)
		{
			if (ft_child(philo, i) < 0)
				return (-10);
		}
		else
			usleep(10);	
	}
	return (1);
}
