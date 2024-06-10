#include<stdio.h>
#include<stdlib.h>

struct trie{
	struct trie *next[26];
	int count;
};
typedef struct trie TRIE;

TRIE buffer[1000000];
int buffer_count;
TRIE *root;

TRIE *get_trie_node()
{
	TRIE *temp;
	int i;
	temp = &buffer[buffer_count];
	buffer_count++;
	//temp = (TRIE *)malloc(sizeof(TRIE));
	for (i = 0;i < 26; i++)
		temp->next[i] = NULL;
	temp->count = 0;
	return temp;
}


void init()
{
	buffer_count = 0;
	root = get_trie_node();
}

void insert_in_trie(char *ch)
{
	TRIE *temp = root;
	int index;
#ifdef DEBUG
	printf("%s-%d --> %s\n", __func__, __LINE__, ch);
#endif
	while (*ch) {
		index = *ch - 'a';
		if(!temp->next[index])
			temp->next[index] = get_trie_node();
		temp = temp->next[index];
		temp->count++;
		ch++;
	}

}

void search_in_trie(char *ch)
{
	TRIE *temp = root;
	int index;
#ifdef DEBUG
	printf("%s-%d --> %s\n", __func__, __LINE__, ch);
#endif
	while (*ch) {
		index = *ch - 'a';
		if (!temp->next[index]) {
			printf("0\n");
			return;
		}	
		temp = temp->next[index];
		ch++;
	}
	printf("%d\n", temp->count);
}


int main()
{
	int N, Q;
//	char q[500];
char w[1000000];
	int t;
	t = scanf("%d %d",&N, &Q);
	init();
	while(N--) {
		t = scanf("%s", w);
		insert_in_trie(w);
	}
	while (Q--) {
		t = scanf("%s", w);
		search_in_trie(w);
	} 
	return 0;
}

