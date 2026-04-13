#include "../GameLib.SDL.h"
#include <stdio.h>

static const char *ChooseExistingPath(const char *pathA, const char *pathB)
{
    FILE *file = fopen(pathA, "rb");
    if (file != NULL) {
        fclose(file);
        return pathA;
    }
    file = fopen(pathB, "rb");
    if (file != NULL) {
        fclose(file);
        return pathB;
    }
    return pathA;
}

int main()
{
    GameLib game;
    if (game.Open(640, 480, "SDL Demo 13 - PlaySound", true) != 0) {
        return 1;
    }
    game.ShowFps(true);

    const char *explosion = ChooseExistingPath("../assets/sound/explosion.wav", "assets/sound/explosion.wav");
    const char *noteDo = ChooseExistingPath("../assets/sound/note_do.wav", "assets/sound/note_do.wav");
    const char *noteRe = ChooseExistingPath("../assets/sound/note_re.wav", "assets/sound/note_re.wav");
    const char *victory = ChooseExistingPath("../assets/sound/victory.wav", "assets/sound/victory.wav");

    const char *lastEffect = "none";
    bool lastOk = true;

    while (!game.IsClosed()) {
        if (game.IsKeyPressed(KEY_ESCAPE)) break;

        game.Clear(COLOR_BLACK);

#if GAMELIB_SDL_HAS_MIXER
        game.DrawText(10, 54, "SDL_mixer support: ON", COLOR_GREEN);
#else
        game.DrawText(10, 54, "SDL_mixer support: OFF", COLOR_RED);
#endif

        if (game.IsKeyPressed(KEY_SPACE)) {
            lastEffect = "explosion.wav";
            lastOk = game.PlayWAV(explosion);
        }
        if (game.IsKeyPressed(KEY_1)) {
            lastEffect = "note_do.wav";
            lastOk = game.PlayWAV(noteDo);
        }
        if (game.IsKeyPressed(KEY_2)) {
            lastEffect = "note_re.wav";
            lastOk = game.PlayWAV(noteRe);
        }
        if (game.IsKeyPressed(KEY_V)) {
            lastEffect = "victory.wav";
            lastOk = game.PlayWAV(victory);
        }

        game.DrawTextScale(10, 10, "PlaySound Demo", COLOR_GOLD, 2);
        game.DrawText(10, 90, "SPACE: Explosion", COLOR_WHITE);
        game.DrawText(10, 102, "1/2: Note Do/Re", COLOR_WHITE);
        game.DrawText(10, 114, "V: Victory", COLOR_WHITE);
        game.DrawText(10, 140, "Uses repo-local WAV files with ../assets and assets fallback paths.", COLOR_GRAY);
        game.DrawPrintf(10, 160, COLOR_LIGHT_GRAY, "Last WAV request: %s (%s)", lastEffect, lastOk ? "OK" : "Failed");
        game.DrawText(10, 460, "ESC to exit", COLOR_DARK_GRAY);

        game.Update();
        game.WaitFrame(60);
    }
    return 0;
}