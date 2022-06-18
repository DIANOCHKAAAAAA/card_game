/**
 * \file
 * \brief Файл, содержащий описание класса Window
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <array>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"

/**
 * \brief Класс, реализующий окно приложения и взаимодействие пользователя с программой
 */
class Window {
public:
    /**
     * \brief Конструктор класса
     * Создаёт окно, загружает шрифты и текстуры
     * \param width ширина окна
     * \param height высота окна
     * \param title заголовок окна
     */
    Window(int, int, std::string);

    /**
     * \brief Запускает цикл отрисовки приложения
     * Создаёт и отрисовывает элементы в окне, определяет логику взаимодействия с приложением
     */
    void run();

    /**
     * \brief Создаёт новую игру
     * Создаёт / пересоздаёт игру, обновляет текстуры карт
     */
    void newGame();

protected:
    /**
     * \brief Выводит сообщение об ошибке и закрывает программу
     * \param info сообщение об ошибке
     */
    void logError(std::string);

    /**
     * \brief Определяет, произошёл ли клик мыши в заданной области
     * \param mouse событие клика мыши
     * \param left x-координата левой стороны прямоугольной области
     * \param top y-координата верхней стороны прямоугольной области
     * \param right x-координата правой стороны прямоугольной области
     * \param down y-координата нижней стороны прямоугольной области
     * \return true, если клик произошёл в указанном прямоугольнике, и false в противном случае
     */
    static bool inArea(sf::Event::MouseButtonEvent, int, int, int, int);

    /**
     * \brief Определяет, находится ли курсор в заданной области
     * \param mouse событие движения мыши
     * \param left x-координата левой стороны прямоугольной области
     * \param top y-координата верхней стороны прямоугольной области
     * \param right x-координата правой стороны прямоугольной области
     * \param down y-координата нижней стороны прямоугольной области
     * \return true, если курсор находится в указанном прямоугольнике, и false в противном случае
     */
    static bool inArea(sf::Event::MouseMoveEvent, int, int, int, int);

private:
    sf::RenderWindow window;                                ///< окно приложения
    const std::string resourcesPath = "../../resources";    ///< путь до папки с ресурсами
    sf::Font font;                                          ///< шрифт
    sf::Texture backgroundTexture;                          ///< текстура фона
    std::array<sf::Texture, card::amount + 1> cardTextures; ///< текстуры карт (52 лицевых сторон и 1 рубашка)
    sf::Texture turnTexture;                                ///< текстура стрелочки, указывающей, чей ход текущий
    sf::Texture infoTexture;                                ///< текстура символа информации
    std::array<sf::RectangleShape, 5> playerCards;          ///< карты игрока
    std::array<sf::RectangleShape, 5> computerCards;        ///< карты компьютера
    std::array<sf::RectangleShape, 5> computerCardsBack;    ///< карты компьютера рубашкой вверх
    Game game;                                              ///< объект класса Game
    bool gameStarted;                                       ///< true, когда игра запущена
    bool gameProgress;                                      ///< true, пока одна из сторон не победит
    int curBet;                                             ///< текущая ставка

};

#endif //WINDOW_H
