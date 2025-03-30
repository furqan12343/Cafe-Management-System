#ifndef ADMIN_H
#define ADMIN_H
#include "include.h"

void startMenu();
void displaystock( char** item, int* price, int* quantity, int n);
void checkstockfile(char** item, int* price, int* quantity, int n);
void Addstock(char** item, int* quantity, int* price, int n);
void removestock( char** item, int* quantity, int* price, int n);
void handleCafeStock( char** item, int* quantity, int* price, int n);
void notif();
void order(char** item, int* quantity, int* price, int n);
void processAdmin();
void employ();
void addemploy();
void removeemployee(const char emp[]);
void seenotif();
void handlecomplains();
void removecomplains();
void seecomplains();

#endif


