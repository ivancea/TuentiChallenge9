#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Point {
    int x, y;

    Point(int _x, int _y) : x(_x), y(_y) {}

    bool operator<(const Point& p) const {
        if (x == p.x) {
            return y < p.y;
        }

        return x < p.x;
    }
};

int main(){
    int n;
    cin >> n;

    for(int caseNumber=1; caseNumber<=n; caseNumber++){
        int width, height, foldCount, punchCount;
        cin >> width >> height >> foldCount >> punchCount;

        int gridWidth = 1;
        int gridHeight = 1;

        bool initialInvertedHorizontal = false;
        bool initialInvertedVertical = false;

        for(int j=0; j<foldCount; j++){
            char fold;
            cin >> fold;

            switch(fold) {
                case 'L':
                case 'R':
                    if (gridWidth == 1) {
                        initialInvertedHorizontal = fold == 'L';
                    }

                    gridWidth *= 2;
                    break;
                case 'T':
                case 'B':
                    if (gridHeight == 1) {
                        initialInvertedVertical = fold == 'T';
                    }

                    gridHeight *= 2;

                    break;
            }
        }

        vector<Point> punches;

        for(int j=0; j<punchCount; j++){
            int punchX, punchY;
            cin >> punchX >> punchY;

            punches.emplace_back(Point(punchX, punchY));
        }

        set<Point> points;

        if (punchCount > 0) {
            for(int i = 0; i < gridWidth; i++) {
                bool invertedHorizontal = initialInvertedHorizontal ^ (i % 2 != 0);

                for(int j = 0; j < gridHeight; j++) {
                    bool invertedVertical = initialInvertedVertical ^ (j % 2 != 0);

                    for (const Point& punch : punches) {
                        points.emplace(Point(
                            (i * width) + (invertedHorizontal ? width - punch.x - 1 : punch.x),
                            (j * height) + (invertedVertical ? height - punch.y - 1 : punch.y)
                        ));
                    }
                }
            }
        }

        cout << "Case #" << caseNumber << ":" << endl;

        for(const Point& point : points) {
            cout << point.x << " " << point.y << endl;
        }
    }
}