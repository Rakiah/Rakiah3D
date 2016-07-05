/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ro_loader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 07:01:35 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/05 15:47:28 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"
#include <get_next_line.h>
#include <fcntl.h>

/*static t_object		*parse_object(char *path, t_bool path_type, char *split)*/
/*{*/
	/*t_object	*object;*/
	/*char		*tmp;*/

	/*tmp = path_type ? split : ft_strjoin(path, split);*/
	/*object = obj_new_init_mesh((t_mesh *)load(tmp));*/
	/*free(tmp);*/
	/*return (object);*/
/*}*/

/*static t_texture	*parse_texture(char *path, t_bool path_type, char *split)*/
/*{*/
	/*t_texture	*texture;*/
	/*char		*tmp;*/

	/*tmp = path_type ? split : ft_strjoin(path, split);*/
	/*texture = (t_texture *)load(tmp);*/
	/*free(tmp);*/
	/*return (texture);*/
/*}*/

/*static t_object		*parse_file(char *path, int fd)*/
/*{*/
	/*t_object	*object;*/
	/*t_material	*material;*/
	/*t_bool		path_type;*/
	/*char		**split;*/
	/*char		*line;*/

	/*path_type = FALSE;*/
	/*object = NULL;*/
	/*material = mat_new(NULL);*/
	/*while (get_next_line(fd, &line) == 1)*/
	/*{*/
		/*split = ft_strsplit(line, ' ', NULL);*/
		/*if (ft_strcmp(split[0], "paths-type:") == 0)*/
			/*path_type = ft_strcmp(split[1], "absolute") == 0 ? TRUE : FALSE;*/
		/*else if (ft_strcmp(split[0], "path-texture:") == 0)*/
			/*material->texture = parse_texture(path, path_type, split[1]);*/
		/*else if (ft_strcmp(split[0], "path-object:") == 0)*/
			/*object = parse_object(path, path_type, split[1]);*/
		/*free(line);*/
	/*}*/
	/*object->mesh->material = material;*/
	/*return (object);*/
/*}*/

void				*load_ro(char *path)
{
	(void)path;
	return (NULL);
	/*int		fd;*/

	/*if ((fd = open(path, O_RDONLY)) < 0)*/
		/*error_exit(ft_strjoin("COULDN'T FIND FILE AT : ", path));*/
	/*return (parse_file(path, fd));*/
}
