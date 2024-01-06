#include "BearLibTerminal.h"
#include "World.h"

int main(int argc, char* argv[]){
    // Sets up BearLibTerminal.
    terminal_open();
    terminal_set("window.title = Infinite Procedural World Generator");
    terminal_set("window.fullscreen = true");
    terminal_set("window.size = 240x135");
    terminal_set("window.cellsize = 8x8");
    terminal_set("font: Demo/BLT/Font.ttf, size = 11x13");
    terminal_set("input.filter = {keyboard+, mouse+}");
    terminal_refresh();

    World world;
    Location offset;
    
    // Loops until the user exits the program.
    bool running{true};
    while (running){
        world.playerLocation() = Location(terminal_state(TK_MOUSE_Y), terminal_state(TK_MOUSE_X)) - offset;
        world.update(world.playerLocation());

        terminal_clear();

        // Prototype method for displaying the world.
        for (auto & regionLocation : world.regionsToLoad()){
            if (world.regionExistsAt(regionLocation)){
                for (auto & tile : world.regionAt(regionLocation)->tiles()){
                    Location worldLocation = world.localToWorld(RelativeLocation(regionLocation, tile.first));

                    if (world.numAdjacentWalls(worldLocation) == 4 && world.tileAt(worldLocation)->type() == TILE_WALL){
                        terminal_put(worldLocation.column() + offset.column(), worldLocation.row() + offset.row(), '.');
                    } else {
                        terminal_put(worldLocation.column() + offset.column(), worldLocation.row() + offset.row(), world.tileAt(worldLocation)->icon());
                    }
                }
            }
        }

        terminal_refresh();

        // Read user input;
        while (terminal_has_input()){
            int input = terminal_read();

            switch (input){
                case TK_W:
                    offset.row() -= 1;
                    break;
                case TK_A:
                    offset.column() -= 1;
                    break;
                case TK_S:
                    offset.row() += 1;
                    break;
                case TK_D:
                    offset.column() += 1;
                    break;
                case TK_UP:
                    world.loadDistance()++;
                    break;
                case TK_DOWN:
                    world.loadDistance()--;
                    break;
                case TK_ESCAPE:
                    running = false;
                    break;
                default:
                    break;
            }
        }
    }

    terminal_close();
    return 0;
}