#include <stdlib.h>
#include <stdio.h>

typedef struct	s_list
{
	int				content;
	struct s_list	*next;
}	t_list;

typedef struct	s_push_swap
{
	int		length_a;
	int		length_b;
	int		max_a;
	int		max_b;
	int		min_a;
	int		min_b;
	t_list	**stack_a;
	t_list	**stack_b;
}	t_push_swap;


void	ft_lstclear(t_list **lst);
int		ft_atoi(const char *str);
t_list	*ft_lstnew(int content);
void	terminate(t_list **stack_a, t_list **stack_b);
t_list	**init_stack(int argc, char **argv);
void	swap(t_list **head);
void	push(t_list **target, t_list **source);
void	reverse_rotate(t_list **head);
void	rotate(t_list **head);
int		find_max(t_list **head);
int		find_min(t_list **head);
int		find_length(t_list **head);
void	ra(t_push_swap	*info);
void	rb(t_push_swap	*info);
void	rr(t_push_swap	*info);
void	rra(t_push_swap	*info);
void	rrb(t_push_swap	*info);
void	rrr(t_push_swap	*info);
void	sa(t_push_swap	*info);
void	sb(t_push_swap	*info);
void	ss(t_push_swap	*info);
void	pa(t_push_swap	*info);
void	pa(t_push_swap	*info);
int		check_duplicates(t_list **head);
void	find_move(t_list **stack_a, t_list **stack_b);
void	set_up(t_push_swap	*info);