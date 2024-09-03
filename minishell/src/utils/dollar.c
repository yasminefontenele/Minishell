/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmine <yasmine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:09:53 by yasmine           #+#    #+#             */
/*   Updated: 2024/08/21 21:20:45 by yasmine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//This function is used to set the dollar sign
char *set_dollar(char *str, int i)
{
    int j;
    char *tmp;

    j = i;
    while (str[++j])
    {
        if ((str[i] == ' ' || str[i] == '\t') && j == i + 1)//if the dollar sign is alone
            return (ft_strdup("$"));
        else if ((str[i] == ' ' || str[i] == '\t'))//is is followed by a space ou tab
        {
            tmp = ft_substr(str, i, j - i);//get the substring
            dollar_handling(&tmp, 0);
            return (tmp);
        }
    }
    if (str[j - 1] == '$')
        return (ft_strdup("$"));
    tmp = ft_substr(str, i, j - i);
    dollar_handling(&tmp, 0);
    return (tmp);
}

int len_dollar(char *str, int i)
{
    int j;

    j = i;
    while (str[++j])
    {
        if (str[j] == ' ' || str[j] == '\t')
            return (j - i);
    }
    return (j - i);
}