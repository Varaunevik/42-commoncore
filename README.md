# get_next_line (125/100)

### Aka. the project you find out everything is a file and nothing will be the same ever again.

![Untitled](https://i.redd.it/86ccw7b8tjn61.jpg)

Let me just start off by saying that this is not financial advice, or, obviously it isn't financial advice, but you get what I mean. This is fully just my notes and they may therefore contain numerous errors, so read it with a critical eye. 

At its core, **get_next_line(GNL)** is a project that aims to develop a function that reads a file line by line. May sound simple, however, my implementation features linked lists - just because I wanted to add some spice.

It can be a little challenging to actually understand what the project is asking for (speaking from experience). [This](https://youtu.be/-Mt2FdJjVno?si=cR092PGJ0IdCx18V) video helped me gain a better understanding, and is a good starting point.

### Project requirements:

1. **Repeated Calls:** The function should be called in a loop to read the text file or standard input line by line. Each time it is called, it should return the next line from the input. 
2. **Return values:** It should return the line that was read. If there is nothing else to read or if an error occurs, it should return NULL.
3. **Terminating chars:** the returned line should include the terminating newline character, except if the end of the file was reached and it does not end with a newline character. 
4. **Buffer size:** we will use a buffer size for the read() function. The size will be defined using a compiler flag D BUFFER_SIZE=n
5. **Compilation:** the program must be compiled with and without the D BUFFER_SIZE flag, along with the usual flags. Eg. cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files.c>
6. **Undefined behaviour:** it is considered undefined behavior if the file pointed to by the file descriptor changed since the last call and read() did not reach end of file. In addition, reading binary files is forbidden unless you handle this behavior logically. 
7. **Forbidden operations:** You cannot use libft, lseek() or global variables.
8. **Bonus part:** develop GNL using only one static variable. It should be able to manage multiple file descriptors simultaneously without losing the reading thread of each file descriptor or returning a line from another file descriptor. 

## Requirements:

- The function must be able to handle multiple file descriptors simultaneously. Which means that the function must be able to read AND retrieve lines from several files at once.
- The function must be able to handle files of any length, from only a few lines to several GBs in size
- It must be able to handle a wide variety of formats, such as ASCII, UTF-8 and binary files.
- What we call a “line that has been read” is a succession of 0 to n chars that end with ‘\n’, ASCII code 0x0a or with end of file EOF.
- The string stored in the parameter “line” should not contain any newline character
- The return value can be 1, 0 or -1 depending on whether a line has been read.  **1** when a line has been read, **0** when EOF has been reached, **-1** when an error happened.

### TL;DR

I will be using linked lists to store the lines of the file. This allows me to add new lines to the end of the list and remove lines from the beginning. 

I will be using a buffer to read the file one block at a time, which reduces number of disk reads and hence improves performance of the program. 

There is also multiple edge cases that needs graceful handling, such as invalid file descriptors or end-of-file. 

In this project we use static variables to maintain state between the function calls. This allows us to keep track of the current position in the file and the remaining data in the buffer.

### Static Variables - uhm what is it really?

**Some differences between a static variable and a “normal” variable:**

| Static variables | Normal variable |
| --- | --- |
| Remains while program is running | Destroyed when a function call where the variable was declared is over |
| Stored neither in the stack nor the heap | Stored in stack  |

A static variable remains while the program is running, whereas a normal variable is destroyed when a function call where the variable was declared is over. 

Static variables are allocated memory in the data segment, not the stack segment.

> Difference between global and static variable is that static variable cannot be accessed from other files.
> 

The reason as to why we are using a static variable it is in case we want to call get_next_line multiple times or until EOF in our main. 

To better understand the difference between having a static and a “normal” variable, we can take a look at the function call results of these two seemingly similar variables:

```c
void function(void)
{
	static int = a;
	int = b;
	
	a = 10;
	b = 10;

	printf("a = %d, b = %d\n", a, b);
	a++;
	b++;
}

int	main(void)
{
	function();
	function();
	function();
	function();
	function();
	return (0);
}
```

**The result a and b after all these function calls will look very different:**

```c
a = 10, b = 10
a = 10, b = 11
a = 10, b = 12
a = 10, b = 13
a = 10, b = 14
```

Now - how would this look in the case of GNL?

The first time you call the get_next_line function in your main, it will return the first line, even if you don’t declare a static linked list. 

However, when you call it again, you will just get the first line again… 

It is only when you take use of the static variable that we can “remember” the last line we returned, and can happily return the NEXT line, and not the first one again and again. 

```c

//imagine the following file includes this: "Hey this is a test. A test for the get next line. Do you like it?"

int main()
{
get_next_line("file.txt");
get_next_line("file.txt");
get_next_line("file.txt");
return (0);
}

//this would be the return value if our GNL has a static linked list
Hey this is a test.
A test for the get next line. 
Do you like it?

//this would be the return value if our GNL did NOT have a static linked list
Hey this is a test.
Hey this is a test.
Hey this is a test.

//as you can see, the second option does not give us the next line. It gives us the first one. In every single function call.
```

![Untitled](https://programmerhumor.io/wp-content/uploads/2021/09/programmerhumor-io-programming-memes-2e199ceeb2a00d5.png)

You know when you declare a local variable inside a function. Yeah, it just heads out once it’s finished. However, the static sticks around waiting until the whole program is over. A keeper if you ask me. Kind of like the friend that will wait for you when tying your shoelaces. 

# What about file descriptors?

I think we all sort of pretend to know what a file descriptor is, at least I was, before **this** project that is.

So if you are one of those still pretending, here you go:

A file descriptor is essentially a unique identifier that your operating system assigns to each **open file.** It's a way for your program to r**efer to files that it has opened or created.** 

**When you open a file in your program, the operating system assigns a file descriptor to that file.** You can then use this file descriptor to perform various operations on the file, such as reading from it or writing from it.

Additionally, when you read bytes from a file descriptor, it remembers where in the file it was last time.
This means, if you read 10 bytes from a file, next time you'll read from the same file descriptor, it will start reading from byte 11. Pretty cool.

**In this project we will not be needing to use open() or close(), simply because that is given as input in our main function.** 

**A valuable source for further and more detailed explanation → [https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)**

# Read()

The read function will play an essential part in this project, so obviously I will now give you a short description of its basics.

*First - the syntax:*

```c
read(int fd, void* buf, size_t count)
```

**Fd** = well, I was sort of hoping you knew by now…

**Buf** = a pointer towards a memory area where we can temporarily store the read characters.

**Count** = number of characters to read. 

### **Return Values**

- returns the Number of bytes read on success (sort of like printf)
- returns 0 on reaching the end of file
- return -1 if error

Read can also help us carry out some of our error handling in this project - such as checking whether it is returning a -1 when we try to read. 

**By checking read(fd, 0, 0) < 0**

This is essentially telling the computer to open the file, reading nothing and storing nothing. We don’t want to actually read anything, because, as we know, the read function “remembers” where we left off (and we haven’t actually started the program yet - we are only error checking). 

SO, what I am trying to say by this is - if your read returns -1 when trying to read the file, it will indicate that there is either an error within the function itself, or that we don’t have read/open permissions. 

# Linked lists (and how they are used in this project)

**If linked lists are completely new to you** (aka. if you didn’t do the libft bonus), **OR if you pretended to know what you were doing in the libft bonus** - I would highly recommend watching a couple of [these](https://www.youtube.com/watch?v=uBZHMkpsTfg&list=PLfqABt5AS4FmXeWuuNDS3XGENJO1VYGxl) videos first.

