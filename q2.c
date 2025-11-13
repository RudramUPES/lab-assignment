}
static void calllog_print(const CallLog *cl) {
    if (cl->count == 0) {
        printf("No recent calls.\n");
        return;
    }
    printf("Recent dialed numbers (newest first):\n");
    printf("#    Time                          Name                           Phone\n");
    printf("---- ---------------------------- ------------------------------ ----------------\n");
    int idx = (cl->head - 1 + CALL_LOG_MAX) % CALL_LOG_MAX;
    for (int i = 0; i < cl->count; ++i) {
        const CallLogEntry *e = &cl->entries[idx];
        char buf[64];
        struct tm *tmv = localtime(&e->when);
        if (tmv) strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tmv);
        else strncpy(buf, "unknown", sizeof(buf));
        printf("%-4d %-28s %-30s %-16s\n", i+1, buf, e->name, e->phone);
        idx = (idx - 1 + CALL_LOG_MAX) % CALL_LOG_MAX;
    }
}
static int calllog_save(const CallLog *cl, const char *path) {
    FILE *f = fopen(path, "wb");
    if (!f) { perror("fopen"); return 0; }
    if (fwrite(cl, sizeof(CallLog), 1, f) != 1) { fclose(f); return 0; }
    fclose(f);
    return 1;
}
static int calllog_load(CallLog *cl, const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return 0;
    CallLog temp;
    if (fread(&temp, sizeof(CallLog), 1, f) != 1) { fclose(f); return 0; }
    *cl = temp;
    fclose(f);
    return 1;
}
static void action_add(Directory *d) {
    char name[MAX_NAME], phone[MAX_PHONE], email[MAX_EMAIL];
    read_line("Name: ", name, sizeof(name));
    read_line("Phone: ", phone, sizeof(phone));
    read_line("Email: ", email, sizeof(email));
