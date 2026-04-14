// 10_sound_demo.cpp - Sound Demo
//
// Demo GameLib sound features: beep, WAV sound effects, MCI background music.
// Note: PlayBeep is blocking, will pause briefly when pressed.
// PlayWAV/PlayMusic return bool so you can detect missing files.
// Learn: PlayBeep, PlayWAV, StopWAV, PlayMusic, StopMusic, IsMusicPlaying
//
// Compile: g++ -o 10_sound_demo.exe 10_sound_demo.cpp -mwindows

#include "../GameLib.h"

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
    game.Open(640, 480, "10 - Sound Demo", true);

    bool lastWavOk = true;
    bool lastMusicOk = true;
    const char *wavEffect = ChooseExistingPath("../assets/sound/explosion.wav", "assets/sound/explosion.wav");
    const char *musicLoop = ChooseExistingPath("../assets/music/battle1.mid", "assets/music/battle1.mid");

    // Key note frequencies (C4 to B4)
    int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};
    const char *noteNames[] = {"C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5"};

    // Currently active button (for visual feedback)
    int activeNote = -1;

    while (!game.IsClosed()) {
        if (game.IsKeyPressed(KEY_ESCAPE)) break;

        game.Clear(COLOR_DARK_BLUE);

        // --- Title ---
        game.DrawTextScale(180, 20, "Sound Demo", COLOR_GOLD, 2);

        // === Section 1: Beep Piano ===
        game.DrawText(40, 70, "Piano (Beep) - Press 1~8:", COLOR_WHITE);
        game.DrawText(40, 85, "Warning: Beep is blocking!", COLOR_ORANGE);

        activeNote = -1;
        for (int i = 0; i < 8; i++) {
            int bx = 40 + i * 70;
            int by = 105;
            bool pressed = game.IsKeyPressed(KEY_1 + i);

            if (pressed) activeNote = i;

            // Piano key
            uint32_t keyColor = (activeNote == i) ? COLOR_YELLOW : COLOR_WHITE;
            game.FillRect(bx, by, 55, 100, keyColor);
            game.DrawRect(bx, by, 55, 100, COLOR_BLACK);
            game.DrawText(bx + 20, by + 75, noteNames[i], COLOR_BLACK);

            if (pressed)
                game.PlayBeep(notes[i], 150);
        }

        // === Section 2: WAV Sound Effect ===
        game.DrawText(40, 230, "WAV Sound Effect:", COLOR_WHITE);

        game.FillRect(40, 250, 200, 30, COLOR_GREEN);
        game.DrawText(55, 258, "W - Play WAV", COLOR_BLACK);
        if (game.IsKeyPressed(KEY_W)) {
            lastWavOk = game.PlayWAV(wavEffect);
        }

        game.FillRect(260, 250, 200, 30, COLOR_RED);
        game.DrawText(290, 258, "S - Stop WAV", COLOR_BLACK);
        if (game.IsKeyPressed(KEY_S))
            game.StopWAV();

        game.DrawText(40, 290, "(uses assets/sound/explosion.wav from the repo)", COLOR_GRAY);
        game.DrawPrintf(40, 305, COLOR_LIGHT_GRAY, "Last WAV start: %s", lastWavOk ? "OK" : "Failed");

        // === Section 3: Background Music ===
        game.DrawText(40, 330, "Background Music (MCI MIDI):", COLOR_WHITE);

        bool musicPlaying = game.IsMusicPlaying();

        game.FillRect(40, 350, 200, 30, musicPlaying ? COLOR_DARK_GREEN : COLOR_GREEN);
        game.DrawText(55, 358, "M - Play Music", COLOR_BLACK);
        if (game.IsKeyPressed(KEY_M) && !musicPlaying) {
            lastMusicOk = game.PlayMusic(musicLoop);
            musicPlaying = game.IsMusicPlaying();
        }

        game.FillRect(260, 350, 200, 30, COLOR_RED);
        game.DrawText(275, 358, "N - Stop Music", COLOR_BLACK);
        if (game.IsKeyPressed(KEY_N) && musicPlaying) {
            game.StopMusic();
        }

        game.DrawText(40, 390, "(uses assets/music/battle1.mid and routes .mid to MCI sequencer)", COLOR_GRAY);

        // Status
        game.DrawPrintf(40, 420, COLOR_LIGHT_GRAY, "Music: %s", game.IsMusicPlaying() ? "Playing" : "Stopped");
        game.DrawPrintf(40, 436, COLOR_LIGHT_GRAY, "Last music start: %s", lastMusicOk ? "OK" : "Failed");

        // Bottom hint
        game.DrawText(40, 460, "ESC to exit", COLOR_DARK_GRAY);

        game.Update();
        game.WaitFrame(60);
    }
    return 0;
}
