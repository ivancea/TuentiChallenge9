#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;

    for(int i=1; i<=n; i++){
        int a,b;
        cin >> a >> b;
        cout << "Case #" << i << ": " << (a+1)/2 + (b+1)/2 << endl;
    }
}