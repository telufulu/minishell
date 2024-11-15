/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/15 18:14:45 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
 * Includes
 */
# include "libft.h"
# include <unistd.h>			// fork
# include <stdio.h>				// printf, perror
# include <stdlib.h>			// malloc, free, exit, getenv
# include <sys/wait.h>			// wait, waitpid, wait3, wait4
# include <signal.h>			// signal, sigaction, kill
# include <sys/stat.h>			// stat, lstat, fstat
# include <sys/ioctl.h>
# include <dirent.h>			// opendir, readdir, closedir
# include <string.h>			// strerror
# include <errno.h>				// errno
# include <termios.h>			// tcsetattr, tcgetattr
# include <term.h>				// tgetent, tgetflag, tgetnum
								//tgetstr, tgoto, tputs
# include <readline/readline.h>	//readline 
# include <readline/history.h>	//add_history

/*
 * Defines
 */
# define SHELL_NAME "minishell"
# define PROMPT "minishell-1.0$ "

/*
 * Structs
 */
typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;
typedef struct s_builts	t_builts;

typedef struct s_data
{
	t_token		**tokens;
	t_cmd		*cmd;
	t_builts	*builts;
	char		*input;
	char		**env;
	int			index;
	int			exit_status;
}				t_data;

/*
 * Files
 */
// main.c

// utils.c
void	check_term(char **envp);
t_data	*init_shell(t_data *d, char **envp, char **argv, int argc);
void	*free_tokens(t_token **tokens);
void	secure_free(void **ptr);
void	ft_shell_error(char *var, char *msg_error, int exit_status);

// env.c
char	*get_env(char **env, char *var);
char	**init_env(char **envp);

// signals.c
void	handle_sigint(int sig);
void	signal_handlers(void);
void	handle_empty_string(t_data *d);

// signals_utils.c
void	set_signal_handler(int signum, void (*handler)(int));
void	reset_signal_handlers_to_default(void);
void	ignore_signals_in_parent(void);
void	restore_parent_signal_handlers(void);
void	check_error(int retval, const char *msg);

#endif
