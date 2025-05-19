#include "operations.c"
int main() {
    char filePath[] = "user_data.txt";
    setFile(filePath);
    char fName[] = "test";
    char lName[] = "test";
    char email[] = "test5@gatech.edu";
    char password[] = "testingPassword";
    if (add(fName, lName, email, password) == 1) {
        printf("\nadd passed");
    } else {
        printf("\nadd failed");
    }
    //should fail this time
    if (add(fName, lName, email, password) == 0) {
        printf("\nadd failed on 2nd attempt");
    } else {
        printf("\nadd passed, when it should've failed");
    }
}
