//
// Created by micha on 11/26/2021.
//

#include "instructions.h"
#include <string.h>
#include <stdio.h>

char *r_format[22] = {
//  instruction     funct           bin
//  -----------------------------------------
        "add",          // 0x20         0010 0000
        "addu",         // 0x21         0010 0001
        "div",          // 0x1A
        "divu",         // 0x1B
        "jalr",         // 0x09
        "jr",           // 0x08
        "mfhi",         // 0x10
        "mthi",         // 0x11
        "mflo",         // 0x12
        "mtlo",         // 0x13
        "mult",         // 0x18
        "multu",        // 0x19
        "nor",          // 0x27
        "xor",          // 0x26
        "or",           // 0x25
        "slt",          // 0x2A
        "sltu",         // 0x2B
        "sll",          // 0x00
        "srl",          // 0x02
        "sra",          // 0x03
        "sub",          // 0x22
        "subu",         // 0x23
};

/**
 * Array of most I-format instructions. Some obscure ones were left out, but
 * this should cover the most widely used MIPS operations.
 */
char *i_format[] = {
//  instruction     opcode           bin
//  -----------------------------------------
        "addi",         // 0x08
        "addiu",        // 0x09
        "andi",         // 0x0C
        "beq",          // 0x04
        "blez",         // 0x06
        "bne",          // 0x05
        "bgtz",         // 0x07
        "ori",          // 0x0D
        "slti",         // 0x0A
        "sltiu",        // 0x0B
        "sw",           // 0x2B
};

char getFormat (const char * instr[]) {
    /**
 * Array of most R-format instructions. Some obscure ones were left out, but
 * this should cover the most widely used MIPS operations.
 */


    // test for r-format

    for (int i = 0; i < (sizeof r_format / sizeof *r_format); i++) {
        if (strcmp((const char *) instr, r_format[i]) == 0) {
            return 'R';
        }
    }
    // test for i-format
    for (int i = 0; i < (sizeof i_format / sizeof *i_format); i++) {
        if (strcmp((const char *) instr, i_format[i]) == 0) {
            return 'I';
        }
    }


    return '-'; // invalid instruction
}

/**
 * Convert decimal to binaru, used for register ID's
 * @param dec decimal value to convert
 * @return binary string
 */


// public

/**
 * Decode instruction into bytecode,
 * @param instr
 * @return char[]: [format] [bytecode]
 */
const char* instructions_decode (char instr[]) {
//  BIT SEGMENTS USED BY BOTH FORMATS
//  seg name        # bits      types used by
//  -----------------------------------------
    char opcode[6];   // 6          R, I
    char rs[5];       // 5          R, I
    char rt[5];       // 5          R, I

    /**
     * Instruction format
     * Possible values:
     * 'R'  :   R-Format
     * 'I'  :   I-Format
     * '-'  :   No format (invalid)
     */
    char format;

// 1. DETERMINE INSTRUCTION FORMAT

    // 1. Split by spaces, then by commas
    char * token = strtok(instr, " ");
    format = getFormat((const char **) token);

// FORMAT-BASED OPERATIONS

    if (format == 'R') {
    //  seg name        # bits      types used by
    //  -----------------------------------------
        char rd[5];       // 5          R
        char shamt[5];    // 5          R
        char funct1[2];   // 2          R
        int funct2[4];    // 4          R
        // todo
        return "R-Format: ";

    } else if (format == 'I') {
        char imm[16];     // 16         I (Immediate)
        return "I-Format: ";
    }

    return "[INVALID INSTRUCTION]\n";
}