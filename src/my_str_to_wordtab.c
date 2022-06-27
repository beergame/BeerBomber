/*
** my_str_to_wordtabe.c for my_str_to_wordtab in /Users/balssa_v/
** 
** Made by BALSSA Victor
** Login   <balssa_v@etna-alternance.net>
** 
** Started on  Thu Dec  1 21:27:58 2016 BALSSA Victor
** Last update Thu Dec  1 21:31:59 2016 BALSSA Victor
*/

#include "server.h"

int count_word(char *str, char separe)
{
	int i;
	int count;

	i = 0;
	count = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == separe)
		i++;
	while (str[i]) {
		if (str[i] == ' ' || str[i] == '\t' || str[i] == separe) {
			while (str[i] == ' ' || str[i] == '\t' || str[i] == separe)
				i++;
			if (str[i])
				count++;
		}
		if (str[i])
			i++;
	}
	return (count);
}

char **my_str_to_wordtab(char *str, char separe)
{
	char **tab;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	if ((tab = malloc(sizeof(*tab) * ((count_word(str, separe) + 1)))) == NULL)
		return (0);
	while (str[i] == '\t' || str[i] == ' ' || str[i] == separe)
		i++;
	while (str[i]) {
		if ((tab[j] = malloc(sizeof(**tab) * (strlen(str) + 1))) == NULL)
			return (0);
		k = 0;
		while (str[i] != ' ' && str[i] != '\t' && str[i] != separe && str[i])
			tab[j][k++] = str[i++];
		tab[j++][k] = '\0';
		while (str[i] == ' ' || str[i] == '\t' || str[i] == separe)
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
