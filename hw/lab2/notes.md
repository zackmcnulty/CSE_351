### Intro

Here are some notes I took about the bombs behavior while I tried to learn how to defuse it. These are just some of
my general notes and ideas. There are more specifics found in the bomb_disas file side by side with their
corresponding assembly instructions.


### Phase 1

Seems like a pretty basic string comparison. Phase 1 stores the immediate value "0x401b18" in %rsi 
which will be used as the second argument for the <strings_not_equal> call. Since we never define a first
argument in %rdi for the <strings_not_equal> function, the first argument will then
be the same as the first argument to phase_1(): namely, it will be the input we provide the program through
the console. (see lecture 12 slide 21 for all the different uses of the registers).

Strings are stored as char arrays, so we can expect "0x401b18" to be an address to the first character in the string.
Using GDB, we can find what the full string is. I used the commands

```
gdb bomb
break 74
run
<type something to respond to bomb program>
x/s 0x401b18
```

where the last command prints the string at the given address (check out [this](https://courses.cs.washington.edu/courses/cse351/19sp/gdb/gdbnotes-x86-64.pdf) convenient cheatsheet for gdb)
This returned the phrase: "Speedy thing goes in, speedy thing comes out."


### Phase 2

The function call <read_six_numbers> inside phase_2 suggests that the passphrase will be a string of six numbers. We can
verify this by noting by the value stored "0x401ed2" stored in %esi right before the sscanf call (line 4017e6 in <read_six_numbers>) will be the second argument to sscanf
based on register conventions. Using GDB, we can determine what value is stored at this address:

```
gdb bomb
x/s 0x401ed2
```

Which returns the string "%d %d %d %d %d %d"). Namely, the code expects 6 integers separated by spaces.

On first inspection, <read_six_numbers> just seems to assume that the argument at %rsi stores an array of integers. It automatically blows
up if less than 6 integers are provided. Otherwise it stores the first 6 of these integers in the registers??
We can see that phase_2 just runs a while loop which parses over the elements stored at %rsp to %rsp + 20.
The loop compares the values stored in %eax and in Memory[%rbx] and the bombs explode if these are not equal (line 400eca). Before this, the code offsets %eax a single
index (4 bytes) behind %rbx (line 400ec4) and increments its value by 5 (Line 400ec7). Hence the bomb explodes unless the value at the previous index is 5 less than the value at the next index.
Hence any such string of integers will suffice. The simplest choice is of course 0,5,10,15,20,25,30



### Phase 3

Seems like a bunch of cases we have to work through. Again, we can see there is a call to sscanf with the address 
"0x401b6e" passed as the second argument (this value is stored in %esi, the 2nd arg position, on line 400ef6 before the sscanf call). 
We know the second arg of sscanf is the format specifier, so this is important info. Using GDB as in phase 2 we can
determine what string is stored at this address:

```
gdb bomb
x/s 0x401b6e
```

This returns "%d %c %d" as the format specifier. So the code expects "int char int". There is some clear switch like
behavior going on, and line 400f1e looks like its referencing a jump table. We can use GDB to inspect this jump table:

```
gdb bomb
x/8gx 0x401b80
```
Which yields the result:

```
0x401b80:       0x0000000000400f25      0x0000000000400f47
0x401b90:       0x0000000000400f69      0x0000000000400f8b
0x401ba0:       0x0000000000400faa      0x0000000000400fc5
0x401bb0:       0x0000000000400fe0      0x0000000000400ffb
```

Reading from left to right and top down, we get the following mappings

```
0 -> 400f25
1 -> 400f47
2 -> 400f69
3 -> 400f8b
4 -> 400faa
5 -> 400fc5
6 -> 400fe0
7 -> 400ffb
```

Once we know the mappings, we just have to focus on a specific case to chose the char and the 2nd int appropriately (the first int determines which case we are in)
It seems any case is possible to solve; its important to note that all cases seem to set a condition for the 2nd int, and then set %eax to some hex number. At
the end of the procedure (line 401020) the code does one last check that the char provided matches the value set at %eax. So all we have to do is look up
an ascii table (man ascii) and choose the ascii character that has hex representation equal to whatever that case set %eax equal to.




### Phase 4

Again it looks like phase 4 is going to use the sscanf function, and stores "0x401b74" as its second argument (the format specifier).
Using GDB, we can look up what string this address references:

```
gdb bomb
x/s 0x401b74
``` 

This returns "%d", so phase 4 is just expecting a single integer as a passcode. There is a quick check that the given number is
positive, but then all the function really does is call <fun4> and compare the return value to 362880. It is clear to see that <fun4> is recursive and
on closer inspection is just the factorial(n) function (see my notes in bomb_disas for further info). Conveniently we see
362880 = 9! so the desired passcode must by 9.



### Phase 5

Again, it looks like phase 5 uses the sscanf function and stores address "0x401ede" as the second argument to sscanf (the format specifier). Using GDB we 
can determine what string is stored at this address:

```
gdb bomb
x/s 0x401ede
```
This yields "%d %d" so the desired passcode consists of two integers. The mask 0xF is applied to these inputs (line 4010b4)
which suggests all that really matters are the last 4 bits of these digits' binary representation. Hence we can assume without loss of
generality that 0 <= x < 16. 

There is a clear while loop between lines 4010ce to 4010df. The line 4010d3 references an address in memory 0x401bc0 and seems to treat it like its an array of integers
( the (,%rax,4) portion treats the address like it is indexable, and the word size of 4 bytes suggests these are integers). Using GDB, we can verify this:

```
gdb bomb
x/d 0x401bc0
```

which gives the result

```
0x401bc0 <array.3135>:  10
```

confirming our belief that this is an integer array. Inspecting the elements of the array with `x/d 0x401bc0 + 4i` gives us:

```
index :   0  1  2   3  4  5   6   7   8  9  10 11 12 13 14 15
array = [10, 2, 14, 7, 8, 12, 15, 11, 0, 4, 1, 13, 3, 9, 6, 5]
```

The fact that there are 16 entries matches well with the fact that we force 0 <= x < 16. Namely, x will be indexing the array.
Inside the while loop, we see we continuously set %eax = array[%eax] and we increment %edx by 1 each time, and %ecx by the value in the array.
At the end, we want %edx = 12 and to choose our second input y to be equal to %ecx. Namely, we want to find a path through the array:

```
x -> array[x] -> array[array[x]] -> ... -> 15
```

that takes exactly 12 steps (this is how we choose the first int x) and we want to choose the second int y to be the sum of all these elements. Starting
at 15 and tracing backwards 12 steps, we get:

```
15 =  array[6] <- 6 = array[14] <- 14 = array[2] <- 2 = array[1] <- 1 = array[10] <- 10 = array[0] ...
		<- 0 = array[8] <- 8 = array[4] <- 4 = array[9] <- 9 = array[13] <- 13 = array[11] <- 11 = array[7] <- 7
```

So we choose x = 7 and y = 11 + 13 + 9 + 4 + 8 + 0 + 10 + 1 + 2 + 14 + 6 + 15 = 93 as our first and second argument respectively.




### Phase 6 (extra credit)

There is a linked list stored at address 0x6028a0 referenced on line 401182 of <phase_6>






### Phase 7 (Secret)

I noticed a lot of the cases set return values, even though they never seem to use them? FOr example, in phase 3 there seems
to be a different return value depending on which case you choose to do. On top of this, on 401860 of the <phase_defused> function we can
see there is a possible call to the secret phase function
