#include "../GameLib.SDL.h"

static int CreateShipSprite(GameLib &game)
{
    int id = game.CreateSprite(16, 16);
    if (id < 0) return -1;

    for (int y = 0; y < 16; y++)
        for (int x = 0; x < 16; x++)
            game.SetSpritePixel(id, x, y, 0x00000000);

    for (int y = 4; y < 14; y++)
        for (int x = 6; x < 10; x++)
            game.SetSpritePixel(id, x, y, COLOR_CYAN);

    game.SetSpritePixel(id, 7, 2, COLOR_WHITE);
    game.SetSpritePixel(id, 8, 2, COLOR_WHITE);
    game.SetSpritePixel(id, 7, 3, COLOR_WHITE);
    game.SetSpritePixel(id, 8, 3, COLOR_WHITE);

    for (int x = 1; x < 6; x++) {
        game.SetSpritePixel(id, x, 9, COLOR_GRAY);
        game.SetSpritePixel(id, x, 10, COLOR_GRAY);
    }

    for (int x = 10; x < 15; x++) {
        game.SetSpritePixel(id, x, 9, COLOR_GRAY);
        game.SetSpritePixel(id, x, 10, COLOR_GRAY);
    }

    game.SetSpritePixel(id, 5, 13, COLOR_DARK_GRAY);
    game.SetSpritePixel(id, 10, 13, COLOR_DARK_GRAY);
    game.SetSpritePixel(id, 7, 14, COLOR_ORANGE);
    game.SetSpritePixel(id, 8, 14, COLOR_ORANGE);
    game.SetSpritePixel(id, 7, 15, COLOR_YELLOW);
    game.SetSpritePixel(id, 8, 15, COLOR_YELLOW);

    return id;
}

static int CreateAnimSheet(GameLib &game)
{
    int id = game.CreateSprite(32, 8);
    if (id < 0) return -1;

    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 32; x++)
            game.SetSpritePixel(id, x, y, 0x00000000);

    uint32_t colors[] = {COLOR_RED, COLOR_ORANGE, COLOR_YELLOW, COLOR_WHITE};
    int sizes[] = {1, 2, 3, 2};
    for (int f = 0; f < 4; f++) {
        int cx = f * 8 + 4;
        int cy = 4;
        int s = sizes[f];
        for (int dy = -s; dy <= s; dy++)
            for (int dx = -s; dx <= s; dx++)
                if (dx * dx + dy * dy <= s * s)
                    game.SetSpritePixel(id, cx + dx, cy + dy, colors[f]);
    }

    return id;
}

int main()
{
    GameLib game;
    if (game.Open(640, 480, "SDL Demo 12 - Sprite Demo", true) != 0) {
        return 1;
    }
    game.ShowFps(true);

    int ship = CreateShipSprite(game);
    int sheet = CreateAnimSheet(game);
    if (ship < 0 || sheet < 0) {
        if (ship >= 0) game.FreeSprite(ship);
        if (sheet >= 0) game.FreeSprite(sheet);
        return 1;
    }

    int shipX = 300;
    int shipY = 350;
    int frame = 0;
    int frameTimer = 0;

    while (!game.IsClosed()) {
        if (game.IsKeyPressed(KEY_ESCAPE)) break;

        if (game.IsKeyDown(KEY_LEFT)) shipX -= 3;
        if (game.IsKeyDown(KEY_RIGHT)) shipX += 3;
        if (game.IsKeyDown(KEY_UP)) shipY -= 3;
        if (game.IsKeyDown(KEY_DOWN)) shipY += 3;

        frameTimer++;
        if (frameTimer >= 10) {
            frameTimer = 0;
            frame = (frame + 1) % 4;
        }

        game.Clear(COLOR_BLACK);

        game.DrawText(20, 20, "DrawSprite (normal):", COLOR_WHITE);
        game.DrawSprite(ship, 20, 40);

        game.DrawText(20, 70, "DrawSpriteEx (flipped):", COLOR_WHITE);
        game.DrawSpriteEx(ship, 20, 90, SPRITE_FLIP_H);
        game.DrawText(50, 95, "H", COLOR_GRAY);
        game.DrawSpriteEx(ship, 80, 90, SPRITE_FLIP_V);
        game.DrawText(110, 95, "V", COLOR_GRAY);
        game.DrawSpriteEx(ship, 140, 90, SPRITE_FLIP_H | SPRITE_FLIP_V);
        game.DrawText(170, 95, "H+V", COLOR_GRAY);

        game.DrawText(20, 130, "DrawSpriteFrameScaled (sprite sheet):", COLOR_WHITE);
        game.DrawSpriteScaled(sheet, 20, 150, 64, 16);
        game.DrawRect(20, 150, 64, 16, COLOR_GRAY);
        game.DrawText(100, 148, "<-- full sheet", COLOR_GRAY);
        game.DrawText(20, 172, "Current frame:", COLOR_GRAY);
        game.DrawSpriteFrameScaled(sheet, 130, 162, 8, 8, frame, 32, 32);
        game.DrawSpriteFrameScaled(sheet, 170, 162, 8, 8, frame, 32, 32, SPRITE_FLIP_H);

        game.DrawText(20, 200, "Move with arrow keys:", COLOR_WHITE);
        game.DrawSprite(ship, shipX, shipY);

        game.DrawText(400, 20, "DrawSpriteScaled (4x):", COLOR_WHITE);
        game.DrawSpriteScaled(ship, 400, 40, 64, 64);
        game.DrawRect(400, 40, 64, 64, COLOR_GRAY);

        game.DrawText(10, 460, "Sprites created with code (CreateSprite + SetSpritePixel)", COLOR_DARK_GRAY);

        game.Update();
        game.WaitFrame(60);
    }

    game.FreeSprite(ship);
    game.FreeSprite(sheet);
    return 0;
}