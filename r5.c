ount = 0;
    while (fscanf(f, "%49[^,],%19[^\n]\n", contacts[contact_count].name, contacts[contact_count].phone) == 2) {
        contact_count++;
        if (contact_count >= MAX_CONTACTS) break;
    }
    fclose(f);
}
void export_contacts() {
    FILE *f = fopen("contacts_export.txt", "w");
    if (!f) {
        printf("Could not export contacts.\n");
        return;
    }
    fprintf(f, "Name,Phone\n");
    for (int i = 0; i < contact_count; i++) {
        fprintf(f, "%s,%s\n", contacts[i].name, contacts[i].phone);
    }
    fclose(f);
    printf("Contacts exported to contacts_export.txt\n");
}
void add_call_log(const char *phone) {
    for (int i = MAX_CALL_LOG - 1; i > 0; i--) {
        strcpy(call_log[i].phone, call_log[i - 1].phone);
    }
    strcpy(call_log[0].phone, phone);
    if (call_log_count < MAX_CALL_LOG) call_log_count++;
}
void show_call_log() {
    if (call_log_count == 0) {
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
    char quer
