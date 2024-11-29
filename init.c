/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:35:55 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/29 18:36:08 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philos.h"

void	ft_init_philos(t_data *data)
{
	if (ft_check_limits(data) != 1)
	{
		printf("ERROR check your args.\n");
		exit (EXIT_FAILURE);
	}
	else
	{
		ft_init_data(data);
		ft_init_mutexes(data);
		ft_init_threads(data);
	}
}

/* sets up each philos data 
(ID, each chopstick iD and inits a mutex lock as well as sim start time)*/

void	ft_init_data(t_data *data)
{
	int	i;

	i = 0;
	ft_data_malloc(data);
	while (i < data->nop)
	{
		data->pandas[i].id = i;
		data->pandas[i].l_chopstick = i;
		data->pandas[i].r_chopstick = (i + 1) % data->nop;
		data->pandas[i].eat_cnt = 0;
		data->pandas[i].last_meal = 0;
		data->pandas[i].data = data;
		data->pandas[i].full = false;
		i++;
	}
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->shared_lock, NULL);
	data->start_t = ft_get_time();
}

/*init mutex for each fork*/
void	ft_init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nop)
	{
		if (pthread_mutex_init(&data->chopstick[i], NULL) != 0)
		{
			perror("Failed to init form mutex");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

/*makes thread for each philo passing ft_routine for each philo to follow*/

void	ft_init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nop)
	{
		pthread_create(&data->threads[i], NULL, ft_routine, &data->pandas[i]);
		i++;
	}
}

void	ft_data_malloc(t_data *data)
{
	data->chopstick = (pthread_mutex_t *)
		malloc(data->nop * sizeof(pthread_mutex_t));
	if (data->chopstick == NULL)
	{
		ft_error(data, C_MALLOC);
		exit(EXIT_FAILURE);
	}
	data->pandas = (t_philo *)malloc(data->nop * sizeof(t_philo));
	if (data->pandas == NULL)
	{
		ft_error(data, P_MALLOC);
		exit(EXIT_FAILURE);
	}
	data->threads = (pthread_t *)malloc(data->nop * sizeof(pthread_t));
	if (data->threads == NULL)
	{
		ft_error(data, T_MALLOC);
		exit(EXIT_FAILURE);
	}
	data->all_satisfied = false;
}