/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:00:29 by bdany             #+#    #+#             */
/*   Updated: 2024/09/05 16:49:25 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	is_think(t_philo *philo)
{
	if (stop_all(philo))
		return ;
	print_action(philo, "is thinking");
	lock_fork(philo);
}

static void	is_sleep(t_philo *philo)
{
	if (stop_all(philo))
		return ;
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->t_to_sleep, philo);
}

void	is_eating(t_philo *philo)
{
	if (!(stop_all(philo)))
	{
		print_action(philo, "is eating");
		pthread_mutex_lock(&philo->data->dead_mutex);
		philo->last_meal_time = get_current_time() - philo->data->start;
		pthread_mutex_unlock(&philo->data->dead_mutex);
		ft_usleep(philo->data->t_to_eat, philo);
		philo->meals_eaten++;
		release_fork(philo);
	}
}

int	*routine(t_philo *philo)
{
	if (philo->data->n_philo == 1)
	{
		print_action(philo, "has taken a fork");
		return (NULL);
	}
	if (philo->philo_id % 2 != 0)
		usleep(10000);
	is_think(philo);
	while (1)
	{
		if (stop_all(philo))
			break ;
		is_eating(philo);
		if (stop_all(philo))
			break ;
		is_sleep(philo);
		if (stop_all(philo))
			break ;
		is_think(philo);
	}
	return (0);
}
