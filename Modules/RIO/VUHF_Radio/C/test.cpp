#include <iostream>
int main(){
    char test[8] = "123.456";
    for (int i = 3; i < 7; ++i) {
        test[i] = test[i + 1];
    }
    test[7] = '\0';
    std::cout << test << std::endl;
    return 0;
}