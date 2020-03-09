#include <string>

int main() {
    int *p = new int;
    *p = 4;

    delete p;
    return 0;
}
