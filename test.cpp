#include <iostream>
#include "staticvector.hpp"
//#include "dynamicvector.hpp"

using namespace std;

void printPoly(int p[], int dp) {
    for(int i=0; i <= dp; ++i) {
        cout << p[i];
        if(i < dp) {
            cout << "x";
            if(i < dp - 1) cout << "^" << dp-i << " + ";
            else cout << " + ";
        }
        else cout << endl;
    }
}

void printPoly(const int p[], const int dp) {
    for(int i=0; i <= dp; ++i) {
        cout << p[i];
        if(i < dp) {
            cout << "x";
            if(i < dp - 1) cout << "^" << dp-i << " + ";
            else cout << " + ";
        }
        else cout << endl;
    }
}

int main() {

    StaticVector<int, 5> sv;
    //DynamicVector<int> dv;

    cout << "Size test:" << endl;
    cout << "Static => " << sv.getSize() << endl;

    cout << endl << "Index access test:" << endl;
    cout << "Member 3 of static => " << sv[3] << endl;


    cout << endl << "Print test:" << endl;
    cout << sv << endl;

    StaticVector<int, 3> sv1, sv2, sv3;
    sv3 = sv1 + sv2;

    cout << "Addition test:" << endl;
    cout << "SV1 " << sv1 << "SV2 " << sv2 << endl << "SV1 + SV2 = SV3" << endl;
    cout << "SV3 " << sv3;

    cout << "Input test:" << endl;
    cin >> sv1;
    cout << "SV1 " << sv1;

    cout << endl << "Multiply test :" << endl;
    sv2 = sv1 * 4;
    cout << "SV2 = SV1 * 4" << endl;
    cout << sv2.getSize() << " " << sv1.getSize() << endl;
    cout << "SV2 " << sv2;


    return 0;
}
