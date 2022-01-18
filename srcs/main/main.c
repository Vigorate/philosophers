/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:30:10 by ambelkac          #+#    #+#             */
/*   Updated: 2022/01/18 22:40:11 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	display_general_data(t_pgen *data)
{
	printf("	---	PHILO ARG DATA ---\n");
	printf("		nbr_of_philo : %d\n", data->nbr_of_philo);
	printf("		time_to_die : %ld\n", data->time_to_die);
	printf("		time_to_eat : %ld\n", data->time_to_eat);
	printf("		time_to_sleep : %ld\n", data->time_to_sleep);
	printf("		must_eat : %d\n\n", data->must_eat);
}

int	main(int ac, char **av)
{
	t_pgen *data;

	data = parse_arg(av, ac);
	if (!data)
		return (1);
//	display_general_data(data);
	dispatch_thread(data);
	return (0);
}