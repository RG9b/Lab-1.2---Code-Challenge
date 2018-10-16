<h1>Managing Memory</h1>
On all computer systems memory is a scarce resource. No matter how much memory is available, it never seems to be enough. It doesn’t seem so long ago that 256MB of RAM was considered sufficient, but now 2GB of RAM is commonplace as a sensible minimum requirement even for desktop systems, with servers usefully having significantly more.
Linux provides protection so that different applications are protected from each other, and it allows applications to apparently access more memory than is physically present in the machine, provided the machine is at least well configured and has sufficient swap space.

<h1>Simple Memory Allocation</h1>
You allocate memory using the malloc call in the standard C library. Also that the size parameter that specifies the number of bytes to allocate isn’t a simple int, although it’s usually an unsigned integer type. MS-DOS-based programs cannot access memory outside the base 640K memory map of PCs.
The program memory1 asks the malloc library to give it a pointer to a megabyte of memory. You check to ensure that malloc was successful and then use some of the memory to show that it exists. When you run the program, you should see Hello World printed out, showing that malloc did indeed return the megabyte.
Malloc returns a void * pointer, you cast the result to the char * that you need. The malloc function is guaranteed to return memory that is aligned so that it can be cast to a pointer of any type.

<h1>Allocating Lots of Memory</h1>
Linux exceed the limitations of the MS-DOS memory model. The memory2 program asks to allocate somewhat more memory than is physically present in the machine, so you might expect malloc to start failing somewhere a little short of the actual amount of memory present, because the kernel and all the other running processes are using some memory.
The program simply loops, asking for more and more memory, until it has allocated twice the amount of memory you said your machine had when you adjusted the define PHY_MEM_MEGS. The surprise is that it works at all, because we appear to have created a program that uses every single byte of physical memory on the author’s machine. Notice that we use the size_t type for our call to malloc.

<h1>Available Memory</h1>
The memory3 program has allocated, and accessed, more memory than this author physically has in his machine at the time of writing. Finally, the system protects itself from this rather aggressive program and kills it. On some systems it may simply exit quietly when malloc fails.
The application’s allocated memory is managed by the Linux kernel. Each time the program asks for memory or tries to read or write to memory that it has allocated, the Linux kernel takes charge and decides how to handle the request.
Initially, the kernel was simply able to use free physical memory to satisfy the application’s request for memory, but once physical memory was full, it started using what’s called swap space. On Linux, this is a separate disk area allocated when the system was installed.
The Linux kernel does all the management for you. The kernel moves data and program code between physical memory and the swap space so that each time you read or write memory, the data always appears to have been in physical memory, wherever it was actually located before you attempted to access it. Eventually, when the application exhausts both the physical memory and the swap space, or when the maximum stack size is exceeded, the kernel finally refuses the request for further memory and may preemptively terminate the program.

<h1>Abusing Memory</h1>
Suppose you try to do “bad” things with memory. In the memory4 program allocate some memory and then attempt to write past the end.
The Linux memory management system has protected the rest of the system from this abuse of memory. To ensure that one badly behaved program (this one) can’t damage any other programs, Linux has terminated it.
Each running program on a Linux system sees its own memory map, which is different from every other program’s. Only the operating system knows how physical memory is arranged, and not only manages it for user programs, but also protects user programs from each other.

<h1>The Null Pointer</h1>
Modern Linux systems are very protective about writing or reading from the address referred to by a null pointer, although the actual behavior is implementation specific.
In the memory5a program you try to access a null pointer. The first printf attempts to print out a string obtained from a null pointer; then the sprintf attempts to write to a null pointer. In this case, Linux (in the guise of the GNU “C” library) has been forgiving about the read and has simply provided a “magic” string containing the characters (null). It hasn’t been so forgiving about the write and has terminated the program.
In the memory5b there is no GNU libc library between you and the kernel now, and the program is terminated.

<h1>Freeing Memory</h1>
The Linux memory management system is quite capable of reliably ensuring that memory is returned to the system when a program ends. Programs that use memory on a dynamic basis should always release unused memory back to the malloc memory manager using the free call. This enables separate blocks to be remerged and enables the malloc library to look after memory, rather than have the application manage it.
If a page of memory is not being used, then the Linux memory manager will be able to move it from physical memory to swap space, where it has little impact on the use of resources. If the program tries to access data inside the memory page that has be moved to swap space, then Linux will very briefly suspend the program, move the memory page back from swap space into physical memory again, and then allow the program to continue, just as though the data had been in memory all along. The memory6 program simply shows how to call free with a pointer to some previously allocated memory.

<h1>Other Memory Allocation Functions</h1>
Calloc allocates memory that can be freed with free, it has somewhat different parameters from malloc: It allocates memory for an array of structures and requires the number of elements and the size of each element as its parameters. The allocated memory is filled with zeros; and if calloc is successful, a pointer to the first element is returned. -m
The realloc function changes the size of a block of memory that has been previously allocated. It’s passed a pointer to some memory previously allocated by malloc, calloc, or realloc and resizes it up or down as requested. The realloc function may have to move data around to achieve this, so it’s important to ensure that once memory has been realloced, you always use the new pointer and never try to access the memory using pointers set up before realloc was called.
