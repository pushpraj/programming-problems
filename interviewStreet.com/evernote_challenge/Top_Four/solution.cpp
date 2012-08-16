//#Enter your code here
#include <iostream>
#include <limits.h>
using namespace std;

int maxValue[4] = {INT_MIN, INT_MIN, INT_MIN, INT_MIN};

int insert( int value ) {
    if ( value < maxValue[3])
        return -1;
    int flag = 0;
    int temp;
    for ( int i=0; i<4; i++ ) {
        if (maxValue[i] < value) {
            temp = maxValue[i];
            maxValue[i] = value;
            value = temp;
        }
    }
}    
    
int main() {
    int size = 0;
    cin >> size;

    int value;
    for (int i =0; i< size; i++ ) {
        cin >> value; 
        insert ( value );
    }
    
    for (int i = 0; i<4; i++ ) {
        cout << maxValue[i] << endl;
    }
    
    return 0;
}

