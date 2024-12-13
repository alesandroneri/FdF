/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:08:52 by aneri-da          #+#    #+#             */
/*   Updated: 2024/10/08 20:18:18 by aneri-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>


size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *nptr);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_atoi_base(const char *str, int str_base);
int	ft_isdigit(int c);
int	ft_atoi_hexa(const char *str);

/*
ft_printf functions.
*/
int		ft_put_ptr(void	*ptr);
int		ft_putchar_count(char c);
int		ft_putstr_count(char *str);
int		ft_putnbr_count(int nb);
int		ft_putnbr_base_count(unsigned int nbr, char *base);
int		ft_printf(const char *format, ...);
/*
gnl functions.
*/
char	*get_next_line(int fd);

#endif
