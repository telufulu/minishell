/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:07:53 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/26 18:24:28 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
# include "minishell.h" // t_data

/*******************************************************************************
 * Structs
 ******************************************************************************/
typedef struct s_cmd
{
	t_data	*data;
	int		infd;
	int		outfd;
	char	**argv;
	char	*path;
}				t_cmd;


/*******************************************************************************
 * Files
 ******************************************************************************/
// executor.c
void	execute_cmd(t_data *d, size_t i);
t_cmd	*init_cmd(t_data *d, size_t n);
void	executor(t_data *d);

// get_path.c
char	*get_path(char *cmd, char **env);

// get_ex_args.c
char	**get_ex_args(char **params, char *tok);
char	**next_params(char **params, size_t n);

// executor_utils.c
int		open_infiles(t_data *d, int in);
int		open_outfiles(t_data *d, int out);
size_t	count_cmds(char *tokens);
size_t	count_args(char *tokens);
size_t	next_pipe(char *tokens);

#endif
