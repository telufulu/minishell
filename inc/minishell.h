/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/10/16 19:24:41 by aude-la-         ###   ########.fr       */
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

typedef struct s_data
{
	t_token	**tokens;
	t_cmd	*cmd;
	char	*input;
	char	**env;
	int		index;
	int		exit_status;
}				t_data;

/*
 * Files
 */
// main.c
//void	close_fds(t_cmd *cmd);
void	clean_loop(t_data *d);
void	handle_input(t_data *d);

// utils.c
void	check_term(char **envp);
t_data	*init_shell(t_data *d, char **envp, char **argv, int argc);
void	*free_tokens(t_token **tokens);
void	print_tokens(t_token **tokens, int fd);
void	ft_shell_error(char *var, char *msg_error);

// env.c
char	*get_env(char **env, char *var);
char	**init_env(char **envp);

// signals.c
void	handle_sigint(int sig);
void	signal_handlers(void);

#endif
