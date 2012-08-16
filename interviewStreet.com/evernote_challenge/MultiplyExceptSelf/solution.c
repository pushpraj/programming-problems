/* Write your code here */

int main (){

        int size = 0;
        int temp = 0;
        scanf("%d",&size);

        long long *input = malloc( sizeof(long long) * (size+2) );
        long long *forwardMult = malloc( sizeof(long long) * (size+2) );

    forwardMult[0] = forwardMult[size+1] = input[0] = input[size+1] = 1;
    
    for (int i =1; i<= size; i++ ) {
        scanf( "%d", &temp);
        input[i] = temp;
    }

    for (int i =1; i<= size; i++ ) {
        forwardMult[i] = forwardMult[i-1] * input[i];
    }
    
    for (int i =size; i>= 1; i-- ) {
        input[i] = input[i+1] * input[i];
    }
        
    for (int i=1; i<=size; i++)
       printf("%Ld\n", forwardMult[i-1]*input[i+1] );
    
    free (input);
    free (forwardMult);
    return 0;
}

