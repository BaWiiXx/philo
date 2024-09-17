/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:35:56 by bdany             #+#    #+#             */
/*   Updated: 2024/09/05 17:08:58 by bdany            ###   ########.fr       */
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
		pthread_mutex_lock(&philo->data->dead_mutex);
		if (philo->data->dead_philo)
			return (1);
		time = get_current_time() - philo->data->start;
		if (time - philo[i].last_meal_time >= (size_t)philo->data->t_to_die)
		{
			philo->data->dead_philo = 1;
			printf("%zu %d died\n", time, philo[i].philo_id);
			pthread_mutex_unlock(&philo->data->dead_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->dead_mutex);
		i++;
	}
	return (0);
}

static int	check_satiety(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->data->n_philo > i && !check_death(philo))
	{
		if (philo->data->n_meals)
		{
			pthread_mutex_lock(&philo->data->dead_mutex);
			if (philo->data->n_eat != philo->data->n_philo && !philo[i].fed_up
				&& philo[i].meals_eaten == philo->data->n_meals)
			{
				philo[i].fed_up++;
				philo->data->n_eat++;
			}
			if (philo->data->n_eat == philo->data->n_philo)
			{
				philo->data->dead_philo = 1;
				pthread_mutex_unlock(&philo->data->dead_mutex);
				return (1);
			}
			pthread_mutex_unlock(&philo->data->dead_mutex);
		}
		i++;
	}
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
			usleep(500);
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
