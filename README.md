# COMPSCI 230 Computer Systems Principles
# Valgrind Lab

This lab is an introduction to `valgrind`, a programming tool for memory
debugging, memory leak detection, and profiling.

To start working on this lab you must be logged in to the Edlab and in your
`cs230` directory. From this directory run the command:

```
$ git clone https://github.com/umass-cs-230/230-lab-cache
```

In the folder you just downloaded, you will find two C files, `example.c` and
`debug_calc.c`, which is reused from the `gdb` lab with a few changes. The
instructor will demonstrate the use of `valgrind` on `example.c`, and you will
repeat the experiments on `debug_calc.c` and answer some associated questions on
Gradescope.

Many tools are included in `valgrind`. We will cover two in this lab: Memcheck
and Lackey.

# Memcheck

Memcheck is a memory error detector. To use Memcheck, compile the programs with
`-g` to include debugging information so that Memcheck's error messages include
exact line numbers:

```
$ gcc -o example -g example.c
```

Then run `valgrind` with:

```
$  valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --track-fds=yes --log-file=output.txt ./example
```

This will save the output of `valgrind` to a file called `output.txt`. (If
`--log-file` option is not specified, `valgrind` will print to `stderr`.)

In the output you will find a section that looks something like this

```
==2997626== Invalid write of size 4
==2997626==    at 0x10916B: f (example.c:6)
==2997626==    by 0x109180: main (example.c:11)
==2997626==  Address 0x4a5f068 is 0 bytes after a block of size 40 alloc'd
==2997626==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==2997626==    by 0x10915E: f (example.c:5)
==2997626==    by 0x109180: main (example.c:11)
```

The `==2997626==` column indicates process ID, and is usually unimportant. The
error messages here tell us that the program is trying to write 4 bytes at an
invalid address ("`Invalid write of size 4`"), from function `f` at line 6 in
`example.c` ("`at 0x10916B: f (example.c:6)`"), which is called by `main` at line
11 in `example.c` ("`by 0x109180: main (example.c:11)`"). The invalid address
where the program is trying to write is "`Address 0x4a5f068 is 0 bytes after a
block of size 40 alloc'd`", allocated by `malloc`, which is called by `f`, which
is called by `main`. You can see that the stack traces, as they are called, list
the function invocations that lead to an error in reverse order. Reading from
the bottom up can help when the stack traces get large.

In the `output.txt` file generated, you can also find a section that looks
something like this:

```
==2997626== HEAP SUMMARY:
==2997626==     in use at exit: 40 bytes in 1 blocks
==2997626==   total heap usage: 1 allocs, 0 frees, 40 bytes allocated
==2997626==
==2997626== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==2997626==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==2997626==    by 0x10915E: f (example.c:5)
==2997626==    by 0x109180: main (example.c:11)
==2997626==
==2997626== LEAK SUMMARY:
==2997626==    definitely lost: 40 bytes in 1 blocks
==2997626==    indirectly lost: 0 bytes in 0 blocks
==2997626==      possibly lost: 0 bytes in 0 blocks
==2997626==    still reachable: 0 bytes in 0 blocks
==2997626==         suppressed: 0 bytes in 0 blocks

```
This section tells us that 40 bytes of memory was leaked ("`definitely lost: 40
bytes in 1 blocks`"). This is because `malloc` allocated memory on the heap but
this space was not later freed.

# Lackey

For the next project, you will be asked to use Lackey to generate trace files.
Run the following:

```
$ valgrind --tool=lackey --trace-mem=yes --log-file=example.trace ./example
```

This will record all the memory accesses in the order they occur and save them
in a file called `example.trace`. In `example.trace` you will see a long list of
records that look like the following:

```
I  04001e26,3
I  04001e29,7
 L 0402e000,8
I  04001e30,7
 S 0402e9f8,8
I  04001e37,7
 S 0402e9e8,8
I  04001e3e,3
```

The format of each line is

```
operation address,size
```

The column `operation` indicates the type of memory access: `I` is an
instruction fetch, `S` is a store, and `L` is a load. The column `address` is
the hexadecimal representation of the memory address accessed, and the column
`size` is the number of bytes accessed by the operation.

Use the Memcheck and Lackey tools on `debug_calc.c`, in the same way as described
above (and demonstrated by the instructor), and answer the associated questions on
Gradescope.
