/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:07:43 by rafnasci          #+#    #+#             */
/*   Updated: 2023/11/21 13:17:37 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_list
{
	char			*buffer_str;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
int		ft_createlist(t_list **list, int fd);
t_list	*ft_lastnode(t_list *list);
void	ft_addlist(t_list **list, char *str);
int		ft_find_nl(t_list *list);
char	*ft_getline(t_list	*list);
int		ft_countlen(t_list *list);
void	ft_copyline(char *str, t_list *list);
char	*ft_lastpart(t_list *list);
void	ft_cleanlist(t_list **list, char *last);

#endif