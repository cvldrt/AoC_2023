#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <tuple>

int FIVE_OF_A_KIND = 1;
int FOUR_OF_A_KIND = 2;
int FULL_HOUSE = 3;
int THREE_OF_A_KIND = 4;
int TWO_PAIR = 5;
int ONE_PAIR = 6;
int HIGH_CARD = 7;

typedef std::tuple<std::string, int> hand;

int get_type(std::string& cards) {
    std::map<char, int> m;

    for (char c : cards) {
        if (m.contains(c))
            m[c]++;
        else
            m[c] = 1;
    }

    if (m.contains('J') && m.size() > 1) {
        auto x = std::max_element(
            m.begin(), m.end(),
            [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
                return p1.second < p2.second;
            });

        x->second += m['J'];
        m.erase('J');
    }

    if (m.size() == 1) return FIVE_OF_A_KIND;
    if (m.size() == 2 &&
        ((*m.begin()).second == 1 || (*++m.begin()).second == 1))
        return FOUR_OF_A_KIND;
    if (m.size() == 2) return FULL_HOUSE;
    if (m.size() == 3 &&
        ((*m.begin()).second == 2 || (*++m.begin()).second == 2))
        return TWO_PAIR;
    if (m.size() == 3) return THREE_OF_A_KIND;
    if (m.size() == 5) return HIGH_CARD;
    return ONE_PAIR;
}

auto cmp = [](hand lhs, hand rhs) {
    auto [lhs_cards, _1] = lhs;
    auto [rhs_cards, _2] = rhs;

    int lhs_type = get_type(lhs_cards);
    int rhs_type = get_type(rhs_cards);

    std::string order = "AKQT98765432J";

    if (lhs_type != rhs_type) return lhs_type > rhs_type;

    for (int i = 0; i < lhs_cards.size(); i++) {
        if (lhs_cards[i] != rhs_cards[i]) {
            return order.find(lhs_cards[i]) > order.find(rhs_cards[i]);
        }
    }

    // should never happen
    return true;
};

std::set<hand, decltype(cmp)> get_hands(std::fstream& fs) {
    std::set<hand, decltype(cmp)> res;

    int bid;
    std::string cards;
    while (fs >> cards >> bid) res.emplace(cards, bid);

    return res;
}

int main() {
    std::fstream input("input.txt");

    int res = 0;

    std::set<hand, decltype(cmp)> hands = get_hands(input);

    int i = 1;
    for (auto& [hand, bid] : hands) res += i++ * bid;

    input.close();

    std::cout << res << std::endl;

    return 0;
}
