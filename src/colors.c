/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:01:47 by rpehkone          #+#    #+#             */
/*   Updated: 2020/08/04 20:23:40 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		get_color_6(int max, int frame_id, int iter)
{
	static int		other2 = 0;
	static int		wait_i = 1;
	static int		wait_time = 0;
	static float	fire_amount = 0;

	if (other2 != frame_id && (wait_i++ + 1))
		other2 = frame_id;
	if (wait_i > wait_time)
	{
		wait_time = rand() % 10;
		fire_amount = (float)(rand() % 100) / 100 + 1;
		wait_i = rand() % 3;
		fire_amount = wait_i < 3 ? fire_amount + 1.5 : fire_amount;
		wait_i = 0;
	}
	if (iter == max)
		return (0xFFFFFF);
	else if (iter < max / fire_amount)
	{
		max /= fire_amount;
		return ((int)(0xFF - 0xFF * ((float)(max - iter) / max)) * 0x10000);
	}
	iter /= fire_amount;
	max /= fire_amount;
	return ((0xFF0000) + ((int)(0xFF * ((float)iter / max)) * 0x100));
}

int		get_color_5(int x, int frame_id, int i)
{
	static int	other2 = 0;
	static int	asd = 0;
	double		red;
	double		grn;
	double		blu;

	if (other2 != frame_id)
	{
		other2 = frame_id;
		asd += 5;
	}
	if (asd > 310)
		asd = 0;
	x += asd;
	if (x > 310)
		x -= 310;
	i = 0;
	while (i < 310 && i != x)
		i++;
	red = sin(0.02 * i + 0) * 127 + 128;
	grn = sin(0.02 * i + 2) * 127 + 128;
	blu = sin(0.02 * i + 4) * 127 + 128;
	return ((int)red * 65536 + (int)grn * 256 + (int)blu);
}

int		select_color(int color, int max, int frame_id, int iter)
{
	int fade;

	fade = 0xFF * ((float)(max - iter) / max);
	if (color == 0)
		return (iter < max ? 0xFFFFFF : 0);
	else if (color == 1)
		return (iter == max ? 0xFFFFFF : fade * 0x10000 + fade * 0x100 + 0xFF);
	else if (color == 2)
	{
		if (iter * 2 < max)
			fade = (0xFF - fade) * 2;
		if (iter * 2 < max)
			return (fade * 0x10000 + fade * 0x100 + fade);
		fade *= 2;
		return (fade * 0x10000 + fade * 0x100 + fade);
	}
	else if (color == 3 && iter == max)
		return (0xFFFFFF);
	else if (color == 3)
		return (iter % 2 ? 0xFF7777 : 0xFFCCCC);
	else if (color == 4)
		return (iter == max ? 0xFF0000 : -216380416);
	else if (color == 5)
		return (get_color_5(310 * ((float)(max - iter) / max), frame_id, 0));
	return (get_color_6(max, frame_id, iter));
}

void	color_settings(t_args *args)
{
	static int last_down = 0;

	if (!last_down)
	{
		args->color = is_key_down(124) ? args->color + 1 : args->color;
		args->color = is_key_down(123) ? args->color - 1 : args->color;
	}
	if (args->color < 0)
		args->color = 6;
	else if (args->color > 6)
		args->color = 0;
	last_down = is_key_down(124) || is_key_down(123) ? 1 : 0;
}
