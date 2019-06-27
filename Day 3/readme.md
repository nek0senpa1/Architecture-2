# Computer Architecture - Day 3

## Stack Frames

- Stack frames are allocated when a function is called, and deallocated when a function returns.
- If you call two functions sequentially, the local variables in the second function will occupy the same stack space as the local variables in the first.
```
700: 0
699: 2 (a) start of main's stack frame
698: 14 (b)
697: 2 (x)
696: 7 (y)
695: 14 (z) <--- SP
```

```C
int mult2(int x, int y)
{
    int z;

    z = x * y;

    return z;
}

int main(void)
{
    int a = 2;

    int b = mult2(a, 7);

    printf("%d\n", b); // 14
}
```

## LS8 Stack Visual

```
FF: 00 
FE: 00
FD: 00
FC: 00
FB: 00
FA: 00
F9: 00
F8: 00
F7: 00
F6: 00
F5: 00
F4: 00 <-- SP
F3: 12
F2: 32
F1: 00
F0: 00
EF: 00
.
.
.
05: 00
04: 00
03: XX
02: XX
01: XX
00: XX <-- PC


R0: 12
R1: 12
R2: 32

R7: F4 (this is the SP)
```