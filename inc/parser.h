/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:44:12 by aude-la-          #+#    #+#             */
/*   Updated: 2024/09/05 19:46:28 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
# include <stdio.h>      // printf, perror
# include <stdlib.h>     // malloc, free, exit, getenv
# include <unistd.h>   
# include <string.h>   
# include "libft.h"

# ifndef MAX_TOKENS
#  define MAX_TOKENS 600
# endif

/*******************************************************************************
 * Struct
 ******************************************************************************/
typedef struct s_parser
{
	char		**tokens;
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

/*******************************************************************************
 * Files
 ******************************************************************************/
int		get_varname(t_parser *p, const char *s);
int		handle_args(t_parser *p);
int		handle_singlequote(t_parser *p);
int		handle_doublequote(t_parser *p);
int		is_meta_character(char c);
int		is_heredoc(t_parser *p);
int		check_quotes(t_parser *p);
int		define_length(t_parser *p);
char	next_quote(const char *s);
char	*substitute_variable(t_parser *p, char *result);
char	*handle_variable(t_parser *p, char limiter);
char	**main_parser(const char *input, int exit_status);
void	handle_single_quote(t_parser *p);
void	handle_double_quote(t_parser *p);
void	handle_variable_expansion(t_parser *p);
void	append_variable(t_parser *p, char *var);
void	handle_variable_expansion(t_parser *p);
void	append_variable(t_parser *p, char *var);

// tokenizer.c
char	*tokenizer(char **params);

// tokenizer_utils.c
void	is_infl(char **res, char params, int i);
void	is_outfl(char **res, char params, int i);

#endif
