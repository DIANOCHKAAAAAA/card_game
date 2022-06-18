add_executable(card_game_test ${PROJECT_SOURCE_DIR}/src/source/game.cpp test.cpp)
target_link_libraries(card_game_test PUBLIC doctest default)
add_test(NAME card_game_test COMMAND card_game_test --force-colors -d)