#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie{
  int isWord;
  struct Trie *next[26];
};

struct Trie* init()
{
  struct Trie *myTree = (struct Trie*)malloc(sizeof(struct Trie));
  myTree->isWord = 0; 
  int i;
  for(i = 0; i < 26; i++)
    myTree->next[i] = NULL;
  return myTree;
}
void insert(struct Trie *ppTrie, char *word, int k)
{
  if(k == strlen(word))
  {
    ppTrie->isWord = 1;
      return;
  }
  int nextIndex = word[k]-'a';
  if (ppTrie->next[nextIndex] == NULL)
    ppTrie->next[nextIndex] = init();
  insert(ppTrie->next[nextIndex], word, k+1);
}
int numberOfOccurances(struct Trie *pTrie, char *word,int k)
{
  if(k == strlen(word))
    return pTrie->isWord;
  int next = word[k]-'a';
  if (pTrie->next[next] == NULL)
    return 0;
  return numberOfOccurances(pTrie->next[next], word, k+1);
}
struct Trie *deallocateTrie(struct Trie *pTrie)
{
  int i;
  for(i = 0; i < 26; i++)
  {
    if(pTrie->next[i]!=NULL)
      deallocateTrie(pTrie->next[i]);
  }
  free(pTrie);
  pTrie =NULL;
  return pTrie;
}
int main(void)
{
    // read the number of the words in the dictionary
    //  parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    struct Trie* trie = init();

    for (int i = 0; i < 5; i++)
        insert(trie, pWords[i],0);

    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i],0));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}