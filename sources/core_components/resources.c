/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/09 19:10:16 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

void		resources_load(void)
{
	int			i;
	int			count;
	char		**lines;
	char		**split;

	if ((count = rstd_read_lines(RESOURCES_PATH, &lines)) < 0)
		error_exit(rstd_strjoin("NO RESOURCE FILE AT : ", RESOURCES_PATH));
	i = 0;
	while (i < count)
	{
		if (lines[i][0] != '\0')
		{
			split = rstd_strsplit(lines[i], ' ', NULL);
			resources_add(split[0], load(split[1]));
			rstd_delete_tab((void **)split, 2);
		}
		free(lines[i++]);
	}
	free(lines);
}

void		resources_add(char *name, void *data)
{
	t_resource *resource;

	resource = malloc(sizeof(t_resource));
	resource->name = rstd_strdup(name);
	resource->data = data;
	list_push_back(get_core()->resources, resource);
	rstd_putstr("Included resource : ");
	rstd_putendl(name);
}

void		*resources_find(char *name)
{
	t_list		*resources;
	t_resource	*it;

	resources = get_core()->resources;
	list_set_start(resources);
	while ((it = list_next(resources)) != NULL)
		if (rstd_strcmp(name, it->name) == 0)
			return (it->data);
	return (NULL);
}
