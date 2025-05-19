#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include "../database/operations.h"
#include "../database/operations.c"
struct user_details {
    char fName[MAX_LENGTH_STRING];
    char lName[MAX_LENGTH_STRING];
    char email[MAX_LENGTH_STRING];
    char password[MAX_LENGTH_STRING];
};
int findLen(char *, int, char);
void parsePostRequest(char* buffer, int start, int lenOfBuffer, char terminator, struct user_details *details);
