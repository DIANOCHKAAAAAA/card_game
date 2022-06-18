/**
 * \file
 * \brief Файл, содержащий реализацию методов класса Window
 */

#include "../headers/window.h"

Window::Window(int width, int height, std::string title) {
    window.create(sf::VideoMode(width, height), title);
    if (!font.loadFromFile(resourcesPath + "/fonts/VinSlabPro.ttf"))
        logError("Error: could not load font");
    if (!backgroundTexture.loadFromFile(resourcesPath + "/images/background.jpg"))
        logError("Error: could not load background texture");
    if (!turnTexture.loadFromFile(resourcesPath + "/images/arrow.png"))
        logError("Error: could not load arrow texture");
    if (!infoTexture.loadFromFile(resourcesPath + "/images/info.png"))
        logError("Error: could not load info texture");
    gameStarted = false;
    gameProgress = false;

    std::array<std::string, 4> suit = {"spades", "clubs", "diamonds", "hearts"};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            std::string texturePath = resourcesPath + "/images/" + suit[i] + "/";
            switch (j + 1) {
                case 1:
                    texturePath += "ace.png";
                    break;
                case 11:
                    texturePath += "jack.png";
                    break;
                case 12:
                    texturePath += "queen.png";
                    break;
                case 13:
                    texturePath += "king.png";
                    break;
                default:
                    texturePath += std::to_string(j + 1);
                    texturePath += ".png";
            }

            if (!cardTextures[i * 13 + j].loadFromFile(texturePath))
                logError("Error: could not load card texture");
        }
    }
    if (!cardTextures[card::amount].loadFromFile(resourcesPath + "/images/card_back.png"))
        logError("Error: could not load card texture");
}

