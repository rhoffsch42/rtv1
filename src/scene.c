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

void	get_scene(t_env *e, int ac, char **av)
{
	t_str	*lines;

	if (ac < 2)
		ft_errexit("Usage: rtv1 scene.yaml\n", YELLOW, BAD_ARGS);
	lines = ft_getfile(av[1]);
	remove_comments(lines, "#");
	remove_white_spaces(lines);
	lines = (t_str*)remove_list((t_void*)lines, is_empty, free_t_str);
	build_objects(e, lines, 0);

	// t_str	*ptr;
	// ptr = lines;
	// while (ptr)
	// {
	// 	ft_putendl(ptr->str);
	// 	ptr = ptr->next;
	// }
	// if (lines == NULL)
	// 	ft_putendl("null");
	// ft_putendl("dsds");
	// char *pttr;
	// pttr = YA_TITLE;
	// ft_putendl(pttr);
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
