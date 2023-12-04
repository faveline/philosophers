/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:55:34 by faveline          #+#    #+#             */
/*   Updated: 2023/12/04 16:25:19 by faveline         ###   ########.fr       */
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
		printf("Only positive integers are accepted\n");
	if (error == -5)
		printf("A malloc failed\n");
	if (error == -6)
		printf("Thread creation failed\n");
	if (error == -7)
		printf("Problem getting the time\n");
	if (error == -8)
		printf("Problem while de.locking mutex\n");
}

void	ft_exterminate(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nbr_p)
		pthread_mutex_destroy(&philo->fork[i]);
	free(philo->fork);
	free(philo->pers);
}

void	ft_result(t_philo *philo)
{
	int	i;

	if (ft_check_i_eat(philo) == 1)
		printf("The philosophers have all eaten at least %d times.\n",
			philo->nbr_eat);
	else if (philo->all_ok == 0)
	{
		i = 0;
		while (i < philo->nbr_p)
		{
			printf("Philosopher %d ate %d times.\n",
				i + 1, philo->pers[i].i_eat);
			i++;
		}
	}
}
