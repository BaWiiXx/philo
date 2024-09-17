/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:24:19 by baptiste          #+#    #+#             */
/*   Updated: 2024/09/05 16:51:48 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_data(t_data *data, char **argv)
{
	*data = (t_data){0};
	data->n_philo = ft_atoi(argv[1]);
	if (!data->n_philo)
	{
		ft_putstr_fd("you need at least one philosopher\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->n_meals = ft_atoi(argv[5]);
	if (data->t_to_die <= 0 || data->t_to_eat <= 0 || data->t_to_sleep <= 0)
	{
		ft_putstr_fd("negative or zero value is not authorized\n",
			STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	data->start = get_current_time();
	data->n_eat = 0;
	data->dead_philo = 0;
}

int	init_philo(t_philo *philo, t_data *data)
{
	int	i;

	if (!philo || !data->forks)
		return (-1);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->printf_mutex, NULL);
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->forks[i].fork_mutex, NULL);
		philo[i].data = data;
		philo[i].philo_id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].fed_up = 0;
		philo[i].last_meal_time = 0;
		philo[i].left_forks = &data->forks[i];
		philo[i].right_forks = &data->forks[(i + 1) % philo->data->n_philo];
		data->forks[i].is_available = true;
		++i;
	}
	return (0);
}
