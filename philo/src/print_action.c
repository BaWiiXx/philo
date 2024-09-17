/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:00:37 by bdany             #+#    #+#             */
/*   Updated: 2024/09/02 13:19:11 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_action(t_philo *philo, char *str)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->data->dead_mutex);
	if (!(philo->data->dead_philo))
	{
		time = get_current_time() - philo->data->start;
		pthread_mutex_lock(&philo->data->printf_mutex);
		printf("%zu %d %s\n", time, philo->philo_id, str);
		pthread_mutex_unlock(&philo->data->printf_mutex);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
}
