#include <rtv1.h>

static int	get_token_index(char **tokens, int tok_amount, char *str, char *sep)
{
	int		i;

	sep[0] = 0;
	i = 0;
	while (i < tok_amount)
	{
		if (ft_strcmp(tokens[i], str) == 0)
			break ;
		i++;
	}
	if (i >= tok_amount)
		error_yaml(str, YA_ERROR);
	sep[0] = YA_SEPARATOR;
	return (i);
}

static int	get_chart_index(t_env *e, char *str)
{
	int		i;

	i = 0;
	while (i < YA_CHART_AMT)
	{
		if (ft_strcmp(e->chart[i].key_name, str) == 0)
			return (i);
		i++;
	}
	error_yaml(str, YA_BAD_TOKEN);
	return (-1);
}

/* building_algo
** check avec get_chart_index :
** on execute direct la func si on a un token a une seule value
*/

t_str		*building_algo(t_env *e, t_str *ptr, char **tok, \
			int (**func)(t_env*, t_str*))
{
	// ft_putendl("_____________BUILDING ALGO_____________");
	int		i[2];
	int		tok_len;
	int		lines;
	char	*sep;

	tok_len = ft_tablen(tok);
	lines = tok[tok_len + 1][0];
	// ft_putnbr(tok_len);SPACE
	// ft_putnbr(lines);ENDL
	i[0] = 0;
	i[1] = -1;
	while (i[0] < lines)
	{
		// ft_putendl("_________________________________");
		// ft_putendl(ptr->str);
		// ft_putnbr(i[0]);ENDL
		if (i[1] == -1 && (sep = ft_strchr(ptr->str, YA_SEPARATOR)))
		{
			// ft_putstr("i[1]: ");
			i[1] = get_token_index(tok, tok_len, ptr->str, sep);
			// ft_putnbr(i[1]);SPACE
			if (e->chart[get_chart_index(e, tok[i[1]])].val_amount == 1)
				i[1] = (func[i[1]])(e, ptr);
			// ft_putnbr(i[1]);ENDL
			// ft_putendl("OK");
		}
		else if (!(i[1] >= 0 && i[1] < lines))
			error_yaml(ptr->str, YA_ERROR);
		else
			i[1] = func[i[1]](e, ptr);
		// ft_putendl("\t\t\tinc");
		i[0]++;
		ptr = (i[0] < lines) ? ptr->next : ptr;
	}
	return (ptr);
}
