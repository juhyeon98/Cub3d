/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:46:59 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/10 15:28:50 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_line(int const fd)
{
	static char	*remain;
	char		*ret;
	char		buff[BUFF_SZ + 1];
	int			buff_len;

	while (not_contain_nl(remain))
	{
		buff_len = read(fd, buff, BUFF_SZ);
		if (buff_len == 0 && !remain)
			return (NULL);
		if (buff_len == 0 && *remain)
			break ;
		else if ((buff_len < 0) || (buff_len == 0 && !*remain))
		{
			if (remain)
				free(remain);
			return (NULL);
		}
		buff[buff_len] = '\0';
		remain = merge(remain, buff);
	}
	ret = extract(remain);
	organize(remain);
	return (ret);
}

int	not_contain_nl(char const *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str == '\n')
			return (0);
		str++;
	}
	return (1);
}

char	*merge(char *const s1, char const *const s2)
{
	char	*ret;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1)
	{
		ret = ft_strdup(s2);
		if (!ret)
			print_error(E_ALLOC);
	}
	else
	{
		s1_len = ft_strlen(s1);
		s2_len = ft_strlen(s2);
		ret = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
		if (!ret)
			print_error(E_ALLOC);
		ft_strlcpy(ret, s1, s1_len + 1);
		ft_strlcat(ret, s2, s1_len + s2_len + 1);
		free(s1);
	}
	return (ret);
}

char	*extract(char const *const str)
{
	char	*ret;
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	len++;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		print_error(E_ALLOC);
	ft_strlcpy(ret, str, len + 1);
	return (ret);
}

void	organize(char *const str)
{
	size_t	len;
	size_t	index;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	index = 0;
	while (str[index + len])
	{
		str[index] = str[index + len];
		index++;
	}
	str[index] = '\0';
}
