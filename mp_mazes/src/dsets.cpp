/* Your code here! */
#include "dsets.h"
void DisjointSets::addelements(int num) {
    for(int i = 0; i < num; i++) {
        s.push_back(-1);
    }
}
int DisjointSets::find(int elem) {
    if(s[elem] < 0) {
        return elem;
    } else {
        return find(s[elem]);
    }
}
void DisjointSets::setunion(int a, int b) {
    int x = find(a);
    int y = find(b);
    int newSize = s[x] + s[y];
    if(s[x] < s[y]) {
        s[y] = x;
        s[x] = newSize;
    } else {
        s[x] = y;
        s[y] = newSize;
    }
}
int DisjointSets::size(int elem) {
    int i = find(elem);
    int output = (s[i]);
    return -output;
}