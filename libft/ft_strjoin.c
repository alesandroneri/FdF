/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:05:27 by aneri-da          #+#    #+#             */
/*   Updated: 2024/10/08 16:04:22 by aneri-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	join = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (join == NULL)
	{
		free(s1);
		return (NULL);
	}
	while (s1[++i] != '\0')
		join[i] = s1[i];
	while (s2[j] != '\0')
		join[i++] = s2[j++];
	join[i] = '\0';
	return (join);
}
/*#include <stdio.h>
int	main(int ac, char **av)
{
	char	*str;

	str = ft_strjoin(av[1], av[2]);
	if (ac == 3)
	{
		if (str != NULL)
		{
			printf("%s\n", str);
			free(str);
		}
	}
	return (0);
}*/
