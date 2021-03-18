#include<SFML/Graphics.hpp>
#include<iostream>
#include"../include/TimeKeeper.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600),"SFML");

    //window.setFramerateLimit(6);

    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    sf::Text Data;
    Data.setFont(font);
    Data.setCharacterSize(12u);
    Data.setPosition(5.0f, 5.0f);
    

    sf::RectangleShape box[5];

    for(int i = 0; i < 5; i++)
    {
        box[i].setSize(sf::Vector2f(10.0f,10.0f));
        box[i].setOrigin(5.0f, 5.0f);
        box[i].setPosition(100 + i*100 , 200 + i*75);
    }
    std::pair<float, float> bounds = std::make_pair<float, float>(100.0f, 700.0f);

    float speed = 100.0f;
    sf::Vector2f velocity[5] {sf::Vector2f(speed, 0.0f),sf::Vector2f(speed, 0.0f),sf::Vector2f(speed, 0.0f),sf::Vector2f(speed, 0.0f),sf::Vector2f(speed, 0.0f)};

    TimeKeeper::initializeTime();

    while(window.isOpen())
    {
        TimeKeeper::updateTime();

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Key::S) TimeKeeper::timeScale(1.0f); //default
                if(event.key.code == sf::Keyboard::Key::A) TimeKeeper::timeScale(0.5f); //half speed
                if(event.key.code == sf::Keyboard::Key::D) TimeKeeper::timeScale(2.0f); //double speed
                if(event.key.code == sf::Keyboard::Key::W) TimeKeeper::timeScale(0.0f); //pause
            }
        }

        for(int i = 0; i < 5; i++)
        {
            if(box[i].getPosition().x <= bounds.first) velocity[i].x = speed;
            else if(box[i].getPosition().x >= bounds.second) velocity[i].x = -speed;

            box[i].move(velocity[i] * TimeKeeper::deltaTime());
        }
        Data.setString("FPS: " + std::to_string(1.0f/TimeKeeper::frameTime()) + "\tTimeScale: " + std::to_string(TimeKeeper::getTimeScale()) +
                       "\nTime(Static): " + std::to_string(TimeKeeper::timeSinceStart(TimeKeeper::ClockType::Static)) + "s" +
                       "\nTime(Dynamic): " + std::to_string(TimeKeeper::timeSinceStart(TimeKeeper::ClockType::Dynamic)) + "s");

        window.clear(sf::Color::Black);
        for(int i = 0; i < 5; i++) window.draw(box[i]);
        window.draw(Data);
        window.display();
    }

    return 0;
}