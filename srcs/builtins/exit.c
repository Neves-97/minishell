// #include "../../includes/minishell.h"

// void	ft_lstdelone1(t_list *lst, void (*del)(void *))
// {
// 	if (!lst)
// 		return ;
// 	del(lst->content);
// 	free(lst);
// }

// void	ft_lstclear1(t_list **lst, void (*del)(void *))
// {
// 	t_list	*ls;

// 	if (!*lst)
// 		return ;
// 	while (*lst)
// 	{
// 		ls = (*lst)->next;
// 		ft_lstdelone1(*lst, del);
// 		*lst = ls;
// 	}
// 	lst = NULL;
// }

// int	validate_code(char **cmds, int i)
// {
// 	if (cmds[1] && cmds[2])
// 	{
// 		if (!get()->child)
// 			ft_putstr_fd("exit\n", STDOUT_FILENO);
// 		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
// 		return (1);
// 	}
// 	while (cmds[1] && cmds[1][i])
// 	{
// 		if (!ft_isdigit(cmds[1][i++]))
// 		{
// 			if (!get()->child)
// 				ft_putstr_fd("exit\n", STDOUT_FILENO);
// 			ft_putstr_fd("bash: exit: ", STDERR_FILENO);
// 			ft_putstr_fd(cmds[1], STDERR_FILENO);
// 			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
// 			ft_lstclear1(get()->env, free);
// 			free(get()->env);
// 			get()->exit_status = 2;
// 			exit(get()->exit_status);
// 		}
// 	}
// 	return (0);
// }

// int	ft_exit(char **cmds)
// {
// 	int	i;

// 	i = 0;
// 	if (cmds[1] && (cmds[1][0] == '-' || cmds[1][0] == '+'))
// 		i++;
// 	if (validate_code(cmds, i) == 1)
// 		return (1);
// 	if (cmds[1])
// 	{
// 		if (!get()->child)
// 			ft_putstr_fd("exit\n", STDOUT_FILENO);
// 		get()->exit_status = (unsigned char)ft_atoi(cmds[1]);
// 		ft_lstclear1(get()->env, free);
// 		free(get()->env);
// 		exit(get()->exit_status);
// 	}
// 	if (!get()->child)
// 		ft_putstr_fd("exit\n", STDOUT_FILENO);
// 	ft_lstclear1(get()->env, free);
// 	// success_exit(NULL, get()->ast_tmp, get()->free_cmd);
// 	exit(get()->exit_status);
// 	return (0);
// }
