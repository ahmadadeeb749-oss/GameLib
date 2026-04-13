// 17_sprite_scaling.cpp - Sprite Scaling Demo
//
// Load sprite assets and render them at different sizes.
//
// Controls:
//   Mouse wheel / Q E : change scale
//   A D / Left Right  : change explosion frame
//   F                 : toggle horizontal flip
//   R                 : reset scale, frame and flip
//   ESC               : quit
//
// Learn: LoadSprite, DrawSpriteScaled, DrawSpriteFrameScaled,
//        GetSpriteWidth/GetSpriteHeight, SPRITE_COLORKEY,
//        mouse wheel input
//
// Compile: g++ -o 17_sprite_scaling.exe 17_sprite_scaling.cpp -mwindows

#include "../GameLib.h"

static int ClampInt(int value, int minValue, int maxValue)
{
    if (value < minValue) return minValue;
    if (value > maxValue) return maxValue;
    return value;
}

static void DrawPanel(GameLib &game, int x, int y, int w, int h, const char *title)
{
    game.FillRect(x, y, w, h, COLOR_RGB(28, 34, 50));
    game.DrawRect(x, y, w, h, COLOR_RGB(84, 94, 120));
    game.FillRect(x + 1, y + 1, w - 2, 22, COLOR_RGB(38, 48, 72));
    game.DrawText(x + 8, y + 7, title, COLOR_WHITE);
}

static void DrawCheckerboard(GameLib &game, int x, int y, int w, int h, int cell)
{
    uint32_t c0 = COLOR_RGB(48, 54, 70);
    uint32_t c1 = COLOR_RGB(62, 70, 90);

    for (int py = y; py < y + h; py += cell) {
        for (int px = x; px < x + w; px += cell) {
            int cw = cell;
            int ch = cell;
            if (px + cw > x + w) cw = x + w - px;
            if (py + ch > y + h) ch = y + h - py;
            game.FillRect(px, py, cw, ch,
                          (((px - x) / cell + (py - y) / cell) & 1) ? c0 : c1);
        }
    }
}

static void DrawSpriteBox(GameLib &game, int spriteId,
                          int x, int y, int boxW, int boxH,
                          int drawW, int drawH, int flags)
{
    DrawCheckerboard(game, x, y, boxW, boxH, 10);
    game.DrawRect(x, y, boxW, boxH, COLOR_RGB(98, 110, 138));
    game.DrawSpriteScaled(spriteId,
                          x + (boxW - drawW) / 2,
                          y + (boxH - drawH) / 2,
                          drawW, drawH, flags);
}

static void DrawFrameBox(GameLib &game, int spriteId, int frameIndex,
                         int x, int y, int boxW, int boxH,
                         int frameW, int frameH,
                         int drawW, int drawH, int flags)
{
    DrawCheckerboard(game, x, y, boxW, boxH, 10);
    game.DrawRect(x, y, boxW, boxH, COLOR_RGB(98, 110, 138));
    game.DrawSpriteFrameScaled(spriteId,
                               x + (boxW - drawW) / 2,
                               y + (boxH - drawH) / 2,
                               frameW, frameH, frameIndex,
                               drawW, drawH, flags);
}

