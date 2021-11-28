//
// Created by micha on 11/26/2021.
//

#include "instructions.h"
#include "registers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Array of most R-format instructions. Some obscure ones were left out, but
 * this should cover the most widely used MIPS operations.
 */
char *r_format[20][2] = {
//  instruction     funct           bin
//  -----------------------------------------
        { "add",    "32" },      // 0x20
        { "addu",   "33" },      // 0x21
        { "div",    "26" },      // 0x1A
        { "divu",   "27" },      // 0x1B
        { "jalr",   "09" },      // 0x09
        { "jr",     "08" },      // 0x08
        { "mfhi",   "16" },      // 0x10
        { "mthi",   "17" },      // 0x11
        { "mflo",   "18" },      // 0x12
        { "mtlo",   "19" },      // 0x13
        { "mult",   "24" },      // 0x18
        { "multu",  "25" },      // 0x19
        { "nor",    "39" },      // 0x27
        { "xor",    "38" },      // 0x26
        { "or",     "37" },      // 0x25
        { "slt",    "42" },      // 0x2A
        { "sltu",   "43" },      // 0x2B
      //  { "sll",    "00" },      // 0x00
      //  { "srl",    "02" },      // 0x02
        { "sra",    "03" },      // 0x03
        { "sub",    "34" },      // 0x22
        { "subu",   "35" }       // 0x23
};

/**
 * Array of most I-format instructions. Some obscure ones were left out, but
 * this should cover the most widely used MIPS operations.
 */
char *i_format[11][2] = {
//  instruction     opcode           bin
//  -----------------------------------------
        { "addi",   "08" },      // 0x08
        { "addiu",  "09" },      // 0x09
        { "andi",   "12" },      // 0x0C
        { "beq",    "04" },      // 0x04
        { "blez",   "06" },      // 0x06
        { "bne",    "05" },      // 0x05
        { "bgtz",   "07" },      // 0x07
        { "ori",    "13" },      // 0x0D
        { "slti",   "12" },      // 0x0A
        { "sltiu",  "11" },      // 0x0B
        { "sw",     "43" }       // 0x2B
};

char* replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos) {
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

const char * get_opcode(const char * instr[]) {
    for (int i = 0; i < (sizeof i_format / sizeof *i_format); i++) {
        if (strcmp((const char *) instr, i_format[i][0]) == 0) {
            return (const char *) i_format[i][1];
        }
    }
    return NULL;
}

const char * get_funct(const char * instr[]) {
    for (int i = 0; i < (sizeof r_format / sizeof *r_format); i++) {
        if (strcmp((const char *) instr, (const char *) r_format[i][0]) == 0) {
            return (const char *) r_format[i][1];
        }
    }
    return NULL;
}

char get_format (const char **instr) {
    // test for r-format
    for (int i = 0; i < (sizeof r_format / sizeof *r_format); i++) {
        if (strcmp((const char *) instr, r_format[i][0]) == 0) {
            return 'R';
        }
    }

    // test for i-format
    for (int i = 0; i < (sizeof i_format / sizeof *i_format); i++) {
        if (strcmp((const char *) instr, i_format[i][0]) == 0) {
            return 'I';
        }
    }

    return '-'; // invalid instruction
}


// public

/**
 * Decode instruction into bytecode,
 * @param instr
 * @return char[]: [format] [bytecode]
 */
const char* instructions_decode (char instr[]) {
    /**
     * Instruction format
     * Possible values:
     * 'R'  :   R-Format
     * 'I'  :   I-Format
     * '-'  :   No format (invalid)
     */
    char format;


// 1. DETERMINE INSTRUCTION FORMAT

    replace_char(instr, ',', ' ');
    replace_char(instr, '\n', ' ');
    char *p = strtok(instr, " ");
    char *array[4];

    int i = 0;
    while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, " ");
    }

    for (i = 0; i < (sizeof array / sizeof *array); i++) {
        // todo debug only
        //printf("%s\n", array[i]);
    }

    char * instruction = array[0];
    format = get_format((const char **) instruction);

    //  BIT SEGMENTS USED BY BOTH FORMATS
    const char * opcode   = "000000";
    int rs;
    int rt;


// FORMAT-BASED OPERATIONS
    if (format == 'R') {

        int rd  = registers_get((char **) array[1]);
        rs      = registers_get((char **) array[2]);
        rt      = registers_get((char **) array[3]);

        const char *shamt   = "00000";
        const char *funct   = get_funct((const char **) instr);

        char *str = (char*) malloc(64 * sizeof(char));
        sprintf(str, "%c-Format: %s %d %d %d",
                format,
                funct,
                registers_get((char **) array[1]),      // rd
                registers_get((char **) array[2]),      // rs
                registers_get((char **) array[3])       // rt
                );
        return str;

    } else if (format == 'I') {

        opcode = get_opcode((const char **) instr);

        char *str = (char*) malloc(64 * sizeof(char));
        sprintf(str, "%c-Format: %s %d %d %s",
                format,
                opcode,
                registers_get((char **) array[1]),      // rt
                registers_get((char **) array[2]),      // rd
                array[3]);                                    // immediate value
        return str;
    }

    return "[INVALID INSTRUCTION]\n";
}