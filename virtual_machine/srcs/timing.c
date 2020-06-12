/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   timing.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 15:23:22 by tide-jon       #+#    #+#                */
/*   Updated: 2019/11/04 19:49:48 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static float	timediff_msec(struct timeval t0, struct timeval t1)
{
	return ((t1.tv_sec - t0.tv_sec) * 1000.0f +
			(t1.tv_usec - t0.tv_usec) / 1000.0f);
}

void			iwait(void)
{
	static struct timeval	last_time;
	struct timeval			current_time;
	float					time_diff;

	if (last_time.tv_sec == 0 && last_time.tv_usec == 0)
		gettimeofday(&last_time, 0);
	else
	{
		gettimeofday(&current_time, 0);
		time_diff = timediff_msec(last_time, current_time);
		if (time_diff < TIME_INTERVAL_MILISEC)
			usleep((TIME_INTERVAL_MILISEC * 1000) - (int)(time_diff * 1000));
		gettimeofday(&last_time, 0);
	}
}
