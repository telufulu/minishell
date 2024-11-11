/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:23:04 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/11 15:58:31 by aude-la-         ###   ########.fr       */
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
	char			*cmd;
	char			*path;
	char			**ex_argv;
	char			*infd;
	char			*outfd;
	char			*heredoc;
	int				heredoc_fd;
	int				index;
	t_token			**input;
	t_data			*data;
	struct s_cmd	*next;
}				t_cmd;

/*******************************************************************************
 * Files
 ******************************************************************************/
// lexer.c
t_token	**next_cmd(t_token **tokens, t_cmd *c);
void	main_lexer(t_data *d, t_token **tokens);

// cmd_utils.c
t_cmd	*last_cmd(t_cmd *c);
t_cmd	*new_cmd(void);
t_cmd	*add_cmd(t_data *d);
size_t	num_cmd(t_token **tokens);
int		is_token(t_token **tokens, t_type type);

// init_lexer.c
char	*get_cmd(t_token **tokens);
char	**split_path(char **env);
char	*get_path(char **sp_path, char *cmd);
char	*get_fd(t_token **tokens, t_type tp);
char	*get_heredoc(t_token **tokens);

#endif
