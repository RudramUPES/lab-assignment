uct {
    char phone[MAX_PHONE];
    int count;
} CallLog;
Contact contacts[MAX_CONTACTS];
int contact_count = 0;
CallLog call_log[MAX_CALL_LOG];
int call_log_count = 0;
void save_contacts() {
    FILE *f = fopen("contacts.txt", "w");
    if (!f) {
        printf("Could not save contacts.\n");
        return;
    }
    for (int i = 0; i < contact_count; i++) {
        fprintf(f, "%s,%s\n", contacts[i].name, contacts[i].phone);
    }
    fclose(f);
    printf("Contacts saved.\n");
}
void load_contacts() {
    FILE *f = fopen("contacts.txt", "r");
    if (!f) return;
    contact_count = 0;
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
