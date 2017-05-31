#include <rtv1.h>

char	*ft_strtrim_extended(const char *s)
{
	int		i[3];
	char	*dest;

	i[0] = 0;
	while (s[i[0]] == '\v' || s[i[0]] == '\r' || s[i[0]] == '\f' \
		|| s[i[0]] == 32 || s[i[0]] == '\n' || s[i[0]] == '\t')
		i[0]++;
	i[1] = ft_strlen(s) - 1;
	while (s[i[1]] == '\v' || s[i[1]] == '\r' || s[i[1]] == '\f' \
		|| s[i[1]] == 32 || s[i[1]] == '\n' || s[i[1]] == '\t')
		i[1]--;
	i[1] = (i[1] == -1) ? 0 : i[1];
	if (i[1] - i[0] < 0)
		return (ft_strdup("\0"));
	if (!(dest = (char*)malloc(sizeof(char) * (i[1] - i[0] + 2))))
		ft_errexit("Error : malloc fail\n", RED, MALLOC_FAIL);
	i[2] = 0;
	while (i[1] - i[0] >= 0)
	{
		dest[i[2]] = s[i[0]];
		i[0]++;
		i[2]++;
	}
	dest[i[2]] = 0;
	return (dest);
}
