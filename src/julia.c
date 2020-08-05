/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:40:28 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/05 18:42:02 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		julia_iteration(PRECISION cx, PRECISION cy, int max_iter, t_position_xy pos)
{
	PRECISION	zx;
	PRECISION	zy;
	PRECISION	tempx;
	int		iteration;

	zx = 0;
	zy = 0;
	iteration = 0;
	zx = cx;
	zy = cy;
	cx = (3.0 / WIDTH) * (pos.x - WIDTH / 2);
	cy = (2.0 / HEIGHT) * (pos.y - HEIGHT / 2);
	while ((zx * zx + zy * zy < 4) && (iteration < max_iter))
	{
		tempx = zx * zx - zy * zy + cx;
		zy = 2 * zx * zy + cy;
		zx = tempx;
		iteration++;
	}
	return (iteration);
}

void	julia(t_settings *settings, int start, int stop)
{
	t_position_xy	pos;
	PRECISION		cx;
	PRECISION		cy;
	int			x;
	int			y;

	y = start;
	pos.x = settings->pos.x + WIDTH;
	pos.y = settings->pos.y + HEIGHT;
	while (!(x = 0) && y < stop)
	{
		while (x < WIDTH)
		{
			cx = (x - WIDTH / 2) * ((ASPECT_WIDTH * settings->zoom) / WIDTH);
			cy = (y - HEIGHT / 2) * ((ASPECT_HEIGHT * settings->zoom) / HEIGHT);
			pixel_put(x, y, select_color(settings->color, settings->max_iter, settings->frame, julia_iteration(cx, cy, settings->max_iter, pos)));
			x++;
		}
		y++;
	}
}
