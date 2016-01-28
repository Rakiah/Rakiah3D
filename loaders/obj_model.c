/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_model.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 07:04:05 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/18 18:20:16 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"
#include "get_next_line.h"

static	t_obj_index		*parse_index(char *token)
{
	int			i;
	t_obj_index		*obj_index;
	char			**sub_tokens;

	i = 0;
	if ((obj_index = malloc(sizeof(t_obj_index))) == NULL)
		error_exit("MEMORY ALLOCAITON FAILED");
	sub_tokens = ft_strsplit(token, '/', NULL);
	obj_index->i[0] = -1;
	obj_index->i[1] = -1;
	obj_index->i[2] = -1;
	while (sub_tokens[i] != NULL)
	{
		obj_index->i[i] = ft_atoi(sub_tokens[i]) - 1;
		free(sub_tokens[i++]);
	}
	free(sub_tokens);
	return (obj_index);
}

static void				parse_face_line(t_list *index, char **split)
{
	int			i;

	i = 0;
	while (i < 3)
	{
		list_push_back(index, parse_index(split[i + 1]));
		i++;
	}
}

static void				parse_coord(t_list *p,
							t_list *t,
							t_list *n,
							char **split)
{
	void *parsed;

	if (split[0][1] == '\0')
	{
		parsed = v4f_new(strtod(split[1], NULL),
				strtod(split[2], NULL),
				strtod(split[3], NULL), 1.0f);
		list_push_back(p, parsed);
	}
	else if (split[0][1] == 't')
	{
		parsed = v2f_new(strtod(split[1], NULL),
				strtod(split[2], NULL));
		list_push_back(t, parsed);
	}
	else if (split[0][1] == 'n')
	{
		parsed = v3f_new(strtod(split[1], NULL),
				strtod(split[2], NULL),
				strtod(split[3], NULL));
		list_push_back(n, parsed);
	}
}

static t_obj_model		*obj_model_init(t_list *list[4])
{
	t_obj_model *ret;

	if ((ret = malloc(sizeof(t_obj_model))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	ret->count = list[3]->count;
	ret->pos = list[0];
	ret->tex_coords = list[1];
	ret->normals = list[2];
	ret->index = list[3];
	return (ret);
}

t_obj_model				*obj_model_new(int fd)
{
	int			i;
	char			*line;
	t_list			*lists[4];

	i = -1;
	while (++i < 4)
		lists[i] = list_new(sizeof(void *));
	while (get_next_line(fd, &line) == 1)
	{
		if (*line == 'v')
			parse_coord(lists[0],
					lists[1],
					lists[2],
					ft_strsplit(line, ' ', NULL));
		else if (*line == 'f')
			parse_face_line(lists[3], ft_strsplit(line, ' ', NULL));
		free(line);
	}
	return (obj_model_init(lists));
}
