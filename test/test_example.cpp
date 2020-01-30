extern "C" {
    void* memset(void*, int, size_t);
    int memcmp(const void*, const void*, size_t);
    void* malloc(size_t);
}
struct T1 {
    T1 *t1pt1;
};
typedef struct T1 * PT1;
struct T2 {
    T1 *t2pt1;
    int t2a[5];
};
struct T3 {
    T2 *t3t2;
    void init() {
        memset(t3t2->t2a, 0, sizeof(t3t2->t2a)); // recommend: sizeof(t3t2->t2a); this is not a bug in the sample code
    }
};
int main() {
    T1 t1, *pt1 = &t1;
    T2 t2, *pt2 = &t2;
    T3 t3; t3.t3t2 = &t2; t3.t3t2->t2pt1=pt1;
    char *b1 = new char[10];
    unsigned *b2 = new unsigned[10];
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // memset
    ////////////////////////////////////////////////////////////////////////////////////////////////
// &var,sizeof(&var) -- popular fix was Remove & in sizeof but we can't see the & in the sizeof expr
    memset(&t1, 0, sizeof(&t1)); // recommend: sizeof(struct T1)
    memset(t3.t3t2->t2a, 0, sizeof(t3.t3t2->t2a)); // recommend: sizeof(t3.t3t2->t2a); this is not a bug in the sample code
// &var,sizeof(ptr-typedef)
    memset(&t1, 0, sizeof(PT1)); // recommend: sizeof(struct T1)
// &var,sizeof(wrong-class)
    memset(&t1, 0, sizeof(T2));  // recommend: sizeof(t1)
// &var,sizeof(wrong-var)
    memset(&t1, 0, sizeof(&t2));  // recommend: sizeof(t1)
// var,sizeof(ptr-typedef)
    memset(pt1, 0, sizeof(PT1)); // recommend: sizeof(struct T1)
// var,sizeof(var) - built-in type
    memset(b1, 0, sizeof(b1));   // recommend: N * sizeof(*b1) where N is the length of the array
    memset(b2, 0, sizeof(b2));   // recommend: N * sizeof(*b2) where N is the length of the array
// var,sizeof(var) - not built-int type
    memset(pt1, 0, sizeof(pt1)); // recommend: sizeof(*pt1)
// &var,sizeof(ptr-struct)
    memset(&t1, 0, sizeof(struct T1*)); // recommend: sizeof(struct T1)
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //alloc; var is the variable being assigned to instead of being an arg to the function
    ////////////////////////////////////////////////////////////////////////////////////////////////
// alloc,var,sizeof(ptr-typedef)
    pt1 = (PT1)malloc(sizeof(PT1));   // recommend: sizeof(struct T1)
// alloc,var,sizeof(var)
    pt1 = (PT1)malloc(sizeof(pt1));   // recommend: sizeof(*pt1)
// alloc,var,sizeof(var)
    t3.t3t2->t2pt1->t1pt1 = (PT1)malloc(sizeof(pt1));   // recommend: sizeof(*(t3.t3t2->t2pt1->t1pt1))
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //todo: memcmp; this has 2 ptr args
    ////////////////////////////////////////////////////////////////////////////////////////////////
//&v1,&v1,sizeof(&v2) -- popular fix was Remove & in sizeof but we can't see the & in the sizeof expr
    memcmp(&t1,&t2,sizeof(&t1));  // recommend: sizeof(struct T1)
//v1,v2,sizeof(v1)
    memcmp(pt1,pt2,sizeof(pt1));  // recommend: sizeof(*pt1)
//v1,v2,sizeof(v2)
    memcmp(pt1,pt2,sizeof(pt2));  // recommend: sizeof(*pt1)
//v1,v2,sizeof(ptr-typedef)
    memcmp(pt1,pt2,sizeof(PT1));  // recommend: sizeof(struct T1)
//&v1,v2,sizeof(v2)
    memcmp(&t1,pt2,sizeof(pt2)); // recommend: sizeof(t1)
//&v1,&v2,sizeof(ptr-typdef)
    memcmp(&t1,&t2,sizeof(PT1)); // recommend: sizeof(struct T1)
//&v1,v2,sizeof(ptr-struct)
    memcmp(&t1,pt2,sizeof(T1*)); // recommend: sizeof(struct T1)
//v1,&v2,sizeof(v1)
    memcmp(pt1,&t2,sizeof(pt1)); // recommend: sizeof(*pt1)
}
