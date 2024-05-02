#include <stdio.h>
#include <string.h>
#include <math.h>

#define shapeText(TYPE) int (*perimeter) (struct TYPE*); \
                        int (*area) (struct TYPE*);

typedef struct Shape_s
{
    shapeText(shape_s);
} shape_t;

typedef struct circle_s
{
    shapeText(circle_s);
    int radius;
} circle_t;

typedef struct rectangle_s
{
    shapeText(rectangle_s);
    int width, height;
} rectangle_t;

typedef struct square_s
{
    shapeText(square_s);
    int side;
} square_t;

typedef struct triangle_s
{
    shapeText(triangle_s);
    int s1, s2, s3;
} triangle_t;

int CirclePerimeter(circle_t *obj)
{
    return 4 * 2 * obj->radius;
}

int CircleArea(circle_t *obj)
{
    return 4 * obj->radius * obj->radius;
}

int RectanglePerimeter(rectangle_t * obj)
{
    return 2 * (obj->width + obj->height);
}

int RectangleArea(rectangle_t *obj)
{
    return obj->width * obj->height;
}

int SquarePerimeter(square_t *obj)
{
    return 4 * obj->side;
}

int SquareArea(square_t *obj)
{
    return obj->side * obj->side;
}

int TrianglePerimeter(triangle_t *obj)
{
    return obj->s1 + obj->s2 + obj->s3;
}

int TriangleArea(triangle_t *obj)
{
    int s = (obj->s1 + obj->s2 + obj->s3) / 2;
    return sqrt(s * (s - obj->s1) * (s - obj->s2) * (s - obj->s3));
}

void CircleNew(circle_t *obj)
{
    obj->perimeter = CirclePerimeter;
    obj->area = CircleArea;
}

void RectangleNew(rectangle_t *obj)
{
    obj->perimeter = RectanglePerimeter;
    obj->area = RectangleArea;
}

void SquareNew(square_t *obj)
{
    obj->perimeter = SquarePerimeter;
    obj->area = SquareArea;
}

void TriangleNew(triangle_t *obj)
{
    obj->perimeter = TrianglePerimeter;
    obj->area = TriangleArea;
}

int main()
{
    int n, p, a;
    int sum_p = 0, sum_a = 0;
    char shape[10] = {'\0'};

    scanf("%d", &n);

    while (n > 0)
    {
        scanf("%s", shape);
        if (strcmp(shape, "circle") == 0)
        {
            circle_t c;
            CircleNew(&c);
            int radius;

            scanf("%d", &radius);
            c.radius = radius;
            shape_t *sq = (shape_t *)&c;
            p = sq->perimeter(sq);
            a = sq->area(sq);
        }
        else if (strcmp(shape, "rectangle") == 0)
        {
            rectangle_t r;
            RectangleNew(&r);
            int width, height;

            scanf("%d %d", &width, &height);
            r.width = width;
            r.height = height;
            shape_t *sq = (shape_t *)&r;
            p = sq->perimeter(sq);
            a = sq->area(sq);
        }
        else if (strcmp(shape, "square") == 0)
        {
            square_t s;
            SquareNew(&s);
            int side;

            scanf("%d", &side);
            s.side = side;
            shape_t *sq = (shape_t *)&s;
            p = sq->perimeter(sq);
            a = sq->area(sq);
        }
        else if (strcmp(shape, "triangle") == 0)
        {
            triangle_t t;
            TriangleNew(&t);
            int s1, s2, s3;

            scanf("%d %d %d", &s1, &s2, &s3);
            t.s1 = s1;
            t.s2 = s2;
            t.s3 = s3;
            shape_t *sq = (shape_t *)&t;
            p = sq->perimeter(sq);
            a = sq->area(sq);
        }
        
        printf("%s %d %d\n", shape, p, a);
        sum_p += p;
        sum_a += a;
        n--;
    }
    printf("%d %d\n", sum_p, sum_a);
}