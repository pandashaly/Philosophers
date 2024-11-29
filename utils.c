/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:37:43 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/29 18:37:45 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philos.h"

long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(useconds_t time)
{
	uint64_t	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
		usleep(100);
	return ;
}

void	ft_write_lock(t_philo *panda, const char *msg)
{
	if (!panda->data->dead)
	{
		pthread_mutex_lock(&panda->data->print_lock);
		if (!panda->data->dead)
		{
			printf("%013ld - Panda %d %s\n", ft_get_time()
				- panda->data->start_t, panda->id + 1, msg);
		}
		pthread_mutex_unlock(&panda->data->print_lock);
	}
}
