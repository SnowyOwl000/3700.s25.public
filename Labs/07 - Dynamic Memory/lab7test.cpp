#include <iostream>
#include "sampler.h"
#include "disjointSet.h"

using namespace std;

#define REPI(ctr,start,limit) for (uint32_t ctr=(start);(ctr)<(limit);(ctr)++)
#define OPF(b) ((b) ? "pass" : "fail")

const int32_t
    SAMPLER_SIZE = 1000000,
    DS_SIZE = 10000;

uint8_t
    myRank[DS_SIZE] = {0};
uint32_t
    samplerCheck1[SAMPLER_SIZE]={0},
    samplerCheck2[SAMPLER_SIZE]={0},
    myParent[DS_SIZE];

uint32_t myFind(uint32_t a) {
    uint32_t
        stack[32],top=0;

    if (a >= DS_SIZE)
        throw std::domain_error("myFind: Invalid element");

//    if (a != myParent[a])
//        myParent[a] = myFind(myParent[a]);

    while (a != myParent[a]) {
        stack[top++] = a;
        a = myParent[a];
    }

    while (top > 0) {
        top--;

        myParent[stack[top]] = a;
    }

    return a;
}

void myUnion(uint32_t a,uint32_t b) {

    a = myFind(a);
    b = myFind(b);

    if (a != b) {
        if (myRank[b] > myRank[a])
            myParent[a] = b;
        else {
            if (myRank[a] == myRank[b])
                myRank[a]++;

            myParent[b] = a;
        }
    }
}

int main() {
    Sampler
        s(SAMPLER_SIZE),
        dss(DS_SIZE * DS_SIZE);
    DisjointSet
        ds(DS_SIZE);
    bool
        okay;

    // check the sampler
    REPI(i,0,SAMPLER_SIZE) {
        uint32_t e = s.getSample();

        samplerCheck1[e] = 1;
        samplerCheck2[e] = i;
    }

    okay = true;
    for (unsigned int n : samplerCheck1)
        if (n != 1)
            okay = false;
    cout << "sampler elements used: " << OPF(okay) << endl;

    // calculate a correlation coefficient. This should be very close to 0
    double
        r,sumXY=0,sumX=0,sumY=0,sumX2=0,sumY2=0;

    REPI(i,0,SAMPLER_SIZE) {
        sumX += i;
        sumY += samplerCheck2[i];
        sumX2 += i * (double)i;
        sumY2 += samplerCheck2[i] * (double)samplerCheck2[i];
        sumXY += i * (double)samplerCheck2[i];
    }

    r = (SAMPLER_SIZE * sumXY - sumX * sumY) /
            (sqrt(SAMPLER_SIZE * sumX2 - sumX * sumX) *
            sqrt(SAMPLER_SIZE * sumY2 - sumY * sumY));
    cout << "          correlation: " << r << endl;

    // check disjoint set
    REPI(i,0,DS_SIZE) {
        myParent[i] = i;
        myRank[i] = 0;
    }

    // initially, check that find(i) == i for all i
    okay = true;
    REPI(i,0,DS_SIZE) {
        if (ds.find(i) != myFind(i) || ds.find(i) != i)
            okay = false;
    }
    cout << " disjoint set initial: " << OPF(okay) << endl;

    // now, choose all pairs randomly and join them
    okay = true;
    REPI(i,0,DS_SIZE * DS_SIZE) {
        int32_t
            e = dss.getSample(),
            a = e / DS_SIZE,
            b = e % DS_SIZE;

        // if a and b are in different sets, join them
        if (myFind(a) != myFind(b)) {
            myUnion(a, b);
            ds.join(a, b);
            // make sure find(i) is correct for all i
            REPI(j, 0, DS_SIZE) {
                if (ds.find(j) != myFind(j))
                    okay = false;
            }
        }
    }
    // at the end, make sure all finds are the same
    REPI(i,0,DS_SIZE)
        if (ds.find(i) != ds.find(0))
            okay = false;
    cout << "   disjoint set final: " << OPF(okay) << endl;

    return 0;
}
