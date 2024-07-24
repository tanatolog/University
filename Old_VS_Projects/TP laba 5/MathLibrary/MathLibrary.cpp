#include "pch.h"
#include <utility>
#include <limits.h>
#include "MathLibrary.h"

bool Kramer(float a[12], float& x1, float& x2, float& x3) {
    float det = a[0] * a[4] * a[8] + a[1] * a[5] * a[6] + a[2] * a[3] * a[7] - a[2] * a[4] * a[6] - a[3] * a[1] * a[8] - a[0] * a[7] * a[5];
    if (det == 0) {
        return false;
    }
    float det1 = a[9] * a[4] * a[8] + a[1] * a[5] * a[11] + a[10] * a[7] * a[2] - a[2] * a[4] * a[11] - a[10] * a[1] * a[8] - a[7] * a[5] * a[9];
    float det2 = a[0] * a[10] * a[8] + a[9] * a[5] * a[6] + a[3] * a[11] * a[2] - a[2] * a[10] * a[6] - a[3] * a[9] * a[8] - a[11] * a[5] * a[0];
    float det3 = a[0] * a[4] * a[11] + a[1] * a[10] * a[6] + a[3] * a[7] * a[9] - a[9] * a[4] * a[6] - a[3] * a[1] * a[11] - a[0] * a[7] * a[10];
    x1 = det1 / det;
    x2 = det2 / det;
    x3 = det3 / det;
    return true;
}

extern "C" bool Kramer(float* a, float& x1, float& x2);

bool Kramer(float a[2], float& x1) {
    if (a[0] == 0) {
        return false;
    }
    x1 = a[1] / a[0];
    return true;
}

int NumofVar(float matrix[12], float& xx1, float& xx2, float& xx3) {
    if (Kramer(matrix, xx1, xx2, xx3)) {
        return 300;
    }
    else {
        float arr[6];
        float ar[2];
        if (matrix[0] + matrix[3] + matrix[6] == 0) {

            if (matrix[1] + matrix[4] + matrix[7] == 0) {
                ar[0] = matrix[2]; ar[1] = matrix[9];
                if (Kramer(ar, xx3)) {
                    return 13;
                }
                else {
                    ar[0] = matrix[5]; ar[1] = matrix[10];
                    if (Kramer(ar, xx3)) {
                        return 13;
                    }
                    else {
                        ar[0] = matrix[8]; ar[1] = matrix[11];
                        if (Kramer(ar, xx3)) {
                            return 13;
                        }
                    }
                }
            }

            if (matrix[2] + matrix[5] + matrix[8] == 0) {
                ar[0] = matrix[1]; ar[1] = matrix[9];
                if (Kramer(ar, xx2)) {
                    return 12;
                }
                else {
                    ar[0] = matrix[4]; ar[1] = matrix[10];
                    if (Kramer(ar, xx2)) {
                        return 12;
                    }
                    else {
                        ar[0] = matrix[7]; ar[1] = matrix[11];
                        if (Kramer(ar, xx2)) {
                            return 12;
                        }
                    }
                }
            }

            arr[0] = matrix[1]; arr[1] = matrix[2]; arr[2] = matrix[9];
            arr[3] = matrix[4]; arr[4] = matrix[5]; arr[5] = matrix[10];

            if (Kramer(arr, xx2, xx3)) {
                return 223;
            }
            else {
                arr[3] = matrix[7]; arr[4] = matrix[8]; arr[5] = matrix[11];
                if (Kramer(arr, xx2, xx3)) {
                    return 223;
                }
                else {
                    arr[0] = matrix[4]; arr[1] = matrix[5]; arr[2] = matrix[10];
                    if (Kramer(arr, xx2, xx3)) {
                        return 223;
                    }
                }
            }
        }
        if (matrix[1] + matrix[4] + matrix[7] == 0) {

            if (matrix[0] + matrix[3] + matrix[6] == 0) {
                ar[0] = matrix[2]; ar[1] = matrix[9];
                if (Kramer(ar, xx3)) {
                    return 13;
                }
                else {
                    ar[0] = matrix[5]; ar[1] = matrix[10];
                    if (Kramer(ar, xx3)) {
                        return 13;
                    }
                    else {
                        ar[0] = matrix[8]; ar[1] = matrix[11];
                        if (Kramer(ar, xx3)) {
                            return 13;
                        }
                    }
                }
            }

            if (matrix[2] + matrix[5] + matrix[8] == 0) {
                ar[0] = matrix[0]; ar[1] = matrix[9];
                if (Kramer(ar, xx1)) {
                    return 11;
                }
                else {
                    ar[0] = matrix[3]; ar[1] = matrix[10];
                    if (Kramer(ar, xx1)) {
                        return 11;
                    }
                    else {
                        ar[0] = matrix[6]; ar[1] = matrix[11];
                        if (Kramer(ar, xx1)) {
                            return 11;
                        }
                    }
                }
            }

            arr[0] = matrix[0]; arr[1] = matrix[2]; arr[2] = matrix[9];
            arr[3] = matrix[3]; arr[4] = matrix[5]; arr[5] = matrix[10];
            if (Kramer(arr, xx1, xx3)) {
                return 213;
            }
            else {
                arr[3] = matrix[6]; arr[4] = matrix[8]; arr[5] = matrix[11];
                if (Kramer(arr, xx1, xx3)) {
                    return 213;
                }
                else {
                    arr[0] = matrix[3]; arr[1] = matrix[5]; arr[2] = matrix[10];
                    if (Kramer(arr, xx1, xx3)) {
                        return 213;
                    }
                }
            }
        }
        if (matrix[2] + matrix[5] + matrix[8] == 0) {
            if (matrix[1] + matrix[4] + matrix[7] == 0) {
                ar[0] = matrix[0]; ar[1] = matrix[9];
                if (Kramer(ar, xx1)) {
                    return 11;
                }
                else {
                    ar[0] = matrix[3]; ar[1] = matrix[10];
                    if (Kramer(ar, xx1)) {
                        return 11;
                    }
                    else {
                        ar[0] = matrix[6]; ar[1] = matrix[11];
                        if (Kramer(ar, xx1)) {
                            return 11;
                        }
                    }
                }
            }

            if (matrix[0] + matrix[3] + matrix[6] == 0) {
                ar[0] = matrix[1]; ar[1] = matrix[9];
                if (Kramer(ar, xx2)) {
                    return 12;
                }
                else {
                    ar[0] = matrix[4]; ar[1] = matrix[10];
                    if (Kramer(ar, xx2)) {
                        return 12;
                    }
                    else {
                        ar[0] = matrix[7]; ar[1] = matrix[11];
                        if (Kramer(ar, xx2)) {
                            return 12;
                        }
                    }
                }
            }

            arr[0] = matrix[0]; arr[1] = matrix[1]; arr[2] = matrix[9];
            arr[3] = matrix[3]; arr[4] = matrix[4]; arr[5] = matrix[10];
            if (Kramer(arr, xx1, xx2)) {
                return 212;
            }
            else {
                arr[3] = matrix[6]; arr[4] = matrix[7]; arr[5] = matrix[11];
                if (Kramer(arr, xx1, xx2)) {
                    return 212;
                }
                else {
                    arr[0] = matrix[3]; arr[1] = matrix[4]; arr[2] = matrix[10];
                    if (Kramer(arr, xx1, xx2)) {
                        return 212;
                    }
                }
            }
        }
    }
    return 0;
}