# Computer Architecture - Day 4

## Subroutines

- Essentially like functions in high level languages
  - The two main differences are that they take in no arguments and they have no return values
- How do we pass parameters or get return values?
    - Pass them in registers, but this allow us to use nested function calls or recursion.
    - The second option is to use the stack, this allows for nested function calls and recursion.

### Incrementing the PC

```C
unsigned char IR = 0b1000010; // 0b1000010 is LDI

// get the number of operands
// add 1 for the instruction itself
int add_to_pc = (IR >> 6) + 1;
int is_subroutine = (IR >> 4) & 1; // is 0 or 1
//  0b0101
//  0b0001
//& ------
//  0b0001

while (running) {
switch(command) {
    case LDI:
    // LDI stuff
    break;
}
    if(!is_subroutine) {
        cpu->pc += add_to_pc;
    }
}
```