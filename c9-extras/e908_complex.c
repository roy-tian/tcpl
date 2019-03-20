#include <stdio.h>
#include <math.h>

typedef struct complex {
    double real_part;
    double imaginary_part;
} complex;

void set_complex(complex *z, double real, double imaginary) {
    z->real_part = real;
    z->imaginary_part = imaginary;
}

complex new_complex(double real, double imaginary) {
    complex result;
    set_complex(&result, real, imaginary);
    return result; 
}

void print_complex(complex z) {
    if (z.imaginary_part > 0.0) {
        printf("%.2f + %.2fi", z.real_part, z.imaginary_part);
    } else if (z.imaginary_part < 0.0) {
        printf("%.2f - %.2fi", z.real_part, -z.imaginary_part);
    } else {
        printf("%.2f", z.real_part);
    }
}

int complex_equal(complex z1, complex z2) {
    return (z1.real_part == z2.real_part &&
            z1.imaginary_part == z2.imaginary_part);
}

complex complex_conjugate(complex z) {
    z.imaginary_part = -z.imaginary_part;
    return z;
}
complex complex_reciplrocal(complex z) {
    return new_complex (
        z.real_part / (pow(z.real_part, 2) + pow(z.imaginary_part, 2)),
        -z.imaginary_part / (pow(z.real_part, 2) + pow(z.imaginary_part, 2))
    );
}

complex complex_add(complex z1, complex z2) {
    return new_complex (
        z1.real_part + z2.real_part,
        z1.imaginary_part + z2.imaginary_part
    );
}

complex complex_subtract(complex z1, complex z2) {
    return new_complex (
        z1.real_part - z2.real_part,
        z1.imaginary_part - z2.imaginary_part
    );
}

complex complex_multiply(complex z1, complex z2) {
    return new_complex (
        z1.real_part * z2.real_part - z1.imaginary_part * z2.imaginary_part,
        z1.real_part * z2.imaginary_part + z1.imaginary_part * z2.real_part 
    );
}

complex complex_divide(complex z1, complex z2) {
    return complex_multiply(z1, complex_reciplrocal(z2));
}

int main() {
    complex z1 = new_complex(1, 2);
    complex z2 = new_complex(3, 4);
    print_complex(z1);
    printf(" / ");
    print_complex(z2);
    printf(" = ");
    print_complex(complex_divide(z1, z2));
}