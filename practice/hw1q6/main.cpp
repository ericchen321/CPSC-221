#include <iostream>
using namespace std;

int raspberryscone(int n) {
    int s = 0;
    int r = 0;
    for (int q = 0; q < n; q++)
    s = s + q;
    for (r = s; r > 2; r--)
    s--;
    return r * s;
}

unsigned long long peanutbuttercheesecake(int n) {
    unsigned long long count = 0;
    unsigned long long i = 0;
    unsigned long long j = 4 * n;
    for (unsigned long long k = j * j; k > 1; k = k / 2) {
        i++;
        count++;
    }
    // cout << count << endl;
    return i * i / 4;
}

int almondcaramelbrittle(int n) {
    int count = 0;
    int c = 0;
    int s;
    for (s = 1; s < n * n * n * n; s = s * n) {
        c++;
        count++;
    }
    // cout << count << endl;
    return c * s;
}

void vanillacustardblueberrytorte(int n) {
    int j = 1;
    unsigned long long count = 0;
    for (int k = 0; k < raspberryscone(n/2) * almondcaramelbrittle(n); k++){
        j = 2 * j;
        count++;
    }
    for (int m = j; m > 1; m = m / 2){
        count++;
    }
    cout << count << endl;
}

int pirouline(int n) {
    int j = 0;
    for (int k = 0; k < raspberryscone(n) * n; k++)
        j = j + 2;
    return peanutbuttercheesecake(almondcaramelbrittle(j));
}

int main(){
    vanillacustardblueberrytorte(20);
}
