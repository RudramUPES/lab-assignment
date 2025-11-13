
    }
    if (name[0] != '\0') { strncpy(c->name, name, MAX_NAME-1); c->name[MAX_NAME-1] = '\0'; }
    if (phone[0] != '\0') { strncpy(c->phone, phone, MAX_PHONE-1); c->phone[MAX_PHONE-1] = '\0'; }
    if (email[0] != '\0') { strncpy(c->email, email, MAX_EMAIL-1); c->email[MAX_EMAIL-1] = '\0'; }
    return 1;
}
static int dir_delete(Directory *d, int id) {
    for (size_t i = 0; i < d->size; ++i) {
        if (d->data[i].id == id) {
            d->data[i] = d->data[d->size - 1];
            d->size--;
            return 1;
        }
    }
    return 0;
}
static int cmp_name(const void *a, const void *b) {
    const Contact *x = (const Contact*)a;
    const Contact *y = (const Contact*)b;
    int r = ci_cmp(x->name, y->name);
    if (r == 0) r = ci_cmp(x->phone, y->phone);
    return r;
}
static int cmp_phone(const void *a, const void *b) {
    const Contact *x = (const Contact*)a;
    const Contact *y = (const Contact*)b;
    int r = strcmp(x->phone, y->phone);
    if (r == 0) r = ci_cmp(x->name, y->name);
    return r;
}
static void dir_sort_by_name(Directory *d) { qsort(d->data, d->size, sizeof(Contact), cmp_name); }
static void dir_sort_by_phone(Directory *d) { qsort(d->data, d->size, sizeof(Contact), cmp_phone); }
static void dir_list(const Directory *d) {
    if (d->size == 0) {
        printf("No contacts.\n");
        return;
    }
    printf("ID   Name                           Phone             Email\n");
    printf("---- ------------------------------ ---------------- ------------------------------\n");
    for (size_t i = 0; i < d->size; ++i) {
        printf("%-4d %-30s %-16s %-30s\n",
               d->data[i].id, d->data[i].name, d->data[i].phone, d->data[i].email);
    }
}
static void dir_search(const Directory *d, const char *query) {
    int found = 0;
    for (size_t i = 0; i < d->size; ++i) {
        if (ci_contains(d->data[i].name, query) || ci_contains(d->data[i].phone, query)) {
            if (!found) {
                printf("Matches:\n");
                printf("ID   Name                           Phone             Email\n");
                printf("---- ------------------------------ ---------------- ------------------------------\n");
            }
            found = 1;
            printf("%-4d %-30s %-16s %-30s\n",
                   d->data[i].id, d->data[i].name, d->data[i].phone, d->data[i].email);
        }
    }
    if (!found) printf("No matches.\n");
}
static int dir_save(const Directory *d, const char *path) {
