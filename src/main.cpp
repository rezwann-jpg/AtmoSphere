#include "App.h"

int main() {
    App app("AtmoSphere", 1280, 720);

    while (app.Running()) {
        app.HandleEvents();
        app.Update();
        app.Draw();
    }

    return 0;
}