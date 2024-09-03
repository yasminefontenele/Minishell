/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmine <yasmine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:57:57 by yasmine           #+#    #+#             */
/*   Updated: 2024/08/21 21:07:53 by yasmine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int count_backslash(char *line, int i)
{
    int count;

    count = 0;
    if(i == 0)
        return (0);
    while (i-- >= 0)
    {
        if (i >= 0 && line[i] == '\\')
            count++;
        else
            break;
    }
    return (count);
}

//This function is used to check if the backslash is valid
int valid_backslash(char **tokens)
{
    int i;
    int j;
    t_quote q;

    i = -1;
    while(tokens[++i])
    {
        j = -1;
        q = init_quote();//initialize the quote structure
        while (tokens[i][++j])
        {
            if (tokens[i][j] == '\\' && q.double_quote == false) && q.single_quote == false)//if the backslash is not in a quote
                return (0);
            if (tokens[i][j] == '\'' || tokens[i][j] == '\"')//if the token is a quote
                q = set_quote_values(tokens[i][j], q);
        }
    }
    return (1);
}