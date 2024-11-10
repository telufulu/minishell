/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:29:13 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/10 17:04:27 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
# include "minishell.h"	// t_data
# include "lexer.h"		// t_cmd
# include "parser.h"	// t_token
/*******************************************************************************
 * Defines
 ******************************************************************************/
# define RD 0
# define WR 1

/*******************************************************************************
 * Files
 ******************************************************************************/
// main_executor.c
void	main_executor(t_data *d, t_cmd *c);

// utils_executor.c
void	write_fd(int old, int new);
int		get_exit_status(int status);

// redirections.c
void	redin_child(int *oldfd, t_cmd *c);
void	redout_child(int *pipefd, t_bool next, t_cmd *c);
int		redir_father(int oldfd, int *pipefd, t_bool next);

#endif
