#include "main.h"

int test_polynomial() {
    double res;
    int err = polynomial(&res, 2.0, 3, 1.0, 1.0, 5.0);
    if (err)
        return err;
    printf("%f\n", res);
    err = polynomial(&res, 5.0, 6, 2.0, 1.0, 1.0, 2.0, 3.0, 4.0);
    if (err)
        return err;
    printf("%f\n", res);
    err = polynomial(&res, 4.0, 2, 2.0, 15.0);
    if (err)
        return err;
    printf("%f\n\n\n", res);

    return 0;
}

int test_points() {
    // Example 1: A Convex Quadrilateral
//    Point points1[] = { {0, 0}, {4, 0}, {4, 4}, {0, 4} };
//    int result1 = is_convex(4, points1[0], points1[1], points1[2], points1[3]);
//    printf("Example 1: A Convex Quadrilateral\n");
//    printf("Expected result: 1 (convex)\n");
//    printf("Actual result: %d\n\n", result1);
    Point points1[] = { {4, 4}, {2, 2}, {4, 0} };
    int result1 = is_convex(3, points1[0], points1[1], points1[2]);
//    printf("Example 1: A Convex Quadrilateral\n");
//    printf("Expected result: 1 (convex)\n");
    printf("Actual result: %d\n\n", result1);

    // Example 2: A Concave Quadrilateral
    Point points2[] = { {0, 0}, {4, 0}, {2, 2}, {4.0, 4.0}, {0, 4} };
    int result2 = is_convex(4, points2[0], points2[1], points2[2], points2[3]);
    printf("Example 2: A Concave Quadrilateral\n");
    printf("Expected result: 0 (concave)\n");
    printf("Actual result: %d\n\n", result2);

    // Example 3: A Convex Pentagon
    Point points3[] = { {0, 0}, {2, 0}, {4, 2}, {2, 4}, {0, 2} };
    int result3 = is_convex(5, points3[0], points3[1], points3[2], points3[3], points3[4]);
    printf("Example 3: A Convex Pentagon\n");
    printf("Expected result: 1 (convex)\n");
    printf("Actual result: %d\n\n", result3);

    // Example 4: A Concave Pentagon
    Point points4[] = { {0, 0}, {4, 0}, {4, 4}, {2, 2}, {0, 4} };
    int result4 = is_convex(5, points4[0], points4[1], points4[2], points4[3], points4[4]);
    printf("Example 4: A Concave Pentagon\n");
    printf("Expected result: 0 (concave)\n");
    printf("Actual result: %d\n\n", result4);

    // Example 5: A Triangle (Always Convex)
    Point points5[] = { {0, 0}, {4, 0}, {2, 4} };
    int result5 = is_convex(3, points5[0], points5[1], points5[2]);
    printf("Example 5: A Triangle (Always Convex)\n");
    printf("Expected result: 1 (convex)\n");
    printf("Actual result: %d\n\n", result5);

    // Example 6: A Line Segment (Not a Polygon)
    Point points6[] = { {0, 0}, {4, 0} };
    int result6 = is_convex(2, points6[0], points6[1]);
    printf("Example 6: A Line Segment (Not a Polygon)\n");
    printf("Expected result: 0 (not a polygon)\n");
    printf("Actual result: %d\n\n", result6);

    // Example 7: A Single Point (Not a Polygon)
    Point points7[] = { {0, 0} };
    int result7 = is_convex(1, points7[0]);
    printf("Example 7: A Single Point (Not a Polygon)\n");
    printf("Expected result: 0 (not a polygon)\n");
    printf("Actual result: %d\n\n", result7);

    // Example 8: A Convex Hexagon
    Point points8[] = { {0, 0}, {3, 0}, {5, 2}, {3, 4}, {0, 4}, {-2, 2} };
    int result8 = is_convex(6, points8[0], points8[1], points8[2], points8[3], points8[4], points8[5]);
    printf("Example 8: A Convex Hexagon\n");
    printf("Expected result: 1 (convex)\n");
    printf("Actual result: %d\n\n", result8);

    // Example 9: A Concave Hexagon
    Point points9[] = { {0, 0}, {3, 0}, {5, 2}, {3, 4}, {0, 4}, {1, 2} };
    int result9 = is_convex(6, points9[0], points9[1], points9[2], points9[3], points9[4], points9[5]);
    printf("Example 9: A Concave Hexagon\n");
    printf("Expected result: 0 (concave)\n");
    printf("Actual result: %d\n\n", result9);

    // Example 10: A Convex Octagon
    Point points10[] = { {0, 0}, {2, 0}, {4, 2}, {4, 4}, {2, 6}, {0, 6}, {-2, 4}, {-2, 2} };
    int result10 = is_convex(8, points10[0], points10[1], points10[2], points10[3], points10[4], points10[5], points10[6], points10[7]);
    printf("Example 10: A Convex Octagon\n");
    printf("Expected result: 1 (convex)\n");
    printf("Actual result: %d\n\n", result10);

    // Example 11: A Concave Octagon
    Point points11[] = { {0, 0}, {2, 0}, {4, 2}, {4, 4}, {2, 6}, {0, 6}, {-2, 4}, {0, 2} };
    int result11 = is_convex(8, points11[0], points11[1], points11[2], points11[3], points11[4], points11[5], points11[6], points11[7]);
    printf("Example 11: A Concave Octagon\n");
    printf("Expected result: 0 (concave)\n");
    printf("Actual result: %d\n\n", result11);

    // Example 12: A Convex Non-Regular Polygon (Irregular Heptagon)
    Point points12[] = { {0, 0}, {3, 0}, {5, 2}, {4, 4}, {2, 5}, {0, 4}, {-1, 2} };
    int result12 = is_convex(7, points12[0], points12[1], points12[2], points12[3], points12[4], points12[5], points12[6]);
    printf("Example 12: A Convex Non-Regular Polygon (Irregular Heptagon)\n");
    printf("Expected result: 1 (convex)\n");
    printf("Actual result: %d\n\n", result12);

    // Example 13: A Concave Non-Regular Polygon (Irregular Heptagon)
    Point points13[] = { {0, 0}, {3, 0}, {5, 2}, {4, 4}, {2, 5}, {0, 4}, {1, 2} };
    int result13 = is_convex(7, points13[0], points13[1], points13[2], points13[3], points13[4], points13[5], points13[6]);
    printf("Example 13: A Concave Non-Regular Polygon (Irregular Heptagon)\n");
    printf("Expected result: 0 (concave)\n");
    printf("Actual result: %d\n\n", result13);

    return 0;
}

void test_kaprekar() {
    Array a;
    create_arr(5, &a);

    for (int i = 1; i < 100000; ++i) {
        value_to_arr_base(i, 10, &a);
        if (is_kaprekar(a, 10)) {
            print_arr(a);
        }
    }
    destroy(&a);
}

int main() {
    int err = test_polynomial();
    if (err)
        return err;

//    test_points();
//    test_kaprekar();
//    Point a = {0, 0}, b = {0}, c, d;

//    kaprekar_handler(3, 6, "00000001", "0000000000006", "4", "9", "123", "45");

    return 0;
}
