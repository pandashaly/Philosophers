/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:36:59 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/29 18:37:03 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philos.h"

/*./philo <num_of_philos> <time_to_ded> 
<time_to_eat> <time_to_sleep> 
[num times each philo must eat]
./philo 5 800 200 200*/

int	ft_parser(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (0);
	if (ft_arg_check(av))
		return (0);
	data->nop = ft_atoi(av[1]);
	data->life_t = ft_atoi(av[2]);
	data->eat_t = ft_atoi(av[3]);
	data->nap_t = ft_atoi(av[4]);
	data->dead = 0;
	if (ac == 6)
		data->must_eat_t = ft_atoi(av[5]);
	else
		data->must_eat_t = -1;
	if (data->nop <= 0 || data->life_t <= 0
		|| data->eat_t <= 0 || data->nap_t <= 0
		|| (ac == 6 && data->must_eat_t <= 0))
		return (0);
	return (ft_check_limits(data));
}

int	ft_atoi(const char *str)
{
	int	s;
	int	r;

	s = 1;
	r = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		s++;
	if (*str == '-')
		s = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		r = r * 10 + *str++ - '0';
	return (r * s);
}

int	ft_check_limits(t_data *data)
{
	if (data->nop > MAX_PHILOS || data->nop <= 0)
	{
		printf("Error: Num of philos must be between 1 and %d.\n", MAX_PHILOS);
		return (0);
	}
	if (data->life_t > MAX_TIME
		|| data->eat_t > MAX_TIME || data->nap_t > MAX_TIME)
	{
		printf("Error: Time values must be between 1 and %d ms.\n", MAX_TIME);
		return (0);
	}
	if (data->must_eat_t < -1)
	{
		printf("Error: Num of times each philo must eat must be + or -1.\n");
		return (0);
	}
	return (1);
}

int	ft_arg_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if ((av[i][j] < '0' || av[i][j] > '9'))
				return (ft_error(NULL, WRONG_AV));
			j++;
		}
		i++;
	}
	return (0);
}
