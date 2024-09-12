/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:18:21 by fimazouz          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/10 20:42:25 by firdawssema      ###   ########.fr       */
=======
/*   Updated: 2024/09/12 11:28:22 by fimazouz         ###   ########.fr       */
>>>>>>> ca0e902071020c232e7aea1c649b042fae72d6f6
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

<<<<<<< HEAD
// void control_c(int sig)
// {
// 	printf("\nminihsell> ");
//     rl_replace_line("minishell> ", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }
=======
>>>>>>> ca0e902071020c232e7aea1c649b042fae72d6f6

void control_c(int sig)
{
	(void)(sig);

  	//rl_replace_line("minishell>", 0); 
	
	//printf("\nMINISHELL>");
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
