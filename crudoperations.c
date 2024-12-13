#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct User{
    int id;
    char name[50];
    int age;
};

void createfileifnotpresent();
void adduser();
void displayusers();
void deleteuser();
void updateuser();

int main()
{
    int option;
    createfileifnotpresent();
    while(1)
    {
        printf("CRUD Operations\n");
        printf("1.add user\n");
        printf("2.display user\n");
        printf("3.delete user\n");
        printf("4.modify user\n");
        printf("5.exit\n");
        printf("Now enter your choice:\n");
        scanf("%d",&option);
        switch (option)
        {
        case 1:adduser();break;
        case 2:displayusers();break;
        case 3:deleteuser();break;
        case 4:updateuser();break;
        case 5:printf("Exiting now\n");exit(0);
        default:printf("invalid entry try again\n");break;
        }
    }
    return 0;
}

void createfileifnotpresent()
{
    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("File is Empty.\n");
        exit(1);
    }
    fclose(file);
}

void adduser()
{
    struct User user;
    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("couldnt open the file.\n");
        return;
    }
    printf("Enter the User ID: ");
    scanf("%d", &user.id);
    printf("Enter Name: ");
    scanf(" %[^\n]s", user.name);
    printf("Enter Age: ");
    scanf("%d", &user.age);
    fprintf(file, "%d,%s,%d\n", user.id, user.name, user.age);
    fclose(file);
    printf("User added successfully.\n");
}

void displayusers()
{
    FILE *file = fopen("users.txt", "r");
    struct User user;
    if (file == NULL) {
        printf("unable to open file.\n");
        return;
    }
    printf("\nThe user records are given below\n");
    while (fscanf(file, "%d,%[^,],%d\n", &user.id, user.name, &user.age) != EOF) {
        printf("ID: %d, Name: %s, Age: %d\n", user.id, user.name, user.age);
    }
    fclose(file);
}

void updateuser()
{
    int id, found = 0;
    struct User user;
    FILE *file = fopen("users.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter User ID to update: ");
    scanf("%d", &id);

    while (fscanf(file, "%d,%[^,],%d\n", &user.id, user.name, &user.age) != EOF) {
        if (user.id == id) {
            found = 1;
            printf("Enter New Name: ");
            scanf(" %[^\n]s", user.name);
            printf("Enter New Age: ");
            scanf("%d", &user.age);
        }
        fprintf(tempFile, "%d,%s,%d\n", user.id, user.name, user.age);
    }

    fclose(file);
    fclose(tempFile);

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (found) {
        printf("User updated successfully.\n");
    } else {
        printf("User ID not found.\n");
    }
}

void deleteuser()
{
    int id, found = 0;
    struct User user;
    FILE *file = fopen("users.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter User ID to delete: ");
    scanf("%d", &id);

    while (fscanf(file, "%d,%[^,],%d\n", &user.id, user.name, &user.age) != EOF) {
        if (user.id == id) {
            found = 1;
            continue; // Skip writing this user to the temp file
        }
        fprintf(tempFile, "%d,%s,%d\n", user.id, user.name, user.age);
    }

    fclose(file);
    fclose(tempFile);

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (found) {
        printf("User deleted successfully.\n");
    } else {
        printf("User ID not found.\n");
    }
}