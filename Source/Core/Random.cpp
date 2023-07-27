#include <YAWN/Core/Random.hpp>

using namespace YAWN;

Random Random::Global;

Random::Random(int seed)
    : mMt(), mMtTempered() {
    mMt[0] = seed;

    for (int i = 1; i < Size; ++i) {
        mMt[i] = 0x6c078965 * (mMt[i - 1] ^ mMt[i - 1] >> 30) + i;
    }
}

int Random::Next() {
    if (mIndex == Size) {
        GenerateNumbers();
        mIndex = 0;
    }

    return mMtTempered[mIndex++];
}

void Random::GenerateNumbers() {
    int i = 0;

    while (i < Difference) {
        i = Unroll(i, i + Period);
    }

    while (i < Size - 1) {
        i = Unroll(i, i - Difference);
    }

    int x = M32(mMt[Size - 1]) | L31(mMt[0]);
    mMt[Size - 1] = mMt[Period - 1] ^ (x >> 1) ^ (((x << 31) >> 31) & MagicNumber);

    for (int i = 0; i < Size; ++i) {
        int x = mMt[i];
        x ^= x >> 11;
        x ^= x << 7 & 0x9d2c5680;
        x ^= x << 15 & 0xefc60000;
        x ^= x >> 18;
        mMtTempered[i] = x;
    }
}

int Random::Unroll(int i, int value) {
    int x = M32(mMt[i]) | L31(mMt[i + 1]);
    mMt[i] = mMt[value] ^ (x >> 1) ^ (((x << 31) >> 31) & MagicNumber);
    return i + 1;
}

int Random::M32(int x) {
    return 0x80000000 & x;
}

int Random::L31(int x) {
    return 0x7FFFFFFF & x;
}
