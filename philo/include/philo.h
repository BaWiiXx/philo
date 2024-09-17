/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:01:05 by bdany             #+#    #+#             */
/*   Updated: 2024/09/05 17:13:04 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	bool			is_available;
	pthread_mutex_t	fork_mutex;
}					t_fork;

typedef struct s_data
{
	int				n_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				n_meals;
	int				n_eat;
	int				dead_philo;
	long int		start;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	eat_c_mutex;
	pthread_mutex_t	last_m_mutex;
	t_fork			*forks;
}					t_data;

typedef struct s_philo
{
	int				philo_id;
	t_fork			*left_forks;
	t_fork			*right_forks;
	int				nb_fork;
	int				meals_eaten;
	int				fed_up;
	long			last_meal_time;
	t_data			*data;
	pthread_t		thread_id;
}					t_philo;

void				*ft_calloc(size_t count, size_t size);
int					ft_atoi(const char *nptr);
void				ft_putstr_fd(char *s, int fd);
void				print_action(t_philo *philo, char *str);
int					ft_usleep(size_t m_sec, t_philo *philo);
int					*routine(t_philo *philo);
long int			get_current_time(void);
int					stop_all(t_philo *philo);
int					check_argument(char **av);
int					init_philo(t_philo *philo, t_data *data);
void				init_data(t_data *data, char **argv);
void				destroy_all_mutex(t_data *data);
void				supervisor(t_philo *philo);
void				handle_threads(t_philo *philo);
void				release_fork(t_philo *philo);
void				lock_fork(t_philo *philo);

#endif
