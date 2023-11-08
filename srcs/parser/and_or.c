/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:16:22 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:16:23 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*and_or(void)
{
	t_ast	*new_node;
	t_list	*backup;

	backup = get()->tokens_tmp;
	new_node = ao_case1();
	if (new_node)
		return (new_node);
	get()->tokens_tmp = backup;
	new_node = ao_case2();
	if (new_node)
		return (new_node);
	get()->tokens_tmp = backup;
	new_node = ao_case3();
	if (new_node)
		return (new_node);
	return (NULL);
}

// <job> '&&' <and or>

t_ast	*ao_case1(void)
{
	t_ast	*new_node;
	t_ast	*job_node;
	t_ast	*and_or_node;

	job_node = job();
	if (!job_node)
		return (NULL);
	if (!get()->tokens_tmp || !get()->tokens_tmp->next)
		return (free_ast(job_node));
	if (get()->tokens_tmp->type != AST_AND || \
		get()->tokens_tmp->next->type != AST_AND)
		return (free_ast(job_node));
	new_node = ast_new_node(AST_AND);
	if (!new_node)
		return (NULL);
	new_node->content = ft_strdup("&&");
	ast_add_node(new_node, job_node, 0);
	get()->ast_tmp = new_node;
	get()->tokens_tmp = get()->tokens_tmp->next->next;
	and_or_node = and_or();
	if (!and_or_node)
		return (free_ast(new_node));
	ast_add_node(new_node, and_or_node, 1);
	return (new_node);
}

// <job> '||' <and or>

t_ast	*ao_case2(void)
{
	t_ast	*new_node;
	t_ast	*job_node;
	t_ast	*and_or_node;

	job_node = job();
	if (!job_node)
		return (NULL);
	if (!get()->tokens_tmp || !get()->tokens_tmp->next)
		return (free_ast(job_node));
	if (get()->tokens_tmp->type != AST_PIPE || \
		get()->tokens_tmp->next->type != AST_PIPE)
		return (free_ast(job_node));
	new_node = ast_new_node(AST_OR);
	if (!new_node)
		return (NULL);
	new_node->content = ft_strdup("||");
	ast_add_node(new_node, job_node, 0);
	get()->ast_tmp = new_node;
	get()->tokens_tmp = get()->tokens_tmp->next->next;
	and_or_node = and_or();
	if (!and_or_node)
		return (free_ast(new_node));
	ast_add_node(new_node, and_or_node, 1);
	return (new_node);
}

// <job>

t_ast	*ao_case3(void)
{
	t_ast	*new_node;

	if (!get()->tokens_tmp)
		return (NULL);
	new_node = job();
	if (!new_node)
		return (NULL);
	if (get()->tokens_tmp)
		if (get()->tokens_tmp->type == AST_AND || 
			get()->tokens_tmp->type == AST_PIPE)
			return (free_ast(new_node));
	return (new_node);
}
