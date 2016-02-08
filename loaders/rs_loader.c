/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_loader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 07:01:35 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/25 15:16:41 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"
#include <get_next_line.h>
#include <fcntl.h>

static void	parse_scale(t_object *obj, char **splitted)
{
	t_vector3f	scale;

	if (obj == NULL)
		return ;
	v3f_set(&scale,
			strtod(splitted[1], NULL),
			strtod(splitted[2], NULL),
			strtod(splitted[3], NULL));
	trs_set_scale(obj->transform, &scale);
}

static void	parse_rotation(t_object *obj, char **splitted)
{
	t_vector3f	rot;

	if (obj == NULL)
		return ;
	v3f_set(&rot,
			ft_atoi(splitted[1]),
			ft_atoi(splitted[2]),
			ft_atoi(splitted[3]));
	trs_set_rot(obj->transform, &rot);
}

static void	parse_position(t_object *obj, char **splitted)
{
	t_vector3f	pos;

	if (obj == NULL)
		return ;
	v3f_set(&pos,
		ft_atoi(splitted[1]),
		ft_atoi(splitted[2]),
		ft_atoi(splitted[3]));
	trs_set_pos(obj->transform, &pos);
}

static void	*parse_item(char *path, char *split, t_bool path_type)
{
	t_object	*object;
	char		*tmp;

	tmp = path_type ? split : ft_strjoin(path, split);
	object = (t_object *)load(tmp);
	free(tmp);
	return (object);
}

static void	parse_multiply(char **splitted, t_object *obj)
{
	int		i;
	int		j;
	char		**splits[3];
	t_vector3f	vectmp;
	t_object	*tmp;

	i = 1;
	splits[0] = ft_strsplit(splitted[2], '/', NULL);
	splits[1] = ft_strsplit(splitted[3], '/', NULL);
	splits[2] = ft_strsplit(splitted[4], '/', NULL);
	while (i < ft_atoi(splitted[1]) + 1)
	{
		tmp = obj_new_init_mesh(get_core()->window, obj->mesh);
		j = 0;
		while (j < 3)
		{
			((t_vector3f *)tmp->transform)[j] = ((t_vector3f *)obj->transform)[j];
			v3f_set(&vectmp,
				strtod(splits[j][0], NULL) * i,
				strtod(splits[j][1], NULL) * i,
				strtod(splits[j][2], NULL) * i);
			v3f_add(((t_vector3f *)tmp->transform) + j, &vectmp);
			j++;
		}
		i++;
	}
}

void		*load_rs(char *path)
{
	int			fd;
	char		*line;
	char		**splitted;
	t_bool		path_type;
	t_object	*obj;

	obj = NULL;
	path_type = FALSE;
	if ((fd = open(path, O_RDONLY)) < 0)
		error_exit(ft_strjoin("COULDN'T FIND FILE AT : ", path));
	while (get_next_line(fd, &line) == 1)
	{
		splitted = ft_strsplit(line, ' ', NULL);
		if (ft_strequ(splitted[0], "paths-type:"))
			path_type = ft_strequ(splitted[1], "absolute");
		else if (ft_strequ(splitted[0], "path-object:"))
			obj = parse_item(path, splitted[1], path_type);
		else if (ft_strequ(splitted[0], "position:"))
			parse_position(obj, splitted);
		else if (ft_strequ(splitted[0], "rotation:"))
			parse_rotation(obj, splitted);
		else if (ft_strequ(splitted[0], "scale:"))
			parse_scale(obj, splitted);
		else if (ft_strequ(splitted[0], "multiply:"))
			parse_multiply(splitted, obj);
		free(line);
	}
	close(fd);
	return (obj);
}
