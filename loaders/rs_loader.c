/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_loader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 07:01:35 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/18 18:12:12 by bkabbas          ###   ########.fr       */
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

static void	*parse_item(t_env *core, char *path, char *split, t_bool path_type)
{
	t_object	*object;
	char		*tmp;

	tmp = path_type ? split : ft_strjoin(path, split);
	object = (t_object *)load(core, tmp);
	free(tmp);
	return (object);
}

void		*load_rs(t_env *core, char *path)
{
	int			fd;
	t_bool		path_type;
	char		*line;
	char		**splitted;
	t_object	*obj;

	if ((fd = open(path, O_RDONLY)) < 0)
		error_exit(ft_strjoin("COULDN'T FIND FILE AT : ", path));
	while (get_next_line(fd, &line) == 1)
	{
		splitted = ft_strsplit(line, ' ', NULL);
		if (ft_strequ(splitted[0], "paths-type:"))
			path_type = ft_strequ(splitted[1], "absolute");
		else if (ft_strequ(splitted[0], "path-object:"))
			obj = parse_item(core, path, splitted[1], path_type);
		else if (ft_strequ(splitted[0], "position:"))
			parse_position(obj, splitted);
		else if (ft_strequ(splitted[0], "rotation:"))
			parse_rotation(obj, splitted);
		else if (ft_strequ(splitted[0], "scale:"))
			parse_scale(obj, splitted);
		free(line);
	}
	close(fd);
	return (obj);
}
