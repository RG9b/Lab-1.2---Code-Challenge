#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

#define MAX_T 5
#define COLUMN_SIZE 2000
#define ROW_SIZE 2000
#define FULL_SIZE COLUMN_SIZE*ROW_SIZE
#define PATH_A "./matA.dat"
#define PATH_B "./matB.dat"

pthread_mutex_t *mutexes;
long *result, *matrix,*matrixA,*matrixB,*tmpRow,*tmpCol,**buffers,NUM_BUFFERS;
pthread_t tid[ROW_SIZE];


long * readMatrix(char *filename)
{
	FILE *fp;
	fp = fopen(filename, "r");
	int i;
	for(i=0;i<FULL_SIZE;i++)
	{
        	fscanf(fp,"%ld",&matrix[i]);
	}
	fclose(fp);
	return matrix;
}

long *getColumn(int col, long *matrix)
{
	int i;
	for(i=0; i<COLUMN_SIZE;i++)
	{
		tmpCol[i] = matrix[(COLUMN_SIZE*i)+col];
	}
	return tmpCol;
}

long *getRow(int row, long *matrix)
{
	int i;
	for(i=0; i<ROW_SIZE;i++)
	{
		tmpRow[i] = matrix[ROW_SIZE*row+i];
	}
	return tmpRow;
}

int getLock(){
	int i;
	for(i=0;i<NUM_BUFFERS;i++){
		if(pthread_mutex_trylock(&mutexes[i])==0){
			return i;
		}
	}
	return -1;
}

int releaseLock(int lock){
	if(pthread_mutex_unlock(&mutexes[lock])==0){
		return 0;
	}
	return -1;
}

long dotProduct(long *vec1,long *vec2){
	int i;
	long r=0;
	for(i=0;i<ROW_SIZE;i++){
		r=r+(vec1[i]*vec2[i]);
	}
	return r;
}

void *runner(void *param) 
{
	int buff,i;
	while((buff=getLock())==-1);
	for(i=0;i<COLUMN_SIZE;i++){
		buffers[buff][i]=dotProduct(getRow((int)param,matrixA),getColumn(i,matrixB));
	}
	for(i=0;i<COLUMN_SIZE;i++){
		result[(int)param*ROW_SIZE+i]=buffers[buff][i];
	}
	printf("buffer: %ld\n",buff);

	releaseLock(buff);
	pthread_exit(0);
}

long *multiply(long *matA, long *matB){ 
	int i,p,colu=0;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	for(p=0;p<(ROW_SIZE/MAX_T);p++){
		for(i=0;i<MAX_T;i++){	
			pthread_create(&tid[i],&attr,runner,(void *)colu);
			colu++;
		}
		for(i=0;i<MAX_T;i++)
			pthread_join(tid[i],NULL);
	}
	return result;
}

int saveResultMatrix(long *result){
	int i;
	FILE *fp = fopen("result.dat","w");
	if (fp==NULL) return -1;

	for(i=0;i<FULL_SIZE;i++){
		fprintf(fp,"%ld\n",result[i]);
	}
	fclose(fp);
	return 0;
}

int main(int argc, char *argv[])
{
	long i;
	long *res;
	printf("Number of buffers wanted: ");
	scanf("%d",&NUM_BUFFERS);
	matrixA=malloc(FULL_SIZE*sizeof(long));
	matrixB=malloc(FULL_SIZE*sizeof(long));
	matrix=malloc(FULL_SIZE*sizeof(long));
	result=malloc(FULL_SIZE*sizeof(long));
	res=malloc(FULL_SIZE*sizeof(long));
	tmpCol = malloc(ROW_SIZE*sizeof(long));
	tmpRow = malloc(ROW_SIZE*sizeof(long));
	mutexes=malloc(NUM_BUFFERS*sizeof(pthread_mutex_t));

	buffers=malloc(NUM_BUFFERS*sizeof(long*));
	for(i=0;i<NUM_BUFFERS;i++){
		buffers[i]=malloc(ROW_SIZE*sizeof(long));
		pthread_mutex_init(&mutexes[i],NULL);
	}

	//memcpy(tmpRow,getRow(0,matrixA),ROW_SIZE*sizeof(long));
	//memcpy(tmpCol,getColumn(0,matrixB),ROW_SIZE*sizeof(long));
	//printf("%ld \n",matrixA[0]);
	//printf("%ld \n",matrixA[3999999]);
	//getRow(1, matrixA);
	//printf("%ld \n",dotProduct(tmpRow,tmpCol));
	memcpy(matrixA,readMatrix(PATH_A),FULL_SIZE*sizeof(long));
	memcpy(matrixB,readMatrix(PATH_B),FULL_SIZE*sizeof(long));
	memcpy(res,multiply(matrixA,matrixB),FULL_SIZE*sizeof(long));
	//printf("%ld\n",res[0]);
	saveResultMatrix(res);
	free(buffers);
	free(mutexes);
	free(matrixA);
	free(matrixB);
	free(result);
	free(tmpCol);
	free(tmpRow);
	//getRow(0,matrixA);
	//pthread_mutex_destroy(mutexes);
	return 0;
}

