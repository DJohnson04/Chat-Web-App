//Primary file that runs the server
#include "Head.h"



int main()
{
    //////Constant Vars
    const char BAD_REQUEST[] = "HTTP/1.1 400 Error\n\n";
    const char POSTCREATE_ACCOUNT[] = "POST /create_account";
    const char GETCREATE_ACCOUNT[] = "get /create_account";

    const char POSTLOGIN[] = "POST /login";
    const char GETLOGIN[] = "GET /login";

    const char GETHOME[] = "GET /home";
    const char GET_CHAT[] = "GET  /chat_";

    //handle socket creation
    int server_socket = socket(PF_INET6, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct  sockaddr*) &server_address, sizeof(server_address));
    while (listen(server_socket, 10) != -1) {
        int request_socket = accept(server_socket, NULL, NULL);
        char HTTPREQUEST[1000];
        memset(HTTPREQUEST, 0, sizeof(HTTPREQUEST));
        recv(request_socket, HTTPREQUEST, sizeof(HTTPREQUEST), 0);
        printf("\nRequest Received:\n %s\n\n", HTTPREQUEST);
        //need to sort POST /create_account HTTP/1.1 || GET /create_account HTTP/1.1 || GET /login || GET /home HTTP/1.1 || get /chat_roomname HTTP/1.1
        if (strncmp(HTTPREQUEST, "GET", 3) == 0) {
            if (strncmp(HTTPREQUEST, "GET /chat_", 10) == 0) {
                int o = 11;
                while (HTTPREQUEST[o] != ' ') {
                    o++;
                } 
                char room_name[o - 11];
                strncpy(room_name, &HTTPREQUEST[11], o - 11);
                printf("\nRoom Name: %s\n", room_name);
                load_chatroom(request_socket, room_name);
            }
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
            printf("\n File Path: \n %s", file_path);
            FILE *file = fopen(file_path, "r");
            if (file == NULL) {
                printf("error has occured when attempting to access this page due to file being null");
                //send back failed response
                printf("Attempted access page: %s", file_path);
                write(request_socket, BAD_REQUEST, sizeof(BAD_REQUEST));
                continue;
            }
            //find length of file:
            fseek(file, 0, SEEK_END);
            size_t sizeOfFile = ftell(file);
            fseek(file, 0, SEEK_SET);

            char *file_contents = malloc(sizeOfFile);
            if (file_contents == NULL) {
                printf("An error has occured when trying to malloc for file_contents");
                
                write(request_socket, BAD_REQUEST, sizeof(BAD_REQUEST));
                continue;
            }
            fread(file_contents, 1, sizeOfFile, file);
            //prep HTTP response and send it back
            char http_status_line[] = "HTTP/1.1 200 OK\n\n";
            char http_response[sizeof(http_status_line)/sizeof(http_status_line[0]) + sizeOfFile];
            snprintf(http_response, sizeof(http_response), "%s%s", http_status_line, file_contents);
            write(request_socket, http_response, sizeof(http_response));
            
            memset(http_response, 0, sizeof(http_response));
            free(file_contents);
        } else if (strncmp(HTTPREQUEST, "POST", 4) == 0) {
            if (strncmp(HTTPREQUEST, POSTCREATE_ACCOUNT, sizeof(POSTCREATE_ACCOUNT)) == 0) {
                //See Account Creation.c for more, inputs details into file, if they do not exist, sends a html request back depending on the result
                AccountCreation(request_socket, HTTPREQUEST);
                memset(HTTPREQUEST, 0, sizeof(HTTPREQUEST));
            }
        }
    }
}


