/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:37:13 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/29 18:37:26 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philos.h"

void	*ft_routine(void *arg)
{
	t_philo	*panda;

	panda = (t_philo *)arg;
	if (panda->id % 2)
		ft_usleep(100);
	while (!panda->data->dead && !panda->full)
	{
		ft_think(panda);
		if (panda->data->dead)
			break ;
		if (!ft_eat(panda))
			break ;
		if (panda->data->dead)
			break ;
		ft_nap(panda);
		if (panda->data->dead)
			break ;
	}
	if (&panda->data->chopstick[panda->l_chopstick]
		== &panda->data->chopstick[panda->r_chopstick])
		pthread_mutex_unlock(&panda->data->chopstick[panda->l_chopstick]);
	return (NULL);
}

void	ft_think(t_philo *panda)
{
	ft_write_lock(panda, THINK);
}

static bool	ft_take_chopsticks(t_philo *panda)
{
	if (panda->id % 2 == 0)
	{
		pthread_mutex_lock(&panda->data->chopstick[panda->l_chopstick]);
		ft_write_lock(panda, L_C);
		if (&panda->data->chopstick[panda->l_chopstick]
			== &panda->data->chopstick[panda->r_chopstick])
		{
			pthread_mutex_unlock(&panda->data->chopstick[panda->r_chopstick]);
			return (false);
		}
		pthread_mutex_lock(&panda->data->chopstick[panda->r_chopstick]);
		ft_write_lock(panda, R_C);
	}
	else
	{
		pthread_mutex_lock(&panda->data->chopstick[panda->r_chopstick]);
		ft_write_lock(panda, R_C);
		if (&panda->data->chopstick[panda->l_chopstick]
			== &panda->data->chopstick[panda->r_chopstick])
		{
			pthread_mutex_unlock(&panda->data->chopstick[panda->r_chopstick]);
			return (false);
		}
		pthread_mutex_lock(&panda->data->chopstick[panda->l_chopstick]);
		ft_write_lock(panda, L_C);
	}
	return (true);
}

bool	ft_eat(t_philo *panda)
{
	if (!ft_take_chopsticks(panda))
		return (false);
	ft_write_lock(panda, EAT);
	panda->last_meal = ft_get_time() - panda->data->start_t;
	panda->eat_cnt++;
	ft_usleep(panda->data->eat_t);
	pthread_mutex_unlock(&panda->data->chopstick[panda->r_chopstick]);
	pthread_mutex_unlock(&panda->data->chopstick[panda->l_chopstick]);
	ft_write_lock(panda, B_C);
	return (true);
}

/*void	ft_eating_msg(t_philo *panda)
{
	const char	*flavors[] = {"chocolate", "glazed",
		"sprinkled", "jelly", "honey"};
	const char	*flavor = flavors[panda->id % 5];
	printf("%ld - ", ft_get_time() - panda->data->start_t);
	printf("Panda %d is eating a %s donut.\n", panda->id + 1, flavor);
	//printf("Panda %d is eating a donut.\n", panda->id + 1);
}*/

void	ft_nap(t_philo *panda)
{
	ft_write_lock(panda, NAP);
	ft_usleep(panda->data->nap_t);
}
