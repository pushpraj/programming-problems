
#include <stdlib.h>

int testcase() {
	int N=0, K=0;
	scanf("%d",&N);
	scanf("%d",&K);
	
	int S = N / K;

	int count = 0;
	int index = 0;
	do {
//	  if( S>K ) {
	   div_t val = div(index, S);
	   index = (K-val.quot-1) + val.rem*K;
//	  } else {
//	   div_t val = div(index, K);
//	   index = (-val.quot-1) + (val.rem+1)*S;
//	  }
	   count ++;
	} while (index != 0);

	printf("%d\n", count);	
}

int main(void) {
	int testcase_count = 0;
	scanf("%d",&testcase_count);
	
	int i = 0, j =0;
	for ( i=0; i< testcase_count; i++) {
		testcase();
	}
	
	return 0;
}
