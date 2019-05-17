#define CTEST_MAIN
#define CTEST_COLOR_OK

#include <circle.h>
#include <ctest.h>

int main(int argc, const char** argv)
{
    return ctest_main(argc, argv);
}

// CHECK INPUT ERRORS
CTEST(input_test, run)
{
    // Given
    Circle c;
    char str[] = "circle(1.1 1.2, 1.3)\0";

    // When
    const int result = scan_errors(&c, str, 0);

    // Then
    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(input_test, name_error)
{
    // Given
    Circle c;
    char str[] = "notcircle(1.1 1.2, 1.3)\0";

    // When
    const int result = scan_errors(&c, str, 0);

    // Then
    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(input_test, missing_first_bracket_error)
{
    // Given
    Circle c;
    char str[] = "circle 1.1 1.2, 1.3)\0";

    // When
    const int result = scan_errors(&c, str, 0);

    // Then
    const int expected = 2;
    ASSERT_EQUAL(expected, result);
}

CTEST(input_test, missing_last_bracket_error)
{
    // Given
    Circle c;
    char str[] = "circle(1.1 1.2, 1.3\0";

    // When
    const int result = scan_errors(&c, str, 0);

    // Then
    const int expected = 2;
    ASSERT_EQUAL(expected, result);
}

CTEST(input_test, coordinate_error_first_coordinate)
{
    // Given
    Circle c;
    char str[] = "circle(e.1 1.1, 1.3)\0";

    // When
    const int result = scan_errors(&c, str, 0);

    // Then
    const int expected = 4;
    ASSERT_EQUAL(expected, result);
}

CTEST(input_test, coordinate_error_second_coordinate)
{
    // Given
    Circle c;
    char str[] = "circle(1.1 error.1, 1.3)\0";

    // When
    const int result = scan_errors(&c, str, 0);

    // Then
    const int expected = 4;
    ASSERT_EQUAL(expected, result);
}

CTEST(input_test, radius_error)
{
    // Given
    Circle c;
    char str[] = "circle(1.1 2.1, -1.3)\0";

    // When
    const int result = scan_errors(&c, str, 0);

    // Then
    const int expected = 5;
    ASSERT_EQUAL(expected, result);
}

CTEST(input_test, garbage_at_the_end_error)
{
    // Given
    Circle c;
    char str[] = "circle(1.1 2.1, 1.3) 123\0";

    // When
    const int result = scan_errors(&c, str, 0);

    // Then
    const int expected = 3;
    ASSERT_EQUAL(expected, result);
}

// CHECK CALCULATION
CTEST(calculation_test, check_perimiter)
{
    // Given
    Circle c = {1.1, 1.2, 1.3, 0};

    // When
    const int result = get_perimeter(&c, 0);

    // Then
    const int expected = 8.168141;
    ASSERT_EQUAL(expected, result);
}

CTEST(calculation_test, check_area)
{
    // Given
    Circle c = {1.1, 1.2, 1.3, 0};

    // When
    const int result = get_area(&c, 0);

    // Then
    const int expected = 5.309292;
    ASSERT_EQUAL(expected, result);
}

CTEST(calculation_test, check_intersect_true)
{
    // Given
    Circle c[2];
    c[0].x = 1.1;
    c[0].y = 1.2;
    c[0].r = 1.3;
    c[0].index = 0;
    c[1].x = 2.1;
    c[1].y = 2.2;
    c[1].r = 2.3;
    c[1].index = 1;

    // When
    const int result = get_intersect(c, 0, 1);

    // Then
    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(calculation_test, check_intersect_false)
{
    // Given
    Circle c[2];
    c[0].x = 1.1;
    c[0].y = 1.2;
    c[0].r = 1.3;
    c[0].index = 0;
    c[1].x = 2.1;
    c[1].y = 2.2;
    c[1].r = 0.1;
    c[1].index = 1;

    // When
    const int result = get_intersect(c, 0, 1);

    // Then
    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}
