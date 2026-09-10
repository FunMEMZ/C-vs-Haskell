/*
 * 任务：质数的无优化筛、埃筛和欧拉筛；sigma 求和；矩阵；导数、积分；排列、组合。
 * 编译：gcc -std=c11 -O2 -Wall -Wextra 02_02_math_primes_sigma_matrix_calculus_combinatorics.c -lm
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>


/* ---------- 无优化筛：试除法 ---------- */

static bool is_prime_naive(int n) {
    if (n < 2) return false;
    for (int d = 2; (long long)d * d <= n; ++d)
        if (n % d == 0) return false;
    return true;
}

static void naive_primes(int limit) {
    printf("naive  primes <= %d:", limit);
    for (int i = 2; i <= limit; ++i)
        if (is_prime_naive(i)) printf(" %d", i);
    printf("\n");
}


/* ---------- 埃拉托斯特尼筛 ---------- */

static void sieve_eratosthenes(int limit) {
    bool prime[105];
    for (int i = 0; i <= limit; ++i) prime[i] = true;
    prime[0] = prime[1] = false;

    for (int p = 2; (long long)p * p <= limit; ++p)
        if (prime[p])
            for (int x = p * p; x <= limit; x += p)
                prime[x] = false;

    printf("eratosthenes primes <= %d:", limit);
    for (int i = 2; i <= limit; ++i)
        if (prime[i]) printf(" %d", i);
    printf("\n");
}


/* ---------- 欧拉（线性）筛 ---------- */

static void sieve_euler(int limit) {
    bool comp[105] = { false };
    int primes[105];
    int pc = 0;

    for (int i = 2; i <= limit; ++i) {
        if (!comp[i]) primes[pc++] = i;
        for (int j = 0; j < pc && (long long)i * primes[j] <= limit; ++j) {
            comp[i * primes[j]] = true;
            if (i % primes[j] == 0) break;   /* 保证每个合数只被最小质因子筛一次 */
        }
    }

    printf("euler  primes <= %d:", limit);
    for (int i = 0; i < pc; ++i) printf(" %d", primes[i]);
    printf("\n");
}


/* ---------- sigma 求和：n 的所有正因子之和 ---------- */

static long long sigma(int n) {
    long long sum = 0;
    for (int d = 1; d <= n; ++d)
        if (n % d == 0) sum += d;
    return sum;
}


/* ---------- 矩阵：2x2 乘法 ---------- */

static void matrix_mul_2x2(const double a[2][2], const double b[2][2], double c[2][2]) {
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            c[i][j] = 0.0;
            for (int k = 0; k < 2; ++k)
                c[i][j] += a[i][k] * b[k][j];
        }
}

static void matrix_demo(void) {
    double a[2][2] = { {1, 2}, {3, 4} };
    double b[2][2] = { {5, 6}, {7, 8} };
    double c[2][2];
    matrix_mul_2x2(a, b, c);
    printf("matrix A*B = [[%.0f, %.0f], [%.0f, %.0f]]\n",
           c[0][0], c[0][1], c[1][0], c[1][1]);
}


/* ---------- 导数、积分（多项式，系数升幂存储） ---------- */

static double eval_poly(const double a[], int n, double x) {
    double y = 0.0;
    for (int i = n - 1; i >= 0; --i) y = y * x + a[i];
    return y;
}

static void poly_derivative(const double a[], int n, double d[]) {
    for (int i = 1; i < n; ++i) d[i - 1] = a[i] * i;
}

static void poly_integral(const double a[], int n, double b[]) {
    b[0] = 0.0;                         /* 取积分常数为 0 */
    for (int i = 0; i < n; ++i) b[i + 1] = a[i] / (i + 1.0);
}

static void calculus_demo(void) {
    double f[4] = {5.0, -2.0, 0.0, 1.0};     /* f(x) = x^3 - 2x + 5 */
    double df[3], F[5];

    poly_derivative(f, 4, df);
    poly_integral(f, 4, F);

    printf("f(x)=x^3-2x+5, f(2)=%.0f\n", eval_poly(f, 4, 2.0));
    printf("f'(x) coefficients (asc): %.0f %.0f %.0f\n", df[0], df[1], df[2]);
    printf("Integral coefficients (asc): %.2f %.2f %.2f %.2f %.2f\n",
           F[0], F[1], F[2], F[3], F[4]);
}


/* ---------- 排列、组合 ---------- */

static long long perm_count(int n, int k) {
    long long r = 1;
    for (int i = 0; i < k; ++i) r *= n - i;
    return r;
}

static long long comb_count(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    long long r = 1;
    for (int i = 1; i <= k; ++i) r = r * (n - k + i) / i;
    return r;
}

static void swap_int(int *a, int *b) { int t = *a; *a = *b; *b = t; }

static void print_permutations(int a[], int l, int r) {
    if (l == r) {
        for (int i = 0; i <= r; ++i) printf("%d", a[i]);
        printf(" ");
        return;
    }
    for (int i = l; i <= r; ++i) {
        swap_int(&a[l], &a[i]);
        print_permutations(a, l + 1, r);
        swap_int(&a[l], &a[i]);
    }
}

static void print_comb_rec(int a[], int n, int k, int start, int chosen[], int depth) {
    if (depth == k) {
        printf("{");
        for (int i = 0; i < k; ++i) printf("%s%d", i ? "," : "", chosen[i]);
        printf("} ");
        return;
    }
    for (int i = start; i < n; ++i) {
        chosen[depth] = a[i];
        print_comb_rec(a, n, k, i + 1, chosen, depth + 1);
    }
}

static void combinatorics_demo(void) {
    int p[3] = {1, 2, 3};
    int c[4] = {1, 2, 3, 4};
    int chosen[2];

    printf("P(5,2)=%lld, C(5,2)=%lld\n", perm_count(5, 2), comb_count(5, 2));
    printf("permutations of {1,2,3}: ");
    print_permutations(p, 0, 2);
    printf("\n");
    printf("combinations of size 2 from {1,2,3,4}: ");
    print_comb_rec(c, 4, 2, 0, chosen, 0);
    printf("\n");
}


int main(void) {
    naive_primes(30);
    printf("\n");
    sieve_eratosthenes(30);
    printf("\n");
    sieve_euler(30);
    printf("\n");
    printf("sigma(12)=%lld\n", sigma(12));
    printf("\n");
    matrix_demo();
    printf("\n");
    calculus_demo();
    printf("\n");
    combinatorics_demo();
    return 0;
}