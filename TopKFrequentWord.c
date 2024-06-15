#include<stdio.h>
#include<stdlib.h>

struct trie{
	struct trie *next[26];
	int is_end;
};
typedef struct trie TRIE;
TRIE buffer[100000];
int buffer_count = 0;
TRIE *root;
struct ll{
	int idx;
	struct ll *next;
};
typedef struct ll LL;
LL ll_buffer[100000];
int ll_buffer_count = 0;

LL *freq_map[102]  = {NULL};
char master_db[505][11];
int masterdb_count = 0;
int freq[505];
int visited[505];

void my_strcpy(char *dest, char *src)
{
	while(*src) {
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';
}

TRIE *get_trie_node()
{
	TRIE *temp;
	int i;
	temp = &buffer[buffer_count++];
	for(i=0;i<26;i++)
		temp->next[i] = NULL;
	temp->is_end = 0;
	return temp;
}

LL *get_ll_node(int idx)
{
	LL *temp;
	temp = &ll_buffer[ll_buffer_count++];
	temp->next = NULL;
	temp->idx = idx;

	return temp;
}

int insert_in_trie(char *ch)
{
	int index;
	TRIE *temp = root;
	while(*ch) {
		index = *ch - 'a';
		if(!temp->next[index])
			temp->next[index] = get_trie_node();
		temp = temp->next[index];
		ch++;
	}
	if(!temp->is_end)
		temp->is_end = ++masterdb_count;
	return(temp->is_end);
}

int my_strcmp(char *str1, char *str2)
{
	while(*str1 == *str2){
		if(*str1 == '\0')
			break;
		*str1++;
		*str2++;
	}

	return(*str1 - *str2);
}

void insert_in_list(LL **head_ref, int idx)
{
	LL *new_node;
	LL *temp, *prev;
	int flag = 0;

	printf("[%s - %d] --> %s\n", __func__, __LINE__, master_db[idx]);
	if (*head_ref == NULL || 
			my_strcmp(master_db[idx], master_db[(*head_ref)->idx]) < 0) {

		new_node = get_ll_node(idx);
		new_node->next =  *head_ref;
		*head_ref = new_node;
	} else {
		temp = *head_ref;
		while(temp->next && my_strcmp(master_db[idx], master_db[temp->next->idx]) >= 0 ) {
			temp = temp->next;
		}
		new_node = get_ll_node(idx);
		new_node->next = temp->next;
		temp->next = new_node;
	}
}

void init()
{
	int i;
	buffer_count = 0;
	ll_buffer_count = 0;
	masterdb_count = 0;
	root = &buffer[buffer_count++];
	for(i=0;i<102;i++)
		freq_map[i] = NULL;
	for(i=0;i<505;i++) {
		freq[i] = 0;
		master_db[i][0] = '\0';
		visited[i] = 0;
	}
	root = get_trie_node();
}
char** topKFrequent(char** words, int wordsSize, int k, int* returnSize)
{
	char **result;
	int i;
	int hash;
	LL *temp;
	int j;

	init();
	result = (char **)malloc(k * sizeof(char *));
	for(i=0;i<k;i++)
		result[i] = (char *)malloc(11*sizeof(char));

	for(i=0;i<wordsSize;i++) {
		hash = insert_in_trie(words[i]);
		if (master_db[hash][0] != '\0') {
			freq[hash]++;
			continue;
		}else {
			my_strcpy(master_db[hash], words[i]);
			freq[hash]++;
		}
	}
	for(i=0;i<wordsSize;i++) {
		hash = insert_in_trie(words[i]);
		if (!visited[hash]) {
			insert_in_list(&freq_map[freq[hash]], hash);
			visited[hash] = 1;
		}
	}
	j = 0;
	for(i=100;i>=1 && k; i--) {
		temp = freq_map[i];
		while(temp && k) {
			printf("[%s - %d] %s\n", __func__, __LINE__, master_db[temp->idx]);
			my_strcpy(result[j], master_db[temp->idx]);
			j++;
			k--;
			temp = temp->next;
		}

	}
	*returnSize = j;
	return(result);
}


int main()
{
	char **words;
	int i;
	int N, K;
	char **result;
	int result_count = 0;
	words = (char **)malloc(1000 *sizeof(char *));
	for(i=0;i<1000;i++)
		words[i] = (char *)malloc(11*sizeof(char));
	scanf("%d %d", &N, &K);
	i = 0;
	while(i<N) {
		scanf("%s", words[i]);
		i++;
	}
	topKFrequent(words, N, K, &result_count);

	return 0;
}
