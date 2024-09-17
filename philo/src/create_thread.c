/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:37:42 by bdany             #+#    #+#             */
/*   Updated: 2024/09/03 18:13:49 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	start_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philo)
	{
		pthread_create(&philo[i].thread_id, NULL, (void *)routine, &philo[i]);
		++i;
	}
	return (i);
}

void	handle_threads(t_philo *philo)
{
	int	i;

	i = start_thread(philo);
	if (i == philo->data->n_philo)
		supervisor(philo);
	while (i--)
		pthread_join(philo[i].thread_id, NULL);
}
