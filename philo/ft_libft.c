/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:59:35 by faveline          #+#    #+#             */
/*   Updated: 2023/11/29 18:09:54 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_philo(const char *str)
{
	int	i;
	int	atoi;
	int	signe;

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

static int	ft_size_itoa(int n)
{
	int	size;

	size = 0;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*ft_nbr(int n, char *itoa, int size)
{
	itoa[size] = 0;
	if (n == 0)
		itoa[0] = 48;
	while (n > 0)
	{
		itoa[size - 1] = n % 10 + 48;
		size--;
		n /= 10;
	}
	return (itoa);
}

static char	*ft_int_min(void)
{
	char	*itoa;

	itoa = (char *)malloc(12 * sizeof(char));
	if (itoa == NULL)
		return (itoa);
	itoa[0] = '-';
	itoa = ft_nbr(214748364, itoa, 10);
	itoa[10] = 56;
	itoa[11] = '\0';
	return (itoa);
}

char	*ft_itoa_philo(int n)
{
	char	*itoa;
	int		size;

	if (n == -2147483648)
	{
		itoa = ft_int_min();
		return (itoa);
	}
	else if (n <= 0)
		size = ft_size_itoa(n) + 1;
	else
		size = ft_size_itoa(n);
	itoa = (char *)malloc((size + 1) * sizeof(char));
	if (itoa == NULL)
		return (itoa);
	if (n < 0)
	{
		n *= -1;
		itoa[0] = '-';
		itoa = ft_nbr(n, itoa, size);
	}
	else
		itoa = ft_nbr(n, itoa, size);
	return (itoa);
}
