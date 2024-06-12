//
// Created by user on 2024-06-01.
//

#define N 120

int main(){
    int matrix1[120][120];
    int matrix2[120][120];
    int matrix3[120][120] = {0,};
    #include "init_matrix120x120.h"
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return matrix3[119][119];
}
