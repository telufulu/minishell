/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:07:53 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/18 00:05:52 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
/*******************************************************************************
 * Structs
 ******************************************************************************/
typedef struct s_cmd
{
	t_data	*data;
	char	**params;
	char	*tokens;
	int		infd;
	int		outfd;
	char	**argv;
	char	*path;
}				t_cmd;


/*******************************************************************************
 * Files
 ******************************************************************************/
// executor.c
void	executor(t_data *d);

// create_cmds.c
int		open_infiles(t_cmd *d, int in);
int		open_outfiles(t_cmd *d, int out);
char	**get_ex_args(char **params, char *tok);
t_cmd	*init_cmd(t_data *d, size_t i);
t_cmd	**create_cmds(size_t nb_cmds, t_data *d);

// executor_utils.c
size_t	count_cmds(char *tokens);
size_t	count_args(char *tokens);
void	mv_params(char *tokens, char **params, size_t i, t_cmd *c);
size_t	next_pipe(char *tokens);
#endif
