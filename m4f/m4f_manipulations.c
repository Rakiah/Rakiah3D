/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m4f_manipulations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:10 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/13 04:28:27 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

void		m4f_identity(t_matrix4f *matrix)
{
	int x;
	int y;

	x = 0;
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			matrix->m[x][y] = x == y ? 1 : 0;
			y++;
		}
		x++;
	}
}

float		m4f_get_determinant(t_matrix4f *m)
{
	return (m->m[0][3] * m->m[1][2] * m->m[2][1] * m->m[3][0] - m->m[0][2] *
	m->m[1][3] * m->m[2][1] * m->m[3][0] - m->m[0][3] * m->m[1][1] *
	m->m[2][2] * m->m[3][0] + m->m[0][1] * m->m[1][3] * m->m[2][2] *
	m->m[3][0] + m->m[0][2] * m->m[1][1] * m->m[2][3] * m->m[3][0] -
	m->m[0][1] * m->m[1][2] * m->m[2][3] * m->m[3][0] - m->m[0][3] *
	m->m[1][2] * m->m[2][0] * m->m[3][1] + m->m[0][2] * m->m[1][3] *
	m->m[2][0] * m->m[3][1] + m->m[0][3] * m->m[1][0] * m->m[2][2] *
	m->m[3][1] - m->m[0][0] * m->m[1][3] * m->m[2][2] * m->m[3][1] -
	m->m[0][2] * m->m[1][0] * m->m[2][3] * m->m[3][1] + m->m[0][0] *
	m->m[1][2] * m->m[2][3] * m->m[3][1] + m->m[0][3] * m->m[1][1] *
	m->m[2][0] * m->m[3][2] - m->m[0][1] * m->m[1][3] * m->m[2][0] *
	m->m[3][2] - m->m[0][3] * m->m[1][0] * m->m[2][1] * m->m[3][2] +
	m->m[0][0] * m->m[1][3] * m->m[2][1] * m->m[3][2] + m->m[0][1] *
	m->m[1][0] * m->m[2][3] * m->m[3][2] - m->m[0][0] * m->m[1][1] *
	m->m[2][3] * m->m[3][2] - m->m[0][2] * m->m[1][1] * m->m[2][0] *
	m->m[3][3] + m->m[0][1] * m->m[1][2] * m->m[2][0] * m->m[3][3] +
	m->m[0][2] * m->m[1][0] * m->m[2][1] * m->m[3][3] - m->m[0][0] *
	m->m[1][2] * m->m[2][1] * m->m[3][3] - m->m[0][1] * m->m[1][0] *
	m->m[2][2] * m->m[3][3] + m->m[0][0] * m->m[1][1] * m->m[2][2] *
	m->m[3][3]);
}

void		m4f_invert(t_matrix4f *m)
{
	float	det;
	int		i;
	int		j;

	det = 1 / m4f_get_determinant(m);
	m4f_adjugate(m);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m->m[i][j] *= det;
			j++;
		}
		i++;
	}
}

void		m4f_print(t_matrix4f *matrix)
{
	int x;
	int y;

	ft_putstr("matrix4f values :\n");
	x = 0;
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			ft_putchar('[');
			ft_putnbr(floor(matrix->m[x][y]));
			ft_putchar(']');
			if (y == 3)
				ft_putchar('\n');
			else
				ft_putchar(' ');
			y++;
		}
		x++;
	}
}
