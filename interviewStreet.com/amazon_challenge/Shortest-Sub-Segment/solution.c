
#include <string.h>
#include <limits.h>

typedef int tag;
#define NoTag -1

int *hash = NULL;
int hashSize = 0;
tag maxTag = NoTag;

int hashForString(char *word) {
  if (*word == 0)
    return 0;
  return hashForString (word+1) * 31 + (*word);
}

void insertInWordTrie (char* word) {
  tag already = searchInWordTrie (word);
  if (already != NoTag)
    return;
  
  if (hashSize <= maxTag +1 ) {
    hashSize += 10;
    hash = (int *)realloc (hash, sizeof(int)*hashSize);
  }
  maxTag++;
  hash[maxTag] = hashForString(word);
  return;
}

tag searchInWordTrie (char* word) {
  int i =0;
  int hashString = hashForString(word);
  for (i=0; i< maxTag +1; i++) {
    if (hash[i]==hashString)
      return i;
  }
  return NoTag;
}


struct queueWordInstance {
  char *ptr;
  tag wordTag;
  struct queueWordInstance *next;
};

typedef struct queue{
  struct queueWordInstance *start;
  struct queueWordInstance *end;
  int length;
} queue;

tag getHeadTagInQueue(queue *wordQueue) {
  return wordQueue -> start -> wordTag;
}

void insertAtEndInQueue(queue **wordQueue, char *iterWord, tag wordTag) {
  if ((*wordQueue) == NULL) {
    (*wordQueue) = (struct queue *)malloc (sizeof (struct queue));
    memset (*wordQueue, 0, sizeof (queue));
  }
  
  queue *currentQueue = *wordQueue;
  struct queueWordInstance *instance = (struct queueWordInstance *)malloc (sizeof(struct queueWordInstance));
  instance -> ptr = iterWord;
  instance -> wordTag = wordTag;
  instance -> next = NULL;
  
  if (currentQueue -> end)
    currentQueue -> end -> next = instance;
  
  currentQueue -> end = instance;
  if (currentQueue -> start == NULL)
    currentQueue -> start = instance;

  currentQueue -> length = currentQueue -> end -> ptr - currentQueue -> start -> ptr + strlen(currentQueue -> end -> ptr);
  return;
}

void deleteHeadInQueue( queue **wordQueue ) {
  struct queueWordInstance *instance = NULL;
  if ( (*wordQueue)-> start == (*wordQueue)->end ) {
    instance = (*wordQueue)-> start;
    free( *wordQueue );
    *wordQueue = NULL;
  } else {
    instance = (*wordQueue)-> start;
    (*wordQueue)-> start = (*wordQueue)-> start -> next;
    queue *currentQueue = *wordQueue;
    currentQueue -> length = currentQueue -> end -> ptr - currentQueue -> start -> ptr + strlen(currentQueue -> end -> ptr);
  }
  
  free (instance);
  return;
}

struct queueWordInstance *dupWordInstance( struct queueWordInstance *srcQueue ) {
  struct queueWordInstance *dest = (struct queueWordInstance *) malloc (sizeof(struct queueWordInstance));
  dest -> ptr = srcQueue -> ptr;
  dest -> wordTag = srcQueue -> wordTag;
  dest -> next = NULL;
}

void copyQueueInstance ( queue *srcQueue, queue **destQueue ) {
  if ( *destQueue != NULL )
    free (*destQueue);
  
  (*destQueue) = (queue *)malloc (sizeof(queue));
  (*destQueue)->start = dupWordInstance(srcQueue->start);
  (*destQueue)->end   = dupWordInstance(srcQueue->end);
  (*destQueue)->length = srcQueue->length;
}

int main() {
  char* inputLine = (char*)malloc(sizeof(char)*200001);
  gets(inputLine);
  
  int wordCount = 0;
  scanf("%d", &wordCount);
  
  char word[16];
  int i=0;
  for (i=0; i<wordCount; i++) {
    scanf("%s",word);
    insertInWordTrie (word);
  }
  
  tag *tagList = (tag *)malloc (sizeof(tag)*(maxTag+1));
  memset (tagList, 0, sizeof(tag)*(maxTag+1));
  int currentTagCount = 0;
  
  queue *wordQueue = NULL;
  queue *bestSubSegQueue = NULL;
  
  char *iterWord = inputLine;
  for (iterWord = strtok(inputLine, " "); iterWord ; iterWord = strtok(NULL, " ") ) {
    tag wordTag = searchInWordTrie (iterWord);
    if (wordTag == NoTag) 
      continue;
    
    // mark tag in tagList
    tagList[wordTag] ++;
    // maintain no of found words till now in window
    if (tagList[wordTag] == 1) 
      currentTagCount ++;
    
    //insert the word in wordQueue
    insertAtEndInQueue( &wordQueue, iterWord, wordTag );
    
    // if atleast one occurence of word is found
    if (currentTagCount == (maxTag +1)) {
      // try to reduce words from left
      while (tagList[ getHeadTagInQueue(wordQueue) ] > 1 ) {
        deleteHeadInQueue(&wordQueue);
      }
      
      // compare if shortest sub-segment and save accordingly
      if (bestSubSegQueue == NULL || bestSubSegQueue->length > wordQueue -> length) {
        copyQueueInstance( wordQueue, &bestSubSegQueue);
      }
    }
  }
  
  //print answer
  char *startStr = wordQueue -> start -> ptr;
  while (startStr != wordQueue -> end -> ptr) {
    if (*startStr == 0)
      printf(" ");
    else 
      printf("%c", *startStr);
  }
  printf ("%s",wordQueue ->end -> ptr);
  return;
}

