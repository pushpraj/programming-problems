/* Enter your code here. Read input from STDIN. Print output to STDOUT */

enum loc {
    left,
    right,
    top,
    bottom, 
    center
};

#define setSize 100000
int *directPtr, *actualSet, actualSetSize, directPtrSize;

int connectComponents( int *array, int index, int indexKnown ) {
  if (array[index] == 0 ) 
    return 1;
  
  if ( array[indexKnown] == 1) {
    array[ indexKnown] = array[index];
    return 0;
  }
  
  if ( array[index] == array[indexKnown]) {
    return 0;
  }
  
  if (directPtr [ array[index] ] > directPtr[ array[indexKnown] ]) {
    actualSet[ directPtr[ array[index] ] ] = -1;
    directPtr [ array[index] ] = directPtr[ array[indexKnown] ];
  } else if (directPtr [ array[index] ] != directPtr[ array[indexKnown] ]){
    actualSet[ directPtr[ array[indexKnown] ] ] = -1;
    directPtr [ array[indexKnown] ] = directPtr[ array[index] ];    
  }
  return 0;
}

void markIndex( int *array, int index ) {
  actualSetSize++;
  actualSet[actualSetSize] = actualSetSize;
  directPtrSize++;
  directPtr[directPtrSize] = actualSetSize;
  array[ index ] = directPtrSize;
}

void markConnectedComponent ( int *array, int size, int index )
{
    int locationX = center;
    int locationY = center; 
  int isNew = 1;
    if (array[index] == 1) {
        if ( index < size ) {
            locationY = top;
        } else if (index > size * (size-1)) {
            locationY = bottom;
        }
        
        if (index%size == 0) {
            locationX = left;
        } else if (index%size == size-1) {
            locationX = right;
        }
        
        if (locationX==left)
            if (locationY == top) {
              // empty
            } else {
              isNew &= connectComponents( array, index - size + 1, index );
              isNew &= connectComponents( array, index - size, index );
            }
        else if (locationX==right)
            if (locationY == top) {
              isNew &= connectComponents( array, index - 1, index );
            } else {
              isNew &= connectComponents( array, index - 1, index );
              isNew &= connectComponents( array, index - size, index );
              isNew &= connectComponents( array, index - size - 1, index );
            }
        else 
            if (locationY == top) {
              isNew &= connectComponents( array, index - 1, index );
            } else {
              isNew &= connectComponents( array, index - 1, index );
              isNew &= connectComponents( array, index - size - 1, index );
              isNew &= connectComponents( array, index - size, index );
              isNew &= connectComponents( array, index - size + 1, index );
            }
    }
  
    if (isNew)
      markIndex( array, index);
}

int getComponent(int *array, int size) {
    int count = 0, i = 0;
    actualSetSize = -1;
    directPtrSize = 1;
    for (i=0; i<size*size; i++)
        if (array[i]==1){
            markConnectedComponent( array, size, i);
       }
    for (i=0; i<actualSetSize+1; i++)
      if (actualSet[i]!=-1)
        count ++;
    return count;   
}

int main()
{
  directPtr = (int *)malloc(sizeof(int)*setSize);
  actualSet = (int *)malloc(sizeof(int)*setSize);

    int size;
    int testcaseCount;
    int *array, i;
    
    scanf("%d",&testcaseCount);
    while(testcaseCount--){
        scanf("%d",&size);
        array = (int*)malloc(sizeof(int)*(size*size));
        for (i=0; i<size*size; i++)
            scanf("%d",array+i);
        
        int count = getComponent(array, size);
        printf("%d\n",count);
        
        free(array);
    }
}

