#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

using ll = long long;

ll lagrange_interpolation(const vector<pair<ll, ll>>& points, ll x) {
    ll result = 0;
    int k = points.size();
    for (int i = 0; i < k; ++i) {
        ll xi = points[i].first;
        ll yi = points[i].second;
        ll term = yi;
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                ll xj = points[j].first;
                term *= (x - xj);
                term /= (xi - xj);
            }
        }
        result += term;
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./main <json_file>\n";
        return 1;
    }

    ifstream f(argv[1]);
    json data;
    f >> data;

    int n = data["keys"]["n"];
    int k = data["keys"]["k"];
    map<int, ll> pairs = data["keys"]["pairs"].get<map<int, ll>>();

    // Try removing one key at a time
    vector<pair<int, ll>> pair_list(pairs.begin(), pairs.end());
    ll secret = -1;

    for (int skip = 0; skip <= n - k; ++skip) {
        vector<pair<ll, ll>> subset;
        for (int i = 0; i < n; ++i) {
            if (i == skip) continue;
            subset.push_back(pair_list[i]);
            if (subset.size() == k) break;
        }

        ll guess = lagrange_interpolation(subset, 0);
        if (secret == -1) secret = guess;
        else if (secret != guess) {
            secret = guess;
            break;
        }
    }

    cout << "Secret: " << secret << endl;
    return 0;
}