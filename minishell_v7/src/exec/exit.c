/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliskam <eliskam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:15:25 by emencova          #+#    #+#             */
/*   Updated: 2024/09/30 23:32:39 by eliskam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

long long ft_atoll(const char *str)
{
    long long result;
    int sign;
    const char *ptr;

    result = 0;
    sign = 1;
    ptr = str;
    while (*ptr == ' ' || (*ptr >= 9 && *ptr <= 13))
        ptr++;
    if (*ptr == '-' || *ptr == '+')
    {
        if (*ptr == '-')
            sign = -1;
        ptr++;
    }
    while (*ptr >= '0' && *ptr <= '9')
    {
        if (result > (LLONG_MAX - (*ptr - '0')) / 10)
            return (sign == 1) ? LLONG_MAX : LLONG_MIN;
        result = result * 10 + (*ptr - '0');
        ptr++;
    }
    return (result * sign);
}



int m_exit(t_shell *shell, t_list *cmd_node, int *leave)
{
    t_exec *cmd;
    char *arg;
    int exit_value;
    int i;

    cmd = (t_exec *)cmd_node->content;
    *leave = !shell->cmds->next;
    i = 0; 
    if (!cmd->args || !cmd->args[1])
        exit(0);
    if (cmd->args[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        *leave = 0;
        return (1);
    }
    arg = cmd->args[1];
    while (arg[i] != '\0')
    {
        if (!ft_isdigit(arg[i]) && !(i == 0 && (arg[i] == '-' || arg[i] == '+')))
        {
            ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
            exit (1);
        }
        i++;
    }
    long long int long_exit_value = ft_atoll(arg);
    if (long_exit_value < INT_MIN || long_exit_value > INT_MAX)
    {
        ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
        return (1);
    }

    exit_value = (int)(long_exit_value % 256);
    if (exit_value < 0)
        exit_value += 256;

    printf("Exiting with status %d\n", exit_value);
    exit(exit_value);
}

/*

int m_exit(t_shell *shell, t_list *cmd_node, int *leave)
{
    t_exec *cmd;
    char *arg;
    int exit_value;
    int i;

    cmd = (t_exec *)cmd_node->content;
    *leave = !shell->cmds->next;
    i = 0; 
    if (!cmd->args || !cmd->args[1])
        exit(0);
    if (cmd->args[2])
    {
        *leave = 0;
        return (1);
    }
    arg = cmd->args[1];
    while (arg[i] != '\0')
    {
        if (!ft_isdigit(arg[i]) && !(i == 0 && (arg[i] == '-' || arg[i] == '+')))
            return (1); // Indicate failure
        i++;
    }
    exit_value = ft_atoi(arg) % 256;
    if (exit_value < 0)
        exit_value += 256;

    printf("Exiting with status %d\n", exit_value);
    exit(exit_value);
}*/