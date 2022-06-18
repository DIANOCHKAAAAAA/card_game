add_executable(card_game main.cpp headers/window.h source/window.cpp headers/game.h source/game.cpp headers/card.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
target_link_libraries(card_game sfml-graphics)

if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()