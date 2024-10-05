/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:01:24 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/24 20:01:26 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int		ft_matrixlen(char **s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strncmp(char *s1, char *s2);
int		check_input(int argc, char **argv, int start);
int		ft_strlen(char *s);
int		handle_check(char *str, int sign);
void	further_init_stack(int argc, char **argv, t_push_swap *info);
int		in_order(t_list **stack_a);
void	solve_three(t_push_swap *info);
void	situation(int situation, t_push_swap *info);
