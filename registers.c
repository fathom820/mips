//
// Created by micha on 11/24/2021.
//

#include "registers.h"
#include <string.h>


/**
 * Definition table for all register ID's and their usages.
 * When a binary file is parsed, it will refer to this table
 * for the register ID's.
 */
char *registers[] = {
//      register ID     standard use            num
//      -------------------------------------------
        "$zero",        // always 0             r0
//      -------------------------------------------
        "$at",          // ----- RESERVED ----- r1
//      -------------------------------------------
        "$v0",          // stores results       r2
        "$v1",          // ^                    r3
//      -------------------------------------------
        "$a0",          // stores arguments     r4
        "$a1",          // ^                    r5
        "$a2",          // ^                    r6
        "$a3",          // ^                    r7
//      -------------------------------------------
        "$t0",          // temp                 r8
        "$t1",          // ^                    r9
        "$t2",          // ^                    r10
        "$t3",          // ^                    r11
        "$t4",          // ^                    r12
        "$t5",          // ^                    r13
        "$t6",          // ^                    r14
        "$t7",          // ^                    r15
//      -------------------------------------------
        "$s0",          // saved for later use  r16
        "$s1",          // ^                    r17
        "$s2",          // ^                    r18
        "$s3",          // ^                    r19
        "$s4",          // ^                    r20
        "$s5",          // ^                    r21
        "$s6",          // ^                    r22
        "$s7",          // ^                    r23
//      -------------------------------------------
        "$t8",          // more temps           r24
        "$t9",          // ^                    r25
//      -------------------------------------------
        "$k0",          // ----- RESERVED ----- r26
        "$k1",          // ----- RESERVED ----- r27
//      -------------------------------------------
        "$gp",          // global pointer       r28
        "$sp",          // stack pointer        r29
        "$fp",          // frame pointer        r30
        "$ra",          // return address       r31
};


/**
 * get register number for respective register ID
 * if invalid (not found / reserved) return -1
 * @param regId register ID
 * @return register number
 */
int getRegister (char regId[]){
    for (int i = 0; i < 32; i++) {
        if (strcmp(regId, registers[i]) == 0) {
            if (i == 1 || i == 26 || i == 27) {
                return -1;
            } else {
                return i;
            }
        }
    }
    return -1;
}