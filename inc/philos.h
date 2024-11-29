/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:38:09 by ssottori          #+#    #+#             */
/*   Updated: 2024/11/29 18:38:24 by ssottori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include <pthread.h>
# define __USE_XOPEN 1
# include <sys/time.h>
# include <unistd.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdint.h>

//tmp

# define L_C "has taken LEFT chopstick"
# define R_C "has taken RIGHT chopstick"
# define B_C "has dropped BOTH chopsticks"
# define THINK "is thinking about food."
# define NAP "is sleeping..."
# define EAT "is eating a donut."
# define DEAD "has died."

//	pthread_err
# define TH_ERR "oop! couldn't create thread."
# define C_MALLOC "Error: Failed to allocate memory for chopsticks.\n"
# define P_MALLOC "Error: Failed to allocate memory for philos.\n"
# define T_MALLOC "Error: Failed to allocate memory for threads.\n"
# define WRONG_AV "Error: Invalid input character.\n"
# define ZOO "Error: Unable to create zookeeper thread.\n"

# define MAX_PHILOS 500
# define MAX_TIME 1000000

/*      STRUCTS      */

typedef struct s_philo
{
	int				id;
	int				l_chopstick;
	int				r_chopstick;
	atomic_int		eat_cnt;
	atomic_long		last_meal;
	struct s_data	*flavor;
	struct s_data	*data;
	atomic_bool		full;
}	t_philo;

typedef struct s_data
{
	int				nop;
	int				life_t;
	int				eat_t;
	int				nap_t;
	atomic_int		must_eat_t;
	atomic_long		start_t;
	atomic_int		dead;
	atomic_bool		all_satisfied;
	pthread_mutex_t	*chopstick;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	shared_lock;
	t_philo			*pandas;
	pthread_t		*threads;
	const char		**flavors;
}	t_data;

/*       FUNCTIONS      */

/* PARSER */
int		ft_atoi(const char *s);
int		ft_parser(t_data *data, int ac, char **av);
int		ft_check_limits(t_data *data);

/* INIT */
void	ft_init_philos(t_data *data);
void	ft_init_data(t_data *data);
void	ft_init_mutexes(t_data *data);
void	ft_init_threads(t_data *data);
void	ft_data_malloc(t_data *data);

/* ROUTINE */

void	ft_think(t_philo *panda);
bool	ft_eat(t_philo *panda);
void	ft_nap(t_philo *panda);

/* UTILS */

long	ft_get_time(void);
void	*ft_routine(void	*arg);
void	ft_usleep(useconds_t time);

void	ft_clear_table(t_data *data);

void	ft_zookeeper(t_data *data);

bool	ft_have_all_eaten(t_data *data);
int		ft_error(t_data *data, char *str);
void	ft_write_lock(t_philo *panda, const char *msg);
int		ft_arg_check(char **av);

#endif