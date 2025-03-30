#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "include.h"

void processEmployee();
bool displayEmployeeMainMenu();
void startwork();
void generatebill(char** item, int* price, int* quantity, int n, char** orderitems, int* orderquant, int c);
void searchitems( char** item, int* price, int* quantity, int n);
void takeorder( char** item, int* price, int* quantity, int n);
void viewonlineorder(char** item, int* price, int* quantity, int n);

#endif
