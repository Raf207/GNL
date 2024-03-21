/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:18:38 by rafnasci          #+#    #+#             */
/*   Updated: 2024/03/21 16:47:47 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_copyline(char *str, t_list *list)
{
	int	i;
	int	j;

	if (!list)
		return ;
	j = 0;
	while (list)
	{
		i = -1;
		while (list->buffer_str[++i])
		{
			str[j++] = list->buffer_str[i];
			if (list->buffer_str[i] == '\n')
			{
				str[j] = '\0';
				return ;
			}
		}
		list = list->next;
	}
	str[j] = '\0';
}

char	*ft_getline(t_list	*list)
{
	int		len_line;
	char	*new_line;

	len_line = ft_countlen(list);
	new_line = malloc (sizeof(char) * (len_line + 1));
	if (!new_line)
		return (NULL);
	ft_copyline(new_line, list);
	return (new_line);
}

int	ft_find_nl(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = -1;
		while (list->buffer_str[++i] && i < BUFFER_SIZE)
			if (list->buffer_str[i] == '\n')
				return (1);
		list = list->next;
	}
	return (0);
}

int	ft_createlist(t_list **list, int fd)
{
	char	*buffer;
	int		counter;

	while (!ft_find_nl(*list))
	{
		buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (ft_cleanlist(list, NULL), 1);
		counter = read(fd, buffer, BUFFER_SIZE);
		if (counter == 0)
			return (free(buffer), 0);
		buffer[counter] = '\0';
		ft_addlist(list, buffer);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*str;
	char			*last;

	if (fd < 0 || fd > OPEN_MAX || read(fd, &str, 0) < 0 || BUFFER_SIZE < 0
		|| BUFFER_SIZE > INT32_MAX - 1)
		return (ft_cleanlist(&list, NULL), NULL);
	if (ft_createlist(&list, fd) == 1)
		return (NULL);
	if (!list)
		return (NULL);
	str = ft_getline(list);
	if (!str)
		return (ft_cleanlist(&list, NULL), NULL);
	last = ft_lastpart(list);
	if (!last)
		return (ft_cleanlist(&list, NULL), free(str), NULL);
	ft_cleanlist(&list, last);
	return (str);
}

// #include <fcntl.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*str;
// 	int		i;

// 	i = 0;
// 	fd = open("text.txt", O_RDONLY);
// 	str = get_next_line(fd);
// 	while (str)
// 	{
// 		str = get_next_line(fd);
// 		printf("ligne %d: %s\n", ++i, str);
//  		free(str);
//  	}
//  }