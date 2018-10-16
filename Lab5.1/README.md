<h1>Managing Memory</h1>
On all computer systems memory is a scarce resource. No matter how much memory is available, it never seems to be enough. It doesn’t seem so long ago that 256MB of RAM was considered sufficient, but now 2GB of RAM is commonplace as a sensible minimum requirement even for desktop systems, with servers usefully having significantly more.


Linux provides protection so that different applications are protected from each other, and it allows applications to apparently access more memory than is physically present in the machine, provided the machine is at least well configured and has sufficient swap space.

<h1>Freeing Memory</h1>
The Linux memory management system is quite capable of reliably ensuring that memory is returned to the system when a program ends. Programs that use memory on a dynamic basis should always release unused memory back to the malloc memory manager using the free call. This enables separate blocks to be remerged and enables the malloc library to look after memory, rather than have the application manage it.


If a page of memory is not being used, then the Linux memory manager will be able to move it from physical memory to swap space, where it has little impact on the use of resources. If the program tries to access data inside the memory page that has be moved to swap space, then Linux will very briefly suspend the program, move the memory page back from swap space into physical memory again, and then allow the program to continue, just as though the data had been in memory all along. The memory6 program simply shows how to call free with a pointer to some previously allocated memory.
