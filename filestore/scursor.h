typedef struct strcursor {
    String *s;
    status state;
    String *seg;
    i64 position;
    i64 compare;
    i64 localPosition;
    i64 segIdx;
    i64 immidiateLength;
} SCursor;

typedef struct strcursor_range {
    status state;
    SCursor *start;
    SCursor *end;
} Range;

SCursor* SCursor_Make(MemCtx *m, String *s);
status SCursor_Prepare(SCursor *sc, i64 length);
status SCursor_Incr(SCursor *sc, i64 length);
status SCursor_Reset(SCursor *sc);
status SCursor_Find(Range *range, String *search, int anchor);
