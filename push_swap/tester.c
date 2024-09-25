#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_list
{
	int				content;
	struct s_list	*next;
}	t_list;

typedef struct s_push_swap
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
	int		t_position;
}	t_make_move;

typedef struct s_moves
{
	int	ra;
	int	rb;
	int	rra;
	int	rrb;
	int	position;
	int	best_position;
	int	best_content;
}	t_moves;

void	ft_lstclear(t_list **lst);
int		ft_atoi(const char *str);
t_list	*ft_lstnew(int content);
void	terminate(t_list **stack_a, t_list **stack_b, char *str);
t_list	**init_stack(int argc, char **argv, int start);
void	swap(t_list **head);
void	push(t_list **target, t_list **source);
void	reverse_rotate(t_list **head);
void	rotate(t_list **head);
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
void	push_to_b(t_push_swap *info, int from, int to);
void	arrange(t_push_swap *info, t_moves *moves);
void	set_zero(int *a, int *b);
void	solve_two(t_push_swap *info);
void	push_back(t_push_swap *info);
void	set_make_move(t_push_swap *info, t_make_move *vars, t_list **curr);
int		count_moves(t_push_swap	*info, int position, int content);
int		find_target_position(t_list **stack_b, int a_c);
int		max(int a, int b);
int		min(int a, int b, int c, int d);
void	order_b(t_push_swap *info);
void	set_vars_order_b(t_moves *moves);
void	set_up(t_push_swap *info);
void	put_str(char *s);
void	main_controls(t_push_swap *info);
size_t	count_n_words(char const *str, char c);
size_t	next_word(char const *s, size_t i, char c, char **dst);
char	**ft_split(char const *s, char c);
int	ft_matrixlen(char **s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);


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
	vars.t_position = find_target_position(info->stack_b, vars.best_content);
	push_to_b(info, vars.best_position, vars.t_position);
}

void	set_zero(int *a, int *b)
{
	*a = 0;
	*b = 0;
}

void	push_to_b(t_push_swap *info, int source_position, int target_position)
{
	t_moves	m;
	int		min_m;

	m.ra = source_position;
	m.rb = target_position;
	m.rra = info->length_a - m.ra;
	m.rrb = info->length_b - m.rb;
	min_m = min(max(m.ra, m.rb), max(m.rra, m.rrb), m.ra + m.rrb, m.rb + m.rra);
	if (max(m.ra, m.rb) <= min_m)
		set_zero(&m.rra, &m.rrb);
	else if (max(m.rra, m.rrb) <= min_m)
		set_zero(&m.ra, &m.rb);
	else if (m.ra + m.rrb <= min_m)
		set_zero(&m.rra, &m.rb);
	else if (m.rb + m.rra <= min_m)
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
	while ((moves->rra)-- > 0)
		rra(info);
	while ((moves->rrb)-- > 0)
		rrb(info);
}

void	set_make_move(t_push_swap *info, t_make_move *vars, t_list **curr)
{
	*curr = *(info->stack_a);
	vars->position = 1;
	vars->least_moves = count_moves(info, 0, (*curr)->content);
	vars->best_content = (*curr)->content;
	vars->best_position = 0;
}

int	max(int a, int b)
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

void	main_controls(t_push_swap *info)
{
	if (!info->stack_b)
		terminate(info->stack_a, info->stack_b, "Error\nMalloc error");
	*info->stack_b = NULL;
	if (find_length(info->stack_a) < 2)
		terminate(info->stack_a, info->stack_b, NULL);
	if (check_duplicates(info->stack_a))
		terminate(info->stack_a, info->stack_b, "Error\nInvalid input");
}

int	ft_matrixlen(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
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
	while (info->length_b)
	{
		if (info->rotations == 0)
		{
			if ((*(info->stack_b))->content < info->higher)
			{
				rra(info);
				info->rotations++;
			}
		}
		if (info->rotations == 1)
		{
			if ((*(info->stack_b))->content < info->lower)
			{
				rra(info);
				info->rotations++;
			}
		}
		pa(info);
	}
	while (info->rotations++ < 2)
		rra(info);
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
		else if (t_c < a_c && curr->content < a_c && curr->content > t_c)
		{
			t_position = position;
			t_c = curr->content;
		}
		curr = curr->next;
		position++;
	}
	return (t_position);
}

