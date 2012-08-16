//#Enter your code here
#include <iostream>
#include <limits.h>
#include <stdio.h>
using namespace std;

char ** list;
char ** startList = NULL;
char ** endList = NULL;
int currentSize = 0;
int maxSize = 0;

int insert ();
int remove ();
int display ();

int insert () {
    char *string = (char *)malloc (sizeof(char)*100);
    cin >> string;
    if (endList == startList && currentSize > 0) {
        remove();
    }

    (*endList) = string;
    endList ++;
    currentSize ++;
    if (endList == list + maxSize ) {
        endList = list;
    }
}

int remove () {
    if (endList == startList && currentSize == 0) 
        return -1;
    
    char * currentString = *startList;
    startList ++;
    currentSize --;
    if (startList == list + maxSize ) {
        startList = list;
    }
    free (currentString);
}

int display () {
    char ** iter = startList;
    int restToPrint = currentSize;
    while (restToPrint != 0) {
        cout << *iter << endl;
        iter ++;
        restToPrint--;
        if (iter == list + maxSize) 
            iter = list;
    }
}

int main (){
    cin >> maxSize;
    
    list = (char **) malloc (sizeof (char*) * maxSize);
    startList = list;
    endList = list;

    char comd;
    int count;
    cin >> comd;
    while (comd != 'Q') {
        if (comd == 'A') {
            cin >> count;
            for (int i=0; i<count; i++) 
                insert();
        } else if (comd == 'R'){
            cin >> count;
            for (int i=0; i<count; i++) 
                remove();
        } else if (comd == 'L'){
            display();
        }
        
        cin >> comd;
    }
    
    
}

