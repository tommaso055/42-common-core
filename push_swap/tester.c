#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct	s_list
{
	int				content;
	struct s_list	*next;
}	t_list;

typedef struct	s_push_swap
{
	int		length_a;
	int		length_b;
	int		rotations;
	int		higher;
	int		lower;
	t_list	**stack_a;
	t_list	**stack_b;
}	t_push_swap;

typedef struct s_make_move
{
	int		best_content;
	int		position;
	int		best_position;
	int		least_moves;
	int		moves;
	int		target_position;
}	t_make_move;

typedef struct s_moves
{
	int ra;
	int rb;
	int rra;
	int rrb;
}	t_moves;

void	ft_lstclear(t_list **lst);
int		ft_atoi(const char *str);
t_list	*ft_lstnew(int content);
void	terminate(t_list **stack_a, t_list **stack_b);
t_list	**init_stack(int argc, char **argv);
void	swap(t_list **head);
void	push(t_list **target, t_list **source);
void	reverse_rotate(t_list **head);
void	rotate(t_list **head);
// int		find_max(t_list **head);
// int		find_min(t_list **head);
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
void	pb(t_push_swap	*info);
int		check_duplicates(t_list **stack_a);
void	make_move(t_push_swap	*info);
void    push_to_b(t_push_swap *info, int from, int to);
void	arrange(t_push_swap *info, t_moves *moves);
void	set_zero(int *a, int *b);
void	solve_two(t_push_swap *info);
void	push_back(t_push_swap *info);
void	set_make_move(t_push_swap *info, t_make_move *vars, t_list **curr);
int	count_moves(t_push_swap	*info, int position, int content);
int	find_target_position(t_list **stack_b, int a_c);
int max(int a, int b);
int	min(int a, int b, int c, int d);

void	make_move(t_push_swap	*info)
{
	t_list		*curr;
	t_make_move	vars;

	set_make_move(info, &vars, &curr);
	curr = curr->next;
	while (curr)
	{
		vars.moves = count_moves(info, vars.position, curr->content);
		if (vars.moves < vars.least_moves)
		{
			vars.least_moves = vars.moves;
			vars.best_content = curr->content;
			vars.best_position = vars.position;
		}
		vars.position++;
		curr = curr->next;
	}
    vars.target_position = find_target_position(info->stack_b, vars.best_content);
    push_to_b(info, vars.best_position, vars.target_position);
}

void	set_zero(int *a, int *b)
{
	*a = 0;
	*b = 0;
}

void    push_to_b(t_push_swap *info, int source_position, int target_position)
{
	t_moves	m;
	int	min_m;

	m.ra = source_position;
	m.rb = target_position;
	m.rra = info->length_a - m.ra;
	m.rrb = info->length_b - m.rb;

	min_m = min(max(m.ra, m.rb), max(m.rra, m.rrb), m.ra + m.rrb, m.rb + m.rra);
	if (max(m.ra, m.rb) <= min_m)
		set_zero(&m.rra, &m.rrb);
	else if (max(m.ra, m.rb) <= min_m)
		set_zero(&m.rra, &m.rrb);
	else if(m.ra + m.rrb <= min_m)
		set_zero(&m.rra, &m.rb);
	else if(m.rb + m.rra <= min_m)
		set_zero(&m.ra, &m.rrb);
	arrange(info, &m);
	pb(info);
}

void	arrange(t_push_swap *info, t_moves *moves)
{
	while (moves->ra > 0 && moves->rb > 0)
	{
		moves->ra--;
		moves->rb--;
		rr(info);
	}
	while (moves->rra > 0 && moves->rrb > 0)
	{
		moves->rra--;
		moves->rrb--;
		rrr(info);
	}
	while ((moves->ra)-- > 0)
		ra(info);
	while ((moves->rb)-- > 0)
		rb(info);
	while ((moves->ra)-- > 0)
		ra(info);
	while ((moves->ra)-- > 0)
		ra(info);
}

