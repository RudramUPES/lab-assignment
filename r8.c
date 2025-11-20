#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100
#define MAX_NAME 50
#define MAX_PHONE 20
#define MAX_EMAIL 64
#define MAX_CALL_LOG 10

typedef struct {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
} Contact;

typedef struct {
    char phone[MAX_PHONE];
} CallLog;

Contact contacts[MAX_CONTACTS];
CallLog call_log[MAX_CALL_LOG];

int contact_count = 0;
int call_log_count = 0;

/* -------------------- BASIC UTIL -------------------- */

void strip(char *s) {
    if (!s) return;
    int n = strlen(s);
    if (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r'))
        s[n-1] = '\0';
}

/* -------------------- FILE HANDLING -------------------- */

void save_contacts() {
    FILE *f = fopen("contacts.txt", "w");
    if (!f) return;

    for (int i = 0; i < contact_count; i++) {
        fprintf(f, "%s,%s,%s\n",
                contacts[i].name,
                contacts[i].phone,
                contacts[i].email);
    }
    fclose(f);
}

void load_contacts() {
    FILE *f = fopen("contacts.txt", "r");
    if (!f) return;

    char name[MAX_NAME], phone[MAX_PHONE], email[MAX_EMAIL];
    contact_count = 0;

    while (fscanf(f, "%49[^,],%19[^,],%63[^\n]\n",
                  name, phone, email) == 3)
    {
        strcpy(contacts[contact_count].name, name);
        strcpy(contacts[contact_count].phone, phone);
        strcpy(contacts[contact_count].email, email);
        contact_count++;
    }
    fclose(f);
}

/* -------------------- CONTACT FEATURES -------------------- */

int find_contact(const char *phone) {
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
