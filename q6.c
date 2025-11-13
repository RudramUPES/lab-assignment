#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAX_NAME   64
#define MAX_PHONE  20
#define MAX_EMAIL  64
#define CALL_LOG_MAX 50
#define CONTACTS_DB     "contacts.dat"
#define CALL_LOG_DB     "calllog.dat"
#define EXPORT_TXT      "contacts_export.txt"
typedef struct {
    int id;
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
} Contact;
