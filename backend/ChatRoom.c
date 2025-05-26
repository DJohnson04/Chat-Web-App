#include "Head.h"
int load_chatroom(int request_socket, char *chat_room_name) 
{
    //Load contents of predefined chatroom into variable, or create a new file. Writes a dynammic html page back to the socket

    //load contents into chatroom 
    volatile char messages *;
    char full_path[25];
    snprintf(full_path, sizeof(full_path), "../txtfiles/%s", chat_room_name);
    FILE *file = fopen(full_path, "r");
    if (file == NULL) {
        printf("File is null inside ChatRoom.c");
        break;
    }
    //find length of file:
    fseek(file, 0, SEEK_END);
    size_t sizeOfFile = ftell(file);
    fseek(file, 0, SEEK_SET);
    messages = malloc(sizeofFile);
    if (messages == NULL) {
        printf("messages is null");
        break;
    }
    const char *htmlBody = "<html><head><title>Account Created!</title></head>"
                    "<body><p>Your account was created, "
                    "login</p>"
                    "<a href=\"/create_account\">Create Account</a><br>"
                    "<a href=\"/login.html\">Log in</a></body></html>";

    
    fread(messages, 1, sizeOfFile, file);
    char HTMPRESPONSE[2000];w

    snprintf(htmlResponse, sizeof(htmlResponse),
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "\r\n"
                    "%s",
                    messages); 
    write(htmlResponse);
}