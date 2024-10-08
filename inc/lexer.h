/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:23:04 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/10 20:02:18 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
# include "minishell.h"	//t_data, t_token
# include "parser.h"	// t_type

/*******************************************************************************
 * Structs
 ******************************************************************************/
typedef struct s_cmd
{
	int				index;
	char			*cmd;
	char			*path;
	int				infd;
	int				outfd;
	struct s_cmd	*next;
}				t_cmd;

/*******************************************************************************
 * Files
 ******************************************************************************/
// lexer.c
t_token	**next_cmd(t_token **tokens);
void	main_lexer(t_data *d, t_token **tokens);

// cmd_utils.c
t_cmd	*last_cmd(t_cmd *c);
t_cmd	*new_cmd(void);
t_cmd	*add_cmd(t_data *d);
size_t	num_cmd(t_token **tokens);

// lexer_utils.h
char	*get_cmd(t_token **tokens);
char	**split_path(char **env);
char	*get_path(char **sp_path, char *cmd);
void	open_fd(int *fd, t_token **tokens, t_type tp);
#endif
