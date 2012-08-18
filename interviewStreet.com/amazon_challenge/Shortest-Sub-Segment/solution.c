
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
  char ch = *word;
  if (ch >= 'a' && ch <= 'z')
    ch = ch -'a' + 'A';
  return hashForString (word+1) * 31 + ch;
}

void insertInWordTrie (char* word) {
  tag already = searchInWordTrie (word);
  if (already != NoTag)
    return;
  
  if (hash == NULL ) {
    hash = (int *)malloc (sizeof(int)*100);
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
  return dest;
}

void copyQueueInstance ( queue *srcQueue, queue **destQueue ) {
  if ( *destQueue != NULL )
    free (*destQueue);
  
  (*destQueue) = (queue *)malloc (sizeof(queue));
  (*destQueue)->start = dupWordInstance(srcQueue->start);
  (*destQueue)->end   = dupWordInstance(srcQueue->end);
  (*destQueue)->length = srcQueue->length;
}

void getString( char* inputLine ){
  char c;

  int index = 0;
  while ( (c= getchar()) != '\n') {
    if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ' ) {
      inputLine[index] = c;
      index ++;
    }
  }
  return;
}

int main() {
  char* inputLine = (char*)malloc(sizeof(char)*200001);
  getString(inputLine);
  
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
      tag headTag = getHeadTagInQueue(wordQueue);
      while (tagList[ headTag ] > 1 ) {
        tagList[ headTag ] --;
        deleteHeadInQueue(&wordQueue);
        headTag = getHeadTagInQueue(wordQueue);
      }
      
      // compare if shortest sub-segment and save accordingly
      if (bestSubSegQueue == NULL || bestSubSegQueue->length > wordQueue -> length) {
        copyQueueInstance( wordQueue, &bestSubSegQueue);
      }
    }
  }
  
  //print answer
  if (bestSubSegQueue) {
    char *startStr = bestSubSegQueue -> start -> ptr;
    while (startStr != bestSubSegQueue -> end -> ptr) {
      if (*startStr == 0)
        printf(" ");
      else 
        printf("%c", *startStr);
      startStr ++;
    }
    printf ("%s",bestSubSegQueue ->end -> ptr);
  } else {
    printf ("NO SUBSEGMENT FOUND");
  }
  return;
}