int main()
{
    GameLib game;
    const int SW = 920;
    const int SH = 600;
    game.Open(SW, SH, "17 - Sprite Scaling", true);

    int plane = game.LoadSprite("../assets/plane1.png");
    int explosion = game.LoadSprite("../assets/explosion.png");
    if (plane >= 0) game.SetSpriteColorKey(plane, COLORKEY_DEFAULT);
    if (explosion >= 0) game.SetSpriteColorKey(explosion, COLORKEY_DEFAULT);

    int scale = 4;
    int frame = 0;
    bool flip = false;

    while (!game.IsClosed()) {
        if (game.IsKeyPressed(KEY_ESCAPE)) break;

        int wheel = game.GetMouseWheelDelta();
        if (wheel != 0) scale += wheel;
        if (game.IsKeyPressed(KEY_Q)) scale--;
        if (game.IsKeyPressed(KEY_E)) scale++;
        scale = ClampInt(scale, 1, 5);

        if (game.IsKeyPressed(KEY_A) || game.IsKeyPressed(KEY_LEFT))
            frame = (frame + 3) % 4;
        if (game.IsKeyPressed(KEY_D) || game.IsKeyPressed(KEY_RIGHT))
            frame = (frame + 1) % 4;

        if (game.IsKeyPressed(KEY_F)) flip = !flip;
        if (game.IsKeyPressed(KEY_R)) {
            scale = 4;
            frame = 0;
            flip = false;
        }

        game.Clear(COLOR_RGB(18, 22, 36));
        game.FillRect(0, 0, SW, 56, COLOR_RGB(10, 14, 24));
        game.DrawText(20, 16, "Wheel/Q/E scale   A/D change frame   F flip   R reset   ESC quit", COLOR_WHITE);

        if (plane < 0 || explosion < 0) {
            game.DrawText(20, 90, "Failed to load sprite assets from ../assets/", COLOR_RED);
            if (plane < 0)
                game.DrawText(20, 110, "Missing: plane1.png", COLOR_LIGHT_GRAY);
            if (explosion < 0)
                game.DrawText(20, 126, "Missing: explosion.png", COLOR_LIGHT_GRAY);
            game.Update();
            game.WaitFrame(60);
            continue;
        }

        int planeW = game.GetSpriteWidth(plane);
        int planeH = game.GetSpriteHeight(plane);
        int frameW = 32;
        int frameH = 32;
        int flags = SPRITE_COLORKEY | (flip ? SPRITE_FLIP_H : 0);
        const char *flipText = flip ? "On" : "Off";

        game.DrawPrintf(20, 34, COLOR_LIGHT_GRAY,
                        "Scale: %dx   Frame: %d   Flip: %s", scale, frame, flipText);

        DrawPanel(game, 20, 72, 200, 508, "Source Sprites");
        game.DrawText(36, 104, "plane1.png", COLOR_LIGHT_GRAY);
        DrawCheckerboard(game, 36, 124, 168, 96, 8);
        game.DrawRect(36, 124, 168, 96, COLOR_RGB(98, 110, 138));
        game.DrawSpriteEx(plane,
                  36 + (168 - planeW) / 2,
                  124 + (96 - planeH) / 2,
                          SPRITE_COLORKEY);
        game.DrawPrintf(36, 228, COLOR_GRAY, "Original size: %dx%d", planeW, planeH);

        game.DrawText(36, 268, "explosion.png sheet", COLOR_LIGHT_GRAY);
        DrawCheckerboard(game, 36, 288, 168, 88, 8);
        game.DrawRect(36, 288, 168, 88, COLOR_RGB(98, 110, 138));
        game.DrawSpriteScaled(explosion, 40, 312, 160, 40, SPRITE_COLORKEY);
        game.DrawRect(40 + frame * 40, 312, 40, 40, COLOR_GOLD);
        game.DrawText(36, 386, "Frame 0..3, each 32x32", COLOR_GRAY);

        game.DrawText(36, 434, "Uses:", COLOR_WHITE);
        game.DrawText(36, 454, "Same art at many sizes", COLOR_LIGHT_GRAY);
        game.DrawText(36, 470, "Zoom a frame from a sheet", COLOR_LIGHT_GRAY);
        game.DrawText(36, 486, "Keep pixels sharp", COLOR_LIGHT_GRAY);

        DrawPanel(game, 240, 72, 660, 250, "DrawSpriteScaled");
                game.DrawText(256, 104, "Scaled plane", COLOR_LIGHT_GRAY);
                DrawSpriteBox(game, plane, 256, 124, 340, 180,
                                            planeW * scale, planeH * scale, flags);
        game.DrawPrintf(256, 286, COLOR_WHITE,
                                                "%dx%d -> %dx%d", planeW, planeH, planeW * scale, planeH * scale);

        game.DrawText(620, 104, "Wide stretch", COLOR_LIGHT_GRAY);
                DrawSpriteBox(game, plane, 620, 124, 110, 84, 96, 64, flags);
        game.DrawText(620, 216, "96x64", COLOR_GRAY);

        game.DrawText(750, 104, "Tall stretch", COLOR_LIGHT_GRAY);
                DrawSpriteBox(game, plane, 750, 124, 110, 140, 72, 128, flags);
        game.DrawText(750, 272, "72x128", COLOR_GRAY);
        game.DrawText(620, 294, "Flip applies to scaled draw too", COLOR_LIGHT_GRAY);

        DrawPanel(game, 240, 334, 660, 246, "DrawSpriteFrameScaled");
        game.DrawText(256, 366, "Sheet preview", COLOR_LIGHT_GRAY);
        DrawCheckerboard(game, 256, 386, 184, 96, 8);
        game.DrawRect(256, 386, 184, 96, COLOR_RGB(98, 110, 138));
        game.DrawSpriteScaled(explosion, 268, 414, 160, 40, SPRITE_COLORKEY);
        game.DrawRect(268 + frame * 40, 414, 40, 40, COLOR_GOLD);
        game.DrawText(256, 494, "A/D changes the highlight", COLOR_GRAY);

        game.DrawText(470, 366, "Current frame", COLOR_LIGHT_GRAY);
        DrawFrameBox(game, explosion, frame,
                     470, 386, 400, 176,
                     frameW, frameH,
                     frameW * scale, frameH * scale,
                     flags);
        game.DrawPrintf(470, 542, COLOR_WHITE,
                        "32x32 -> %dx%d", frameW * scale, frameH * scale);

        game.Update();
        game.WaitFrame(60);
    }

    if (plane >= 0) game.FreeSprite(plane);
    if (explosion >= 0) game.FreeSprite(explosion);
    return 0;
}