typedef struct match {
    cls type; 
    status state;
    String *s; 
    int position;
} Match;

Match *Match_Make(MemCtx *m, String *s);
status Match_Feed(Match *mt, uchar c);
void Match_Reset(Match *mt);
