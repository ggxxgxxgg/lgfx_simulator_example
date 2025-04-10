#include <LGFX_AUTODETECT.hpp>
#include <random>

static LGFX _lcd(240, 240);

static LGFX_Sprite *_canvas;
#define _canvas_update() _canvas->pushSprite(0, 0)

std::random_device rd;
std::mt19937 gen(rd());
int Game_random(int low, int high) {
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

void setup() {
    _lcd.init();
    _canvas = new LGFX_Sprite(&_lcd);
    _canvas->createSprite(_lcd.width(), _lcd.height());
}

void loop() {
    _canvas->fillSmoothCircle(
        Game_random(0, _canvas->width()), Game_random(0, _canvas->height()),
        Game_random(1, 24), Game_random(TFT_BLACK, TFT_WHITE));
    _canvas_update();
    lgfx::delay(1);
}