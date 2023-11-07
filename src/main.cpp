#include "../include/configurator.h"
#include "../include/gui.h"
#include "../include/scheduler.h"
#include "../include/tui.h"

int main(int argc, char** argv) {

#if defined(DEBUG_BUILD)
    auto config = new configurator("config.json");
#else
    std::string home = getenv("HOME");
    auto config = new configurator(home + "/.config/hyprland-wallpaper-manager/config.json");
#endif
    auto im = new wallpaperManager(config);

    auto sched = new scheduler(config, im);

#ifdef COMPILE_GUI
    auto g = new gui(config, im, sched);
    g->run(argc, argv);

#else
    auto tuiMenu = tui(im, *sched, config);
    tuiMenu.renderMenu();
#endif

    return 0;
}