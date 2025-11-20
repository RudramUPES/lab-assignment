
    char name[MAX_NAME], phone[MAX_PHONE], email[MAX_EMAIL];

    printf("Name: ");  fgets(name, sizeof(name), stdin); strip(name);
    printf("Phone: "); fgets(phone, sizeof(phone), stdin); strip(phone);
    printf("Email: "); fgets(email, sizeof(email), stdin); strip(email);

    if (find_contact(phone) != -1) {
        printf("Phone already exists.\n");
        return;
    }

    strcpy(contacts[contact_count].name, name);
    strcpy(contacts[contact_count].phone, phone);
    strcpy(contacts[contact_count].email, email);

    contact_count++;
    printf("Contact added.\n");
}

void update_contact() {
    char phone[MAX_PHONE];
    printf("Enter phone of contact to update: ");
    fgets(phone, sizeof(phone), stdin); strip(phone);

    int i = find_contact(phone);
    if (i == -1) {
        printf("Contact not found.\n");
        return;
    }

    char name[MAX_NAME], new_phone[MAX_PHONE], email[MAX_EMAIL];

    printf("New name (enter to keep same): ");
    fgets(name, sizeof(name), stdin); strip(name);

    printf("New phone (enter to keep same): ");
    fgets(new_phone, sizeof(new_phone), stdin); strip(new_phone);

    printf("New email (enter to keep same): ");
    fgets(email, sizeof(email), stdin); strip(email);

    if (strlen(name)) strcpy(contacts[i].name, name);
    if (strlen(new_phone)) strcpy(contacts[i].phone, new_phone);
    if (strlen(email)) strcpy(contacts[i].email, email);

    printf("Contact updated.\n");
}

void delete_contact() {
    char phone[MAX_PHONE];
    printf("Enter phone to delete: ");
    fgets(phone, sizeof(phone), stdin); strip(phone);

    int i = find_contact(phone);
    if (i == -1) {
        printf("Contact not found.\n");
        return;
    }

    for (int j = i; j < contact_count - 1; j++)
        contacts[j] = contacts[j + 1];

    contact_count--;
    printf("Deleted.\n");
}

void list_contacts() {
    if (contact_count == 0) {
        printf("No contacts.\n");
        return;
    }

    printf("\nAll Contacts:\n");
    printf("No.  Name                           Phone            Email\n");
    printf("---- ------------------------------ ---------------- -------------------------\n");

    for (int i = 0; i < contact_count; i++) {
        printf("%-4d %-30s %-16s %-30s\n",
               i + 1,
               contacts[i].name,
               contacts[i].phone,
               contacts[i].email);
    }
}

void search_contacts() {
    char q[MAX_NAME];
    printf("Search: ");
    fgets(q, sizeof(q), stdin); strip(q);

    int found = 0;

    for (int i = 0; i < contact_count; i++) {
        if (strstr(contacts[i].name, q) ||
            strstr(contacts[i].phone, q) ||
            strstr(contacts[i].email, q))
        {
            if (!found) printf("\nMatches:\n");
            found = 1;

            printf("%-30s %-16s %-30s\n",
                   contacts[i].name,
                   contacts[i].phone,
                   contacts[i].email);
        }
    }

    if (!found) printf("No match found.\n");
}

/* -------------------- CALL LOG -------------------- */

void add_call(const char *phone) {
    for (int i = MAX_CALL_LOG - 1; i > 0; i--)
        strcpy(call_log[i].phone, call_log[i - 1].phone);

    strcpy(call_log[0].phone, phone);

    if (call_log_count < MAX_CALL_LOG) call_log_count++;
}

void show_calls() {
    if (call_log_count == 0) {
        printf("No recent calls.\n");
        return;
    }

    printf("\nRecent Calls:\n");
    for (int i = 0; i < call_log_count; i++)
        printf("%d. %s\n", i + 1, call_log[i].phone);
}

void dial_number() {
    char phone[MAX_PHONE];
    printf("Enter number to dial: ");
    fgets(phone, sizeof(phone), stdin);
    strip(phone);

    printf("Dialing %s...\n", phone);
    add_call(phone);
}

/* -------------------- MAIN MENU -------------------- */

int main() {
    load_contacts();
    int choice;

    do {
        printf("\n--- Telephone Directory ---\n");
        printf("1. Add Contact\n");
        printf("2. Update Contact\n");
        printf("3. Delete Contact\n");
        printf("4. Search Contacts\n");
        printf("5. List Contacts\n");
        printf("6. Save Contacts\n");
        printf("7. Dial Number\n");
        printf("8. Show Recent Calls\n");
        printf("0. Exit\n");
        printf("Choose: ");

        scanf("%d%*c", &choice);

        switch (choice) {
            case 1: add_contact(); break;
            case 2: update_contact(); break;
            case 3: delete_contact(); break;
            case 4: search_contacts(); break;
            case 5: list_contacts(); break;
            case 6: save_contacts(); printf("Saved.\n"); break;
            case 7: dial_number(); break;
            case 8: show_calls(); break;
            case 0: save_contacts(); printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}
