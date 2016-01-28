#ifndef FT_STRUCTS_H
# define FT_STRUCTS_H

#include "libft.h"

struct		s_array
{
	void	*array;
	size_t	element_size;
	size_t	bytes_size;
	size_t	count;
};

struct		s_node
{
	void	*data;
	t_node	*next;
	t_node	*prev;
};

struct		s_list
{
	t_node	*start;
	t_node	*end;
	t_node	*iterator;
	size_t	count;
	size_t	elem_size;
	int	current;
};

#endif
