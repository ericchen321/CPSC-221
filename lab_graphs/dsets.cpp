/**
 * @file dsets.cpp
 * Disjoint Sets implementation.
 */

#include <vector>
#include "dsets.h"

void DisjointSets::addelements(int num)
{
    // add 'num' values of -1
    values.reserve(values.size() + num);
    for (int i = 0; i < num; i++)
        values.push_back(-1);
}

int DisjointSets::find(int elem)
{
    if (values[elem] < 0) // if a root, return
        return elem;
    else // otherwise find the root and path compress
        return values[elem] = find(values[elem]);
}

int DisjointSets::size(int elem)
{
    return -values[find(elem)];
}

void DisjointSets::setunion(int a, int b)
{
    // Find roots
    a = find(a);
    b = find(b);
    // Check for self assignment
    if (a != b) {
        // union by size
        if (values[a] <= values[b]) {
            values[a] += values[b];
            values[b] = a;
        } else {
            values[b] += values[a];
            values[a] = b;
        }
    }
}
