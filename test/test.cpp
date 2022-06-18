#ifndef TEST
#define TEST

#include <iostream>
#include <doctest.h>
#include "../src/headers/game.h"

TEST_CASE("Game::changeBet(int) test") {
    Game game;
    game.reset();
    REQUIRE(game.getBet() == 5);
    game.changeBet(6);
    REQUIRE(game.getBet() == 6);
    game.changeBet(13);
    REQUIRE(game.getBet() == 13);
    REQUIRE_THROWS_AS(game.changeBet(13), std::invalid_argument);
    REQUIRE_THROWS_AS(game.changeBet(12), std::invalid_argument);
    REQUIRE_THROWS_AS(game.changeBet(65), std::invalid_argument);
    game.reset();
    REQUIRE_THROWS_AS(game.changeBet(0), std::invalid_argument);
    REQUIRE_THROWS_AS(game.changeBet(4), std::invalid_argument);
    REQUIRE_THROWS_AS(game.changeBet(-2), std::invalid_argument);
}

TEST_CASE("Game::countCombination(gambler) test") {
    Game game;
    std::array<GameCard, 5> minCombination = {
        std::make_pair(card::SPADES, card::ACE),
        std::make_pair(card::CLUBS, card::ACE),
        std::make_pair(card::DIAMONDS, card::ACE),
        std::make_pair(card::HEARTS, card::ACE),
        std::make_pair(card::SPADES, card::TWO)
    };
    game.playerHand = minCombination;
    REQUIRE(game.countCombination(Game::PLAYER) == 6);
    std::array<GameCard, 5> maxCombination = {
        std::make_pair(card::SPADES, card::KING),
        std::make_pair(card::CLUBS, card::KING),
        std::make_pair(card::DIAMONDS, card::KING),
        std::make_pair(card::HEARTS, card::KING),
        std::make_pair(card::SPADES, card::QUEEN)
    };
    game.playerHand = maxCombination;
    REQUIRE(game.countCombination(Game::PLAYER) == 64);
    std::array<GameCard, 5> randomCombination = {
        std::make_pair(card::DIAMONDS, card::ACE),
        std::make_pair(card::HEARTS, card::TEN),
        std::make_pair(card::SPADES, card::FIVE),
        std::make_pair(card::CLUBS, card::JACK),
        std::make_pair(card::DIAMONDS, card::JACK)
    };
    game.playerHand = randomCombination;
    REQUIRE(game.countCombination(Game::PLAYER) == 38);
}

TEST_CASE("Game::getGameCard(int) test") {
    std::array<GameCard, 52> cardDeck = {
        std::make_pair(card::SPADES, card::ACE),
        std::make_pair(card::SPADES, card::TWO),
        std::make_pair(card::SPADES, card::THREE),
        std::make_pair(card::SPADES, card::FOUR),
        std::make_pair(card::SPADES, card::FIVE),
        std::make_pair(card::SPADES, card::SIX),
        std::make_pair(card::SPADES, card::SEVEN),
        std::make_pair(card::SPADES, card::EIGHT),
        std::make_pair(card::SPADES, card::NINE),
        std::make_pair(card::SPADES, card::TEN),
        std::make_pair(card::SPADES, card::JACK),
        std::make_pair(card::SPADES, card::QUEEN),
        std::make_pair(card::SPADES, card::KING),
        std::make_pair(card::CLUBS, card::ACE),
        std::make_pair(card::CLUBS, card::TWO),
        std::make_pair(card::CLUBS, card::THREE),
        std::make_pair(card::CLUBS, card::FOUR),
        std::make_pair(card::CLUBS, card::FIVE),
        std::make_pair(card::CLUBS, card::SIX),
        std::make_pair(card::CLUBS, card::SEVEN),
        std::make_pair(card::CLUBS, card::EIGHT),
        std::make_pair(card::CLUBS, card::NINE),
        std::make_pair(card::CLUBS, card::TEN),
        std::make_pair(card::CLUBS, card::JACK),
        std::make_pair(card::CLUBS, card::QUEEN),
        std::make_pair(card::CLUBS, card::KING),
        std::make_pair(card::DIAMONDS, card::ACE),
        std::make_pair(card::DIAMONDS, card::TWO),
        std::make_pair(card::DIAMONDS, card::THREE),
        std::make_pair(card::DIAMONDS, card::FOUR),
        std::make_pair(card::DIAMONDS, card::FIVE),
        std::make_pair(card::DIAMONDS, card::SIX),
        std::make_pair(card::DIAMONDS, card::SEVEN),
        std::make_pair(card::DIAMONDS, card::EIGHT),
        std::make_pair(card::DIAMONDS, card::NINE),
        std::make_pair(card::DIAMONDS, card::TEN),
        std::make_pair(card::DIAMONDS, card::JACK),
        std::make_pair(card::DIAMONDS, card::QUEEN),
        std::make_pair(card::DIAMONDS, card::KING),
        std::make_pair(card::HEARTS, card::ACE),
        std::make_pair(card::HEARTS, card::TWO),
        std::make_pair(card::HEARTS, card::THREE),
        std::make_pair(card::HEARTS, card::FOUR),
        std::make_pair(card::HEARTS, card::FIVE),
        std::make_pair(card::HEARTS, card::SIX),
        std::make_pair(card::HEARTS, card::SEVEN),
        std::make_pair(card::HEARTS, card::EIGHT),
        std::make_pair(card::HEARTS, card::NINE),
        std::make_pair(card::HEARTS, card::TEN),
        std::make_pair(card::HEARTS, card::JACK),
        std::make_pair(card::HEARTS, card::QUEEN),
        std::make_pair(card::HEARTS, card::KING)
    };
    for (int i = 0; i < cardDeck.size(); i++)
        REQUIRE(Game::getGameCard(i) == cardDeck[i]);
    REQUIRE_THROWS_AS(Game::getGameCard(-1), std::invalid_argument);
    REQUIRE_THROWS_AS(Game::getGameCard(52), std::invalid_argument);
    REQUIRE_THROWS_AS(Game::getGameCard(100), std::invalid_argument);
}

TEST_CASE("Game::isContains(std::array<int, 10>, int) test") {
    std::array<int, 10> array = {-2, 4, 0, 123, 7, 7, 12, -7, 4, 99};
    REQUIRE(Game::isContains(array, -7));
    REQUIRE(Game::isContains(array, -2));
    REQUIRE(Game::isContains(array, 0));
    REQUIRE(Game::isContains(array, 4));
    REQUIRE(Game::isContains(array, 7));
    REQUIRE(Game::isContains(array, 12));
    REQUIRE(Game::isContains(array, 99));
    REQUIRE(Game::isContains(array, 123));
    REQUIRE(!Game::isContains(array, -1));
    REQUIRE(!Game::isContains(array, 1));
    REQUIRE(!Game::isContains(array, 100));
}

#endif //TEST
