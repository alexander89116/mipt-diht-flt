#include <bits/stdc++.h>

static const int INF = INT_MAX / 2;

class RegularExpressionException: public std::logic_error {
public:
    explicit RegularExpressionException()
        : std::logic_error("Regular expression is incorrect") {}
};

template<typename T>
std::pair<T, T> pop2last(std::stack<T>& stack) {
    if (stack.size() < 2) {
        throw RegularExpressionException();
    }

    T a, b;
    a = stack.top();
    stack.pop();
    b = stack.top();
    stack.pop();

    return { b, a };
}

int main() {
    std::string regularExpression;
    char c;

    std::cin >> regularExpression >> c;

    int n = regularExpression.length();

    std::stack<int> min_length;
    std::stack<int> max_suffix_length;
    std::stack<bool> is_only_char; // true, if exist word, which |w| != 0 and is consists of only c

    for (size_t i = 0; i < n; ++i) {
        if (regularExpression[i] == '.') {
            auto pair_min_len = pop2last<int>(min_length);
            auto pair_max_suffix = pop2last<int>(max_suffix_length);
            auto pair_is_only_char = pop2last<bool>(is_only_char);
            if (pair_is_only_char.second) {
                max_suffix_length.push(std::min(pair_max_suffix.first + pair_max_suffix.second, INF));
            } else if (pair_min_len.second == 0 && pair_max_suffix.first > pair_max_suffix.second) {
                max_suffix_length.push(pair_max_suffix.first);
            } else {
                max_suffix_length.push(pair_max_suffix.second);
            }

            is_only_char.push((pair_is_only_char.first && pair_is_only_char.second)
                           || (!pair_min_len.first && pair_min_len.second && pair_is_only_char.second)
                           || (pair_min_len.first && !pair_min_len.second && pair_is_only_char.first));
            min_length.push(pair_min_len.first + pair_min_len.second);
        } else if (regularExpression[i] == '+') {
            auto pair_min_len = pop2last<int>(min_length);
            auto pair_max_suffix = pop2last<int>(max_suffix_length);
            auto pair_is_only_char = pop2last<bool>(is_only_char);

            max_suffix_length.push(std::max(pair_max_suffix.first, pair_max_suffix.second));
            min_length.push(std::min(pair_min_len.first, pair_min_len.second));
            is_only_char.push(pair_is_only_char.first || pair_is_only_char.second);
        
        } else if (regularExpression[i] == '*') {
            if (is_only_char.empty() || min_length.empty() || max_suffix_length.empty()) {
                throw RegularExpressionException();
            }

            min_length.pop();
            min_length.push(0);

            int last_regular_subexpression_max_suffix = max_suffix_length.top();
            max_suffix_length.pop();

            bool last_regular_subexpression_is_only_char = is_only_char.top();
            is_only_char.pop();

            if (last_regular_subexpression_is_only_char) {
                max_suffix_length.push(INF);
                is_only_char.push(true);
            } else {
                max_suffix_length.push(last_regular_subexpression_max_suffix);
                is_only_char.push(false);
            }
        } else if (regularExpression[i] == '1') {
            max_suffix_length.push(0);
            min_length.push(0);
            is_only_char.push(false);
        } else if (regularExpression[i] == c) {
            max_suffix_length.push(1);
            min_length.push(1);
            is_only_char.push(true);
        } else {
            max_suffix_length.push(0);
            min_length.push(1);
            is_only_char.push(false);
        }
    }

    if (max_suffix_length.size() != 1) {
        throw RegularExpressionException();
    }

    if (max_suffix_length.top() == INF) {
        std::cout << "inf" << std::endl;
    } else {
        std::cout << max_suffix_length.top() << std::endl;
    }
    return 0;
}