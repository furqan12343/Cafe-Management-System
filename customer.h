#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "include.h"

void processCustomer();
void display(char head[40], char** item, int* price, int* quantity, int n);
void placeOrder(char head[40], char** item, int* price, int* quantity, int n);
void complaints(const char* name, const char* complain);
void seenotification();
void onlineorder(char head[40], char** item, int* price, int* quantity, int n);
void playandwin(char** item, int* price, int* quantity, int n);

#endif
