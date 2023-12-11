/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:55:34 by faveline          #+#    #+#             */
/*   Updated: 2023/12/11 17:12:51 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_philo(int error)
{
	if (error == -1)
		printf("Wrong number of argument\n");
	if (error == -2)
		printf("The numbers should be ints\n");
	if (error == -3)
		printf("Characters other than digit are refuse\n");
	if (error == -4)
		printf("Only strictly positive integers are accepted\n");
	if (error == -5)
		printf("A malloc failed\n");
	if (error == -6)
		printf("Thread creation failed\n");
	if (error == -7)
		printf("Problem getting the time\n");
	if (error == -8)
		printf("Problem while de.locking mutex\n");
	if (error == -10)
		printf("Too many philosophers\n");
}

void	ft_exterminate(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nbr_p)
	{
		if (philo->fork)
			pthread_mutex_destroy(&philo->fork[i]);
		if (philo->def_eat)
			pthread_mutex_destroy(&philo->def_eat[i]);
	}
	pthread_mutex_destroy(&philo->wait);
	pthread_mutex_destroy(&philo->wait_i);
	free(philo->eat_t);
	free(philo->eat_i);
	free(philo->fork);
	free(philo->pers);
	free(philo->def_eat);
}

void	ft_ini_var(t_philo *philo)
{
	philo->fork = NULL;
	philo->def_eat = NULL;
	philo->eat_t = NULL;
	philo->eat_i = NULL;
	philo->pers = NULL;
}
