#include <cstdio>
#include <cstdlib>

void num_to_mars_color(int num_color, char color[2])
{
    int digit_1 = num_color % 13;
    color[1] = digit_1 < 10 ? '0' + digit_1 : 'A' + digit_1 - 10;
    int digit_2 = num_color / 13;
    color[0] = digit_2 < 10 ? '0' + digit_2 : 'A' + digit_2 - 10;
}

int main()
{
    int num_red, num_green, num_blue;
    char rgb_color[8] = "#000000";
    scanf("%d%d%d", &num_red, &num_green, &num_blue);
    num_to_mars_color(num_red, rgb_color + 1);
    num_to_mars_color(num_green, rgb_color + 3);
    num_to_mars_color(num_blue, rgb_color + 5);
    printf("%s\n", rgb_color);
    return 0;
}