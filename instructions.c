//
// Created by micha on 11/26/2021.
//

#include "instructions.h"
#include "registers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Array of most R-format instructions. Some obscure ones were left out, but
 * this should cover the most widely used MIPS operations.
 */
char *r_format[13][2] = {
//  instruction     funct           bin
//  -----------------------------------------
        { "add",    "32" },      // 0x20
        { "addu",   "33" },      // 0x21
        { "div",    "26" },      // 0x1A
        { "divu",   "27" },      // 0x1B
        { "mult",   "24" },      // 0x18
        { "multu",  "25" },      // 0x19
        { "nor",    "39" },      // 0x27
        { "xor",    "38" },      // 0x26
        { "or",     "37" },      // 0x25
        { "slt",    "42" },      // 0x2A
        { "sltu",   "43" },      // 0x2B
        { "sub",    "34" },      // 0x22
        { "subu",   "35" }       // 0x23
};

/**
 * Array of most I-format instructions. Some obscure ones were left out, but
 * this should cover the most widely used MIPS operations.
 */
char *i_format[6][2] = {
//  instruction     opcode           bin
//  -----------------------------------------
        { "addi",   "08" },      // 0x08
        { "addiu",  "09" },      // 0x09
        { "andi",   "12" },      // 0x0C
        { "ori",    "13" },      // 0x0D
        { "slti",   "12" },      // 0x0A
        { "sltiu",  "11" },      // 0x0B
};

const char * replace_char(char* str, char find, char replace){
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

long dec_to_bin (int n) {
    long long bin = 0;
    long long rem, i = 1;

    while (n!=0) {
        rem = n % 2;
        n /= 2;
        bin += rem * i;
        i *= 10;
    }

    return bin;
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
    char *array[4] = { NULL, NULL, NULL, NULL };

    int i = 0;
    while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, " ");
    }

    for (int i = 0; i < (sizeof array / sizeof *array); i++) {
        if (array[i] == NULL) {
            array[i] = "NULL";
        }
    }


    char * instruction = array[0];
    format = get_format((const char **) instruction);

    //  BIT SEGMENTS USED BY BOTH FORMATS
    const char * opcode;


// FORMAT-BASED OPERATIONS
    if (format == 'R') {

        const char * shamt   = "00000";
        const char * funct   = get_funct((const char **) instr);

        char *str = (char*) malloc(64 * sizeof(char));
        sprintf(str, "%c-Format: %ld %ld %ld %ld",
                format,
                dec_to_bin((atoi(funct))),
                dec_to_bin(registers_get((char **) array[1])),      // rd
                dec_to_bin(registers_get((char **) array[2])),      // rs
                dec_to_bin(registers_get((char **) array[3]))       // rt
                );
        return str;

    } else if (format == 'I') {

        opcode = get_opcode((const char **) instr);

        char *str = (char*) malloc(64 * sizeof(char));
        sprintf(str, "%c-Format: %ld %ld %ld %ld",
                format,
                dec_to_bin(strtol(opcode, 0, 10)),
                dec_to_bin(registers_get((char **) array[1])),      // rt
                dec_to_bin(registers_get((char **) array[2])),      // rd
                dec_to_bin(strtol(array[3], 0, 10))  // immediate value
                );
        return str;
    }

    return "[INVALID INSTRUCTION]\n";
}