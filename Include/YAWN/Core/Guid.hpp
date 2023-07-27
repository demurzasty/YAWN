#pragma once 

#include "String.hpp"
#include "Random.hpp"

namespace YAWN {
    class Guid {
    public:
        static Guid Generate(Random& random = Random::Global);

    public:
        Guid();

        explicit Guid(int data[4]);

        explicit Guid(const String& data);

        Guid(const Guid&) = default;
        Guid(Guid&&) noexcept = default;

        Guid& operator=(const Guid&) = default;
        Guid& operator=(Guid&&) noexcept = default;

        bool operator==(const Guid& guid) const;

        bool operator!=(const Guid& guid) const;

        bool operator<(const Guid& guid) const;

        bool operator>(const Guid& guid) const;

        String ToString() const;

    private:
        union {
            int mData[4];
            char mBytes[16];
        };
    };
}
