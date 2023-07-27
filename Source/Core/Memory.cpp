#include <YAWN/Core/Memory.hpp>
#include <YAWN/Core/Assert.hpp>

#include <stdlib.h>
#include <string.h>

using namespace YAWN;

void* Memory::Allocate(int size) {
    YAWN_ASSERT(size >= 0);

    if (size > 0) {
        return malloc(size_t(size));
    }

    return nullptr;
}

void* Memory::Reallocate(void* data, int size) {
    YAWN_ASSERT(size >= 0);

    if (size > 0) {
        return realloc(data, size_t(size));
    }

    free(data);
    return nullptr;
}

void Memory::Deallocate(void* data) {
    free(data);
}

void Memory::Copy(void* dst, const void* src, int size) {
    YAWN_ASSERT(size >= 0);

    memcpy(dst, src, size_t(size));
}

int Memory::Compare(const void* mem1, const void* mem2, int size) {
    return memcmp(mem1, mem2, size_t(size));
}

