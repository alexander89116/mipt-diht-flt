#include <bits/stdc++.h>
#include "earley.h"

int main() {
    int n; std::cin >> n;
    std::vector<NEarley::TRule> grammar(n);
    for (int i = 0; i < n; i++) {
        std::cin >> grammar[i];
    }
    std::string s;
    std::cin >> s;
    if (NEarley::Earley(grammar, s)) {
        std::cout << "correct\n";
    } else {
        std::cout << "incorrect\n";
    }
    return 0;
}