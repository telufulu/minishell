/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/05 19:37:24 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
# include "libft.h"
# include "parser.h"

# include <unistd.h>
# include <stdio.h>				// printf, perror
# include <stdlib.h>			// malloc, free, exit, getenv
# include <sys/wait.h>			// wait, waitpid, wait3, wait4
# include <signal.h>			// signal, sigaction, kill
# include <sys/stat.h>			// stat, lstat, fstat
# include <dirent.h>			// opendir, readdir, closedir
# include <string.h>			// strerror
# include <errno.h>				// errno
# include <termios.h>			// tcsetattr, tcgetattr
# include <term.h>				// tgetent, tgetflag, tgetnum, tgetstr, tgoto
								// tputs
# include <readline/readline.h>	//add_history, readline 

/*******************************************************************************
 * Defines
 ******************************************************************************/
# define SHELL_NAME "minishell"
# define PROMPT "minishell$ "

// Params
# define PIPE	0x01
# define CMD	0x02
# define ARG	0x03
# define INFL	0x04
# define OUTFL	0x05
# define AMP	0x06
# define OPER	0x07

/*******************************************************************************
 * Structs
 ******************************************************************************/
typedef struct s_data
{
	char	*input;
	char	**params;
	char	*tokens;
	char	**env;
	int		index;
	int		exit_status;
}				t_data;

/*******************************************************************************
 * Files
 ******************************************************************************/
// main.c
void	good_exit(t_data *d);

// utils.c
void	check_term(char **envp);
void	init_shell(t_data *d, char **envp, char **argv, int argc);

// env.c
char	*get_env(char **env, char *var);
char	**init_env(char **envp);

#endif
