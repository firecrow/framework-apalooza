typedef struct string {
    char *content;
    i64 length;
    i64 allocated;
    struct string *next;
} String;

String *String_Make(uchar *content);
status String_Add(String *a, String *additional);
i64 String_Length(String *s);
