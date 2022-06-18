#include "window/window.hpp"
#include "engine/engine.hpp"
#include "engine/game.hpp"
#include "game/scenes/soccer.hpp"

int main(int argc, char const *argv[])
{
    Window window;
    Engine engine(&window);
    Game game(std::move(SoccerLevel()));
    engine.process(game);
    return 0;
}
