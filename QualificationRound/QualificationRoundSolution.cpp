#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

const int M_MAX = 123456;

struct Intersection {
    int id;
    vector<string> incoming;
    vector<int> times;

    Intersection(const int newId, vector<string> newIncoming, vector<int> newTimes) : id(newId), incoming(newIncoming), times(newTimes) {}
};

struct Street {
    int B;
    int E;
    string name;
    int L;

    Street &operator=(Street other) {
        this->B = other.B;
        this->E = other.E;
        this->name = other.name;
        this->L = other.L;
        return *this;
    }

    Street(const int newB, const int newE, const string newName, const int newL) : B(newB), E(newE), name(newName), L(newL) {}
};

ostream &operator<<(std::ostream& os, const Street &value) {
    return os << value.B << " " << value.E << " " << value.name << " " << value.L << '\n';
}

void solve(string inputFile, string outputFile) {

    ifstream fin(inputFile);
    ofstream fout(outputFile);

    int D, I, S, V, F;

    fin >> D >> I >> S >> V >> F;

    vector<Street> streets;
    vector<Intersection> intersections;
    vector<vector<string>> routes;
    vector<int> carState(V, 0);
    map<string, int> maxMap;
    map<string, map<int, int>> carCntMap;
    map<string, int> streetL;

    for (int i = 0; i < I; i++) {
        Intersection newIntersection = Intersection(i, vector<string>(), vector<int>());
        intersections.push_back(newIntersection);
    }

    for (int i = 0; i < S; i++) {
        int B, E, L;
        string name;
        fin >> B >> E >> name >> L;
        if (maxMap.find(name) == maxMap.end()) {
            maxMap.insert(make_pair(name, 0));
        }
        streetL.insert(make_pair(name, L));
        streets.push_back((Street(B, E, name, L)));
        intersections[E].incoming.push_back(name);
    }

    for (int i = 0; i < V; i++) {
        vector<string> newRoute;
        int nr;
        fin >> nr;
        int time = 0;
        for (int j = 0; j < nr; j++) {
            string newStreet;
            fin >> newStreet;
            newRoute.push_back(newStreet);
            if (carCntMap.find(newStreet) != carCntMap.end()) {
                if (carCntMap[newStreet].find(time) != carCntMap[newStreet].end()) {
                    carCntMap[newStreet].find(time)++;
                    int val = carCntMap[newStreet][time];
                    maxMap[newStreet] = max(maxMap[newStreet], val);
                }
                else {
                    carCntMap[newStreet].insert(make_pair(time, 1));
                }
            }
            else {
                carCntMap.insert(make_pair(newStreet, map<int, int>()));
            }
        }

        routes.push_back(newRoute);
    }

    /*for (map<string, int>::iterator it = interMap.begin(); it != interMap.end(); it++) {
        fout << it->first << " " << it->second << "\n";
    }*/

    fout << I << "\n";
    for (int i = 0; i < I; i++) {
        int currInc = intersections[i].incoming.size();
        fout << i << "\n";
        fout << currInc << "\n";
        random_shuffle(intersections[i].incoming.begin(), intersections[i].incoming.end());
        for (int j = 0; j < currInc; j++) {
            fout << intersections[i].incoming[j] << " " << // No time left... << "\n";
        }
    }

    /*int currTime = 0;
    while (currTime < D) {
        bool found = false;

    }*/
}

int main() {

    solve("a.in", "a.out");
    solve("b.in", "b.out");
    solve("c.in", "c.out");
    solve("d.in", "d.out");
    solve("e.in", "e.out");
    solve("f.in", "f.out");
    return 0;
}