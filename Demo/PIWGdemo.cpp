#include "BearLibTerminal.h"
#include "World.h"

int main(int argc, char* argv[]){
    terminal_open();
    terminal_set("window.title = Infinite Procedural World Generator");
    terminal_set("window.fullscreen = true");
    terminal_set("window.size = 240x135");
    terminal_set("window.cellsize = 8x8");
    terminal_set("font: Demo/BLT/Font.ttf, size = 11x13");
    terminal_set("input.filter = {keyboard+, mouse+}");
    terminal_refresh();

    World world;
    
    bool running{true};
    while (running){
        world.playerLocation() = Location(terminal_state(TK_MOUSE_Y), terminal_state(TK_MOUSE_X));
        world.update(world.playerLocation());

        terminal_clear();
    
        for (auto & regionLocation : world.renderedRegions()){
            for (auto & tile : world.regionAt(regionLocation)->tiles()){
                Location worldLocation = world.localToWorld(RelativeLocation(regionLocation, tile.first));

                if (world.numAdjacentWalls(worldLocation) == 4 && world.tileAt(worldLocation)->type() == TILE_WALL){
                    terminal_put(worldLocation.column(), worldLocation.row(), '.');
                } else {
                    terminal_put(worldLocation.column(), worldLocation.row(), world.tileAt(worldLocation)->icon());
                }
            }
        }

        terminal_refresh();

        while (terminal_has_input()){
            int input = terminal_read();

            switch (input){
                case TK_UP:
                    world.renderDistance()++;
                    break;
                case TK_LEFT:
                    world.regionSize()--;
                    world.unloadRegions(world.renderedRegions());
                    break;
                case TK_DOWN:
                    world.renderDistance()--;
                    break;
                case TK_RIGHT:
                    world.regionSize()++;
                    world.unloadRegions(world.renderedRegions());
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