void	set_make_move(t_push_swap *info, t_make_move *vars, t_list **curr)
{
	*curr = *(info->stack_a);
	vars->position = 1;
	vars->least_moves = count_moves(info, 0, (*curr)->content);
	vars->best_content = (*curr)->content;
	vars->best_position = 0;
}

int	count_moves(t_push_swap	*info, int position, int content)
{
	int	ra;
	int	rra;
	int	rb;
	int	rrb;
	int	moves;

	ra = position;
	rb = find_target_position(info->stack_b, content);
	rra = info->length_a - position;
	rrb = info->length_b - rb;
	moves = min(max(ra, rb), max(rra, rrb), ra + rrb, rb + rra);
	return (moves);
}

int	find_target_position(t_list **stack_b, int a_c)
{
	t_list	*curr;
	int		position;
	int		t_position;
	int		t_c;

	position = 1;
	t_position = 0;
	t_c = (*stack_b)->content;
	curr = (*stack_b)->next;
	while (curr)
	{
		if (t_c > a_c && (curr->content > t_c || curr->content < a_c))
		{
			t_position = position;
			t_c = curr->content;
		}
		else if (t_c < a_c && curr->content < t_c)
		{
			t_position = position;
			t_c = curr->content;
		}
		curr = curr->next;
		position++;
	}
	return (t_position);
}


int max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

int	min(int a, int b, int c, int d)
{
	if (d < a && d < b && d < c)
		return (d);
	if (c < a && c < b && c < d)
		return (c);
	if (b < a && b < c && b < d)
		return (b);
	return (a);
}

int	find_length(t_list **head)
{
	int		length;
	t_list	*curr;

	if (!head || !*head)
		return (0);
	length = 1;
	curr = *head;
	while (curr->next)
	{
		curr = curr->next;
		length++;
	}
	return (length);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*curr;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		curr = (*lst)->next;
		free(*lst);
		*lst = curr;
		
	}
    free(lst);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	ans;

	i = 0;
	sign = 1;
	ans = 0;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		ans = ans * 10 + str[i] - 48;
		i++;
	}
	return (ans * sign);
}

t_list	*ft_lstnew(int content)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->next = NULL;
	list->content = content;
	return (list);
}

void	terminate(t_list **stack_a, t_list **stack_b)
{
	ft_lstclear(stack_a);
    ft_lstclear(stack_a);
	exit(1);
}

t_list	**init_stack(int argc, char **argv)
{
	int		i;
	t_list	**head;
	t_list	*last;
	int		n;

	head = (t_list **)malloc(sizeof(t_list *));
	if (!head)
		terminate(NULL, NULL);
	i = 1;
	n = ft_atoi(argv[i]);
	if (!n && argv[i][0] != '0')
		terminate(head, NULL);
	*head = ft_lstnew(n);
	last = (*head);
	while(++i < argc)
	{
		n = ft_atoi(argv[i]);
		if (!n && argv[i][0] != '0')
			terminate(head, NULL);
		last->next = ft_lstnew(n);
		if (!(last->next))
			terminate(head, NULL);
		last = last->next;
	}
	return (head);
}

int	main()
{
	t_push_swap	info;

	int argc = 7;
	char *argv[7] = {"push_swap", "1", "2", "3", "4", "5", "6"};

	info.stack_a = init_stack(argc, argv);
	info.stack_b = (t_list **)malloc(sizeof(t_list *));
	if (!info.stack_b)
		terminate(info.stack_a, info.stack_b);
	*info.stack_b = NULL;
	if (find_length(info.stack_a) < 2 || check_duplicates(info.stack_a))
		terminate(info.stack_a, info.stack_b);
	info.length_a = find_length(info.stack_a);
	info.length_b = 0;
	info.rotations = 0;
	if (info.length_a == 2)
	{
		solve_two(&info);
		terminate(info.stack_a, info.stack_b);
	}
	pb(&info);
	while (info.length_a > 2)
		make_move(&info);
	solve_two(&info);
	while (info.length_b)
		push_back(&info);
	while (info.rotations < 2)
		rra(&info);
	terminate(info.stack_a, info.stack_b);
}

