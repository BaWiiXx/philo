/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:35:56 by bdany             #+#    #+#             */
/*   Updated: 2024/09/02 13:15:12 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	stop_all(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->dead_philo)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (0);
}

static int	check_death(t_philo *philo)
{
	int		i;
	size_t	time;

	i = 0;
	while (philo->data->n_philo > i)
	{
		time = get_current_time() - philo->data->start;
		pthread_mutex_lock(&philo->data->last_m_mutex);
		if (time - philo[i].last_meal_time >= (size_t)philo->data->t_to_die)
		{
			pthread_mutex_lock(&philo->data->printf_mutex);
			printf("%zu %d died\n", time, philo->philo_id);
			pthread_mutex_unlock(&philo->data->printf_mutex);
			pthread_mutex_lock(&philo->data->dead_mutex);
			philo->data->dead_philo = 1;
			pthread_mutex_unlock(&philo->data->dead_mutex);
			pthread_mutex_unlock(&philo->data->last_m_mutex);
			return (1);
		}
		i++;
		pthread_mutex_unlock(&philo->data->last_m_mutex);
	}
	return (0);
}

static int	check_satiety(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->data->n_philo > i && !check_death(philo))
	{
		pthread_mutex_lock(&philo->data->eat_c_mutex);
		philo->data->not_hungry
			+= (philo[i].meals_eaten >= philo->data->n_meals);
		pthread_mutex_unlock(&philo->data->eat_c_mutex);
		i++;
	}
	if (philo->data->not_hungry == philo->data->n_philo
		&& philo->data->n_meals != 0)
	{
		pthread_mutex_lock(&philo->data->dead_mutex);
		philo->data->dead_philo = 1;
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	philo->data->not_hungry = 0;
	return (0);
}

void	supervisor(t_philo *philo)
{
	size_t	time;

	if (philo->data->n_philo > 1)
	{
		while (1)
		{
			if (stop_all(philo))
				break ;
			if (check_satiety(philo))
				break ;
			if (stop_all(philo))
				break ;
		}
	}
	else
	{
		time = get_current_time() - philo->data->start;
		while (time < (size_t)philo->data->t_to_die)
			time = get_current_time() - philo->data->start;
		print_action(philo, "died");
		pthread_mutex_lock(&philo->data->dead_mutex);
		philo->data->dead_philo = 1;
		pthread_mutex_unlock(&philo->data->dead_mutex);
	}
}
