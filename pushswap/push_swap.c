#include "push_swap.h"

t_list *gen_list(char **argv)
{
	
}

t_list  *rr(t_list *head)
{
	t_list *new_tail;

	new_tail = head;
	while(new_tail->next->next != NULL)
		new_tail = new_tail->next;
	new_tail->next->next = head;
	head = new_tail->next;
	new_tail->next = NULL;
	return (head);
}

t_list  *r(t_list *head)
{
	t_list  *tail;

	tail = head;
	while(tail->next != NULL)
		tail = tail->next;
	tail->next = head;
	head = head->next;
	tail->next->next = NULL;
	return (head);
} 

int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	t_list	stack_a;
	stack_a= gen_list(argv);
}