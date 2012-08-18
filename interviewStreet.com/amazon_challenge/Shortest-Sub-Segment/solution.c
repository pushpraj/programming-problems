
#include <string.h>
#include <limits.h>

typedef int tag;
#define NoTag -1

typedef struct wordTrie {
  char ch;
  struct wordTrie *nextCharList;
  int nextCharListCount;
  int tag;
} wordTrie;

wordTrie *head = NULL;
tag maxTag = NoTag;

void insertInWordTrie (char* word) {
  // todo
  if (head == NULL) {
    head = (wordTrie *)malloc (sizeof(struct wordTrie));
    head -> ch = '.';
    head -> tag = NoTag;
    head -> nextCharListCount = 0;
    head -> nextCharList = NULL;
  }
  
  wordTrie *iter = head;
  while (*word) {
    
    
    word++;
  }
}

tag searchInWordTrie (char* word) {
  //todo
  return NoTag;
}


struct queueWordInstance {
  char *ptr;
  tag wordTag;
  struct queueWordInstance *next;
};

typedef struct {
  struct queueWordInstance *start;
  struct queueWordInstance *end;
  int length;
} queue;

tag getHeadTagInQueue(queue *wordQueue) {
  return wordQueue -> start -> wordTag;
}

void insertAtEndInQueue(queue **wordQueue, char *iterWord, tag wordTag) {
  if ((*wordQueue) == NULL) {
    *wordQueue = (queue *)malloc (sizeof (queue));
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
  
  tag *tagList = (tag *)malloc (sizeof(tag)*maxTag);
  memset (tagList, 0, sizeof(tag)*maxTag);
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
    if (currentTagCount == maxTag) {
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
  char *startStr = queue -> start -> ptr;
  while (start != queue -> end -> ptr) {
    if (*startStr == 0)
      printf(" ");
    else 
      printf("%c", *startStr);
  }
  printf ("%s",queue ->end -> ptr);
  return;
}

