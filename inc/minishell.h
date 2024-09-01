/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:07 by telufulu          #+#    #+#             */
/*   Updated: 2024/09/01 10:56:46 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
 * Includes
 */
# include "libft.h"
# include <unistd.h>    
# include <stdio.h>      // printf, perror
# include <stdlib.h>     // malloc, free, exit, getenv
# include <sys/wait.h>   // wait, waitpid, wait3, wait4
# include <signal.h>     // signal, sigaction, kill
# include <sys/stat.h>   // stat, lstat, fstat
# include <dirent.h>     // opendir, readdir, closedir
# include <string.h>     // strerror
# include <errno.h>      // errno
# include <termios.h>    // tcsetattr, tcgetattr
# include <term.h>       // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h>

/*
 * Defines
 */
# define SHELL_NAME "minishell"
# define PROMPT "minishell$ "

# define CMD
# define ARG
# define PIPE '|'
# define AMPER '&'
# define INFL '<'
# define OUTFL '>'

/*
 * Structs
 */
typedef struct s_data
{
    char	**env;
    char	*input;
    char	**tokens;
}		t_data;

typedef struct s_token
{
	char	*str;
	char	token;
}

typedef struct s_cmd
{
    char	*in_fd;
    char	*cmd;
    char	**execve_argv;
    char	**out_fd;
	char	redir;
}		t_cmd;

/*
 * Files
 */
// main.c

//* UTILS*//
// init_env.c
char	**copy_env(char **envp);
t_data	*init_env(char **envp);
char	*get_env(char **envp, char *var);

// errors.c
void	exit_shell(int status);

// frees.c
void	free_data(t_data **data);

//* LEXER *//
//cmd.c
t_cmd	*create_cmd(char **tokens);

#endif
