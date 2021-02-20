#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

const int M_MAX = 123456;

struct Value {
    bool found;
    int prev;
    int cnt2;
    int cnt3;
    int cnt4;

    Value &operator=(Value other) {
        this->found = other.found;
        this->prev = other.prev;
        this->cnt2 = other.cnt2;
        this->cnt3 = other.cnt3;
        this->cnt4 = other.cnt4;
        return *this;
    }
};

ostream &operator<<(std::ostream& os, const Value &value) {
    return os << value.found << " " << value.prev << " " << value.cnt2 << " " << value.cnt3 << " " << value.cnt4 << '\n';
}

void getValues(int M, int T2, int T3, int T4, vector<Value> &values) {
    values[0] = Value{ true, -1, 0, 0, 0 };

    for (int i = 0; i < M - 3; i++) {
        if (values[i].found && T4 >= values[i].cnt4 + 1) {
            values[i + 4] = Value{ true, i, values[i].cnt2, values[i].cnt3, values[i].cnt4 + 1 };
        }
    }

    for (int i = 0; i < M - 2; i++) {
        if (!values[i + 3].found && values[i].found && T3 >= values[i].cnt3 + 1) {
            values[i + 3] = Value{ true, i, values[i].cnt2, values[i].cnt3 + 1, values[i].cnt4 };
        }
    }

    for (int i = 0; i < M - 1; i++) {
        if (!values[i + 2].found && values[i].found && T2 >= values[i].cnt2 + 1) {
            values[i + 2] = Value{ true, i, values[i].cnt2 + 1, values[i].cnt3, values[i].cnt4 };
        }
    }
}

void solve(string inputFile, string outputFile) {

    ifstream fin(inputFile);
    ofstream fout(outputFile);

    int M = 0;
    int T2;
    int T3;
    int T4;

    fin >> M >> T2 >> T3 >> T4;

    int currentCount = 0;
    vector<vector<string>> pizzas;
    vector<Value> values(M_MAX, Value{ false, 0, 0, 0, 0 });
    getValues(M, T2, T3, T4, values);

    /*for (int i = 0; i < 500; i++) {
        fout << values[i];
    }*/

    for (int i = 0; i < M; i++) {

        int currCnt;
        fin >> currCnt;
        pizzas.push_back(vector<string>());

        for (int j = 0; j < currCnt; j++) {
            string ingredient;
            fin >> ingredient;
            pizzas[i].push_back(ingredient);
        }

        sort(pizzas[i].begin(), pizzas[i].end());
    }

    vector<vector<int>> deliveries;

    int bestValue = M;
    while (!values[bestValue].found) {
        bestValue--;
    }

    while (bestValue) {
        int teamCnt = bestValue - values[bestValue].prev;
        vector<int> newDelivery;
        switch (teamCnt) {
            case 4:
                newDelivery = vector<int>{
                    currentCount, currentCount + 1, currentCount + 2, currentCount + 3
                };
                deliveries.push_back(newDelivery);
                currentCount += 4;
                break;
            case 3:
                newDelivery = vector<int>{
                    currentCount, currentCount + 1, currentCount + 2
                };
                deliveries.push_back(newDelivery);
                currentCount += 3;
                break;
            case 2:
                newDelivery = vector<int>{
                    currentCount, currentCount + 1
                };
                deliveries.push_back(newDelivery);
                currentCount += 2;
                break;
            default: 
                break;
        }

        bestValue = values[bestValue].prev;
    }

    fout << deliveries.size() << "\n";

    for (int i = 0; i < deliveries.size(); i++) {
        fout << deliveries[i].size();

        for (int j = 0; j < deliveries[i].size(); j++) {
            fout << " " << deliveries[i][j];
        }

        fout << "\n";
    }
}

int main() {

    solve("a.in", "a.out");
    solve("b.in", "b.out");
    solve("c.in", "c.out");
    solve("d.in", "d.out");
    solve("e.in", "e.out");

    return 0;
}