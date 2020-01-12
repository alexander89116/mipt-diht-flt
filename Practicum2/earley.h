#include <bits/stdc++.h>

namespace NEarley {

    struct TRule {
        char From;
        std::string To;

        friend std::istream& operator>>(std::istream &in, TRule &rule) {
            std::string s;
            in >> s;
            rule.From = s[0];
            rule.To = s.substr(2, s.length());
            return in;
        }

        bool operator<(const TRule &rule) const {
            return (From < rule.From) || (From == rule.From && To < rule.To);
        }

        bool operator==(const TRule &rule) const {
            return (From == rule.From && To == rule.To);
        }
    };


    struct TSituation {
        TRule Rule;
        int DotPosition;
        int Num;

        bool operator<(const TSituation &sit) const {
            return (Rule < sit.Rule) ||
                   (Rule == sit.Rule && DotPosition < sit.DotPosition) ||
                   (Rule == sit.Rule && DotPosition == sit.DotPosition && Num < sit.Num);
        }
    };

    
    void Scan(std::vector<std::set<TSituation>> &d, std::string &w, int j) {
        if (j < 0) return;

        for (auto &situation : d[j]) {
            if (situation.DotPosition >= situation.Rule.To.length()) continue;
            if (situation.Rule.To[situation.DotPosition] == w[j]) {
                d[j + 1].insert({ situation.Rule, situation.DotPosition + 1, situation.Num });
            }
        }
    }

    void Complete(std::vector<std::set<TSituation>> &d, int j) {
        std::vector<TSituation> new_sit;
        for (auto &competed_sit: d[j]) {
            if (competed_sit.DotPosition != competed_sit.Rule.To.length()) continue;
            for (auto &situation: d[competed_sit.Num]) {
                if (situation.Rule.To[situation.DotPosition] == competed_sit.Rule.From) {
                    new_sit.push_back({ situation.Rule, situation.DotPosition + 1, situation.Num });
                }
            }
        }

        for (auto sit: new_sit) {
            d[j].insert(sit);
        }
    }

    void Predict(std::vector<TRule> &grammar, std::vector<std::set<TSituation>> &d, int j) {
        std::vector<TSituation> new_sit;
        for (auto &situation: d[j]) {
            if (situation.DotPosition >= situation.Rule.To.length()) continue;
            for (auto &rule: grammar) {
                if (rule.From == situation.Rule.To[situation.DotPosition]) {
                    new_sit.push_back({ rule, 0, j });
                }
            }
        }

        for (auto sit: new_sit) {
            d[j].insert(sit);
        }
    }

    bool Earley(std::vector<TRule> &grammar, std::string &w) {
        std::vector<std::set<TSituation>> D;
        D.resize(w.length() + 1);
        D[0].insert({ { 'S', "A" }, 0, 0 });
        int sz;
        for (int j = 0; j <= w.length(); j++) {
            Scan(D, w, j - 1);
            do {
                sz = D[j].size();
                Complete(D, j);
                Predict(grammar, D, j);
            } while (sz != D[j].size());
        }
        return D[w.length()].find({ { 'S', "A" }, 1, 0 }) != D[w.length()].end();
    }
}