void Window::run() {
    sf::Sprite background(backgroundTexture);

    sf::Text newGameButton(L"Новая игра", font, 24);
    newGameButton.setFillColor(sf::Color::White);
    newGameButton.setPosition(10, 10);

    sf::RectangleShape infoButton(sf::Vector2f(30, 30));
    infoButton.setPosition(760, 10);
    infoButton.setTexture(&infoTexture);
    bool info = false;

    sf::Text playerCombinationInfo("", font, 24);
    playerCombinationInfo.setFillColor(sf::Color::White);
    playerCombinationInfo.setPosition(10, 560);

    sf::RectangleShape turnInfo(sf::Vector2f(30, 30));
    turnInfo.setTexture(&turnTexture);

    sf::Text betInfo("", font, 64);
    betInfo.setFillColor(sf::Color::White);
    betInfo.setPosition(368, 220);
    sf::Text betIncButton("+", font, 64);
    betIncButton.setFillColor(sf::Color::White);
    betIncButton.setPosition(500, 220);
    sf::Text betDecButton("-", font, 64);
    betDecButton.setFillColor(sf::Color::White);
    betDecButton.setPosition(268, 220);

    sf::Text acceptButton(L"Принять", font, 32);
    acceptButton.setFillColor({100, 100, 100});
    acceptButton.setPosition(220, 326);
    bool acceptButtonActive = false;
    sf::Text checkButton(L"Проверить", font, 32);
    checkButton.setFillColor({100, 100, 100});
    checkButton.setPosition(450, 326);
    bool checkButtonActive = false;
    bool computerMadeTurn = false;

    while (window.isOpen()) {
        if (gameProgress && game.whoseTurn() == Game::PLAYER) {
            if (curBet > game.getBet())
                acceptButtonActive = true;
            if (curBet == game.getBet() && computerMadeTurn)
                checkButtonActive = true;
        }
        if (gameProgress && game.whoseTurn() == Game::COMPUTER) {
            acceptButtonActive = false;
            checkButtonActive = false;
            bool isIncrease = game.computerTurn();
            sf::sleep(sf::seconds(3.0));
            computerMadeTurn = true;
            curBet = game.getBet();
            if (isIncrease)
                gameProgress = false;
        }

        sf::Event event{};
        while (this->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved) {
                if (inArea(event.mouseMove, 0, 0, 130, 50))
                    newGameButton.setFillColor(sf::Color::Blue);
                else
                    newGameButton.setFillColor(sf::Color::White);
                if (inArea(event.mouseMove, 750, 0, 800, 50))
                    info = true;
                else
                    info = false;
                if (inArea(event.mouseMove, 490, 210, 558, 278))
                    betIncButton.setFillColor(sf::Color::Blue);
                else
                    betIncButton.setFillColor(sf::Color::White);
                if (inArea(event.mouseMove, 258, 210, 326, 278))
                    betDecButton.setFillColor(sf::Color::Blue);
                else
                    betDecButton.setFillColor(sf::Color::White);
                if (acceptButtonActive) {
                    if (inArea(event.mouseMove, 210, 316, 330, 365))
                        acceptButton.setFillColor(sf::Color::Blue);
                    else
                        acceptButton.setFillColor(sf::Color::White);
                } else {
                    acceptButton.setFillColor({100, 100, 100});
                }
                if (checkButtonActive) {
                    if (inArea(event.mouseMove, 440, 316, 586, 365))
                        checkButton.setFillColor(sf::Color::Blue);
                    else
                        checkButton.setFillColor(sf::Color::White);
                } else {
                    checkButton.setFillColor({100, 100, 100});
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (inArea(event.mouseButton, 0, 0, 130, 50))
                    newGame();
                if (game.whoseTurn() == Game::PLAYER && gameProgress) {
                    if (inArea(event.mouseButton, 490, 210, 558, 278) && curBet < 64)
                        curBet++;
                    if (inArea(event.mouseButton, 258, 210, 326, 278) && curBet > 5 && curBet > game.getBet())
                        curBet--;
                    if (inArea(event.mouseButton, 210, 316, 330, 365) && acceptButtonActive)
                        game.changeBet(curBet);
                    if (inArea(event.mouseButton, 440, 316, 586, 365) && checkButtonActive)
                        gameProgress = game.acceptBet();
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(background);
        window.draw(newGameButton);
        window.draw(infoButton);

        if (gameStarted) {
            for (auto &card : playerCards)
                window.draw(card);
            for (auto &card : computerCardsBack)
                window.draw(card);

            sf::String info = L"Стоимость вашей комбинации: ";
            info += std::to_string(game.countCombination(Game::PLAYER));
            playerCombinationInfo.setString(info);
            window.draw(playerCombinationInfo);

            sf::Vector2f arrowPosition(630, game.whoseTurn() == Game::PLAYER ? 475 : 95);
            turnInfo.setPosition(arrowPosition);
            window.draw(turnInfo);

            betInfo.setString((curBet < 10 ? "0" : "") + std::to_string(curBet));
            window.draw(betInfo);
            window.draw(betIncButton);
            window.draw(betDecButton);

            window.draw(acceptButton);
            window.draw(checkButton);

            if (!gameProgress) {
                for (auto &card : computerCards)
                    window.draw(card);

                sf::RectangleShape rect;
                rect.setPosition(0, 200);
                rect.setSize(sf::Vector2f(800, 200));
                rect.setFillColor({100, 100, 200, 200});
                window.draw(rect);

                bool isWin = game.winner() == Game::PLAYER;
                sf::String endString(isWin ? L"Победа" : L"Проигрыш");
                sf::Text endText(endString, font, 128);
                endText.setFillColor(isWin ? sf::Color::Green : sf::Color::Red);
                endText.setPosition(isWin ? sf::Vector2f(230, 200) : sf::Vector2f(130, 200));
                window.draw(endText);
            }
        }

        if (info) {
            sf::RectangleShape rect;
            rect.setPosition(0, 0);
            rect.setSize(sf::Vector2f(800, 600));
            rect.setFillColor({50, 50, 50, 220});
            window.draw(rect);

            sf::String string = L"В игре Арлекин каждый игрок получает по 5 карт.\n"
                                "В свой ход каждый игрок объявляет комбинацию своему\n"
                                "соседу, который либо принимает её, либо проверяет.\n"
                                "Если комбинация принята, то сосед должен ответить\n"
                                "большей комбинацией. Если сосед проверяет, и\n"
                                "комбинация оказалась блефом, то игрок проигрывает,\n"
                                "но если игрок не блефовал, тогда проверяющий его\n"
                                "игрок проигрывает";
            sf::Text text(string, font, 30);
            text.setFillColor(sf::Color::White);
            text.setPosition(sf::Vector2f(70, 165));
            window.draw(text);
        }

        window.display();
    }
}

void Window::newGame() {
    game.reset();
    gameStarted = true;
    gameProgress = true;
    curBet = game.getBet();

    sf::Vector2f cardSize(80.0, 120.0);
    for (int i = 0; i < playerCards.size(); i++) {
        playerCards[i].setSize(cardSize);
        playerCards[i].setPosition(187.5 + 85.0 * i, 430);
        int cardId = game.playerCards()[i].first * 13 + game.playerCards()[i].second - 1;
        playerCards[i].setTexture(&cardTextures[cardId]);
    }
    for (int i = 0; i < computerCards.size(); i++) {
        computerCards[i].setSize(cardSize);
        computerCards[i].setPosition(187.5 + 85.0 * i, 50);
        int cardId = game.computerCards()[i].first * 13 + game.computerCards()[i].second - 1;
        computerCards[i].setTexture(&cardTextures[cardId]);
    }
    for (int i = 0; i < computerCardsBack.size(); i++) {
        computerCardsBack[i].setSize(cardSize);
        computerCardsBack[i].setPosition(187.5 + 85.0 * i, 50);
        computerCardsBack[i].setTexture(&cardTextures[card::amount]);
    }
}

void Window::logError(std::string info) {
    std::cerr << info << std::endl;
    window.close();
}

bool Window::inArea(sf::Event::MouseButtonEvent mouse, int left, int top, int right, int down) {
    int x = mouse.x;
    int y = mouse.y;
    return x < right && x > left && y < down && y > top;
}

bool Window::inArea(sf::Event::MouseMoveEvent mouse, int left, int top, int right, int down) {
    int x = mouse.x;
    int y = mouse.y;
    return x < right && x > left && y < down && y > top;
}
