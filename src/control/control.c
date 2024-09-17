<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:30:27 by firdawssema       #+#    #+#             */
/*   Updated: 2024/09/12 22:42:21 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void control_c(int sig)
{
	(void)(sig);

	rl_on_new_line();
	rl_redisplay();
	write(STDOUT_FILENO, "\nminishell> ", 12);
	rl_redisplay();
}

void	control_d()
{
	printf("exit\n");
	exit(1);
}

void	control_backslash(int sig)
{
	(void)sig;
}

void	control()
{
	signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
}

// int	main()
// {
// 	char *input;

//     control();  // Set up signal handling

//     while (1)
//     {
//         input = readline("minishell> ");
//         if (!input)  // If readline returns NULL, Ctrl+D was pressed
//         {
//             control_d();  // Handle Ctrl+D by exiting
//         }

//         if (input && *input)  // If user provided input, add it to history
//         {
//             add_history(input);
//         }

//         free(input);  // Free memory allocated by readline
//     }

//     return 0;
// }
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:18:21 by fimazouz          #+#    #+#             */
/*   Updated: 2024/09/10 13:14:53 by fimazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

// void control_c(int sig)
// {
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void	control_d()
// {
// 	printf("exit\n");
// 	exit(1);
// }

// void	control_backslash()
// {
	
// }

// void	control()
// {
// 	signal(SIGINT, control_c);
// }

// int	main()
// {
// 	char *input;

//     control();  // Set up signal handling

//     while (1)
//     {
//         input = readline("minishell> ");
//         if (!input)  // If readline returns NULL, Ctrl+D was pressed
//         {
//             control_d();  // Handle Ctrl+D by exiting
//         }

//         if (input && *input)  // If user provided input, add it to history
//         {
//             add_history(input);
//         }

//         free(input);  // Free memory allocated by readline
//     }

//     return 0;
// }
>>>>>>> ad1b7fbba2f85588b978f7e1a88c2dd25eb29f2c
