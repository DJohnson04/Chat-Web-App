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
#include <sys/stat.h>

//ACCOUNTCREATION Header||||||||||||||||||||||||||||

struct user_details {
    char fName[MAX_LENGTH_STRING];
    char lName[MAX_LENGTH_STRING];
    char email[MAX_LENGTH_STRING];
    char password[MAX_LENGTH_STRING];
};
int findLen(char *, int, char);
void parsePostRequest(char* buffer, int start, int lenOfBuffer, char terminator, struct user_details *details);
int AccountCreation(int user_socket, char* buffer);

//Server.c Header|||||||||||||||||||||||||||||||||||||||||
//HTTP REQUEST HEADERS
const char POSTCREATE_ACCOUNT[] = "POST /create_account";
const char GETCREATE_ACCOUNT[] = "get /create_account";

const char POSTLOGIN[] = "POST /login";
const char GETLOGIN[] = "GET /login";

const char GETHOME[] = "GET /home";

const char GET_CHAT[] = "GET  /chat_";
const char POSTCHAT[] = "POST /chat_"


