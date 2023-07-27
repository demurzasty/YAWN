#pragma once 

#include "../Core/Array.hpp"

namespace YAWN {
    class Application {
    public:
        static void Setup();

        static void Run();

        template<typename TService>
        static void AddService() {
            sInitializations.Add(&TService::Initialize);
            sReleases.Add(&TService::Release);
        }

        static void AddInitializationStep(void(*initialization)()) {
            sInitializations.Add(initialization);
        }

    private:
        static Array<void(*)()> sInitializations;
        static Array<void(*)()> sReleases;
    };
}
