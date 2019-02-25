#ifndef ENUMS_H
#define ENUMS_H

enum class Algo {
    Bubble = 1,
    Insertion,
    Selection,
    Merge,
    Quick,
    Heap
};

enum ColumnTable {
    Algo,
    SizeVector,
    TimeMedium,
    Freq
};

enum class IndexQuery {
    AllRecord,
    MediumTime,
    MediumTimeAllAlg
};

enum Order {
    Crescent = 0,
    Decrescent = 1,
    Random = 2
};
enum IndexVector {
    Original,
    Selection,
    Insertion,
    Bubble,
    Merge,
    Quick,
    Heap
};
#endif // ENUMS_H
