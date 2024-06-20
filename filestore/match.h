enum anchor_types {
    ANCHOR_CONTAINS = 0,
    ANCHOR_START = 1,
};

typedef struct match {
    cls type; 
    status state;
    String *s; 
    int position;
    int anchor;
    int intval;
} Match;

Match *Match_Make(MemCtx *m, String *s, int anchor);
status Match_Feed(Match *mt, uchar c);
void Match_Reset(Match *mt);
