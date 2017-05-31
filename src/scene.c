/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 18:17:25 by rhoffsch          #+#    #+#             */
/*   Updated: 2017/05/25 18:17:27 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static t_str		*get_file(char *filename)
{
	t_str	*ptr[3];
	char	*buf;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		ft_errexit("Error: open", RED, OPEN_FAIL);
	ptr[2] = NULL;
	while (get_next_line(fd, &buf) > 0)
	{
		if ((ptr[0] = (t_str*)malloc(sizeof(t_str))) == NULL)
			ft_errexit("Error: malloc", RED, MALLOC_FAIL);
		ptr[0]->str = ft_strdup(buf);
		ptr[0]->next = NULL;
		if (ptr[2] == NULL)
		{
			ptr[1] = ptr[0];
			ptr[2] = ptr[0];
		}
		else
		{
			ptr[1]->next = ptr[0];
			ptr[1] = ptr[1]->next;
		}
	}
	return (ptr[2]);
}

static void			remove_comments(t_str *ptr)
{
	char	*ptr1;

	while (ptr)
	{
		ptr1 = ft_strchr(ptr->str, YA_COMMENT);
		if (ptr1)
			ptr1[0] = 0;
		ptr = ptr->next;
	}
}

void	remove_white_spaces(t_str *ptr)
{
	char	*str;

	while (ptr)
	{
		str = ptr->str;
		ptr->str = ft_strtrim_extended(ptr->str);
		free(str);
		ptr = ptr->next;
	}
}

void	get_scene(t_env *e, int ac, char **av)
{
	t_str	*lines;

	if (ac < 2)
		ft_errexit("Usage: rtv1 scene.yaml\n", YELLOW, BAD_ARGS);
	lines = get_file(av[1]);
	remove_comments(lines);
	remove_white_spaces(lines);
	lines = remove_list(lines, is_empty);
	build_objects(e, lines);


	t_str	*ptr;
	ptr = lines;
	while (ptr)
	{
		ft_putendl(ptr->str);
		ptr = ptr->next;
	}
	if (lines == NULL)
		ft_putendl("null");
	ft_putendl("dsds");
	char *pttr;
	pttr = YA_TITLE;
	ft_putendl(pttr);
	// int i = 0;
	// while (i < YA_CHART_AMT)
	// {
	// 	ft_putendl("_______");
	// 	ft_putendl(e->chart[i].key_name);
	// 	ft_putnbrendl(e->chart[i].val_amount);
	// 	ft_putendl((e->chart[i].val_type == YA_CHAR) ? "text" : "numbers");
	// 	i++;
	// }
}
