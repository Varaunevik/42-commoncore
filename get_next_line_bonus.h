/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:56:06 by vaunevik          #+#    #+#             */
/*   Updated: 2024/03/02 13:40:16 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_list
{
	char			content[BUFFER_SIZE + 1];
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*read_to_node(int fd, int *byte_read);
int		find_newline(t_list *node);
void	create_list(t_list **list, int fd);
void	list_to_line(t_list *byte_list, char **line);
void	create_line(t_list **byte_buff, char **line, int i);
void	clean_list(t_list **list);
void	pass_over_node(t_list *list, t_list **pass_over);
void	free_list(t_list *list);
int		check_line(char **line, t_list *list);

#endif
