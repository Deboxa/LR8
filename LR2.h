#ifndef LR2
#define LR2


#define MAX_STR_SIZE 500
#define MAX_TOKEN_SIZE 100


typedef struct _node
{
	char token[MAX_TOKEN_SIZE];
	struct _node* prev;
	struct _node* next;
} node;

int lr2(void);

int is_vowel(char* token);

void print_node(node* head);

void free_node(node* head);

void modify_nodes(node* head);

void add_node(node** head, char* token);

node* create_node(char* token);

int input_validation(const char* str);

int is_latin(char sim);


#endif