typedef struct string {
    uchar *bytes;
    i64 length;
    i64 allocated;
    struct string *next;
} String;

String *String_Make(MemCtx *m, uchar *bytes);
status String_Add(MemCtx *m, String *a, uchar *bytes);
i64 String_Length(String *s);
