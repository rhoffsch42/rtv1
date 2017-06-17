#include <rtv1.h>

static char    *strtrim_atof(char *str)
{
  int i;
  int p;

  p = 0;
  i = 0;
  if (str[i] == '-' || str[i] == '+')
    i++;
  if (str[i] == '.')
  {
    i++;
    p++;
  }
  while (ft_isdigit(str[i]) == 1)
  {
    i++;
    if (str[i] == '.' && p == 0)
    {
      i++;
      p++;
    }
  }
  str[i] = 0;
  return (str);
}

float           ft_atof(char *s)
{
  char  *sep;
  char  *str;
  float res[2];
  int   i;
  int   len;

  str = ft_strtrim_extended(s);
  str = strtrim_atof(str);
  if ((sep = ft_strchr(str, '.')) != NULL)
    sep[0] = 0;
  i = (str[0] == '-' || str[0] == '+') ? 1 : 0;
  len = ft_strlen(str);
  res[0] = 0;
  res[1] = 0;
  while (i < len)
    res[0] = (float)(10 * (int)res[0] + str[i++] - 48);
  if (sep)
  {
    i++;
    // changer le while en while (isdigit() == 1) et enelver strtrim_atof ?
    while (str[i] != 0)
      res[1] = (float)(10 * (int)res[1] + str[i++] - 48);
    res[0] += (res[1] / powf(10, ft_strlen(sep + 1)));
  }
  res[0] = (str[0] == '-') ? -res[0] : res[0];
  return (res[0]);
}
