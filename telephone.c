#include<stdio.h>
#include<string.h>
#define MAX_CONTACTS 100
int main (){
    int choice;
    do{
        printf("Telephone Directory");
        printf("1. Add Contacts");
        printf("2. Show Contacts");
        printf("3. Update Contacts");
        printf("4. Delete Conttacts");
        printf("5. Exit");
        printf("Enter Your Choice");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
            addContact();
            break;
            case 2:
            showContacts();
            break;
            case 3:
            updateContact();
            break;
            case 4:
            deleteContact();
            break;
            case 5:
            printf
        }
    }
}