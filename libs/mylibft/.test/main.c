/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:31:57 by telufulu          #+#    #+#             */
/*   Updated: 2023/08/27 15:20:09 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "test.h"

int	main(int argc, char **argv)
{
	int	flag;

	flag = 0;
	if (argc == 2)
	{
		if (!strcmp(argv[1], "part1"))
			flag += test_part1(argc, argv);
		else if (!strcmp(argv[1], "part2"))
			flag += test_part2(argc, argv);
		else if (!strcmp(argv[1], "bonus"))
			flag += test_bonus(argc, argv);
		else
		{	
			flag += test_part1(argc, argv);
			flag += test_part2(argc, argv);
			flag += test_bonus(argc, argv);
		}
		if (!flag)
		{
			printf("\x1b[31merror:\x1b[0m unknown argument\n");
			return (-1);
		}
		else if (flag == 3)
			printf("%5c LIBFT \x1b[32m SUCCES🎉\x1b[0m %c\n", '-', '-');
		else if (flag > 3)
			printf("%5c LIBFT \x1b[31m FAIL 😨\x1b[0m %c\n", '-', '-');
	}
	else
	{
		printf("\x1b[31merror:\x1b[0m empty argument\n");
		return (-1);
	}
	return (0);
}
