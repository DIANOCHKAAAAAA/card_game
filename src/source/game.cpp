/**
 * \file
 * \brief Файл, содержащий реализацию методов класса Game
 */

#include "../headers/game.h"

Game::Game() : gameProgress(false), turn(PLAYER), bet(5) {
    std::srand(std::time(nullptr));
}

void Game::reset() {
    std::array<int, 10> cardValues{};

    int i = 0;
    while (i < 10) {
        int value = std::rand() % card::amount;
        if (isContains(cardValues, value))
            continue;
        cardValues[i] = value;
        i++;
    }

    for (i = 0; i < 5; i++) {
        playerHand[i] = getGameCard(cardValues[2 * i]);
        computerHand[i] = getGameCard(cardValues[2 * i + 1]);
    }

    gameProgress = true;
    turn = static_cast<gambler>(std::rand() % 2);
    bet = 5;
}

void Game::changeBet(int value) {
    if (gameProgress) {
        if (value <= bet)
            throw std::invalid_argument("Small Bet: " + std::to_string(value));
        if (value > 64)
            throw std::invalid_argument("Big Bet: " + std::to_string(value));
        bet = value;
        changeTurn();
    }
}

int Game::getBet() const {
    return bet;
}

bool Game::acceptBet() {
    gameProgress = false;
    return gameProgress;
}

Game::gambler Game::whoseTurn() const {
    return turn;
}

std::array<GameCard, 5> Game::playerCards() const {
    return playerHand;
}

std::array<GameCard, 5> Game::computerCards() const {
    return computerHand;
}

int Game::countCombination(Game::gambler gambler) const {
    auto cards = gambler == PLAYER ? playerHand : computerHand;
    int sum = 0;
    for (auto &card : cards)
        sum += card.second;
    return sum;
}

bool Game::computerTurn() {
    if (turn == COMPUTER) {
        if ((bet == 64 || rand() % 2 == 0) && bet > 5) {
            acceptBet();
            return true;
        } else {
            int maxRaise = 64 - bet;
            int raise;
            if (rand() % 2 && bet < countCombination(COMPUTER))
                raise = countCombination(COMPUTER);
            else
                raise = bet + (rand() % (maxRaise + 1)) + 1;
            changeBet(raise);
            return false;
        }
    }
}

Game::gambler Game::winner() {
    if (countCombination(static_cast<gambler>(abs(turn - 1))) == bet) {
        return static_cast<gambler>(abs(turn - 1));
    } else {
        return turn;
    }
}

void Game::changeTurn() {
    turn = static_cast<gambler>(abs(turn - 1));
}

GameCard Game::getGameCard(int id) {
    if (id < 0 || id >= 52)
        throw std::invalid_argument("Bad id: " + std::to_string(id));
    int suitAmount = 13;
    auto suit = static_cast<card::suit>(id / suitAmount);
    auto value = static_cast<card::value>(id % suitAmount + 1);
    return std::make_pair(suit, value);
}

bool Game::isContains(std::array<int, 10> array, int value) {
    bool result = false;
    for (auto &element : array) {
        if (element == value) {
            result = true;
            break;
        }
    }
    return result;
}
