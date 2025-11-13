
typedef struct {
    int id;
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
} Contact;
typedef struct {
    char phone[MAX_PHONE];
    char name[MAX_NAME];
    time_t when;
} CallLogEntry;
typedef struct {
    CallLogEntry entries[CALL_LOG_MAX];
    int head;
    int count;
} CallLog;
typedef struct {
    Contact *data;
    size_t size;
    size_t cap;
    int next_id;
} Directory;
static void strip_newline(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    if (n && (s[n-1] == '\n' || s[n-1] == '\r')) s[n-1] = '\0';
}
static void read_line(const char *prompt, char *buf, size_t n) {
    if (prompt) {
        printf("%s", prompt);
        fflush(stdout);
    }
    if (fgets(buf, (int)n, stdin) == NULL) {
        if (n) buf[0] = '\0';
        return;
    }
    strip_newline(buf);
}
static int read_int(const char *prompt) {
    char line[64];
    for (;;) {
        read_line(prompt, line, sizeof(line));
        if (line[0] == '\0') return 0;
        char *end = NULL;
        long v = strtol(line, &end, 10);
        if (end && *end == '\0') return (int)v;
        printf("Invalid number, try again.\n");
    }
}
static int ci_char(int c) { return tolower((unsigned char)c); }
static int ci_cmp(const char *a, const char *b) {
    while (*a && *b) {
        int da = ci_char(*a), db = ci_char(*b);
        if (da != db) return (da < db) ? -1 : 1;
        ++a; ++b;
    }
    if (*a == *b) return 0;
    return (*a) ? 1 : -1;
}
static int ci_contains(const char *hay, const char *needle) {
    size_t nh = strlen(hay), nn = strlen(needle);
    if (nn == 0) return 1;
    for (size_t i = 0; i + nn <= nh; ++i) {
        size_t j = 0;
        while (j < nn && ci_char(hay[i+j]) == ci_char(needle[j])) ++j;
        if (j == nn) return 1;
    }
    return 0;
}
static void dir_init(Directory *d) {
    d->data = NULL;
    d->size = 0;
    d->cap = 0;
    d->next_id = 1;
}
static void dir_reserve(Directory *d, size_t need) {
    if (need <= d->cap) return;
    size_t ncap = d->cap ? d->cap * 2 : 16;
    if (ncap < need) ncap = need;
    Contact *nd = (Contact*)realloc(d->data, ncap * sizeof(Contact));
    if (!nd) {
        fprintf(stderr, "Out of memory.\n");
        exit(1);
    }
    d->data = nd;
    d->cap = ncap;
}
static void dir_free(Directory *d) {
    free(d->data);
    dir_init(d);
}
static int dir_find_index_by_phone(const Directory *d, const char *phone) {
    for (size_t i = 0; i < d->size; ++i) {
        if (strcmp(d->data[i].phone, phone) == 0) return (int)i;
    }
    return -1;
}
static Contact* dir_find_by_id(Directory *d, int id) {
    for (size_t i = 0; i < d->size; ++i)
        if (d->data[i].id == id) return &d->data[i];
    return NULL;
}
static int dir_add(Directory *d, const char *name, const char *phone, const char *email) {
    if (dir_find_index_by_phone(d, phone) != -1) {
        printf("Duplicate phone number. Not added.\n");
        return 0;
    }
    dir_reserve(d, d->size + 1);
    Contact *c = &d->data[d->size++];
    c->id = d->next_id++;
    strncpy(c->name, name, MAX_NAME-1); c->name[MAX_NAME-1] = '\0';
    strncpy(c->phone, phone, MAX_PHONE-1); c->phone[MAX_PHONE-1] = '\0';
    strncpy(c->email, email, MAX_EMAIL-1); c->email[MAX_EMAIL-1] = '\0';
    return 1;
}
static int dir_update(Directory *d, int id, const char *name, const char *phone, const char *email) {
    Contact *c = dir_find_by_id(d, id);
    if (!c) return 0;
    if (phone[0] != '\0' && strcmp(phone, c->phone) != 0) {
        if (dir_find_index_by_phone(d, phone) != -1) {
            printf("Phone number already exists. Update aborted.\n");
            return 0;
