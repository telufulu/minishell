/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/02 02:05:43 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
 * Includes
 */
# include <unistd.h>		// write
# include <stddef.h>		// size_t
# include <stdio.h>			// printf, perror
# include <stdlib.h>		// malloc, free, exit, getenv
# include <sys/wait.h>		// wait, waitpid, wait3, wait4
# include <signal.h>		// signal, sigaction, kill
# include <sys/stat.h>		// stat, lstat, fstat
# include <dirent.h>		// opendir, readdir, closedir
# include <string.h>		// strerror
# include <errno.h>			// errno
# include <termios.h>		// tcsetattr, tcgetattr
# include <term.h>			// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h>	//readline, rl_replace_line, rl_redisplay
								//rl_on_new_line
# include <readline/history.h>	//add_history

/*
 * Defines
 */
# define SHELL_NAME "minishell"
# define PROMPT "minishell-1.0$ "

/*
 * Structs
 */
typedef struct s_data
{
	char	*input;
	char	**params;
	char	*tokens;
	char	**env;
	int		index;
	int		exit_status;
}				t_data;

/*
 * Files
 */
// main.c

// env.c
char	*get_env(char **env, char *var);
char	**init_env(char **envp);

#endif
