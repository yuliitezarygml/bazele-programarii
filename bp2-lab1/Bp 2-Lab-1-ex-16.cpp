// 16.Se citește un vector A cu n elemente numere întregi. Să se elaboreze un program
// care citește, afișează și construiește doi vectori B și C astfel:
// - vectorul B va conține elementele pare din vectorul A.
// - vectorul C va conține elementele impare din vectorul A.

#include <iostream>
using namespace std;

void splitByParity(int A[], int n, int B[], int &nB, int C[], int &nC){
    
    if(n > 0){            
        splitByParity(A, n-1, B, nB, C, nC);

        if ((A[n-1] % 2) == 0){
            B[nB] = A[n-1];
            nB++;
        }
        else {
            C[nC] = A[n-1];
            nC++;
        }
    }
}
int main(){
    unsigned int n;
    cout << "Introduceti numarul de elemente: ";
    cin >> n;

    int A[n];
    cout << "Introduceti elementele: ";
    int countpar = 0;
    int countimpar = 0;
    int par = 0;
    int impar = 0;
    
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        if ((A[i] % 2)!=0){
            impar=impar + 1;
        }
        else if ((A[i] % 2) == 0) {
            par = par + 1;
        }
    }
    
    int B[par];
    int C[impar];
    int nB = 0, nC = 0;
    
    splitByParity(A,n,B,nB,C,nC);
    
    cout << "Vectorul A (vectorul de baza): ";
    for (int i = 0; i < n; i++){
        cout << A[i] << " ";
    }
    
    cout << "\nVectorul B (pare): ";
    for (int i = 0; i < nB; i++){
        cout << B[i] << " ";
    }
    
    cout << "\nVectorul C (impare): ";
    for (int i = 0; i < nC; i++){
        cout << C[i] << " ";
    }

    return 0;
}