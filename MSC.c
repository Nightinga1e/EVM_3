#include "MSC.h"

#include <stdio.h>

int sc_memory[SC_MEM_SIZE];
int sc_register;

int sc_memoryInit() {
    for (int i = 0; i < SC_MEM_SIZE; ++i) {
        sc_memory[i] = 0;
    }
    printf("\n *Memory init*  \n");
    return 0;
}

int sc_memorySet(int address, int value) {
    if (address < 0 || address >= SC_MEM_SIZE) {
        sc_regSet(MEM_OUT, 1);
	Er_Handler(1);
        return 1;
    }
    sc_memory[address] = value;
    printf("\n *Memory set* \n");
    return 0;
}

int sc_memoryGet(int address, int *value) {
    if (address < 0 || address >= SC_MEM_SIZE) {
        sc_regSet(MEM_OUT, 1);
	Er_Handler(1);
        return 1;
    }
    *value = sc_memory[address];
    printf("\n *Memory get* \n");
    return 0;
}

int sc_memorySave(char filename[]) {
    FILE *fp;
    if ((fp = fopen(filename, "wb")) == NULL) {
	Er_Handler(2);
        return 1;
    }
    fwrite(&sc_memory, sizeof(sc_memory), 1, fp);
    fclose(fp);
    printf("\n *Memory save* \n");
    return 0;
}

int sc_memoryLoad(char filename[]) {
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL) {
	Er_Handler(3);
        return 1;
    }
    fread(&sc_memory, sizeof(sc_memory), 1, fp);
    fclose(fp);
    printf("\n *Memory load* \n");
    return 0;
}

int sc_regInit() {
    sc_register = 0x0;
    printf("\n *Reg init* \n");
    return 0;
}

int sc_regSet(int reg, int value) {
    if (reg == MEM_OUT || reg == INVALID_REG || reg == WRONG_COMMAND) {
        if (value == 1) {
            sc_register |= reg;
        } else if (value == 0) {
            sc_register &= ~reg;
        } else {
            sc_register |= INVALID_REG;
	    Er_Handler(4);
            return 1;
        }
    }else{
	Er_Handler(5);
	}
    printf("\n *reg set* \n");
    return 0;
}

int sc_regGet(int reg, int *value) {
    if (reg < 1 || reg > REG_SIZE) {
        sc_regSet(INVALID_REG, 1);
	Er_Handler(5);
        return 1;
    }
    *value = (sc_register >> (reg - 1)) & 0x1;
    printf("\n *Reg get* \n");
    return 0;
}


int sc_commandEncode(int command, int operand, int *value) {
    if (command < 0x10 ||
        (command > 0x11 && command < 0x20) ||
        (command > 0x21 && command < 0x30) ||
        (command > 0x33 && command < 0x40) ||
        (command > 0x43 && command < 0x51) ||
        command > 0x76) {
        sc_regSet(WRONG_COMMAND, 1);
	Er_Handler(6);
        return 1;
    }
    if (operand > 0x7F || operand < 0x0) {
        sc_regSet(WRONG_COMMAND, 1);
	Er_Handler(7);
        return 1;
    }
    *value = (command << 7) | operand;
    	printf("\n *Command encode* \n");
    return 0;
}


int sc_commandDecode(int value, int *command, int *operand) {

    if ((value >> 14) != 0x0) {
	sc_regSet(WRONG_COMMAND, 1);
	Er_Handler(8);
        return 1;
    }

    *operand = value & 0x7F;
    *command = value >> 7;

    if (*command < 0x10 ||
        (*command > 0x11 && *command < 0x20) ||
        (*command > 0x21 && *command < 0x30) ||
        (*command > 0x33 && *command < 0x40) ||
        (*command > 0x43 && *command < 0x51) ||
        *command > 0x76) {
        sc_regSet(WRONG_COMMAND, 1);
	Er_Handler(6);
        return 1;
    }
    if (*operand > 0x7F || *operand < 0x0) {
        sc_regSet(WRONG_COMMAND, 1);
	Er_Handler(7);
        return 1;
    }
    printf("\n *Command decode* \n");
    return 0;
}

int Er_Handler(int Er_Num)
{
	printf("Error: (code: %d):\n", Er_Num);
	switch(Er_Num)
	{
		case 1:
			printf("Out of memory.\n\n");
			break;
		case 2:
			printf("Cannot save RAM\n\n");
			break;
		case 3:
			printf("Cannot load a RAM\n\n");
			break;
		case 4:
			printf("Wrong value.\n\n");
			break;
		case 5:
			printf("Wrong register.\n\n");
			break;
		case 6:
			printf("Wrong command\n\n");
			break;
		case 7:
			printf("Wrong operand\n\n");
			break;
		case 8:
			printf("Wrong command/operand\n\n");
			break;
		}
	return 0;
}
