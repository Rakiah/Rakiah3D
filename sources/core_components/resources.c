/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/05 15:52:39 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"
#include <fcntl.h>
#include <get_next_line.h>

void		resources_load()
{
	int			fd;
	char		*line;
	char		**split;

	if ((fd = open(RESOURCES_PATH, O_RDONLY)) < 0)
		error_exit(ft_strjoin("COULDN'T FIND RESOURCE FILE AT : ", RESOURCES_PATH));
	while (get_next_line(fd, &line) == 1)
	{
		split = ft_strsplit(line, ' ', NULL);
		resources_add(split[0], load(split[1]));
		ft_delete_tab((void **)split, 2);
		free(line);
	}
}

void		resources_add(char *name, void *data)
{
	t_resource *resource;

	resource = malloc(sizeof(t_resource));
	resource->name = ft_strdup(name);
	resource->data = data;
	list_push_back(get_core()->resources, resource);
	ft_putstr("Included resource : ");
	ft_putendl(name);
}

void		*resources_find(char *name)
{
	t_list		*resources;
	t_resource	*it;

	resources = get_core()->resources;
	list_set_start(resources);
	while ((it = list_next(resources)) != NULL)
		if (ft_strcmp(name, it->name) == 0)
			return (it->data);
	return (NULL);
}
