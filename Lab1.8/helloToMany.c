
#include <pthread.h>
#include <stdio.h>
/* the thread runs in this function */

typedef struct{
	long ID;
	long iteration;
}mythread;
int num_thread;
void *runner(void *param); 
main(int argc, char *argv[])
{
	int i, scope,NUM_THREADS,num_thread=0;
	printf("Enter the number of threads: ");
	scanf("%d",&NUM_THREADS);
	mythread threads[NUM_THREADS];
	pthread_t tid[NUM_THREADS]; 
	pthread_attr_t attr; 		

	pthread_attr_init(&attr);
	if (pthread_attr_getscope(&attr,&scope) != 0)
		fprintf(stderr, "Unable to get scheduling scope.\n");
	else {
		num_thread++;
		if (scope == PTHREAD_SCOPE_PROCESS)
			printf("PTHREAD_SCOPE_PROCESS\n");
		else if (scope == PTHREAD_SCOPE_SYSTEM){
			printf("PTHREAD_SCOPE_SYSTEM\n");
		}else 
			fprintf(stderr,"Illegal scope value.\n");
	}
	if (pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM) != 0)
	//if (pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS) != 0) //en clase
		printf("unable to set scheduling policy.\n");

	for (i = 0; i < NUM_THREADS; i++){
		threads[i].ID=rand()%(NUM_THREADS*10);
		threads[i].iteration=i;
		pthread_create(&tid[i],&attr,runner,(void*)&threads[i]); 
		//pthread_create(&tid[i],&attr,runner,NULL);//en clase
		printf("I am thread %d. Created new thread (%ld) in iteration %d...\n",num_thread,threads[i].ID,threads[i].iteration);
		
		if ((i+1)%5==0) sleep(1);
	}
	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(tid[i], NULL);
}

void *runner(void *param) 
{
	mythread *tid=param;
	printf("Hello from thread %d - I was created in iteration %ld\n",tid->ID,tid->iteration);
	
	pthread_exit(0);
}

