/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:03:05 by faveline          #+#    #+#             */
/*   Updated: 2023/12/04 18:31:28 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_creat_philos(t_philo *philo)
{
	int	i;

	if (ft_creat_malloc(philo) < 0)
		return (-5);
	i = -1;
	if (pthread_create(&philo->early, NULL, ft_check_early, philo) != 0)
		return (-6);
	ft_get_t0(philo);
	while (++i < philo->nbr_p)
	{
		philo->inc = i;
		philo->pers[i].i_eat = 0;
		if (pthread_mutex_init(&philo->fork[i], NULL) < 0)
			return (-6);
		if (pthread_create(&philo->pers[i].thread, NULL, ft_philo, philo) != 0)
			return (-6);
		while (philo->inc != -1)
			i = i * 1;
	}
	return (1);
}
