/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:18:43 by faveline          #+#    #+#             */
/*   Updated: 2023/12/01 15:45:47 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atoi_long(const char *str)
{
	int		i;
	long	atoi;
	int		signe;

	signe = 1;
	atoi = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		i++;
		signe = -1;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		atoi = atoi * 10 + str[i] - 48;
		i++;
	}
	return (atoi * signe);
}

static void	ft_philo_struct(int nbr, int i, t_philo *philo)
{
	if (i == 1)
		philo->nbr_p = nbr;
	else if (i == 2)
		philo->t_death = (useconds_t)nbr;
	else if (i == 3)
		philo->t_eat = (useconds_t)nbr;
	else if (i == 4)
		philo->t_sleep = (useconds_t)nbr;
	else if (i == 5)
		philo->nbr_eat = nbr;
}

static int	ft_strcmp_philo(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;	
	}
	return (str1[i] - str2[i]);

}

int	ft_creat_struct(int	argc, char *argv[], t_philo *philo)
{
	int		i;
	int		nbr;
	char	*check;

	if (argc != 5 && argc != 6)
		return (-1);
	i = 0;
	while (++i < argc)
	{
		nbr = ft_atoi_philo(argv[i]);
		if (nbr != ft_atoi_long(argv[i]))
			return (-2);
		check = ft_itoa_philo(nbr);
		if (ft_strcmp_philo(argv[i], check) != 0)
			return (free(check), -3);
		free(check);
		if (nbr < 0)
			return (-4);
		ft_philo_struct(nbr, i, philo);
	}
	if (argc == 5)
		philo->nbr_eat = -1;
	return (1);
}
