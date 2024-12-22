/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:39:36 by aneri-da          #+#    #+#             */
/*   Updated: 2024/12/22 17:39:39 by aneri-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../fdf.h"

int	ft_count_words(char const *str, char sep)
{
	int	count;
	int	word;
	int	i;

	count = 0;
	word = 0;
	i = 0;
	while (str != NULL && str[i] != '\0')
	{
		if (str[i] != sep && word == 0)
		{
			count++;
			word = 1;
		}
		else if (str[i] == sep)
			word = 0;
		i++;
	}
	return (count);
}
