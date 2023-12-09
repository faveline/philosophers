/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:05:17 by faveline          #+#    #+#             */
/*   Updated: 2023/12/09 15:31:17 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	int		error;
	t_philo	philo;
	int		i;

	error = ft_creat_struct(argc, argv, &philo);
	if (error < 0)
		return (ft_error_philo(error), 1);
	error = ft_creat_philos(&philo);
	if (error < 0)
		return (ft_error_philo(error), ft_exterminate(&philo), 1);
	error = ft_loop_philo(&philo);
	if (error < 0)
		return (ft_error_philo(error), ft_exterminate(&philo), 1);
	i = -1;
	while (++i < philo.nbr_p)
		pthread_join(philo.pers[i].thread, NULL);
	ft_exterminate(&philo);
	return (0);
}	
