/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 01:47:24 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/12 20:05:19 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINGS_H
# define BUILTINGS_H

/******************************************************************************
 * Includes
 *****************************************************************************/
# include "lexer.h"		// t_cmd
# include <unistd.h>	// execve

/******************************************************************************
 * Includes
 *****************************************************************************/
# define N_BUILTINGS 7

/******************************************************************************
 * Structs
 *****************************************************************************/
typedef struct s_builts
{
	char	*cmd;
	int		(*built)(t_cmd *, char **env);
	char	**env;
}				t_builts;

/******************************************************************************
 * Files
 *****************************************************************************/
// builtings.c
t_builts	*init_builtings(t_builts *builtings, char **env);
int			my_execve(t_cmd *c, t_builts *builts, char **env);

// builts_utils.c
t_bool		is_built(t_builts *builts, char *cmd);
int			ft_built_error(char *var, char *msg_error, int exit_status);
char		*reset_var(t_cmd *c, char *var, char *new_value, char **env);

// echo_built.c
int			echo_built(t_cmd *c, char **env);

// cd_built.c
int			cd_built(t_cmd *c, char **env);

// basic_builtings.c
int			exit_built(t_cmd *c, char **env);
int			env_built(t_cmd *c, char **env);
int			pwd_built(t_cmd *c, char **env);

//unset_built.c
int			unset_built(t_cmd *c, char **env);
int			find_arg(char **env, char *var);

//export_built.c
int			export_built(t_cmd *c, char **env);
char		*new_var(char *input, int len);
char		*get_var(char *arg);
t_bool		is_quote(char c);

// heredoc._built.c
int			handle_heredoc(t_cmd *cmd);
void		setup_heredoc_signals(void);
void		restore_signals(void);

#endif
