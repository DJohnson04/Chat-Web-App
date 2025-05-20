//Primary file that runs the server
#include "Head.h"
#include "../database/operations.h"

int main()
{
    //handle socket creation
    int server_socked = socket(IF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_address, (struct  sockaddr*) &server_address, sizesof(server_address));
    while (listen(server_socket, 10) != -1) {
        int request_socket = accept(server_socket, NULL, NULL);
        char HTTPREQUEST[1000];
        memset(HTTPREQUEST, 0, sizeof(HTTPREQUEST));
        recv(request_socket, HTTPREQUEST, sizeof(HTTPREQUEST), 0);
        printf("\nRequest Received:\n %s\n\n", HTTPREQUEST);
        //need to sort POST /create_account HTTP/1.1 || GET /create_account HTTP/1.1 || GET /login || GET /home HTTP/1.1 || get /chat_roomname HTTP/1.1
        if (strncmp(HTTPREQUEST, "GET", 3) == 0) {
            //Handle Get Requests
            //Find File under frontend, or return bad request or some error
            // get requested file from HTTPREQUEST -> add '../frontend/file_path' -> store file contents inside buffer, 
            char http_file_path[25];
            int p = 5;
            while (HTTPREQUEST[p] != ' ' && p < 30) {
                http_file_path[p - 5] = HTTPREQUEST[p];
            }
            char file_path[50];
            snprintf(file_path, sizeof(file_path), "../frontend/%s", http_file_path);
            FILE *file = fopen(file_path, "r");
            if (file == NULL) {
                printf("error has occured when attempting to access this page due to file being null")
                //TODO: send back failed response
                
                

                //
            }
            //find length of file:
            fseek(file, 0, SEEK_END);
            size_t sizeOfFile = ftell(file);
            fseek(file, 0, SEEK_SET);

            char *file_Contents = malloc(sizeOfFile);
            fread(file_Contents, 1, sizeOfFile, file);
            //TODO: prep HTTP response and send it back
            free(file_Contents);

        } else if (strncmp(HTTPREQUEST, "POST", 4) == 0) {
            if (strncmp(HTTPREQUEST, POSTCREATE_ACCOUNT, sizeof(POSTCREATE_ACCOUNT)) == 0) {
                //See Account Creation.c for more, inputs details into file, if they do not exist, sends a html request back depending on the result
                AccountCreation(request_socket, HTTPREQUEST);
                memset(HTTPREQUEST, 0, sizeof(HTTPREQUEST));
            }
        }
    }
}
