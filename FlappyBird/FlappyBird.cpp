#include "pch.h"

#include "StatesManager.h"
#include "MainMenu.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
    StatesManager engine;

    /*std::string dir = argv[0];

    dir = dir.substr(0U, dir.find_first_of("\\/"));*/

    engine.init(fs::current_path(), "Test");

    engine.pushState(new MainMenu);

    auto max_frame_time = chrono::duration_cast<chrono::nanoseconds>(1000ms)
        / engine.getMaxFps();
    auto frametime = chrono::steady_clock::now();
    auto deltatime = chrono::steady_clock::now();


    while (engine.isRunning())
    {
        frametime = chrono::steady_clock::now();

        sf::Event ev;
        if (engine.window.pollEvent(ev))
            engine.handleEvent(ev);

        float dt = (chrono::steady_clock::now() - deltatime).count() / 1000000000.f;
        deltatime = chrono::steady_clock::now();

        engine.update(dt);
        engine.draw();

        std::this_thread::sleep_for(max_frame_time - (chrono::steady_clock::now() - frametime));
    }

    engine.cleanup();

    return 0;
}
