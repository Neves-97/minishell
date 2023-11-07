#include "minishell.h"

void	lexer(t_msh *data)
{
	int			i;
	int			start;
	char		quote;
	static char	voidq;

	i = -1;
	quote = 0;
	start = 0;
	while (data->input[++i])
	{
		if (is_separator(data->input[i], &quote) || !data->input[i + 1])
		{
			create_token(data, start, i - is_separator(data->input[i], &voidq));
			if (is_separator(data->input[i], &voidq) && data->input[i] != 32)
				create_token(data, i, i);
			start = i + 1;
		}
	}
	if (quote)
		free_nodes();
	quote_and_expand(data->tokens);
	delete_empty_tokens(&data->tokens);
}

void	create_token(t_msh *data, int start, int i)
{
	char	*str;
	char	void_q;

	void_q = 0;
	str = ft_substr(data->input, start, (i - start + 1));
	if (!(is_whtspc(str)) && \
	(ft_isalnum(str[0]) || !is_separator(str[0], &void_q)))
		ft_lstadd_back(&(data->tokens), ft_lstnew(str, 0));
	else if (!(is_whtspc(str)))
		ft_lstadd_back(&(data->tokens), ft_lstnew(str, str[0]));
	else
		free (str);
}

void	quotes_exception(t_list **head, t_list **tmp)
{
	(*head)->content[0] = '\0';
	(*head) = (*tmp);
	return ;
}

void	free_token(t_list *swap)
{
	free(swap->content);
	free(swap);
}

void	delete_empty_tokens(t_list **head)
{
	t_list	*tmp;
	t_list	*swap;

	tmp = (*head);
	while ((*head) && !(*head)->content[0])
	{
		swap = (*head);
		(*head) = (*head)->next;
		free_token(swap);
		tmp = (*head);
	}
	while ((*head))
	{
		if ((*head)->quote_exc == 1)
			return (quotes_exception(head, &tmp));
		while ((*head)->next && !(*head)->next->content[0])
		{
			swap = (*head)->next;
			(*head)->next = (*head)->next->next;
			free_token(swap);
		}
		(*head) = (*head)->next;
	}
	(*head) = tmp;
}
