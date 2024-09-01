/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:55:13 by aude-la-          #+#    #+#             */
/*   Updated: 2024/07/15 18:56:26 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>     // malloc, free, exit, getenv
# include <unistd.h>    
# include "libft.h"

void	*free_array(char **array);
void	*ft_realloc(void *ptr, size_t size);

#endif
