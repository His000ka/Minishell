#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour vérifier si un caractère est un délimiteur
int is_delimiter(char c, const char *delim) {
    while (*delim) {
        if (c == *delim) {
            return 1;
        }
        delim++;
    }
    return 0;
}

// Fonction pour découper la chaîne en tokens (sans strtok)
char *ft_strtok(char *str, const char *delim) {
    static char *saved_str;  // Pour garder la position lors des appels suivants
    char *token_start;
    
    // Si la chaîne d'entrée est NULL, utiliser la chaîne sauvegardée
    if (str == NULL) {
        str = saved_str;
    }
    
    // Si après l'appel précédent il n'y a plus de chaîne à traiter
    if (str == NULL) {
        return NULL;
    }

    // Ignorer les délimiteurs au début
    while (*str && is_delimiter(*str, delim)) {
        str++;
    }

    // Si on atteint la fin de la chaîne après avoir ignoré les délimiteurs
    if (*str == '\0') {
        return NULL;
    }

    // Début du token
    token_start = str;

    // Avancer jusqu'à trouver un délimiteur ou la fin de la chaîne
    while (*str && !is_delimiter(*str, delim)) {
        str++;
    }

    // Si on est tombé sur un délimiteur, terminer le token et sauvegarder la position
    if (*str) {
        *str = '\0';  // Met un '\0' à la place du délimiteur
        saved_str = str + 1;  // Sauvegarde la position pour le prochain appel
    } else {
        saved_str = NULL;  // Plus de tokens après
    }

    return token_start;  // Retourne le token trouvé
}
