#include <mallow.h>
#include <time.h>
#include <stdlib.h>

#define FIRE_W 100
#define FIRE_H 100
#define SCALE 5

int pixels[FIRE_W * FIRE_H];

uint32_t colors[] = 
{
    0xFF000000, 0xFF070707, 0xFF1F0707, 0xFF2F0F07, 0xFF470F07,
    0xFF571707, 0xFF671F07, 0xFF771F07, 0xFF8F2707, 0xFF9F2F07,
    0xFFAF3F07, 0xFFBF4707, 0xFFC74707, 0xFFDF4F07, 0xFFDF5707,  
    0xFFDF5707, 0xFFD75F07, 0xFFD75F07, 0xFFD7670F, 0xFFCF6F0F,  
    0xFFCF770F, 0xFFCF7F0F, 0xFFCF8717, 0xFFC78717, 0xFFC78F17, 
    0xFFC7971F, 0xFFBF9F1F, 0xFFBF9F1F, 0xFFBFA727, 0xFFBFA727, 
    0xFFBFAF2F, 0xFFB7AF2F, 0xFFB7B72F, 0xFFB7B737, 0xFFCFCF6F,
    0xFFDFDF9F, 0xFFEFEFC7
};

void update()
{
    for (int y = 0; y < FIRE_H; y++)
    {
        for (int x = 0; x < FIRE_W; x++)
        {
            int index = y * FIRE_W + x;

            int below_pixel_index = index + FIRE_W;

            if (below_pixel_index >= FIRE_W * FIRE_H)
                return;

            int decay = rand() % 2;
            int below_pixel_intensity = pixels[below_pixel_index];
            int new_intensity = (below_pixel_intensity - decay) >= 0 ? below_pixel_intensity - decay : 0;

            int new_index = index - decay;

            if (new_index >= 0)
                pixels[new_index] = new_intensity;
        }
    }
}

void draw()
{
    for (int y = 0; y < FIRE_H; y++)
    {
        for (int x = 0; x < FIRE_W; x++)
        {
            int intensity = pixels[y * FIRE_W + x];
            draw_rect(x * SCALE, y * SCALE, SCALE, SCALE, colors[intensity]);
        }
    }
}

int main()
{
    srand(time(NULL));
    init_window(FIRE_W * SCALE, FIRE_H * SCALE, "doomfire");

    for (int i = 0; i < FIRE_W * FIRE_H; i++)
        pixels[i] = 0;

    for (int y = 0; y < FIRE_H; y++)
    {
        for (int x = 0; x < FIRE_W; x++)
        {
            pixels[y * FIRE_W + x] = 36;
        }
    }

    camera2D cam =
    {
        .pos = {FIRE_W * SCALE / 2, FIRE_H * SCALE / 2},
        .zoom = 1.0f
    };

    int t = 0;

    while (!window_should_close())
    {
        t++;
        if (t % 2000000 == 0)
        {
            update();
            start_drawing();
            start_2D(cam);
            clear_bg(COLOR_WHITE);
            draw();
            end_2D();
            end_drawing();
            t = 0;
        }
    }

    close_window();
    return 0;
}
