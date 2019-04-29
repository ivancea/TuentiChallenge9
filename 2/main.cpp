#include <iostream>
#include <map>
#include <string>
#include "C:/includes/Cpp/strings.h"

using namespace std;

int calcPaths(const string& planet, map<string, vector<string>>& links, map<string, int>& cache) {
    int count = 0;
    
    for(const string& target : links[planet]) {
        const auto& it = cache.find(target);

        if (it != cache.end()) {
            count += it->second;

            continue;
        }

        int pathCount = calcPaths(target, links, cache);

        cache[target] = pathCount;
        count += pathCount;
    }

    return count;
}

int main(){
    int n;
    cin >> n;

    for(int i=1; i<=n; i++){
        int planetCount;
        cin >> planetCount;
        cin.ignore();

        map<string, vector<string>> links;
        map<string, int> cache;
        cache["New Earth"] = 1;

        for(int j=0; j<planetCount; j++){
            string line;
            getline(cin, line);

            std::vector<string> tokens = split(line, ':');

            links[tokens[0]] = split(tokens[1], ',');
        }

        cout << "Case #" << i << ": " << calcPaths("Galactica", links, cache) << endl;
    }
}