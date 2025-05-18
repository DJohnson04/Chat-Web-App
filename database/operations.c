#include "macros.h"
FILE* file;
char *file_path;
//returns 1 if passed 0 if failed
int add(char* fName, char *lName, char*email, char *password) {
    file = fopen(file_path, 'a');
    if (file == NULL){
        printf("CALL SETFILE");
        return -1;
    }
    //make sure email doesn't exist in textfile
    if (contains(email) == 1) {
        printf("email exist in file, cannot add this entry");
        fclose(file);
        return 0;
    }
    //email not found, create new entry
    fputs(email, file);
    fputs(fName, file);
    fputs(lName, file);
    fputs(password, file);
    fclose(file);
    return 1;
} 
int remove(char* email) {
    if (file == NULL){
        printf("CALL setFILE");
        exit(-1);
    }

}
//returns 1 if file contains email, 0 if not
int contains(char* email) {
    file = fopen(file, "r");
    if (file == NULL){
        printf("CALL setFILE");
        exit(-1);
    }
    char entry[MAX_LENGTH_STRING * 4];
    while (fgets(entry, sizeof(entry), file)) {
        if (strncmp(email, entry[0], MAX_LENGTH_STRING) == 0) {
            //Email already exists inside file, return 1
            fclose(file);

            return 1;
        } 
    }
    fclose(file);
    return 0;
}
void setFile(char *filePath) {
    file_path = filePath;
}
