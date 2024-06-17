typedef struct string {
    char *bytes;
    i64 length;
    i64 allocated;
    struct string *next;
} String;

typedef struct strcursor {
    String *s;
    String *seg;
    i64 position;
    i64 localPosition;
    i64 segIdx;
} SCursor;

String *String_Make(uchar *content);
status String_Add(String *a, String *additional);
i64 String_Length(String *s);
