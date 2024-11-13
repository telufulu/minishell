/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:16:55 by aude-la-          #+#    #+#             */
/*   Updated: 2024/11/14 00:05:46 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	check_term(char **envp)
{
	struct termios	term;
	char			*tty;

	if (isatty(STDIN_FILENO) && envp)
	{
		tty = ttyname(STDIN_FILENO);
		if (get_env(envp, "SHELL"))
			printf("Shell: %s\n", get_env(envp, "SHELL"));
		if (get_env(envp, "USER"))
			printf("User: %s ", get_env(envp, "USER"));
		if (tty)
			printf("is succesfully logged on %s\n", tty);
		else
			perror("ttyname");
	}
	else
		ft_error("stdin is not a terminal", strerror(errno));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

t_data	*init_shell(t_data *d, char **envp, char **argv, int argc)
{
	if (argc > 1 && argv)
		ft_error("minishell doesn't get any arguments", NULL);
	d = ft_calloc(sizeof(t_data), 1);
	if (!d)
		ft_error("malloc failed creating shell", strerror(errno));
	d->env = init_env(envp);
	if (!d->env)
		ft_error("malloc failed", NULL);
	check_term(d->env);
	d->exit_status = 0;
	return (d);
}

void	*free_tokens(t_token **tokens)
{
	int	i;

	i = -1;
	while (tokens && tokens[++i])
	{
		if (tokens[i]->str)
		{
			free(tokens[i]->str);
			tokens[i]->str = NULL;
		}
		free(tokens[i]);
		tokens[i] = NULL;
	}
	if (tokens)
		free(tokens);
	return (NULL);
}

/*void	print_tokens(t_token **tokens, int fd)
{
	while (tokens && *tokens)
	{
		ft_putstr_fd((*tokens)->str, fd);
		write(1, "\t\t", 2);
		if ((*tokens)->type == COMMAND)
			ft_putstr_fd("COMMAND", fd);
		else if ((*tokens)->type == REDIRECT_IN)
			ft_putstr_fd("REDIRECT_IN", fd);
		else if ((*tokens)->type == REDIRECT_OUT)
			ft_putstr_fd("REDIRECT_OUT", fd);
		else if ((*tokens)->type == APPEND)
			ft_putstr_fd("APPEND", fd);
		else if ((*tokens)->type == HEREDOC)
			ft_putstr_fd("HEREDOC", fd);
		else if ((*tokens)->type == END_HEREDOC)
			ft_putstr_fd("END_HEREDOC", fd);
		else if ((*tokens)->type == PIPE)
			ft_putstr_fd("PIPE", fd);
		else if ((*tokens)->type == FD)
			ft_putstr_fd("FD", fd);
		write(1, "\n", 1);
		tokens++;
	}
}*/

void	ft_shell_error(char *var, char *msg_error, int exit_status)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	if (var && *var)
	{
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg_error && *msg_error)
		ft_putstr_fd(msg_error, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_status);
}

void	secure_free(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
