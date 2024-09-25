/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:16:55 by aude-la-          #+#    #+#             */
/*   Updated: 2024/09/25 19:57:20 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" //libc, t_data
#include "libft.h" //ft_error, get_env, ft_printf

void	check_term(char **envp)
{
	char	*tty;

	if (isatty(STDIN_FILENO) && envp)
	{
		tty = ttyname(STDIN_FILENO);
		if (get_env(envp, "SHELL"))
			ft_printf("Shell: %s\n", get_env(envp, "SHELL"));
		if (get_env(envp, "USER"))
			ft_printf("User: %s ", get_env(envp, "USER"));
		if (tty)
			ft_printf("is succesfully logged on %s\n", tty);
		else
			perror("ttyname");
	}
	else
		ft_error("stdin is not a terminal", strerror(errno));
}

t_data	*init_shell(t_data *d, char **envp, char **argv, int argc)
{
	if (argc > 1 && argv)
		ft_error("minishell doesn't get any arguments", NULL);
	d = ft_calloc(sizeof(t_data), 1);
	if (!d)
		ft_error("malloc failed", strerror(errno));
	d->env = init_env(envp);
	if (!d->env || !*d->env)
		ft_error("init shell failed", strerror(errno));
	check_term(d->env);
	d->exit_status = 0;
	return (d);
}

void	ft_shell_error(char *var, char *msg_error)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	if (var && *var)
		ft_putstr_fd(var, 2);
	if (msg_error && *msg_error)
		ft_putstr_fd(msg_error, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}
