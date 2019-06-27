#include <stdio.h>
#include <stdlib.h>

/*  
we're creating a program that reads instructions and values
from memory and runs in a loop to execute those instructions
*/

#define PRINT_BEEJ 1
#define HALT 2
#define PRINT_NUM 3
#define PRINT_SUM 4
#define SAVE 5
#define PRINT_REGISTER 6
#define ADD 7
#define PUSH 8
#define POP 9

unsigned char registers[8];
unsigned char memory[256];

int main(int argc, char *argv[])
{
    int cur_index = 0;
    int running = 1;

    unsigned char reg_num, val;
    unsigned char reg_num0, reg_num1;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: a.out filename\n");
        return 1;
    }

    char line[1024];
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        return 2;
    }

    int address = 0;

    while (fgets(line, sizeof line, fp) != NULL)
    {
        char *endptr;

        // we use 10 because are instructions are in decimal
        // the instructions on the project are in binary
        unsigned char val = strtoul(line, &endptr, 10);

        // ignore lines with no numbers
        if (endptr == line)
        {
            continue;
        }

        memory[address++] = val;
    }

    fclose(fp);

    // stack pointer
    registers[7] = 244;

    // while our computer is running
    while (running)
    {
        // the current command that is being executed
        unsigned char command = memory[cur_index];

        switch (command)
        {
        case PUSH:
            registers[7]--;
            printf("Stack Pointer: %d\n", registers[7]);
            reg_num = memory[cur_index + 1];
            val = registers[reg_num];
            memory[registers[7]] = val;

            cur_index += 2;
            break;

        case POP:
            reg_num = memory[cur_index + 1];
            registers[reg_num] = memory[registers[7]];

            registers[7]++;
            printf("Stack Pointer: %d\n", registers[7]);

            cur_index += 2;
            break;
        case ADD:
            reg_num0 = memory[cur_index + 1];
            reg_num1 = memory[cur_index + 2];

            registers[reg_num0] += registers[cur_index + 2];

            cur_index += 3;
            break;
        case SAVE:
            val = memory[cur_index + 1];
            reg_num = memory[cur_index + 2];
            registers[reg_num] = val;

            cur_index += 3;
            break;

        case PRINT_REGISTER:
            printf("%d\n", registers[memory[cur_index + 1]]);

            cur_index += 2;
            break;
        case PRINT_BEEJ:
            printf("Beej\n");
            cur_index++;
            break;
        case PRINT_NUM:
            // look ahead to the next index and print it
            printf("%d\n", memory[cur_index + 1]);
            cur_index += 2;
            break;
        case PRINT_SUM:
            // look ahead to the next index and print it
            printf("%d\n", memory[cur_index + 1] + memory[cur_index + 2]);
            cur_index += 3;
            break;
        case HALT:
            running = 0;
            cur_index++;
            break;
        default:
            fprintf(stderr, "Unrecognized instruction\n");
            exit(1);
            break;
        }
    }

    return 0;
}