/* Enter your code here. Read input from STDIN. Print output to STDOUT */

enum loc {
    left,
    right,
    top,
    bottom, 
    center
};

int maxGroupCount = 2;
int groupCount = 0;

void markIndex( int *array, int index ) {  
  array[index] = maxGroupCount;
  maxGroupCount ++;
  groupCount ++;
}

void mergeIndex( int *array, int size, int index1, int index2 ) {
  int i =0;
  groupCount --;

  for (i=0; i< size+2; i++)
    if (array[index2-i] == array[index1])
      array[index2-i] = array [index2];
}

int connectComponents( int *array, int size, int index, int indexKnown ) {
  if (array[index] == 0 ) 
    return 1;
  
  if ( array[indexKnown] == 1) {
    array[ indexKnown] = array[index];
    return 0;
  }
  
  if ( array[index] != array[indexKnown]) {
    mergeIndex(array, size, index, indexKnown);
  }
  return 0;
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
              isNew &= connectComponents( array, size, index - size + 1, index );
              isNew &= connectComponents( array, size, index - size, index );
            }
        else if (locationX==right)
            if (locationY == top) {
              isNew &= connectComponents( array, size, index - 1, index );
            } else {
              isNew &= connectComponents( array, size, index - 1, index );
              isNew &= connectComponents( array, size, index - size, index );
              isNew &= connectComponents( array, size, index - size - 1, index );
            }
        else 
            if (locationY == top) {
              isNew &= connectComponents( array, size, index - 1, index );
            } else {
              isNew &= connectComponents( array, size, index - 1, index );
              isNew &= connectComponents( array, size, index - size - 1, index );
              isNew &= connectComponents( array, size, index - size, index );
              isNew &= connectComponents( array, size, index - size + 1, index );
            }
    }
  
    if (isNew)
      markIndex( array, index);
}

int getComponent(int *array, int size) {

  maxGroupCount = 2;
  groupCount = 0;

  int i = 0;
  for (i=0; i<size*size; i++)
    if (array[i]==1)
      markConnectedComponent( array, size, i);
  
  return groupCount;
}

int main()
{
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

