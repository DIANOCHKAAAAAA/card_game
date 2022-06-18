/**
 * \file
 * \brief Файл, содержащий описание класса Game
 */

#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <array>
#include <utility>
#include "card.h"

/// Пара масть и значение образуют определённую карту
typedef std::pair<card::suit, card::value> GameCard;

/**
 * \brief Класс, реализующий API для взаимодействия с игрой
 */
class Game {
public:
    /// Набор игроков
    enum gambler {
        PLAYER,  ///< Игрок
        COMPUTER ///< Компьютер
    };

    /**
     * \brief Конструктор класса
     * Запускает генератор псевдослучайных чисел
     */
    Game();

    /**
     * \brief Создаёт / пересоздаёт игру
     * Определяет набор карт игроков и очерёдность ходов
     */
    void reset();

    /**
     * \brief Изменяет текущую ставку, после чего передаёт ход другому игроку
     * \param value новое значение ставки
     * \throw std::invalid_argument в случае неверно заданной ставки (ставка меньше предыдущей или больше максимально возможной)
     */
    void changeBet(int);

    /**
     * \brief Возвращает текущую ставку
     * \return текущую ставку
     */
    int getBet() const;

    /**
     * \brief Принимает текущую ставку
     * \return статус игры
     */
    bool acceptBet();

    /**
     * \brief Определяет текущего игрока
     * \return игрока, чей ход текущий
     */
    gambler whoseTurn() const;

    /**
     * \brief Возвращает карты на руке у игрока
     * \return массив карт
     */
    std::array<GameCard, 5> playerCards() const;

    /**
     * \brief Возвращает карты на руке у компьютера
     * \return массив карт
     */
    std::array<GameCard, 5> computerCards() const;

    /**
     * \brief Подсчитывает комбинацию карт определённого игрока
     * \param gambler игрок или компьютер
     * \return сумма комбинации карт
     */
    int countCombination(gambler) const;

    /**
     * \brief Выполняет ход компьютера
     * В случае хода компьютера определяет его действия в зависимости от ситуации и рандома
     * \warning Компилятор кидает warning по поводу отсутствия return в конце, однако они все в блоке if-else
     * \return ход компьютера (принял или проверил)
     */
    bool computerTurn();

    /**
     * \brief Определяет победителя
     * \return победителя
     */
    gambler winner();

#ifndef TEST ///< убирает protected для тестов
protected:
#endif
    /**
     * \brief Передаёт ход следующему игроку
     */
    void changeTurn();

    /**
     * \brief По номеру определяет карту
     * \param id номер карты
     * \throw std::invalid_argument в случае неверно заданного номера
     * \return карту
     */
    static GameCard getGameCard(int);

    /**
     * \brief Проверяет наличие целого числа в массиве
     * \param array массив целых чисел длины 10
     * \param value искомое значение
     * \return true, если значение содержится в массиве, и false в противном случае
     */
    static bool isContains(std::array<int, 10>, int);

#ifndef TEST ///< убирает private для тестов
private:
#endif
    bool gameProgress;                    ///< true, если игра в процессе
    std::array<GameCard, 5> playerHand;   ///< карты игрока
    std::array<GameCard, 5> computerHand; ///< карты компьютера
    gambler turn;                         ///< определяет, чей ход
    int bet;                              ///< последняя ставка

};

#endif //GAME_H
