/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deallocate_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelkac <ambelkac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:31:08 by ambelkac          #+#    #+#             */
/*   Updated: 2021/12/04 15:36:53 by ambelkac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	deallocate_structures(t_pgen *gen, t_pdata **pdata)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(gen->time));
	pthread_mutex_destroy(&(gen->display));
	while (i < gen->nbr_of_philo)
	{
		free(pdata[i]);
		pthread_mutex_destroy(&(gen->timestamp[i]));
		pthread_mutex_destroy(&(gen->forks[i]));
		++i;
	}
	free(gen->forks);
	free(gen->timestamp);
	free(gen);
}