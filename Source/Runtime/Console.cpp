#include <YAWN/Runtime/Console.hpp>

#include <stdio.h>
#include <stdarg.h>

using namespace YAWN;

ExclusiveMutex Console::sMutex;

void Console::Write(const wchar_t* format, ...) {
    va_list args;
    va_start(args, format);
    vwprintf(format, args);
    va_end(args);
}

void Console::Write(const String& format, ...) {
    va_list args;
    va_start(args, &format);
    vwprintf(format.GetData(), args);
    va_end(args);
}

void Console::WriteLine(const wchar_t* format, ...) {
    ExclusiveLock lock(sMutex);

    va_list args;
    va_start(args, format);
    vwprintf(format, args);
    wprintf(L"\n");
    va_end(args);
}

void Console::WriteLine(const String& format, ...) {
    ExclusiveLock lock(sMutex);

    va_list args;
    va_start(args, &format);
    vwprintf(format.GetData(), args);
    wprintf(L"\n");
    va_end(args);
}
