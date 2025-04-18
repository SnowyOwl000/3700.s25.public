#include <iostream>
#include <random>
#include <string>
#include "bstDictionary.h"
#include "sampler.h"

using namespace std;

#define REPI(ctr,start,limit) for (uint32_t ctr=(start);(ctr)<(limit);(ctr)++)
#define OPF(f) ((f) ? "pass" : "fail")

const uint32_t
        N_ITEMS = 1048576;//1048576

int main() {
    BSTDictionary<string,uint32_t>
            d1,d2;
    auto
            keys1 = new string[N_ITEMS];
    auto
            keys2 = new string[N_ITEMS];
    auto
            values1 = new uint32_t[N_ITEMS];
    auto
            values2 = new uint32_t[N_ITEMS];
    random_device
            rd;
    mt19937
            mt(rd());
    uniform_int_distribution<>
            charDis(0,25);
    Sampler
            *s1,*s2;
    bool
            okay;
    // generate two key lists, one for each dictionary
    REPI(i,0,N_ITEMS) {
        REPI(j,0,8) {
            keys1[i] += "abcdefghijklmnopqrstuvwxyz"[charDis(mt)];
            keys2[i] += "abcdefghijklmnopqrstuvwxyz"[charDis(mt)];
        }
        // add counter to keys to prevent duplicates
        keys1[i] += to_string(i);
        keys2[i] += to_string(i);
        // set values to sentinels
        values1[i] = values2[i] = N_ITEMS;
    }

    // add half of the values to d1
    s1 = new Sampler(N_ITEMS);
    REPI(i,0,N_ITEMS/2) {
        uint32_t
                j = s1->getSample();
        values1[j] = i;

        d1[keys1[j]] = values1[j];

        // cout << "added [" << keys1[j] << "] = " << values1[j] << endl;
        // cout << "d1[" << keys1[j] << "] = " << d1[keys1[j]] << endl;
    }
    // add half of the values to d2
    s2 = new Sampler(N_ITEMS);
    REPI(i,0,N_ITEMS/2) {
        uint32_t
                j = s2->getSample();

        values2[j] = i;

        d2[keys2[j]] = values2[j];

        /*  cout << "added [" << keys2[j] << "] = " << values2[j] << endl;
          cout << "d2[" << keys2[j] << "] = " << d2[keys2[j]] << endl; */
    }

    // check that it worked
    okay = true;
    uint32_t
            c = 0;
    REPI(i,0,N_ITEMS)
        try {
            d1.search(keys1[i]);
            c++;
            if (values1[i] == N_ITEMS) {
                okay = false;
                cout << "Key found, not inserted" << endl;
                REPI(j,0,N_ITEMS)
                    if (i != j && keys1[i] == keys1[j])
                        cout << "Duplicate key [" << keys1[i] << "in positions " << i << " and " << j << endl;
            }
        } catch (domain_error &e) {
            if (values1[i] < N_ITEMS) {
                okay = false;
                cout << "key inserted, not found" << endl;
            }
        }
    cout << "Insert half into d1: " << OPF(okay) << endl;
    cout << "c = " << c << endl;

    // check that it worked
    okay = true;
    REPI(i,0,N_ITEMS)
        try {
            d2.search(keys2[i]);
            if (values2[i] == N_ITEMS) {
                okay = false;
                cout << "key found, not inserted" << endl;
                REPI(j,0,N_ITEMS)
                    if (i != j && keys2[i] == keys2[j])
                        cout << "Duplicate key [" << keys2[i] << "in positions " << i << " and " << j << endl;
            }
        } catch (domain_error &e) {
            if (values2[i] < N_ITEMS) {
                okay = false;
                cout << "key inserted, not found" << endl;
            }
        }
    cout << "Insert half into d2: " << OPF(okay) << endl;

    okay = (d1.size() == N_ITEMS / 2) && (d2.size() == N_ITEMS / 2);
    cout << "Size: " << OPF(okay) << endl;

    cout << "Heights: " << d1.height() << ' ' << d2.height() << endl;

    okay = !d1.isEmpty() && !d2.isEmpty();
    cout << "Empty: " << OPF(okay) << endl;

    // check contents of both lists
    okay = true;
    REPI(i,0,N_ITEMS) {
        if (values1[i] < N_ITEMS && d1[keys1[i]] != values1[i])
            okay = false;
        if (values2[i] < N_ITEMS && d2[keys2[i]] != values2[i])
            okay = false;
    }
    cout << "Read: " << OPF(okay) << endl;

    // clear the lists
    d1.clear();
    d2.clear();

    okay = (d1.size() == 0) && (d2.size() == 0);

    cout << "Heights: " << d1.height() << ' ' << d2.height() << endl;

    okay = okay && d1.isEmpty() && d2.isEmpty();
    cout << "Clear: " << OPF(okay) << endl;

    // fill both lists
    REPI(i,0,N_ITEMS) {
        values1[i] = i;
        values2[i] = N_ITEMS + i;
        d1[keys1[i]] = values1[i];
        d2[keys2[i]] = values2[i];
    }

    // remove the odd-valued elements
    REPI(i,0,N_ITEMS)
        if (values1[i] % 2 == 1) {
            d1.remove(keys1[i]);
            d2.remove(keys2[i]);
        }

    okay = (d1.size() == N_ITEMS / 2) && (d2.size() == N_ITEMS / 2);

    cout << "Heights: " << d1.height() << ' ' << d2.height() << endl;

    okay = okay && !d1.isEmpty() && !d2.isEmpty();
    cout << "Remove: " << OPF(okay) << endl;

    // using [] as l- and r-values
    okay = true;
    REPI(i,0,N_ITEMS) {
        if (values1[i] % 2 == 0) {
            d1[keys1[i]] = d1[keys1[i]] * 2;
            if (d1[keys1[i]] != 2 * values1[i])
                okay = false;
        }
        if (values2[i] % 2 == 0) {
            d2[keys2[i]] = d2[keys2[i]] * 2;
            if (d2[keys2[i]] != 2 * values2[i])
                okay = false;
        }
    }
    cout << "[]: " << OPF(okay) << endl;

    return 0;
}