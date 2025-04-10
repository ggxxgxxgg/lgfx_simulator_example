#include "PerformanceWindow.hpp"
#include <LGFX_AUTODETECT.hpp>
#include <random>

static PerformanceWindow *_pw;

void setup() {
    _pw = new PerformanceWindow();
}

void loop() {
    _pw->update();
}
