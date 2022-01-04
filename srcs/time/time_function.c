/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:56:17 by ambelkac          #+#    #+#             */
/*   Updated: 2022/01/04 19:18:36 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void		custom_usleep(long int usec)
{
	long int	timestamp;

	timestamp = get_elapsed_time() + usec;
	while (get_elapsed_time() < timestamp)
	{
		usleep(1);
	}
}

long int	get_elapsed_time(void)
{
	struct timeval	tp;

		gettimeofday(&tp, NULL);
		return ((tp.tv_sec * 1000000 + tp.tv_usec));
}