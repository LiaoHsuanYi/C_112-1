#include <stdio.h>

int main()
{
    int height_cm, weight_p;
    float height_m, weight_kg, BMI;
    while(1)
    {
        scanf("%d", &height_cm);
        if (height_cm == -1)
        {
            break;
        }
        scanf("%d", &weight_p);

        height_m = (float)height_cm/100;
        weight_kg = (float)weight_p * 0.454;

        if (height_m <= 0.5 || height_m >= 2.5)
        {
            printf("Input Height Error\n");
            continue;
        }
        if (weight_kg <= 20 || weight_kg >= 300)
        {
            printf("Input Weight error\n");
            continue;
        }
        
        BMI = weight_kg / (height_m * height_m);
        
        if (BMI >= 18.50 && BMI <= 24)
        {
            printf("%.2lf\n", BMI-0.005);
        }
        else if (BMI > 24)
        {
            printf("BMI too high\n");
        }
        else
        {
            printf("BMI too low\n");
        }
    }
    return 0;
}