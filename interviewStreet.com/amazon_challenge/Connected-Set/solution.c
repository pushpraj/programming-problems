/* Enter your code here. Read input from STDIN. Print output to STDOUT */

enum loc {
    left,
    right,
    top,
    bottom, 
    center
};

void markConnectedComponent ( int *array, int size, int index, int mark )
{
    int locationX = center;
    int locationY = center; 
    if (array[index] == 1) {
        array[index] = mark;
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
                markConnectedComponent( array, size, index + 1, mark );
                markConnectedComponent( array, size, index + size, mark );
                markConnectedComponent( array, size, index + size + 1, mark );
            } else if (locationY == bottom) {
                markConnectedComponent( array, size, index + 1, mark );
                markConnectedComponent( array, size, index - size, mark );
                markConnectedComponent( array, size, index - size + 1, mark );
            } else {
                markConnectedComponent( array, size, index + 1, mark );
                markConnectedComponent( array, size, index + size, mark );
                markConnectedComponent( array, size, index + size + 1, mark );
                markConnectedComponent( array, size, index - size, mark );
                markConnectedComponent( array, size, index - size + 1, mark );
            }
        else if (locationX==right)
            if (locationY == top) {
                markConnectedComponent( array, size, index - 1, mark );
                markConnectedComponent( array, size, index + size, mark );
                markConnectedComponent( array, size, index + size - 1, mark );
            } else if (locationY == bottom) {
                markConnectedComponent( array, size, index - 1, mark );
                markConnectedComponent( array, size, index - size, mark );
                markConnectedComponent( array, size, index - size - 1, mark );
            } else {
                markConnectedComponent( array, size, index - 1, mark );
                markConnectedComponent( array, size, index + size, mark );
                markConnectedComponent( array, size, index + size - 1, mark );
                markConnectedComponent( array, size, index - size, mark );
                markConnectedComponent( array, size, index - size - 1, mark );
            }
        else 
            if (locationY == top) {
                markConnectedComponent( array, size, index - 1, mark );
                markConnectedComponent( array, size, index + size, mark );
                markConnectedComponent( array, size, index + 1, mark );
                markConnectedComponent( array, size, index + size - 1, mark );
                markConnectedComponent( array, size, index + size + 1, mark );
            } else if (locationY == bottom) {
                markConnectedComponent( array, size, index + 1, mark );
                markConnectedComponent( array, size, index - 1, mark );
                markConnectedComponent( array, size, index - size + 1, mark );
                markConnectedComponent( array, size, index - size, mark );
                markConnectedComponent( array, size, index - size - 1, mark );
            } else {
                markConnectedComponent( array, size, index - 1, mark );
                markConnectedComponent( array, size, index + 1, mark );
                markConnectedComponent( array, size, index + size, mark );
                markConnectedComponent( array, size, index - size, mark );
                markConnectedComponent( array, size, index + size - 1, mark );
                markConnectedComponent( array, size, index + size + 1, mark );
                markConnectedComponent( array, size, index - size + 1, mark );
                markConnectedComponent( array, size, index - size - 1, mark );
            }
    } else if (array[index] != 0 && array[index] != mark)
        // crash!
        *((int *)0)=0;
}

int getComponent(int *array, int size) {
    int count = 0, i = 0;
    for (i=0; i<size*size; i++)
        if (array[i]==1){
            markConnectedComponent( array, size, i, count+2 );
            count ++;
        }
    return count;   
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

