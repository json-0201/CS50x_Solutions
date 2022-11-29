#include <cs50.h>
#include <stdio.h>

int get_height(void);

int main(void)
{
    // input height
    int h = get_height();
    int w = 1;
    int spc = h - 1;
    char hash = '#';
    string gap = "  ";


    // for each row
    for (int r = 0; r < h; r++)
    {
        // spacing
        for (int s = 0; s < spc; s++)
        {
            printf(" ");
        }
        spc--;

        // left hash
        for (int c = 0; c < w; c++)
        {
            printf("%c", hash);
        }

        // add gap
        printf("%s", gap);

        // right hash
        for (int c = 0; c < w; c++)
        {
            printf("%c", hash);
        }

        printf("\n");
        w++;
    }
}


int get_height(void)
{
    int height;
    do
    {
        height = get_int("Enter the pyramid height: ");
    }
    while (height < 1 || height > 8);

    return height;
}