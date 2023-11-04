#include "minishell.h"

char	*replace_env_var(char *var)
{
	int	pos;
	int	max;
	int	len;

	if (var[0] == '?')
	{
		free (var);
		return (ft_itoa(get()->exit_status));
	}
	pos = 0;
	while (get()->env[pos] != NULL)
		pos++;
	max = pos;
	pos = search_env(var);
	len = ft_strlen(var);
	free (var);
	if (pos < max)
		return (ft_strdup(get()->env[pos] + len + 1));
	return (NULL);
}

char	*expand(char *cont, char *ns, int *i, int *j)
{
	char	*n2;
	char	*exp;
	int		start;
	int		var_len;

	start = i[0] + 1;
	var_len = 0;
	while (cont[i[0]++] && (ft_isalnum(cont[i[0]]) || cont[i[0]] == '?'))
	{
		var_len++;
		if (cont[i[0] + 1] == '?')
			break ;
	}
	exp = replace_env_var(ft_strndup(cont + start, var_len));
	n2 = ft_strjoin(ns, exp);
	if (n2)
	{
		free (ns);
		free (exp);
		ns = calloc(ft_strlen(n2) + ft_strlen(cont + i[0]) + 1, sizeof(char));
		ft_memcpy(ns, n2, ft_strlen(n2));
		free (n2);
		j[0] = ft_strlen(ns);
	}
	return (ns);
}

char	*before_expand(char *cont, char *ns, int *i, int *j)
{
	char	**split;
	int		y;

	y = -1;
	ns = expand(cont, ns, i, j);
	split = ft_split(ns, 32);
	if (split[0] && !split[1])
	{
		free_ptp(split);
		return (ns);
	}
	while (split[++y])
		ft_lstadd_back(&get()->tokens, ft_lstnew(split[y], 0));
	free(split);
	return (ns);
}

char	*handle_quotes(char *content)
{
	char	q;
	int		i;
	int		j;
	char	*new_str;

	q = 0;
	i = 0;
	j = 0;
	new_str = calloc(ft_strlen(content) + 1, sizeof(char));
	while (content[i])
	{
		if ((content[i] == '\"' || content[i] == '\'') && q == 0)
			q = content[i++];
		else if (content[i] == q)
		{
			q = 0;
			i++;
		}
		else if (content[i] != '$' || (content[i] == '$' && q == '\'') || \
		(!ft_isalnum(content[i + 1]) && content[i + 1] != '?'))
			new_str[j++] = content[i++];
		if (content[i] == '$' && q != '\'')
			new_str = before_expand(content, new_str, &i, &j);
	}
	return (new_str);
}

void	quote_and_expand(t_list *tokens)
{
	t_list	*tmp;
	char	*old_str;
	int		lst_size;

	tmp = tokens;
	while (tokens)
	{
		if (!(is_any_quote(tokens->content[0]) && \
		is_any_quote(tokens->content[1])))
		{
			old_str = tokens->content;
			lst_size = ft_lstsize(tokens);
			tokens->content = handle_quotes(tokens->content);
			if (lst_size != ft_lstsize(tokens))
				tokens->content[0] = '\0';
			free (old_str);
		}
		tokens = tokens->next;
	}
	tokens = tmp;
}

// tmp = get()->tokens;
// while (get()->tokens)
// {
// 	printf("ns: %s, token: %s\n", ns, get()->tokens->content);
// 	if (!ft_strncmp(ns, get()->tokens->content, ft_strlen(ns)))
// 		free_single_token(&get()->tokens);
// 	get()->tokens = get()->tokens->next;
// }
// get()->tokens = tmp;