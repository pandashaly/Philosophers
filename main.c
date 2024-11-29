/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:36:16 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/29 18:36:24 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philos.h"

int	main(int ac, char **av)
{
	t_data		data;

	if (!ft_parser(&data, ac, av))
	{
		printf("Program usage: ");
		printf("./philo <num_of_philos> <time_to_die> <time_to_eat> ");
		printf("<time_to_sleep> [num_ech_philo_must_eat]\n");
		return (EXIT_FAILURE);
	}
	ft_init_philos(&data);
	ft_zookeeper(&data);
	ft_clear_table(&data);
	return (EXIT_SUCCESS);
}
