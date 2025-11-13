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
    FILE *f = fopen(path, "wb");
    if (!f) { perror("fopen"); return 0; }
    if (fwrite(&d->next_id, sizeof(d->next_id), 1, f) != 1) { fclose(f); return 0; }
    size_t sz = d->size;
    if (fwrite(&sz, sizeof(sz), 1, f) != 1) { fclose(f); return 0; }
    if (sz && fwrite(d->data, sizeof(Contact), sz, f) != sz) { fclose(f); return 0; }
    fclose(f);
    return 1;
}
static int dir_load(Directory *d, const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return 0;
    int next_id = 1;
    size_t sz = 0;
    if (fread(&next_id, sizeof(next_id), 1, f) != 1) { fclose(f); return 0; }
    if (fread(&sz, sizeof(sz), 1, f) != 1) { fclose(f); return 0; }
    dir_reserve(d, sz);
    if (sz && fread(d->data, sizeof(Contact), sz, f) != sz) { fclose(f); return 0; }
    d->size = sz;
    d->next_id = next_id;
    fclose(f);
    return 1;
}
static void calllog_init(CallLog *cl) {
    cl->head = 0;
    cl->count = 0;
}
static void calllog_add(CallLog *cl, const char *name, const char *phone) {
    CallLogEntry *e = &cl->entries[cl->head];