int	check_duplicates(t_list **stack_a)
{
	t_list	*curr;
	t_list	*temp_curr;

	curr = (*stack_a);
	while (curr)
	{
		temp_curr = curr->next;
		while (temp_curr)
		{
			if (curr->content == temp_curr->content)
				return (1);
			temp_curr = temp_curr->next;
		}
		curr = curr->next;
	}
	return (0);
}

void	solve_two(t_push_swap *info)
{
	if ((*(info->stack_a))->content > (*(info->stack_a))->next->content)
		ra(info);
	info->higher = (*(info->stack_a))->next->content;
	info->lower = (*(info->stack_a))->content;
}

void	push_back(t_push_swap *info)
{
	if (info->rotations == 0)
	{
		if ((*(info->stack_a))->content < info->higher)
		{
			rra(info);
			info->rotations++;
		}
	}
	if (info->rotations == 1)
	{
		if ((*(info->stack_a))->content < info->lower)
		{
			rra(info);
			info->rotations++;
		}
	}
	pa(info);
}

void	push(t_list **target, t_list **source)
{
	t_list	*temp;

	if (*source == NULL)
		return ;
	temp = (*source);
	(*source) = temp->next;
	temp->next = *target;
	*target = temp;
}

void	pa(t_push_swap	*info)
{
    write(1, "pa\n", 3);
    push(info->stack_a, info->stack_b);
    info->length_a++;
    info->length_b--;
}

void	pb(t_push_swap	*info)
{
    write(1, "pb\n", 3);
    push(info->stack_b, info->stack_a);
    info->length_a--;
    info->length_b++;
}

void	reverse_rotate(t_list **head)
{
	t_list	*new_tail;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	new_tail = *head;
	while (new_tail->next->next != NULL)
		new_tail = new_tail->next;
	new_tail->next->next = *head;
	*head = new_tail->next;
	new_tail->next = NULL;
}

void	rra(t_push_swap	*info)
{
    write(1, "rra\n", 4);
    reverse_rotate(info->stack_a);
}

void	rrb(t_push_swap	*info)
{
    write(1, "rrb\n", 4);
    reverse_rotate(info->stack_b);
}

void	rrr(t_push_swap	*info)
{
    write(1, "rrr\n", 4);
    reverse_rotate(info->stack_a);
    reverse_rotate(info->stack_b);
}

void	rotate(t_list **head)
{
	t_list	*tail;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	tail = *head;
	while(tail->next != NULL)
		tail = tail->next;
	tail->next = *head;
	*head = (*head)->next;
	tail->next->next = NULL;
	return ;
} 

void	ra(t_push_swap	*info)
{
    write(1, "ra\n", 3);
    rotate(info->stack_a);
}

void	rb(t_push_swap	*info)
{
    write(1, "rb\n", 3);
    rotate(info->stack_b);
}

void	rr(t_push_swap	*info)
{
    write(1, "rr\n", 3);
    rotate(info->stack_a);
    rotate(info->stack_b);
}

void	swap(t_list **head)
{
	t_list	*temp;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	temp = (*head)->next;
	(*head)->next = temp->next;
	temp->next = (*head);
	*head = temp;
}

void	sa(t_push_swap	*info)
{
    write(1, "sa\n", 3);
    swap(info->stack_a);
}

void	sb(t_push_swap	*info)
{
    write(1, "sb\n", 3);
    swap(info->stack_b);
}

void	ss(t_push_swap	*info)
{
    write(1, "ss\n", 3);
    swap(info->stack_a);
    swap(info->stack_b);
}
