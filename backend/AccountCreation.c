//Helper file that handles the post request from /createAccount, stores the data in a new database/textfile(for right now),
#include "Head.h"
int AccountCreation(int user_socket, char *buffer)
{
    char infoHeader[] = "fname";
    struct user_details user_data;
        printf("Buffer: %s", buffer);
        //loop thorugh request until blank line is found(where data is stored)
        int counter = 0;
        while (buffer[counter] != '\n') {
            counter++;
        }
        while (counter < 1000 - 6 && buffer[counter] != NULL) {
            if (strncmp(&buffer[counter], infoHeader, 4) == 0){
                //found start of POST request, start parse
                counter +=  6; //counter -> fName[0]
                parsePostRequest(buffer, counter, sizeof(buffer), '&', &user_data);
                break;
            }
            counter++;
        }

        //store data inside file
        char filePath[] = "../database/user_data.txt";
        setFile(filePath);
        char htmlResponse[1500];
        //data alreeady exist inside file,
        if (add(user_data.fName, user_data.lName, user_data.email, user_data.password) == 0) {
            printf("Data already exists inside the text file.\n");

            // HTML body for the error response
            const char *htmlBody = "<html><head><title>Account Couldn't be Created!</title></head>"
                                "<body><p>Your account was not created, due to the email already existing. "
                                "Please attempt to log in, or try again with a different email account.</p>"
                                "<a href=\"/frontend/create_account.html\">Create Account</a><br>"
                                "<a href=\"/frontend/login.html\">Log in</a></body></html>";

            // Calculate content length
            int contentLength = strlen(htmlBody);

            // Prepare full HTTP response
            char htmlResponse[1024];  // Make sure this is large enough
            snprintf(htmlResponse, sizeof(htmlResponse),
                    "HTTP/1.1 400 Bad Request\r\n"
                    "Content-Type: text/html\r\n"
                    "Content-Length: %d\r\n"
                    "\r\n"
                    "%s",
                    contentLength, htmlBody);

            // Write HTTP response back to the client
            write(user_socket, htmlResponse, strlen(htmlResponse));
            //Write HTTP Reponse back to socket, to diseplay new page
        } else {
            const char *htmlBody = "<html><head><title>Account Created!</title></head>"
                       "<body><p>Your account was created, "
                       "login</p>"
                       "<a href=\"/create_account\">Create Account</a><br>"
                       "<a href=\"/login.html\">Log in</a></body></html>";

            char htmlResponse[1024];
            int contentLength = strlen(htmlBody);

            // Format the full HTTP response
            snprintf(htmlResponse, sizeof(htmlResponse),
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "Content-Length: %d\r\n"
                    "\r\n"
                    "%s",
                    contentLength, htmlBody);

            write(user_socket, htmlResponse, strlen(htmlResponse));

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
    memset(details->fName, 0, MAX_LENGTH_STRING);
    if (len > MAX_LENGTH_STRING) {
        printf("First Name too Long");
        return;
    }
    strlcpy(details->fName, &buffer[start], len + 1);
    printf("fName in var: %s\n", details->fName);
    //lName
    start += len + 7; //move counter past fName & to start of lName
    len = findLen(buffer, start, terminator);
    memset(details->lName, 0, MAX_LENGTH_STRING);
    if (len > MAX_LENGTH_STRING) {
        printf("Last Name too Long");
        return;
    }
    strlcpy(details->lName, &buffer[start], len + 1);
    printf("lName in var: %s\n", details->lName);
    //email
    start += len + 7; //move counter past lName & to start of email
    len = findLen(buffer, start, terminator);
    memset(details->email, 0, MAX_LENGTH_STRING);
    if (len > MAX_LENGTH_STRING) {
        printf("Email too Long");
        return;
    }
    strlcpy(details->email, &buffer[start], len + 1);
    printf("email in var: %s\n", details->email);
    //password
    start += len + 7; //move counter past email & to start of password
    len = findLen(buffer, start, terminator);
    memset(details->password, 0, MAX_LENGTH_STRING);

    //if (len > MAX_LENGTH_STRING) {
     //   printf("password too Long");
      //  return;
    //}
    strlcpy(details->password, &buffer[start], len + 1);
    printf("password in var: %s\n", details->password);

} 
//fname=name&lname=name&email=wmail%40server.com&paswd=password