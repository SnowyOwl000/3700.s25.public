#include <iostream>
#include "dictionary.h"

using namespace std;

#define REPI(ctr,start,limit) for (uint32_t ctr=(start);(ctr)<(limit);(ctr)++)
#define OPF(b) ((b)?"pass":"fail")

int main() {
    Dictionary
        d;
    bool
        okay=true;

    REPI(i,0,100)
        d.insert(i,-i);

    try {
        d.insert(999,999);

        okay = false;       // this should not run
    } catch (const overflow_error &e) {
        // you don't have to do anything here
    }
    cout << "overflow: " << OPF(okay) << endl;

    okay = true;
    REPI(i,0,100)
        try {
            if (d.search(99-i) != i - 99)
                okay = false;
        } catch (const domain_error &e) {
            okay = false;
        }

    cout << "  search: " << OPF(okay) << endl;

    REPI(i,0,50)
        d.remove(2*i+1);        // remove odd keys

    okay = true;
    REPI(i,0,50)
        try {
            if (d.search(2 * i) != -2 * i)   // this should never be true
                okay = false;
        } catch (const domain_error &e) {
            okay = false;                   // we should find all even keys
        }
    REPI(i,0,50)
        try {
            d.search(2 * i + 1);            // this should never work

            okay = false;
        } catch (const domain_error &e) {

        }

    cout << "  remove: " << OPF(okay) << endl;

    okay = (d.size() == 50);
    cout << "    size: " << OPF(okay) << endl;

    okay = !d.isEmpty();
    d.clear();
    okay = okay && d.isEmpty();
    cout << " isEmpty: " << OPF(okay) << endl;

    okay = (d.size() == 0);
    cout << "   clear: " << OPF(okay) << endl;

    return 0;
}
