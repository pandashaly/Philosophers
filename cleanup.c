/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:35:43 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/29 18:35:46 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philos.h"

/*destroy mutexes and frees alloc mem when program ends*/
void	ft_clear_table(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nop)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nop)
	{
		pthread_mutex_destroy(&data->chopstick[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	free(data->chopstick);
	data->chopstick = NULL;
	free(data->pandas);
	data->pandas = NULL;
	free(data->threads);
	data->threads = NULL;
}

int	ft_error(t_data *data, char *str)
{
	printf("%s\n", str);
	if (data)
		ft_clear_table(data);
	return (1);
}
