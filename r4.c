   printf("No recent calls.\n");
        return;
    }
    printf("Recent calls:\n");
    for (int i = 0; i < call_log_count; i++) {
        printf("%d. %s\n", i + 1, call_log[i].phone);
    }
}
int find_contact_by_phone(const char *phone) {
    for (int i = 0; i < contact_count; i++) {
        if (strcmp(contacts[i].phone, phone) == 0)
            return i;
    }
    return -1;
}
void add_contact() {
    if (contact_count >= MAX_CONTACTS) {
        printf("Directory full.\n");
        return;
    }
    char name[MAX_NAME], phone[MAX_PHONE];
    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Enter phone: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = '\0';
    if (find_contact_by_phone(phone) != -1) {
        printf("Phone number already exists.\n");
        return;
    }
    strcpy(contacts[contact_count].name, name);
    strcpy(contacts[contact_count].phone, phone);
    contact_count++;
    printf("Contact added.\n");
}
void update_contact() {
    char phone[MAX_PHONE];
    printf("Enter phone number of contact to update: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = '\0';
    int idx = find_contact_by_phone(phone);
    if (idx == -1) {
        printf("Contact not found.\n");
        return;
    }
    char name[MAX_NAME];
    printf("Enter new name (leave blank to keep current): ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    if (strlen(name) > 0) {
        strcpy(contacts[idx].name, name);
    }
    printf("Contact updated.\n");
}
void delete_contact() {
    char phone[MAX_PHONE];
    printf("Enter phone number of contact to delete: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = '\0';

    int idx = find_contact_by_phone(phone);
    if (idx == -1) {
        printf("Contact not found.\n");
        return;
    }
    for (int i = idx; i < contact_count - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    contact_count--;
    printf("Contact deleted.\n");
}
void search_contacts() {
    char query[MAX_NAME];
    printf("Enter search text: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';
    int found = 0;
    for (int i = 0; i < contact_count; i++) {
        if (strstr(contacts[i].name, query) != NULL || strstr(contacts[i].phone, query) != NULL) {
            printf("%s - %s\n", contacts[i].name, contacts[i].phone);
            found = 1;
        }
    }
    if (!found) printf("No contacts found.\n");
}
void sort_contacts_by_name() {
    for (int i = 0; i < contact_count - 1; i++) {
        for (int j = 0; j < contact_count - i - 1; j++) {
            if (strcmp(contacts[j].name, contacts[j + 1].name) > 0) {
                Contact temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }
    printf("Sorted by name.\n");
}
void sort_contacts_by_phone() {
    for (int i = 0; i < contact_count - 1; i++) {
        for (int j = 0; j < contact_count - i - 1; j++) {
            if (strcmp(contacts[j].phone, contacts[j + 1].phone) > 0) {
                Contact temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }
    printf("Sorted by phone number.\n");
}
void list_contacts() {
    if (contact_count == 0) {
        printf("No contacts.\n");
        return;
    }
    for (int i = 0; i < contact_count; i++) {
        printf("%d. %s - %s\n", i + 1, contacts[i].name, contacts[i].phone);
    }
}
void dial_number() {
    char phone[MAX_PHONE];
    printf("Enter phone number to dial: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = '\0';
    printf("Dialing %s...\n", phone);
    add_call_log(phone);
}
int main() {
    load_contacts();
    int choice;
    do {
        printf("\nTelephone Directory\n");
        printf("1. Add contact\n");
        printf("2. Update contact\n");
        printf("3. Delete contact\n");
        printf("4. Search contacts\n");
        printf("5. List contacts\n");
        printf("6. Sort by name\n");
        printf("7. Sort by phone\n");
        printf("8. Save contacts\n");
        printf("9. Export contacts\n");
        printf("10. Dial number\n");
        printf("11. Show recent calls\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d%*c", &choice);
        switch (choice) {
        case 1: add_contact(); break;
        case 2: update_contact(); break;
        case 3: delete_contact(); break;
        case 4: search_contacts(); break;
        case 5: list_contacts(); break;
        case 6: sort_contacts_by_name(); break;
        case 7: sort_contacts_by_phone(); break;
        case 8: save_contacts(); break;
        case 9: export_contacts(); break;
        case 10: dial_number(); break;
        case 11: show_
