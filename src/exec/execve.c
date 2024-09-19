/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:33 by firdawssema       #+#    #+#             */
/*   Updated: 2024/09/19 14:17:45 by firdawssema      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>

// Fonction pour vérifier si c'est un chemin absolu ou relatif
int is_absolute_or_relative(char *cmd)
{
    return (cmd[0] == '/' || cmd[0] == '.');
}

// Fonction pour concaténer deux chaînes avec un '/'
char *path_concat(char *dir, char *cmd)
{
    int len_dir = ft_strlen(dir);
    int len_cmd = ft_strlen(cmd);
    char *full_path = malloc(len_dir + len_cmd + 2); // +2 pour '/' et '\0'

    if (!full_path)
    {
        return NULL;
    }

    ft_strcpy(full_path, dir);
    full_path[len_dir] = '/';             // Ajoute '/' entre le répertoire et la commande
    ft_strcpy(full_path + len_dir + 1, cmd); // Copie la commande après le '/'

    return full_path;
}

// Fonction pour vérifier si un fichier est exécutable
int is_executable(char *path)
{
    struct stat sb;
    
    // Utilisation de stat pour vérifier si le fichier existe et est exécutable
    if (stat(path, &sb) == 0 && sb.st_mode & S_IXUSR)
    {
        return 1; // Le fichier est exécutable
    }
    return 0; // Le fichier n'est pas exécutable ou n'existe pas
}

// Fonction pour rechercher l'exécutable dans les répertoires du PATH
char *find_executable_in_path(char *cmd)
{
    char *path_env = getenv("PATH");
    char *path_token;
    char *full_path = NULL;

    if (!path_env)
        return NULL;
    // On duplique la variable d'environnement PATH
    char *path_copy = strdup(path_env);
    if (!path_copy)
        return NULL;
    // Utilisation de strtok pour parcourir chaque répertoire du PATH
    path_token = strtok(path_copy, ":");
    while (path_token != NULL)
    {
        full_path = path_concat(path_token, cmd);
        if (!full_path)
        {
            free(path_copy);
            return NULL;
        }
        // Vérifier si le fichier est exécutable
        if (is_executable(full_path))
        {
            free(path_copy);
            return full_path;
        }

        free(full_path); // Libérer si ce n'est pas le bon fichier
        path_token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL; // Si aucun exécutable n'est trouvé
}

// Fonction pour exécuter la commande
void execute_command(char *cmd, char **args, char **envp)
{
    char *path = NULL;

    if (is_absolute_or_relative(cmd))
        path = cmd;
    else
    {
        path = find_executable_in_path(cmd);
        if (!path)
        {
            printf("Command not found: %s\n", cmd);
            return;
        }
    }
    // On tente d'exécuter la commande dans un processus enfant
    if (fork() == 0)
    {
        if (execve(path, args, envp) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE); // Le processus enfant doit se terminer en cas d'échec
        }
    }
    else
    {
        int status;
        wait(&status); // Le parent attend que le processus enfant termine
    }
}

// int main(int argc, char **argv, char **envp)
// {
//     if (argc < 2)
//     {
//         fprintf(stderr, "Usage: %s <command>\n", argv[0]);
//         return 1;
//     }

//     // Passe tous les arguments (commande + options) à execute_command
//     execute_command(argv[1], argv + 1, envp);
//     return 0;
// }
