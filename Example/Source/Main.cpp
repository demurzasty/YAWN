#include <YAWN/YAWN.hpp>

using namespace YAWN;

void Initialize() {

}

int Main(int argc, char* argv[]) {
    Directory::SetCurrentDirectory(String::FromUTF8(YAWN_CURRENT_DIRECTORY));

    Application::Setup();

    Application::AddInitializationStep(&Initialize);

    Application::Run();
    return 0;
}
