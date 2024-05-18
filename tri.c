#include<stdio.h>
#include<stdlib.h>


struct trie{
	struct trie *next[26];
	int is_end;
	int prefix_count;
};
typedef struct trie TRIE;

TRIE buffer[2000000];
int buffer_count = 0;
TRIE *root;
char str[25];
int count = 0;

TRIE *get_trie_node()
{
	TRIE *temp;
	int i;
	temp = &buffer[buffer_count];
	buffer_count++;
#if 1
	for (i = 0; i < 26; i++) 
		temp->next[i] = NULL;
	temp->is_end = 0;
	temp->prefix_count = 0;
#endif
	return(temp);
}

void print_trie(TRIE *root, int len)
{
	int i;
	if (!root)
		return;
	if (root->is_end) {
		str[len] = '\0';
		//printf("str = %s\n", str);
		count++;
	}
	for (i = 0; i < 26; i++) {
		str[len] = 'a' + i;
		print_trie(root->next[i], len + 1);
	}
}

int search_in_trie(char *ch)
{
	int index;
	TRIE *temp = root;
	while (*ch) {
		index = *ch - 'a';
		if (temp->next[index])
			temp = temp->next[index];
		else
			return 0;
		ch++;
	}
	count = 0;
//	print_trie(temp, 0);
	return(temp->prefix_count);
}


void insert_in_trie(char *ch)
{
	int i;
	TRIE *temp = root;
	int x;

	while (*ch) {
		x = *ch - 'a';
		if (!temp->next[x])
			temp->next[x] = get_trie_node();
		temp = temp->next[x];
		temp->prefix_count++;
		ch++;
	}
	temp->is_end = 1;
}

int my_strcmp(char *s1, char *s2)
{
	while ( *s1 == *s2 ) {
		if (*s1 == '\0')
			return 0;
		s1++;
		s2++;
	}
	return (*s1 - *s2);

}



int main()
{
	int t;
	char query_type[10];
	char string[30];
	int x;
	x = scanf("%d", &t);
	root = get_trie_node();
	while(t--) {
		x = scanf("%s %s", query_type, string);
		if (!my_strcmp(query_type, "add"))
			insert_in_trie(string);
		else if(!my_strcmp(query_type, "find"))
			printf("%d\n", search_in_trie(string));
	}
	return 0;
}
