/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:44:12 by aude-la-          #+#    #+#             */
/*   Updated: 2024/10/07 12:11:20 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>      // printf, perror
# include <stdlib.h>     // malloc, free, exit, getenv
# include <unistd.h>   
# include <string.h>   
# include "libft.h"
# include "minishell.h"

# ifndef MAX_TOKENS
#  define MAX_TOKENS 600
# endif

typedef enum e_type
{
	COMMAND,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC
}			t_type;

typedef struct s_token
{
	char	*str;
	t_type	type;
}			t_token;

typedef struct s_parser
{
	t_token		**tokens;
	char		**env;
	int			count;
	int			check;
	int			exit_code;
	const char	*s;
	const char	*start;
	const char	*end;
	char		varname[256];
	char		*env_value;
	size_t		length;
	size_t		i;
	size_t		j;
	size_t		l;
}				t_parser;

int		get_varname(t_parser *p, const char *s);
int		handle_args(t_parser *p);
int		handle_singlequote(t_parser *p);
int		handle_doublequote(t_parser *p);
int		is_heredoc(t_parser *p);
int		check_meta_character(t_parser *p);
int		check_quotes(t_parser *p);
int		check_tokens(t_parser *p);
int		define_length(t_parser *p);
char	next_quote(const char *s);
char	*substitute_variable(t_parser *p, char *result);
char	*handle_variable(t_parser *p, char limiter);
t_token	**main_parser(t_data *d);
void	handle_single_quote(t_parser *p);
void	handle_double_quote(t_parser *p);
void	handle_variable_expansion(t_parser *p);
void	append_variable(t_parser *p, char *var);
void	handle_variable_expansion(t_parser *p);
void	append_variable(t_parser *p, char *var);

#endif
