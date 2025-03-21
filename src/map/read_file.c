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

static int	get_height(char *file_name)
{
	char	*line;
	int		height;
	int		fd;

	height = 0;
	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		height++;
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

static int	get_width(char *file_name)
{
	char	*line;
	int		width;
	int		fd;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	if (line != NULL)
	{
		width = ft_count_words(line, ' ');
		free(line);
		line = NULL;
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	return (width);
}

static int	check_color(char *num, t_point *z_line)
{
	char	**value_and_color;

	value_and_color = ft_split(num, ',');
	if (!value_and_color)
		return (0);
	z_line->z_value = ft_atoi(value_and_color[0]);
	if (value_and_color[1])
		z_line->color_hex = ft_strdup(value_and_color[1]);
	if (!value_and_color[1])
	{
		if (z_line->z_value > 0)
			z_line->color_hex = ft_strdup("0xE80C8C");
		else
			z_line->color_hex = ft_strdup("0xFFFFFF");
	}
	free(value_and_color[0]);
	if (value_and_color[1])
		free(value_and_color[1]);
	free(value_and_color);
	return (1);
}

static void	fill_matrix(t_point *z_line, char *line)
{
	char	**nums;
	int		i;

	i = 0;
	nums = ft_split(line, ' ');
	if (!nums)
	{
		free(nums);
		return ;
	}
	while (nums[i] != NULL)
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
	free(line);
}

int	read_file(char *file_name, t_fdf *data)
{
	char	*line;
	int		fd;
	int		i;

	data->height = get_height(file_name);
	data->width = get_width(file_name);
	if (data->width <= 0 || data->height <= 0)
		return (0);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	data->z_matrix = (t_point *)malloc(sizeof(t_point) * data->height
			* data->width);
	if (!data->z_matrix)
		return (0);
	i = -1;
	while (++i < data->height)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		fill_matrix(&data->z_matrix[i * data->width], line);
	}
	line = get_next_line(fd);
	return (close(fd), 1);
}
