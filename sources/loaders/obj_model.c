/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_model.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 07:04:05 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/07 18:53:37 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

static	t_obj_index		*parse_index(char *token)
{
	int				i;
	char			**sub_tokens;
	t_obj_index		*obj_index;

	i = 0;
	obj_index = malloc(sizeof(t_obj_index));
	sub_tokens = rstd_strsplit(token, '/', NULL);
	obj_index->i[0] = -1;
	obj_index->i[1] = -1;
	obj_index->i[2] = -1;
	while (sub_tokens[i] != NULL)
	{
		obj_index->i[i] = rstd_atoi(sub_tokens[i]) - 1;
		free(sub_tokens[i++]);
	}
	free(sub_tokens);
	return (obj_index);
}

static void				parse_face_line(t_list *index, char **s)
{
	int			i;

	i = 0;
	while (i < 3)
	{
		list_push_back(index, parse_index(s[i + 1]));
		i++;
	}
	i = 0;
	while (s[i] != NULL)
		free(s[i++]);
	free(s);
}

static void				parse_coord(t_list *p, t_list *t, t_list *n, char **s)
{
	int		i;
	void	*parsed;

	i = 0;
	if (s[0][1] == '\0')
	{
		parsed = v3f_new(rstd_atof(s[1]), rstd_atof(s[2]), rstd_atof(s[3]));
		list_push_back(p, parsed);
	}
	else if (s[0][1] == 't')
	{
		parsed = v2f_new(rstd_atof(s[1]), rstd_atof(s[2]));
		list_push_back(t, parsed);
	}
	else if (s[0][1] == 'n')
	{
		parsed = v3f_new(rstd_atof(s[1]), rstd_atof(s[2]), rstd_atof(s[3]));
		list_push_back(n, parsed);
	}
	while (s[i] != NULL)
		free(s[i++]);
	free(s);
}

static t_obj_model		*obj_model_init(t_list *list[4])
{
	t_obj_model *ret;

	ret = malloc(sizeof(t_obj_model));
	ret->count = list[3]->count;
	ret->pos = list[0];
	ret->tex_coords = list[1];
	ret->normals = list[2];
	ret->indices = list[3];
	return (ret);
}

void					obj_model_delete(t_obj_model *m)
{
	list_delete_inner(m->pos, list_default_remove_functor);
	list_delete_inner(m->tex_coords, list_default_remove_functor);
	list_delete_inner(m->normals, list_default_remove_functor);
	list_delete_inner(m->indices, list_default_remove_functor);
	free(m);
}

t_obj_model				*obj_model_new(char *file)
{
	int				i;
	int				count;
	t_list			*lists[4];
	char			**lines;

	i = -1;
	while (++i < 4)
		lists[i] = list_new();
	if ((count = rstd_read_lines(file, &lines)) < 0)
		error_exit(rstd_strjoin("COULDN'T FIND FILE AT : ", file));
	i = 0;
	while (i < count)
	{
		if (lines[i][0] == 'v')
			parse_coord(lists[0], lists[1], lists[2],
						rstd_strsplit(lines[i], ' ', NULL));
		else if (lines[i][0] == 'f')
			parse_face_line(lists[3], rstd_strsplit(lines[i], ' ', NULL));
		free(lines[i++]);
	}
	free(lines);
	return (obj_model_init(lists));
}
