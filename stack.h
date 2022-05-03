#define MAX_SIZE 1024

typedef struct node
{
    char string[MAX_SIZE];
    struct node *next;
} node;


int div_round(int a , int b);
void* malloc_X(size_t size);
void free_X(void* ptr);
node *push(char *element, node *head);
node *pop(node *head);
void destroy_stack(node *p);
void display(node *head);
char *show_top(node *head);
int firstWordI(int size, const char *line);