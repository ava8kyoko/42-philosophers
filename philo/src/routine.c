#include "../philo.h"

static void	need_to_sleep(t_philo *p)
{
	long int	time_to_stop;
	long int	delay;

	time_to_stop = 0;
	if (p->state == EAT)
	{
		print_state(p, "is eating");
		pthread_mutex_lock(&p->meal);
		if (p->meal_to_eat != -1) 
			p->meal_to_eat -= 1;
		pthread_mutex_unlock(&p->meal);
		time_to_stop = p->time_last_meal + p->time_to_eat;
		p->state = SLEEP;
	}
	else if (p->state == SLEEP)
	{
		print_state(p, "is sleeping");
		time_to_stop = p->time_last_meal + p->time_to_eat + p->time_to_sleep;
		p->state = THINK;
	}
	while (1)
	{
		delay = time_to_stop - get_time(0, 0);
		if (delay <= 0)
			break;
		usleep(200);
	}
}

// When a hungry philosopher has both his forks at the same time, he eats
// without relasing his forks. When he has finished eating, he puts down
// both of his forks and starts thinking again.
static void	is_eating(t_philo *p)
{
	pthread_mutex_lock(&p->last_meal);
	p->time_last_meal = get_time(0, 0);
	pthread_mutex_unlock(&p->last_meal);
	need_to_sleep(p);
	pthread_mutex_unlock(&p->fork_left);
	pthread_mutex_unlock(p->fork_right);
}

// When a philosopher gets hungry he tries to pick up the two forks that are
// closest to him (left and right). A philosopher may pick up only one fork
// at a time.
// Cannot pick up a fork that is already in the hand of a neighbour.
static void	is_taking_forks(t_philo *p)
{
	while (p->state != EAT)
	{
		if (p->state == THINK || p->state == FORK_RIGHT)
		{
			pthread_mutex_lock(&p->fork_left);
			print_state(p, "has taken a fork_left");
			if (p->state == FORK_RIGHT)
				p->state = EAT;
			else if (p->state == THINK)
				p->state = FORK_LEFT;
		}
		else if (p->state == FORK_LEFT)
		{
			pthread_mutex_lock(p->fork_right);
			print_state(p, "has taken a fork_right");
			if (p->state == FORK_LEFT)
				p->state = EAT;
			else if (p->state == THINK)
				p->state = FORK_RIGHT;
		}
	}
}	

// When a philosopher thinks, he does not interact with his colleagues.
void	*philosophers_routine(void *arg)
{
	t_philo	*p;
	
	p = arg;
	if (p->philo_id % 2 == 0)
	{
		print_state(p, "is thinking");
		usleep(400);
	}
	while (1)
	{
		if (p->state == THINK)
			is_taking_forks(p);
		if (p->state == EAT)
			is_eating(p);
		if (p->state == SLEEP)
			need_to_sleep(p);
		if (p->state == THINK)
			print_state(p, "is thinking");
	}
	return ((void*)0);
}