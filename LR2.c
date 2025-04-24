#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "LR2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int lr2(void)
{
	printf("Enter a string of only Latin letters, separating words with spaces\n(length limit - %d)\n", MAX_STR_SIZE);
	while (getchar() != '\n');
	char* str = (char*)malloc(MAX_STR_SIZE * sizeof(char));
	if (str == NULL)
	{
		printf("Malloc error!\n");
		return 1;
	}
	if (scanf("%499[^\n]", str) != 1 || input_validation(str) != 0)
	{
		printf("Input error!\n");
		free(str);
		return 1;
	}
	node* head = NULL;
	char* tmp = strtok(str, " ");
	if (tmp == NULL)
	{
		printf("Input error!\n");
		free(str);
		return 1;
	}
	while (tmp != NULL)
	{
		add_node(&head,tmp);
		tmp = strtok(NULL, " ");
	}
	modify_nodes(head);
	free_node(head);
	free(str);
	return 0;
}

int is_latin(char sim)
{
	return (sim >= 'A' && sim <= 'Z') || (sim >= 'a' && sim <= 'z'); 
}

int input_validation(const char* str)
{
	int i = 0;
	int var = 0;
	while (str[i] != '\0')
	{
		if (is_latin(str[i]) != 1 && str[i] != ' ') 
		{
			printf("Forbidden symbol - '%c'\n", str[i]);
			var++;
		}
		i++;
	}
	return var;
}

node* create_node(char* token)
{
	node* part = (node*)malloc(sizeof(node));
	if (part == NULL)
	{
		printf("Malloc error!\n");
		return NULL;
	}
	strncpy(part->token, token, MAX_TOKEN_SIZE - 1);
	part->token[MAX_TOKEN_SIZE - 1] = '\0';
	part->next = NULL;
	part->prev = NULL;
	return part;
}

void add_node(node** head, char* token)
{
	if (*head == NULL)
	{
		*head = create_node(token);
		return;
	}
	node* new_node = create_node(token);
	if (new_node == NULL)
	{
		printf("Node create error!\n");
		return;
	}
	(*head)->prev = new_node;
	new_node->next = *head;
	new_node->prev = NULL;
	*head = new_node;
}

void modify_nodes(node* head)
{
	node* vowel_node = NULL;
	node* consonant_node = NULL;
	node* curr = head;
	while (curr != NULL)
	{
		if (is_vowel(curr->token) == 1)
		{
			add_node(&vowel_node, curr->token);
		}
		else if(is_vowel(curr->token) == 0)
		{
			add_node(&consonant_node, curr->token);
		}
		else
		{
			printf("Empty string!\n");
			return;
		}
		curr = curr->next;
	}
	printf("Vowel: ");
	print_node(vowel_node);
	putchar('\n');
	printf("Consonant: ");
	print_node(consonant_node);
	putchar('\n');
	free_node(vowel_node);
	free_node(consonant_node);
}

int is_vowel(char* token)
{
	if (token == NULL || token[0] == '\0')
	{
		return -1;
	}

	if (token[0] == 'a' || token[0] == 'e' || token[0] == 'i' || token[0] == 'o' || token[0] == 'u' || token[0] == 'y' || token[0] == 'A' || token[0] == 'E' || token[0] == 'I' || token[0] == 'O' || token[0] == 'U' || token[0] == 'Y')
	{
		return 1;
	}
	else return 0;
}

void print_node(node* head)
{
	node* curr = head;
	while (curr != NULL)
	{
		printf("%s ", curr->token);
		curr = curr->next;
	}
}

void free_node(node* head) 
{
	while (head != NULL) 
	{
		node* tmp = head;
		head = head->next;
		free(tmp);
	}
}