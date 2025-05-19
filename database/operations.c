#include "operations.h"
char *file_path;
//returns 1 if passed 0 if failed
int add(char* fName, char *lName, char*email, char *password) {
    FILE *file = fopen(file_path, "a");
    if (file == NULL){
        printf("CALL SETFILE");
        return 0;
    }
    //make sure email doesn't exist in textfile
    if (contains(email) == 1) {
        fclose(file);
        return 0;
    }
    //email not found, create new entry
    fputs(email, file);
    fputs(",", file);
    fputs(fName, file);
    fputs(",", file);
    fputs(lName, file);
    fputs(",", file);
    fputs(password, file);
    fputs("\n", file);
    fclose(file);
    return 1;
} 
int removeEntry(char* email) {
    FILE *file = fopen(file_path, "r+");
    if (file == NULL){
        printf("CALL setFILE");
        return -1;
    }

}
//returns 1 if file contains email, 0 if not
int contains(char* email) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL){
        printf("CALL setFILE");
        return 0;
    }
    char entry[MAX_LENGTH_STRING * 100];
    fgets(entry, sizeof(entry), file);
    while ((fgets(entry, sizeof(entry), file)) != NULL) {
        if (strncmp(email, entry, sizeof(email)) == 0) {
            //Email already exists inside file, return 1
            fclose(file);
            return 1;
            //printf("%s", entry);
        } 
    }
    fclose(file);
    return 0;
}
void setFile(char *filePath) {
    file_path = filePath;
}
