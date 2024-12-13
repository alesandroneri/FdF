#include "libft.h"

int		is_base(char c, int base)
{
	char low_base[17] = "0123456789abcdef";
	char upper_base[17] = "0123456789ABCDEF";

	while (base--)
		if (low_base[base] == c || upper_base[base] == c)
			return (1);
	return (0);
}

int		valid_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

int		ft_atoi_base(const char *str, int str_base)
{
	int result;
	int sign;
    int i;

    i = 0;
	result = 0;
    sign = 1;
	if (!str || *str == '\0')
		return (0);
	if (str_base < 2 || str_base > 16)
		return (0);
	while (str[i] <= 32 || str[i] == 127)
		i++;
    if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
            i = i + 2;
	while (str[i] == '-' || str[i] == '+')
    {
            if (str[i] == '-')
                sign *= -1;
            if (str[i + 1] == '-' || str[i + 1] == '+')
                return (0); 
        i++;
    }
	while (is_base(str[i], str_base))
		result = (result * str_base) + valid_value(str[i++]);
	return (result * sign);
}

/*#include <stdio.h>

int main(void)
{
    printf("%d", ft_atoi_base("0x810202", 16));
    return (0);
}*/