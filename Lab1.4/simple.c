#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <linux/utsname.h>

void uptim(void);
void getSystemInfo(void);
void add(int ID,char *name,int age);
void list(void);

typedef struct{
	int ID;
	char *name;
	int age;
}student;

student students[10];
int count=0;

void add(int ID,char *name,int age){
	students[count].ID=ID;
	students[count].name=name;
	students[count].age=age;
	count++;
}
void list(void){
	int i;
	for(i=0;i<count;i++){
		printk("Student: %d ID: %d Name: %s Age: %d \n",i+1,students[i].ID,students[i].name,students[i].age);
	}
}

void getSystemInfo()
{
	struct new_utsname	*uts=utsname();
	printk("Sysname: %s\n",uts->sysname);
	printk("Release: %s\n",uts->release);
	printk("Nodename: %s\n",uts->nodename);
	printk("Version: %s\n",uts->version);
	printk("Machine: %s\n",uts->machine);
}
void uptim()
{
	printk("Uptime: %d Segundos\n",jiffies_to_msecs(get_jiffies_64())/1000);
}

/* This function is called when the module is loaded. */
int simple_init(void)
{
	printk(KERN_INFO "Initialization Module\n");
	uptim();
	getSystemInfo();
	add(1234,"Alejandro Godoy",21);
	add(4567,"Ramon Gradilla",22);
	add(1234,"Jorge Fernando",20);
	list();
	return 0;
}


/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Termination Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
