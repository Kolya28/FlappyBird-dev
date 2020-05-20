#include "pch.h"
// Evolution.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

#include "StatesManager.h"
#include "MainMenu.h"
#include "Test.h"

#define DEBUG

namespace chrono = std::chrono;
using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
    StatesManager engine;

    const char* dir = argv[0];
#if defined(_DEBUG) || defined(DEBUG)
    dir = "C:\\Users\\nikol\\Desktop\\VS projects\\SFML\\FlappyBird\\FlappyBird";
#endif // _DEBUG


    engine.init(dir, 0, 0, "Test", true);



    engine.pushState(new MainMenu);
    //engine.pushState(new Test);

    chrono::nanoseconds max_frame_time = 1000ms / 75;
    chrono::steady_clock::time_point frametime = chrono::steady_clock::now();
    chrono::steady_clock::time_point deltatime = chrono::steady_clock::now();


    while (engine.isRunning())
    {
        frametime = chrono::steady_clock::now();

        sf::Event ev;
        if (engine.window.pollEvent(ev))
            engine.handleEvent(ev);

        float dt = (chrono::steady_clock::now() - deltatime).count() / 1000000000.f;
        deltatime = chrono::steady_clock::now();

        //std::cout << dt << '\n';
        engine.update(dt);
        engine.draw();

        std::this_thread::sleep_for(max_frame_time - (chrono::steady_clock::now() - frametime));
    }

    engine.cleanup();

    return 0;

    //sf::RenderWindow window(sf::VideoMode(500, 500), "test");
    //window.clear();// sf::Color::White);

    //sf::Font f;
    //f.loadFromFile("font.ttf");

    //sf::Text text("TEST",f,30U);
    //text.setPosition(250.f - text.getGlobalBounds().width/2.f ,
    //    250.f - text.getGlobalBounds().height/2.f);

    //text.getLineSpacing();
    //window.draw(text);


    //sf::RectangleShape stripe;
    //stripe.setFillColor(sf::Color::Red);
    //stripe.setSize(sf::Vector2f(1.f, 1000.f));
    //stripe.setPosition(250, 0);
    //window.draw(stripe);

    //stripe.setSize(sf::Vector2f(1000.f, 1.f));
    //stripe.setPosition(0, 250);

    //window.draw(stripe);

    //window.display();

    //std::cin.get();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

