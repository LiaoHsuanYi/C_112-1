#include <stdio.h>

void bmi(float, float);

int main()
{
    float height, weight;
    while(1)
    {
        scanf("%f", &height);
        if (height == -1)
        {
            break;
        }
        scanf("%f", &weight);

        height = (float)height/100;
        weight = (float)weight * 0.454;

        if (height <= 0.5 || height >= 2.5)
        {
            printf("Input Height Error\n");
        }
        else if (weight <= 20 || weight >= 300)
        {
            printf("Input Weight error\n");
        }
        else
        {
            bmi(height, weight);
        }
    }
}


void bmi(float h, float w)
{
    float BMI;
    BMI = w/(h * h);
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

