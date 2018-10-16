<h1>Managing Memory</h1>
On all computer systems memory is a scarce resource. No matter how much memory is available, it never seems to be enough. It doesn’t seem so long ago that 256MB of RAM was considered sufficient, but now 2GB of RAM is commonplace as a sensible minimum requirement even for desktop systems, with servers usefully having significantly more.


Linux provides protection so that different applications are protected from each other, and it allows applications to apparently access more memory than is physically present in the machine, provided the machine is at least well configured and has sufficient swap space.

<h1>Simple Memory Allocation</h1>
You allocate memory using the malloc call in the standard C library. Also that the size parameter that specifies the number of bytes to allocate isn’t a simple int, although it’s usually an unsigned integer type. MS-DOS-based programs cannot access memory outside the base 640K memory map of PCs.

The program memory1 asks the malloc library to give it a pointer to a megabyte of memory. You check to ensure that malloc was successful and then use some of the memory to show that it exists. When you run the program, you should see Hello World printed out, showing that malloc did indeed return the megabyte.

Malloc returns a void * pointer, you cast the result to the char * that you need. The malloc function is guaranteed to return memory that is aligned so that it can be cast to a pointer of any type.
