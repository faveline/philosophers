/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:05:17 by faveline          #+#    #+#             */
/*   Updated: 2023/12/02 18:17:51 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	int		error;
	t_philo	philo;
	int		i;

	if ((error = ft_creat_struct(argc, argv, &philo)) < 0)
		return (ft_error_philo(error), 1);
	if ((error = ft_creat_philos(&philo)) < 0)
		return (ft_error_philo(error), ft_exterminate(&philo), 1);
	if ((error = ft_loop_philo(&philo)) < 0)
		return (ft_error_philo(error), ft_exterminate(&philo), 1);
	i = -1;
	while (++i < philo.nbr_p)
		pthread_join(philo.pers[i].thread, NULL);
	ft_result(&philo);
	ft_exterminate(&philo);
	return (0);   // mettre tout les printf dans la boucle peut peut etre supprimer le problems des timings faux
}
