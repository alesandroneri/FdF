/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:19:55 by aneri-da          #+#    #+#             */
/*   Updated: 2024/11/26 15:48:47 by aneri-da         ###   ########.fr       */
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
/*
Pegar altura da imagem.
*/
int	get_height(char *file_name)
{
	ft_printf("START - get_height\n");
	char	*line;
	int	height;
	int	fd;
	
	height = 0;
	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return (-1);
	while ((line = get_next_line(fd)) != NULL)
	{
		height++;
		free(line);
		line = NULL;
	}
	close(fd);
	ft_printf("END - get_height\n");
	return (height);
}
/*
Pegar largura da imagem.
*/
int	get_width(char *file_name)
{
	ft_printf("START - get_width\n");
	char	*line;
	int	width;
	int	fd;

	fd = open(file_name, O_RDONLY, 0);
	line = get_next_line(fd);
	if (line != NULL)
	{
		width = ft_count_words(line, ' ');
		free(line);
		line = NULL;
	}
	while ((line = get_next_line(fd)) != NULL)
		free(line);
	close(fd);
	ft_printf("END - get_width\n");
	return (width);
}

int check_color(char *num, t_point *z_line)
{
	ft_printf("START - check_color\n");
	char **value_and_color;

    value_and_color = ft_split(num, ',');
    if (!value_and_color)
        return (0);
    // Se a split retornou apenas um elemento, trate isso como um caso especial
    if (value_and_color[1] == NULL)
	{
        z_line->z_value = ft_atoi(value_and_color[0]); // Converta o valor
        z_line->color_hex = ft_strdup("0xFFFFFF"); // Cor padrão
    }
	else
	{
        z_line->z_value = ft_atoi(value_and_color[0]);
        z_line->color_hex = ft_strdup(value_and_color[1]);
    }
    // Libere a memória alocada
    free(value_and_color[0]);
    if (value_and_color[1])
        free(value_and_color[1]);
    free(value_and_color);
	ft_printf("END - check_color\n");
    return (1); // Retorne sucesso
}

/*
Preencher a matrix bidimensasional com os numeros para que possamos ler o mapa adequadamente.
*/
void	fill_matrix(t_point *z_line, char *line)
{
	ft_printf("START - fill_matrix\n");
	char	**nums;
	int		i;
	char	**value_and_color;
	
	i = 0;
	nums = ft_split(line, ' ');
	if (!nums)
	{
		free(line);
		free(nums);
		return ;
	}
	while(nums[i])
	{
		if (!check_color(nums[i], &z_line[i]))
		{
			free(nums[i]);
			continue ;
		}
		free(nums[i]);
		i++;
	}
	free(nums);
	ft_printf("END - fill_matrix\n");
}
/*
Ler o arquivo corretamaente.
*/
void	read_file(char *file_name, t_fdf *data)
{
	ft_printf("START - read_file\n");
	char	*line;
	int	fd;
	int	i;

	data->height = get_height(file_name);
	data->width = get_width(file_name);
	if (data->width <= 0 || data->height <= 0)
		return ;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return ;
	data->z_matrix = (t_point *)malloc(sizeof(t_point) * (data->height * data->width));
	if (!data->z_matrix)
		return ;
	i = 0;
	while (i < data->height)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		fill_matrix(&data->z_matrix[i * data->width], line);
		free(line);
		i++;
	}
	close(fd);
	ft_printf("END - read_file\n");
}
