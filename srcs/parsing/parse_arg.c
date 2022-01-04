/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:31:30 by ambelkac          #+#    #+#             */
/*   Updated: 2021/12/04 16:10:45 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	allocate_forks(t_pgen *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philo);
	data->timestamp = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philo);
	while (i < data->nbr_of_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return ;
		if (pthread_mutex_init(&(data->timestamp[i]), NULL))
			return ;
		++i;
	}
	pthread_mutex_init(&(data->display), NULL);
	pthread_mutex_init(&(data->time), NULL);
}

int	fill_general_data(char **av, int ac, t_pgen *data)
{
	data->nbr_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac > 5)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	allocate_forks(data);
}

int	is_arg_only_numbers(char **av, int ac)
{
	int	i;

	i = 1;
	while (ac < i)
	{
		if (is_number(av[i]))
			return (1);
		++i;
	}
	return (0);
}

t_pgen	*parse_arg(char **av, int ac)
{
	t_pgen	*data;

	if (ac < 5 || ac > 6)
		return (NULL);
	if (is_arg_only_numbers(av, ac))
		return (NULL);
	data = malloc(sizeof(t_pgen));
	if (!data)
		return (NULL);
	fill_general_data(av, ac, data);
	return (data);
}