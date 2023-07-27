#pragma once 

#include "Reference.hpp"

namespace YAWN {
    class Buffer : public Reference {
        YAWN_OBJECT(Buffer, Reference);

    public:
        explicit Buffer(int size);

        Buffer(const void* initialData, int size);

        virtual ~Buffer() override;

        const void* GetData() const;

        void* GetData();

        int GetSize() const;

    private:
        void* mData = nullptr;
        int mSize = 0;
    };
}