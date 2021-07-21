#pragma once
/*
 - Array access.h
 - Header file for demonstrating how to access arrays in C
 - ECED 3403
 - 22 May 21
*/
/* Lets all modules know that print_month() exists */
#define MONTHS 12

/* 
 - Since months[] is global, we need to declare it here 
 - We could *not* create it here because the header file is
   included in both Array access.c and Print month.c, meaning 
   that the same array (with the same name) would be created
   twice. If the compiler didn't object at compile time, the 
   linker probably would.
 - If it is omitted, the compiler would object.  Try it.
*/
char *months[];

/* Lets mainline know that print_month() exists */
extern void print_month(int);
