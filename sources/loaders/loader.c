/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 18:28:50 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/06 18:53:46 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_loader	*find_loader(char *ext)
{
	t_list		*loaders;
	t_loader	*iterator;

	if (ext == NULL)
		error_exit("TRYING TO LOAD A FILE WITHOUT EXTENSION");
	ext++;
	loaders = get_core()->loaders;
	list_set_start(loaders);
	while ((iterator = list_next(loaders)) != NULL)
		if (ft_strequ(ext, iterator->extension))
			return (iterator);
	error_exit(ft_strjoin("NO LOADER FOUND FOR EXTENSION : ", ext));
	return (NULL);
}

void		*load(char *path)
{
	t_loader *loader;

	loader = find_loader(ft_strchr(path, '.'));
	return (loader->method(path));
}
