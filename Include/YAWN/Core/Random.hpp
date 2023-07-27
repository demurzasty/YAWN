#pragma once 

namespace YAWN {
    class Random {
    public:
        static Random Global;

        static constexpr int Size = 624;
        static constexpr int Period = 397;
        static constexpr int Difference = Size - Period;
        static constexpr int MagicNumber = 0x9908b0df;

    public:
        Random(int seed = 0);

        Random(const Random&) = delete;

        Random(Random&&) noexcept = default;

        Random& operator=(const Random&) = delete;

        Random& operator=(Random&&) noexcept = default;

        int Next();

    private:
        void GenerateNumbers();

        int Unroll(int i, int value);

        int M32(int x);

        int L31(int x);

    private:
        int mMt[Size];
        int mMtTempered[Size];
        int mIndex = Size;
    };
}