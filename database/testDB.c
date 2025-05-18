#include "operations.c"
int main() {
    char filePath[] = "user_data.txt";
    setFile(filePath);
    char fName[] = "david";
    char lName[] = "johnson";
    char email[] = "djohnson477@gatech.edu";
    char password[] = "tpsw123";
    if (add(fName, lName, email, password) == -1) {
        printf("add failed");
    } else {
        printf("add passed");
    }
    //should fail this time
    if (add(fName, lName, email, password) == -1) {
        printf("add failed");
    } else {
        printf("add passed, when it should've failed");
    }
}