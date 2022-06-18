/**
 * \file
 * \brief Файл, содержащий пространство имён card для описания карт
 */

#ifndef CARD_H
#define CARD_H

namespace card {
    const int amount = 52; ///< Количество карт в колоде

    /// Набор карточных мастей
    enum suit {
        SPADES,   ///< Пики
        CLUBS,    ///< Крести
        DIAMONDS, ///< Буби
        HEARTS    ///< Черви
    };

    /// Набор карточных значений
    enum value {
        ACE = 1, ///< Туз
        TWO,     ///< 2
        THREE,   ///< 3
        FOUR,    ///< 4
        FIVE,    ///< 5
        SIX,     ///< 6
        SEVEN,   ///< 7
        EIGHT,   ///< 8
        NINE,    ///< 9
        TEN,     ///< 10
        JACK,    ///< Валет
        QUEEN,   ///< Дама
        KING     ///< Король
    };
}

#endif //CARD_H
