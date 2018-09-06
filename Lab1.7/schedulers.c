#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

enum estados{READY,RUN,WAIT,IDLE};

typedef struct{
	int ID,priority,time,time_creation;
	enum estados state;
}process;

char* rstate(int r){
	if(r==0){
		return "READY";
	}else if(r==1){
		return "RUN";
	}else if(r==2){
		return "WAIT";
	}else{
		return "IDLE";
	}
}

process tasks[10];

void createTask(int ID1,int priority1,int time1,int time_creation1){
	tasks[ID1].ID=ID1;
	tasks[ID1].priority=priority1;
	tasks[ID1].time=time1;
	tasks[ID1].time_creation=time_creation1;
	tasks[ID1].state=0;
}
void printTasks(){
	int i;
	printf("Tareas ordenadas:\n");
	for (i=0;i<10;i++){
	printf("ID:%d priority:%d burst time:%d estado:%s \n",tasks[i].ID,tasks[i].priority,tasks[i].time,rstate(tasks[i].state));
	}
}
void Schedul(int comp)
{
	int i, j;
	process key;
   for (i = 1; i < 10; i++)
   {
       key = tasks[i];
       j = i-1;
	if(comp==1){
	       while (j >= 0 && tasks[j].time_creation > key.time_creation)
	       {
		   tasks[j+1] = tasks[j];
		   j = j-1;
	       }
	}else if(comp==2){
	       while (j >= 0 && tasks[j].time > key.time)
	       {
		   tasks[j+1] = tasks[j];
		   j = j-1;
	       }
	}else if(comp==3){
	       while (j >= 0 && tasks[j].priority > key.priority)
	       {
		   tasks[j+1] = tasks[j];
		   j = j-1;
	       }
	}else if(comp==4){
	       while (j >= 0 && tasks[j].time_creation > key.time_creation)
	       {
		   tasks[j+1] = tasks[j];
		   j = j-1;
	       }
	}
       tasks[j+1] = key;
   }
	printTasks();
}

void RUUN(){
	int i=0;
	int count;
	for(i=0;i<10;i++){
		tasks[i].state=1;
		printf("Esta corriendo la tarea: %d, estado: %s\n",tasks[i].ID,rstate(tasks[i].state));
		count=0;
		while(tasks[i].time!=0){
			tasks[i].time--;
			count++;
		}
		tasks[i].state=3;		
		printf("Termino la tarea: %d, tardo: %d segundos, estado: %s\n",tasks[i].ID,count,rstate(tasks[i].state));
	}
}

void devolver(){
	process temp;
	int i;
	temp=tasks[0];
	for(i=0;i<9;i++){
		tasks[i]=tasks[i+1];
	}
	tasks[9]=temp;
}
void RR(int tiempo_q){
	int i=0;
	while(i<8){
		if(tasks[0].state==0){
			tasks[0].state=1;
			printf("Esta corriendo la tarea:%d, estado:%s, tiempo restante:%d segundos\n",tasks[0].ID,rstate(tasks[i].state),tasks[0].time);
			tasks[0].time=tasks[0].time-tiempo_q;
			if(tasks[0].time>0){
				tasks[0].state=0;
				printf("Se interrumpio la tarea:%d, tiempo restante de la tarea:%d segundos, estado:%s\n",tasks[0].ID,tasks[0].time,rstate(tasks[0].state));
			}else{
				tasks[0].state=3;
				printf("Termino la tarea:%d, estado:%s\n",tasks[0].ID,rstate(tasks[0].state));
			}
			i=0;
			devolver();
		}else{
			i++;
			devolver();
		}
	}
}

int main(void){
	int i,tiempo_q;
	char comp;
	printf("Seleccione scheduler:\n1.-First-Come,FirstServed(FCFS)\n2.-Shortest-Job-First(SJF)\n3.-Priority Scheduling\n4.-Round-Robin Scheduling\nNumero:");
	scanf("%d",&comp);
	for (i=0;i<10;i++){
		createTask(i,rand()%100,rand()%30+1,time(NULL));
	}
	if(comp>=1&&comp<=3){
		Schedul(comp);
		RUUN();
	}else if(comp==4){
		Schedul(comp);
		tiempo_q=10;
		RR(tiempo_q);
	}else{
		printf("Numero incorrecto\n");
	}
}
