
#include "cub3d.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*p;

	p = (t_list *)malloc(sizeof(t_list));
	if (!p)
		return (NULL);
	p ->str = content;
	p ->next = NULL;
	return (p);
}


t_list*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->next == NULL)
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (0);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (ft_lstlast(*lst))
	{
		ft_lstlast(*lst)->next = new;
	}
	else
		*lst = new;
}