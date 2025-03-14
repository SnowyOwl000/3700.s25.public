#include <iostream>
#include "CDList.h"

using namespace std;

const uint32_t
        N_ITEMS = 100000;

void times2(uint32_t &n) {
    n <<= 1;
}

void div2(uint32_t &n) {
    n >>= 1;
}

int main() {
    CDList<uint32_t>
            myList;

    cout << "Start testing" << endl;

    for (uint32_t i=0;i<N_ITEMS;i++)
        myList.insert(myList.size(),i);

    cout << "Insert complete" << endl;

    uint32_t
            val = myList.first();

    for (uint32_t i=0;i<N_ITEMS;i++) {
        if (i != val) {
            cout << "Error: i=" << i << "   val=" << val << endl;
            return 1;
        }

        val = myList.next();
    }

    cout << "first and next pass" << endl;

    if (myList.isFirst())
        cout << "isFirst pass" << endl;
    else
        cout << "isFirst fail" << endl;

    if (myList.isEmpty())
        cout << "Non-empty list isEmpty fail" << endl;

    cout << "Searching..."; cout.flush();
    myList.map(times2);
    for (uint32_t i=0;i<2*N_ITEMS;i++) {
        try {
            uint32_t j = myList.search(i);

            if (j != (i >> 1)) {
                cout << "Found i=" << i << " in position " << j << endl;
                break;
            }
        } catch (domain_error &e) {
            if (!(i & 1)) {
                cout << "Could not find i=" << i << endl;
                break;
            }
        }
    }

    cout << "Searching pass" << endl;

    cout << "Removing..."; cout.flush();
    myList.map(div2);
    for (uint32_t i=0;i<N_ITEMS/2;i++)
        myList.remove(i);

//    cout << "List size: " << myList.size() << endl;
//    cout << "First 5 positions: " << myList[0] << ' ' << myList[1] << ' ' << myList[2]
//         << ' ' << myList[3] << ' ' << myList[4] << endl;

    for (uint32_t i=0;i<N_ITEMS;i++) {
        try {
            uint32_t j = myList.search(i);

            if (2 * j + 1 != i) {
                cout << "Found i=" << i << " in position " << j << endl;
                break;
            }
        } catch (domain_error &e) {
            if (i & 1) {
                cout << "Could not find i=" << i << endl;
                break;
            }
        }
    }

    cout << "Remove pass" << endl;

    val = myList.last();

    for (uint32_t i=0;i<N_ITEMS/2;i++) {
        if (N_ITEMS - 2 * i - 1 != val) {
            cout << "Error: i=" << i << "   val=" << val << endl;
            return 1;
        }

        val = myList.prev();
    }

    cout << "last and prev pass" << endl;

    if (myList.isLast())
        cout << "isLast pass" << endl;
    else
        cout << "isFirst fail" << endl;

    myList.current() = 999999999;

    if (myList[N_ITEMS/2-1] == 999999999)
        cout << "cur pass" << endl;
    else
        cout << "cur fail" << endl;

    std::cout << "Testing complete" << std::endl;
    return 0;
}
