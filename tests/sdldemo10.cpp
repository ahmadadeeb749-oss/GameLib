#include "../GameLib.SDL.h"

static int CreateCharSheet(GameLib &game)
{
    int fw = 12;
    int fh = 16;
    int cols = 3;
    int rows = 4;
    int id = game.CreateSprite(fw * cols, fh * rows);
    if (id < 0) return -1;

    for (int y = 0; y < fh * rows; y++)
        for (int x = 0; x < fw * cols; x++)
            game.SetSpritePixel(id, x, y, 0x00000000);

    uint32_t skin = COLOR_RGB(255, 200, 150);
    uint32_t hair = COLOR_BROWN;
    uint32_t shirt = COLOR_BLUE;
    uint32_t pants = COLOR_DARK_BLUE;
    uint32_t shoe = COLOR_DARK_GRAY;

    for (int dir = 0; dir < 4; dir++) {
        for (int f = 0; f < 3; f++) {
            int ox = f * fw;
            int oy = dir * fh;

            for (int dy = 0; dy < 4; dy++)
                for (int dx = 0; dx < 4; dx++)
                    game.SetSpritePixel(id, ox + 4 + dx, oy + dy, skin);

            for (int dx = 0; dx < 4; dx++)
                game.SetSpritePixel(id, ox + 4 + dx, oy, hair);

            for (int dy = 4; dy < 9; dy++)
                for (int dx = 0; dx < 6; dx++)
                    game.SetSpritePixel(id, ox + 3 + dx, oy + dy, shirt);

            for (int dy = 9; dy < 12; dy++)
                for (int dx = 0; dx < 6; dx++)
                    game.SetSpritePixel(id, ox + 3 + dx, oy + dy, pants);

            int leftFootX;
            int rightFootX;
            if (f == 0) {
                leftFootX = 3;
                rightFootX = 7;
            } else if (f == 1) {
                leftFootX = 2;
                rightFootX = 8;
            } else {
                leftFootX = 4;
                rightFootX = 6;
            }

            for (int dy = 12; dy < 14; dy++) {
                game.SetSpritePixel(id, ox + leftFootX, oy + dy, shoe);
                game.SetSpritePixel(id, ox + leftFootX + 1, oy + dy, shoe);
                game.SetSpritePixel(id, ox + rightFootX, oy + dy, shoe);
                game.SetSpritePixel(id, ox + rightFootX + 1, oy + dy, shoe);
            }

            if (dir == 0) {
                game.SetSpritePixel(id, ox + 5, oy + 2, COLOR_BLACK);
                game.SetSpritePixel(id, ox + 7, oy + 2, COLOR_BLACK);
            } else if (dir == 1) {
                game.SetSpritePixel(id, ox + 4, oy + 2, COLOR_BLACK);
            } else if (dir == 2) {
                game.SetSpritePixel(id, ox + 7, oy + 2, COLOR_BLACK);
            } else {
                for (int dx = 0; dx < 4; dx++)
                    game.SetSpritePixel(id, ox + 4 + dx, oy + 1, hair);
            }
        }
    }

    return id;
}

int main()
{
    GameLib game;
    if (game.Open(640, 480, "SDL Demo 10 - Sprite Animation", true) != 0) {
        return 1;
    }
    game.ShowFps(true);

    int charSheet = CreateCharSheet(game);
    if (charSheet < 0) {
        return 1;
    }

    int fw = 12;
    int fh = 16;
    int scale = 3;

    double px = 300.0;
    double py = 220.0;
    double speed = 100.0;
    int dir = 0;
    int frame = 0;
    double animTimer = 0.0;
    bool moving = false;

    while (!game.IsClosed()) {
        if (game.IsKeyPressed(KEY_ESCAPE)) break;

        double dt = game.GetDeltaTime();
        moving = false;

        if (game.IsKeyDown(KEY_DOWN) || game.IsKeyDown(KEY_S)) {
            py += speed * dt;
            dir = 0;
            moving = true;
        }
        if (game.IsKeyDown(KEY_LEFT) || game.IsKeyDown(KEY_A)) {
            px -= speed * dt;
            dir = 1;
            moving = true;
        }
        if (game.IsKeyDown(KEY_RIGHT) || game.IsKeyDown(KEY_D)) {
            px += speed * dt;
            dir = 2;
            moving = true;
        }
        if (game.IsKeyDown(KEY_UP) || game.IsKeyDown(KEY_W)) {
            py -= speed * dt;
            dir = 3;
            moving = true;
        }

        if (px < 0) px = 0;
        if (py < 0) py = 0;
        if (px > game.GetWidth() - fw * scale) px = (double)(game.GetWidth() - fw * scale);
        if (py > game.GetHeight() - fh * scale) py = (double)(game.GetHeight() - fh * scale);

        if (moving) {
            animTimer += dt;
            if (animTimer >= 0.15) {
                animTimer = 0.0;
                frame = (frame + 1) % 3;
            }
        } else {
            frame = 0;
            animTimer = 0.0;
        }

        game.Clear(COLOR_DARK_GREEN);

        for (int i = 0; i < 30; i++) {
            int gx = (i * 97 + 13) % game.GetWidth();
            int gy = (i * 173 + 47) % game.GetHeight();
            game.FillRect(gx, gy, 3, 3, COLOR_GREEN);
        }

        int frameIndex = dir * 3 + frame;
        game.DrawSpriteFrameScaled(charSheet, (int)px, (int)py,
                                   fw, fh, frameIndex,
                                   fw * scale, fh * scale);

        game.DrawText(470, 10, "Sprite Sheet:", COLOR_WHITE);
        int previewScale = 2;
        int sheetW = fw * 3;
        int sheetH = fh * 4;
        int pvX = 470;
        int pvY = 25;
        game.DrawSpriteScaled(charSheet, pvX, pvY, sheetW * previewScale, sheetH * previewScale);
        game.DrawRect(pvX, pvY, sheetW * previewScale, sheetH * previewScale, COLOR_GRAY);
        game.DrawRect(pvX + frame * fw * previewScale, pvY + dir * fh * previewScale,
                      fw * previewScale, fh * previewScale, COLOR_YELLOW);

        const char *dirNames[] = {"Down", "Left", "Right", "Up"};
        game.DrawText(10, 10, "WASD / Arrow keys to move", COLOR_WHITE);
        game.DrawPrintf(10, 25, COLOR_GRAY, "Dir: %s  Frame: %d", dirNames[dir], frame);

        game.Update();
        game.WaitFrame(60);
    }

    game.FreeSprite(charSheet);
    return 0;
}