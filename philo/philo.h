#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

# define FAIL 0
# define SUCCESS 1
# define FORK_LEFT 'L'
# define FORK_RIGHT 'R'
# define EAT 'E'
# define SLEEP 'S'
# define THINK 'T'
# define DIE 'D'
# define MS 'M'
# define MAIN_UNLOCK 'U'
# define SLEEPING 1

typedef struct s_table	t_table;

typedef struct s_philo
{
	char			state;
	int				philo_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_to_eat;
	long int		time_last_meal;
	long int		time_start;
	t_table			*t;
	pthread_t		thread;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	meal;
}				t_philo;

typedef struct s_table
{
	int				end_routine;
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meal;
	long int		actual_time;
	t_philo			p[200];
	pthread_mutex_t	print;
}				t_table;

void		ft_putstr_fd(char *str, int fd);
void		print_state(t_philo *p, char *state);

long int	get_time(t_philo *p, char ms);
int			is_dead(t_philo *p);
int			is_sated(t_philo *p, bool eat);
void		destroy_mutex(t_table *t);

void		*philosophers_routine(void *arg);

bool		is_valid_int(char *str);
int			ft_atoi(const char *str);

int			main(int argc, char **argv);

#endif