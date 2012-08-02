

int testcase() {
	int N=0, K=0;
	scanf("%d",&N);
	scanf("%d",&K);
	
	int S = N / K;

	int count = 0;
	int index = 0;
	do {
	   int a = index / S;
	   int b = index % S;

	   index = (K-a) + b*K;
	   count ++;
	} while (index != 0);

	return count;	
}

int main(void) {
	int testcase_count = 0;
	scanf("%d",&testcase_count);
	int *ans_list = (int *) malloc( sizeof(int) * testcase_count);
	
	int i = 0, j =0;
	for ( i=0; i< testcase_count; i++) {
		ans_list[i] = testcase();
	}
	
	for ( j=0; j< testcase_count; j++) 
		printf("%d\n", ans_list[j]);
	free(ans_list);
	return 0;
}
