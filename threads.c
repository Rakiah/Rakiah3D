/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_loader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:30:57 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/25 15:20:38 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <r3d.h>

void	*cl_loader(char *path)
{
	char			*buffer;
	char			*tmp;
	char			*line;
	int			fd;
	t_task_dispatcher	*thread;

	if ((thread = malloc(sizeof(t_thread))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	if ((fd = open(path, O_WRONLY)) < 0)
		error_exit("NO .CL FILE");
	while (get_next_line(fd, &line) == 1)
	{
		tmp = buffer;
		buffer = ft_strjoin(buffer, line);
		free(tmp);
		free(line);
	}
}
