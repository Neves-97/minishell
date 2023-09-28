#include "../../includes/minishell.h"

// bool is_builtin(t_list *cmd)
// {
//     if (ft_strlen(cmd->str) == 0)
//         return (false);
//     else if (ft_strncmp(cmd->str, "env", ft_strlen(cmd->str) + 1) == 0)
//         return (true);
//     else if (ft_strncmp(cmd->str, "pwd", ft_strlen(cmd->str) + 1) == 0)
//         return (true);
//     else if (ft_strncmp(cmd->str, "export", ft_strlen(cmd->str) + 1) == 0)
//         return (true);
//     else if (ft_strncmp(cmd->str, "unset", ft_strlen(cmd->str) + 1) == 0)
//         return (true);
//     else if (ft_strncmp(cmd->str, "echo", ft_strlen(cmd->str) + 1) == 0)
//         return (true);
//     else if (ft_strncmp(cmd->str, "cd", ft_strlen(cmd->str) + 1) == 0)
//         return (true);
//     else if (ft_strncmp(cmd->str, "exit", ft_strlen(cmd->str) + 1) == 0)
//         return (true);
//     else
//         return (false);
// }

// int ft_strcmp(const char *s1, const char *s2)
// {
//     int i = 0;

//     while (s1[i] && s2[i] && s1[i] == s2[i])
//         i++;
//     return (s1[i] - s2[i]);

// }

// bool execute_buitins(t_cmd *cmd)
// {
//     if (!is_builtin(cmd))
//         return false;
//     if (ft_strcmp(cmd->str, "cd") == 0)
//         return execute_cd(cmd);
//     // else if (ft_strcmp(cmd->str, "pwd") == 0)
//     //     // return execute_pwd(cmd);
//     // else if (ft_strcmp(cmd->str, "echo") == 0)
//     //     // return execute_echo(cmd);
//     // else if (ft_strcmp(cmd->str, "unset") == 0)
//     //     // return execute_unset(cmd);
//     // else if (ft_strcmp(cmd->str, "export") == 0)
//     //     // return execute_export(cmd);
//     // else if (ft_strcmp(cmd->str, "ls") == 0)
//     //     // return execute_ls(cmd);
//     else
//         return false;
// }