/**
 * @file diags.h
 * @author John Scott
 * @brief Built-in LED Diagnostics (Morse Code)
 * @version 1.0
 * @date 2021-11-11
 * 
 * @copyright Copyright (c) 2021 John Scott
 * 
 */
#ifndef INCLUDED_DIAGS_H
#define INCLUDED_DIAGS_H

#define DEBUG false

void dit(int count = 1);
void dah(int count = 1);
void gap(int count = 1);
void S_O_S();

#define DIT_LEN 1
#define DAH_LEN 3
#define EOW_LEN 7

#endif /* INCLUDED_DIAGS_H */
