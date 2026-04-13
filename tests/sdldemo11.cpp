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
    if (game.Open(760, 560, "SDL Demo 11 - Sound Demo", true) != 0) {
        return 1;
    }
    game.ShowFps(true);

    const char *wavExplosion = ChooseExistingPath("../assets/sound/explosion.wav", "assets/sound/explosion.wav");
    const char *wavCoin = ChooseExistingPath("../assets/sound/coin.wav", "assets/sound/coin.wav");
    const char *wavJump = ChooseExistingPath("../assets/sound/jump.wav", "assets/sound/jump.wav");
    const char *musicLoop = ChooseExistingPath("../assets/sound/victory.wav", "assets/sound/victory.wav");

    bool lastWavOk = true;
    bool lastMusicOk = true;
    const char *lastEffect = "none";

    int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};
    const char *noteNames[] = {"C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5"};
    int activeNote = -1;

    while (!game.IsClosed()) {
        if (game.IsKeyPressed(KEY_ESCAPE)) break;

        game.Clear(COLOR_DARK_BLUE);
        game.DrawTextScale(180, 20, "Sound Demo", COLOR_GOLD, 2);

#if GAMELIB_SDL_HAS_MIXER
        game.DrawText(40, 54, "SDL_mixer support: ON", COLOR_GREEN);
#else
        game.DrawText(40, 54, "SDL_mixer support: OFF", COLOR_RED);
#endif

        game.DrawText(40, 70, "Piano (Beep) - Press 1~8:", COLOR_WHITE);
        game.DrawText(40, 85, "PlayBeep is blocking by design, same as the Win32 teaching line.", COLOR_ORANGE);

        activeNote = -1;
        for (int i = 0; i < 8; i++) {
            int bx = 40 + i * 70;
            int by = 105;
            bool pressed = game.IsKeyPressed(KEY_1 + i);

            if (pressed) activeNote = i;

            uint32_t keyColor = (activeNote == i) ? COLOR_YELLOW : COLOR_WHITE;
            game.FillRect(bx, by, 55, 100, keyColor);
            game.DrawRect(bx, by, 55, 100, COLOR_BLACK);
            game.DrawText(bx + 20, by + 75, noteNames[i], COLOR_BLACK);

            if (pressed)
                game.PlayBeep(notes[i], 150);
        }

        game.DrawText(40, 230, "WAV Sound Effect:", COLOR_WHITE);

        game.FillRect(40, 250, 200, 30, COLOR_GREEN);
        game.DrawText(55, 258, "W - Play Explosion", COLOR_BLACK);
        if (game.IsKeyPressed(KEY_W)) {
            lastEffect = "explosion.wav";
            lastWavOk = game.PlayWAV(wavExplosion);
        }

        game.FillRect(260, 250, 200, 30, COLOR_GOLD);
        game.DrawText(295, 258, "C - Play Coin", COLOR_BLACK);
        if (game.IsKeyPressed(KEY_C)) {
            lastEffect = "coin.wav";
            lastWavOk = game.PlayWAV(wavCoin);
        }

        game.FillRect(480, 250, 200, 30, COLOR_CYAN);
        game.DrawText(515, 258, "J - Play Jump", COLOR_BLACK);
        if (game.IsKeyPressed(KEY_J)) {
            lastEffect = "jump.wav";
            lastWavOk = game.PlayWAV(wavJump);
        }

        game.FillRect(40, 290, 200, 30, COLOR_RED);
        game.DrawText(80, 298, "S - Stop WAV", COLOR_BLACK);
        if (game.IsKeyPressed(KEY_S))
            game.StopWAV();

        game.DrawPrintf(40, 330, COLOR_LIGHT_GRAY, "Last WAV request: %s (%s)", lastEffect, lastWavOk ? "OK" : "Failed");
        game.DrawText(40, 345, "Assets: explosion.wav / coin.wav / jump.wav (auto-fallback between ../assets and assets)", COLOR_GRAY);

        game.DrawText(40, 380, "Background Music:", COLOR_WHITE);

        bool musicPlaying = game.IsMusicPlaying();

        game.FillRect(40, 400, 200, 30, musicPlaying ? COLOR_DARK_GREEN : COLOR_GREEN);
        game.DrawText(55, 408, "M - Play Music", COLOR_BLACK);
        if (game.IsKeyPressed(KEY_M) && !musicPlaying) {
            lastMusicOk = game.PlayMusic(musicLoop);
            musicPlaying = game.IsMusicPlaying();
        }

        game.FillRect(260, 400, 200, 30, COLOR_RED);
        game.DrawText(275, 408, "N - Stop Music", COLOR_BLACK);
        if (game.IsKeyPressed(KEY_N) && musicPlaying)
            game.StopMusic();

        game.DrawText(40, 440, "This repo currently uses victory.wav as the looped music source for SDL testing.", COLOR_GRAY);
        game.DrawPrintf(40, 470, COLOR_LIGHT_GRAY, "Music: %s", game.IsMusicPlaying() ? "Playing" : "Stopped");
        game.DrawPrintf(40, 486, COLOR_LIGHT_GRAY, "Last music start: %s", lastMusicOk ? "OK" : "Failed");
        game.DrawText(40, 520, "ESC to exit", COLOR_DARK_GRAY);

        game.Update();
        game.WaitFrame(60);
    }

    return 0;
}