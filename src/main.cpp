#include "log.h"
#include "graphics/window.h"
#include "graphics/shader.h"

static Window window;

static void _init()
{
    logger::init();
    logger::info("------------------------GAIA LOG BEGIN------------------------");
    window.create();
}

static void _run()
{
    window.loop();
    window.destroy();
}

int main()
{
    _init();
    _run();
    return 0;
}