void	put_str(char *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		write (1, &s[i++], 1);
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

void	terminate(t_list **stack_a, t_list **stack_b, char *str)
{
	if (str)
		put_str(str);
	ft_lstclear(stack_a);
	ft_lstclear(stack_b);
	exit(1);
}

t_list	**init_stack(int argc, char **argv, int start)
{
	int		i;
	t_list	**head;
	t_list	*last;
	int		n;

	head = (t_list **)malloc(sizeof(t_list *));
	if (!head)
		terminate(NULL, NULL, "Error\nMalloc error");
	i = start;
	n = ft_atoi(argv[i]);
	if (!n && (argv[i][0] != '0' || argv[i][1] != '\0'))
		terminate(head, NULL, "Error\nInvalid input");
	*head = ft_lstnew(n);
	last = (*head);
	while (++i < argc)
	{
		n = ft_atoi(argv[i]);
		if (!n && (argv[i][0] != '0' || argv[i][1] != '\0'))
			terminate(head, NULL, "Error\nInvalid input");
		last->next = ft_lstnew(n);
		if (!(last->next))
			terminate(head, NULL, "Error\nMalloc error");
		last = last->next;
	}
	return (head);
}

void	set_up(t_push_swap *info)
{
	info->length_a = find_length(info->stack_a);
	info->length_b = 0;
	info->rotations = 0;
	*(info->stack_b) = NULL;
}

int	main()
{
	t_push_swap	info;
	char		**split;
	int			i;

	i = 0;

    int argc = 5;
    char *argv[5] = {"si", "2", "5", "0", "3 1 -1 4 6"};

	if (argc == 1)
		return (0);
	if (argc == 2)
	{
		split = ft_split(argv[1], ' ');
		info.stack_a = init_stack(ft_matrixlen(split), split, 0);
		while(split[i])
			free(split[i++]);
		free(split);
	}
	else
		info.stack_a = init_stack(argc, argv, 1);
	info.stack_b = (t_list **)malloc(sizeof(t_list *));
	set_up(&info);
	if (info.length_a == 2)
	{
		solve_two(&info);
		terminate(info.stack_a, info.stack_b, NULL);
	}
	pb(&info);
	while (info.length_a > 2)
		make_move(&info);
	solve_two(&info);
	order_b(&info);
	push_back(&info);
	terminate(info.stack_a, info.stack_b, NULL);
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

void	set_vars_order_b(t_moves *moves)
{
	moves->rrb = 0;
	moves->ra = 0;
	moves->rra = 0;
	moves->rb = 0;
	moves->position = 1;
	moves->best_position = 0;
}

void	order_b(t_push_swap *info)
{
	t_list	*curr;
	t_moves	vars;

	set_vars_order_b(&vars);
	vars.best_content = (*(info->stack_b))->content;
	curr = (*(info->stack_b))->next;
	while (curr)
	{
		if (curr->content > vars.best_content)
		{
			vars.best_content = curr->content;
			vars.best_position = vars.position;
		}
		curr = curr->next;
		vars.position++;
	}
	if (vars.best_position < info->length_b - vars.best_position)
		vars.rb = vars.best_position;
	else
		vars.rrb = info->length_b - vars.best_position;
	arrange(info, &vars);
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
	while (tail->next != NULL)
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

size_t	count_n_words(char const *str, char c)
{
	size_t	i;
	size_t	count;
	size_t	valid;

	i = 0;
	count = 0;
	valid = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			if (!valid)
				continue ;
			count++;
			valid = 0;
			continue ;
		}
		i++;
		valid = 1;
	}
	if (valid)
		count++;
	return (count);
}

size_t	next_word(char const *s, size_t i, char c, char **dst)
{
	size_t	len;

	len = 0;
	while (s[i + len] != c && s[i + len])
		len++;
	*dst = (char *)malloc((len + 1) * sizeof(char));
	ft_strlcpy(*dst, s + i, len + 1);
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	n_words;
	char	**arr_to_return;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	n_words = count_n_words(s, c);
	arr_to_return = (char **)malloc((n_words + 1) * sizeof(char *));
	if (arr_to_return == NULL)
		return (NULL);
	arr_to_return[n_words] = NULL;
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
			i = next_word(s, i, c, arr_to_return + j++);
		else
			i++;
	}
	return (arr_to_return);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}
