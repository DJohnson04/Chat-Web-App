//handles the post request from /createAccount, stores the data in a new database/textfile(for right now),
#include "Head.h"
int main() 
{
    //allows forms to be accepted
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    char infoHeader[] = "fname";
    struct user_details user_data;

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    while (listen(server_socket, 5) != -1) {
        //connect to specific account form
        int user_socket = accept(server_socket, NULL, NULL);
        char buffer[1000];
        memset(buffer, 0,  sizeof(buffer));
        recv(user_socket, buffer, sizeof(buffer), 0);
        printf("Buffer: %s", buffer);
        //parse post request
        int counter = 0;
        while (counter < 1000 - 6 && buffer[counter] != NULL) {
            if (strncmp(&buffer[counter], infoHeader, 4) == 0){
                //found start of POST request, start parse
                counter +=  6; //counter -> fName[0]
                parsePostRequest(buffer, counter, sizeof(buffer), '&', &user_data);
                break;
            }
            counter++;
        }

        //store data inside
        char filePath[] = ["../database/user_data.txt"];
        setFile(filePath);
        //data alreeady exist inside file, 
        char htmlResponsep[1500];
        if (add(user_data->fName, user_data->lName, user_data->email, user_data->password) == 0) {
            printf("data already existw inside the textfile.");
            //send html form showing account creation failed:
             htmlResponse = "HTTP/1.1 400 Invalid Details\nContent-Type: text/html\n Content-Length: 500\n\n
                <html>
                    <head>
                        <title>Account Couldn't be Created!</title>
                    </head>
                    <body>
                        <p>Your account was not created, due to the email already existing, please attempt to login, or try again with a different email acceount</p>
                        <a href=\"/create_account\">Create Account</a>
                        <a href=\"/login.html\">Log in</a>
                    </body>
                </html>
            "
            //Write HTTP Reponse back to socket, to diseplay new page
        } else {
            htmlResponse = "HTTP/1.1 200 Account Created\nContent-Type: text/html\n Content-Length: 500\n\n
                <html>
                    <head>
                        <title>Account Created!</title>
                    </head>
                    <body>
                        <p>Your account was created, you can now login :)</p>
                        <a href=\"/login.html\">Log in</a>
                        <a hrefj=\"/home.html\">Home</a>
                    </body>
                </html>
            "
        }
        //send htmlREsponse back, and display page
        write(server_socket, htmlResponse, 1500);

        


        free(user_data.fName);
        free(user_data.lName);
        free(user_data.email);
        free(user_data.password);
    }
}

int findLen(char *buffer, int startPos, char terminator) {
    int count = startPos;
    int len = sizeof(buffer) - count;
    while (buffer[count] != terminator && count < 1000) {
        count++;
    }
    
    return (count - startPos);
}

void parsePostRequest(char* buffer, int start, int lenOfBuffer, char terminator, struct user_details *details) {
    //fName
    int len = findLen(buffer, start, terminator);

    details->fName = malloc(sizeof(char) * len + 1);
    if (details->fName == NULL) {
        printf(" ERROR");
    }
    strlcpy(details->fName, &buffer[start], len + 1);
    printf("fName in var: %s\n", details->fName);
    //lName
    start += len + 7; //move counter past fName & to start of lName
    len = findLen(buffer, start, terminator);

    details->lName = malloc(sizeof(char) * len);
    if (details->lName == NULL) {
        printf("another eror :(");
    }
    strlcpy(details->lName, &buffer[start], len + 1);
    printf("lName in var: %s\n", details->lName);
    //email
    start += len + 7; //move counter past lName & to start of email
    len = findLen(buffer, start, terminator);

    details->email = malloc(sizeof(char) * len);
    if (details->email == NULL) {
        printf("another eror :(");
    }
    strlcpy(details->email, &buffer[start], len + 1);
    printf("email in var: %s\n", details->email);
    //password
    start += len + 7; //move counter past email & to start of password
    len = findLen(buffer, start, terminator);
    details->password = malloc(sizeof(char) * len);
    if (details->password == NULL) {
        printf("another eror :(");
    }
    strlcpy(details->password, &buffer[start], len);
    printf("password in var: %s", details->password);
} 
//fname=name&lname=name&email=wmail%40server.com&paswd=password