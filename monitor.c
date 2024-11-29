/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:36:40 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/29 18:36:43 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philos.h"

static void	ft_zookeeper_helper(t_data *data)
{
	if (data->all_satisfied && data->must_eat_t != -1)
	{
		printf("All pandas have eaten %d times. Simulation ending.\n",
			data->must_eat_t);
		data->dead = 1;
	}
	ft_usleep(1);
}

void	ft_zookeeper(t_data *data)
{
	int		i;

	i = 0;
	while (!data->dead)
	{
		if (data->must_eat_t != -1
			&& data->pandas[i].eat_cnt == data->must_eat_t)
			data->pandas[i].full = true;
		if (ft_have_all_eaten(data))
			data->all_satisfied = 1;
		if (!data->pandas[i].full)
		{
			if (((ft_get_time() - data->start_t)
					- data->pandas[i].last_meal) > data->life_t)
			{
				if (!data->pandas[i].full)
				{
					ft_write_lock(data->pandas, DEAD);
					data->dead = 1;
				}
			}
		}
		i = (i + 1) % data->nop;
		ft_zookeeper_helper(data);
	}
}

bool	ft_have_all_eaten(t_data *data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < data->nop)
		if (data->pandas[i].full)
			count++;
	if (count == data->nop)
		return (true);
	return (false);
}
