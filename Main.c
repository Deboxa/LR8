#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Main.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	menu();
	return 0;
}

void menu(void)
{
	functions sw = create;
	int degree;
	int coeff;
	int* ptr = NULL;
	int size = 0;
	polynom* head = NULL;
	do
	{
		printf("Choose function from list:\n"
			"1 - Create polynom\n"
			"2 - Print polynom\n"
			"3 - Sort polynom\n"
			"4 - Remove all elements with even degree\n"
			"5 - Exit out of program\n");
		scanf("%d", &sw);
		switch (sw)
		{
		case create:
			printf("Enter the coefficient and degree before and after the space\n");
			if (scanf("%d %d", &coeff ,&degree) != 2 || check_degree(degree, &ptr, &size) != 0 || coeff == 0)
			{
				while (getchar() != '\n');
				printf("Input error!\n");
				break;
			}
			add_node(&head, degree, coeff);
			break;
		case print:
			print_node(head);
			break;
		case sort:
			sort_node(&head);
			break;
		case func25:
			function25(head);
			break;
		case exit1:
		{
			free(ptr);
			polynom* tmp;
			while (head != NULL)
			{
				tmp = head;
				head = head->next;
				free(tmp);
			}
			return;
		}
		default:
			printf("Input error!\n");
			break;
		}
	} while (sw != exit1);
}

polynom* create_node(int degree, int coeff)
{
	polynom* Node = (polynom*)malloc(sizeof(polynom));
	if (Node == NULL)
	{
		printf("Malloc erorr!\n");
		return NULL;
	}
	Node->coeff = coeff;
	Node->degree = degree;
	Node->next = NULL;
	return Node;
}

void add_node(polynom** head, int degree, int coeff)
{
	polynom* next_node = create_node(degree, coeff);
	if (next_node == NULL)
	{
		printf("Create node error!\n");
		return;
	}
	next_node->next = *head; 
	*head = next_node; 
	return;
}

int check_degree(int degree, int** ptr, int* size) 
{
	if (*ptr != NULL) 
	{
		for (int i = 0; i < *size; i++) 
		{
			if ((*ptr)[i] == degree) 
			{
				printf("Degree %d already exists!\n", degree);
				return 1;
			}
		}
	}
	int new_size = *size + 1;
	int* temp = realloc(*ptr, new_size * sizeof(int));
	if (temp == NULL) 
	{
		printf("Realloc error!\n");
		return 1;
	}
	*ptr = temp;
	(*ptr)[*size] = degree; 
	(*size)++; 
	return 0;
}

void print_node(polynom* head) 
{
	int first = 1;
	int count = 0;
	if (head == NULL) 
	{
		printf("Polynomial is empty!\n");
		return;
	}
	while (head != NULL) 
	{
		int coeff = head->coeff;
		int degree = head->degree;

		if (first == 1)
		{
			if (coeff == 1 && degree == 0)
			{
				printf("1");
				first = 0;
			}
			if (coeff == -1 && degree == 0)
			{
				printf("-1");
				first = 0;
			}
			if (degree == 0 && first != 0)
			{
				printf("%d", coeff);
				first = 0;
			}
			if (degree != 0)
			{
				if (coeff == 1)
				{
					printf("x^%d", degree);
					first = 0;
				}
				if (coeff == -1)
				{
					printf("-x^%d", degree);
					first = 0;
				}
			}
			if (first != 0)
			{
				printf("%dx^%d", coeff, degree);
				first = 0;
			}
			head = head->next;
			count++;
			continue;
		}
		if (coeff < 0)
		{
			printf(" - ");
			coeff = -coeff;
		}
		else
		{
			printf(" + ");
		}
		if (degree == 0)
		{
			printf("%d", coeff);
		}
		else 
		{
			if (coeff == 1)
			{
				printf("x^%d", degree);
			}
			else
			{
				printf("%dx^%d", coeff, degree);
			}
		}
		count++;
		head = head->next;
	}
	printf("\nAmount of monomials: %d\n", count);
}

void function25(polynom** head)
{
	if (*head == NULL)
	{
		printf("Polynomial is empty!\n");
		return;
	}
	if ((*head)->next == NULL && (*head)->degree % 2 == 0)
	{
		*head = NULL;
		return;
	}
	polynom* curr = *head;
	polynom* prev = NULL;
	polynom* next = NULL;
	int count = 0;
	while (curr != NULL)
	{
		next = curr->next;
		if (curr->degree % 2 == 0)
		{
			if (prev == NULL)
			{
				*head = next;
			}
			else
			{
				prev->next = next;
			}
			free(curr);
			count++;
		}
		else
		{
			prev = curr;
		}
		curr = next;
	}
	if (count == 0)
	{
		printf("There are no monomials with even degrees\n");
	}
	else
	{
		printf("Deleled %d monomials\n", count);
	}
}

void sort_node(polynom** head)
{
	if (*head == NULL || (*head)->next == NULL)
		return;
	polynom* prev;
	polynom* current = *head;
	polynom* next = current->next;
	int swap;
	do
	{
		swap = 0;
		prev = NULL;
		current = *head;
		next = current->next;
		while (current != NULL && current->next != NULL) 
		{
			next = current->next;
			if (current->degree < next->degree)
			{
				if (prev == NULL)
				{
					*head = next;
				}
				else
				{
					prev->next = next;
				}
				current->next = next->next;
				next->next = current;
				prev = next;
				swap = 1;

			}
			else
			{
				prev = current;
				current = current->next;
			}
		}
	} while (swap == 1);

}


