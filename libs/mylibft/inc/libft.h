/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:31:25 by telufulu          #+#    #+#             */
/*   Updated: 2024/11/12 20:20:32 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

/*******************************************************************************
 * Defines
 ******************************************************************************/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif
# define MAX_FD 1024
# define DEC_BASE "0123456789"
# define OCT_BASE "01234567"
# define HEX_BASE "0123456789abcdef"

typedef char	t_bool;
# define TRUE 1
# define FALSE 0

/*******************************************************************************
 * Term colors
 ******************************************************************************/
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define DEFAULT "\033[0m"

/*******************************************************************************
 * Basic functions
 ******************************************************************************/
// Part 1 functions
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

// Part 2 functions
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// Bonus
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*******************************************************************************
 * Addicional functions
 ******************************************************************************/
// Printf
typedef struct s_store
{
	char	conv;
	size_t	(*funct)(va_list);
}				t_store;

int		ft_printf(char const *s, ...);
size_t	conv_char(va_list arg);
size_t	conv_string(va_list arg);
size_t	conv_addrss(va_list arg);
size_t	conv_dec(va_list arg);
size_t	conv_unsig(va_list arg);
size_t	conv_hex(va_list arg);
size_t	conv_heupx(va_list arg);
size_t	conv_perc(va_list arg);
size_t	ft_putptr(unsigned long long nb, char *base);
size_t	ft_putunsig(unsigned int nb);

// GNL
char	*get_next_line(int fd);

// Custom
char    	**ft_free_matrix(char **matrix);
void    	ft_error(char *err, char *str_error);
size_t  	ft_putnbr_base(int nb, char *base);
int	    	ft_str_digit(char *s);
size_t  	ft_matrix_len(char **matrix);
void    	ft_print_matrix(char **matrix, int fd);
void    	*ft_realloc(void *ptr, size_t size);
char    	**ft_matrixjoin(char **matrix, char *node);
char    	**ft_matrixdup(char **org, size_t len);
char    	**ft_matrixcpy(char **org, char **new, size_t len);
int	    	ft_strcmp(const char *s1, const char *s2);
long int		ft_atoli(const char *str);
int         ft_isspace(int c);
#endif
