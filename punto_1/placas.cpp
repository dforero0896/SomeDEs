/*
g++ -fopenmp -o placas.o placas.cpp
*/
#include <iostream>
using namespace std;
#include <omp.h>
#include <fstream>

float L = 5e-2; //m
const int S = 512;
float h = L/S;
float l = 1e-2; //m
float d = 1e-2; //m
float V0 = 100.; //m
//int N = 10000;
int N = 2*S*S; //iterations
void initialize(float matrix[S][S]){
  for(int i = 0;i<S;i++){
    for(int k=0;k<S;k++){
      matrix[i][k]=0;
    }
  }
}
void set_boundary_conditions(float matrix[S][S]){
  for(int i=0; i<S;i++){
    matrix[0][i] = 0;
    matrix[i][0] = 0;
    matrix[S-1][i] = 0;
    matrix[i][S-1] = 0;
  }
  int placa_1_y = int((L/2 - d/2)/h);
  int placa_2_y = int((L/2 + d/2)/h);
  int placas_x_1 = int((L/2-l/2)/h);
  int placas_x_2 = int((L/2+l/2)/h);
  for(int i = placas_x_1;i<placas_x_2;i++){
    matrix[placa_1_y][i] = V0/2;
    matrix[placa_2_y][i] = -V0/2;
  }
}
int translate_distance_to_index(float distance){
  int placa_1_y = int((L/2 - d/2)/h);
  int placa_2_y = int((L/2 + d/2)/h);

}
class ElectricField{
public:
  float x;
  float y;
}
int main(int argc, char const *argv[]) {
  float potential[S][S];
  initialize(potential);
  set_boundary_conditions(potential);
  for(int iter =0;iter<N;iter++){
    if(iter % 1000 == 0){
      cout << iter << "/" << N << endl;
    }
    int i,k;
    #pragma omp parallel for private(i,k)
    for( i = 1;i<S-1;i++){
      for( k=1;k<S-1;k++){
        potential[i][k] = 0.25*(potential[i+1][k]+potential[i-1][k]+potential[i][k+1]+potential[i][k-1]);
      }
      set_boundary_conditions(potential);
    }
  }
  ofstream initial_conds;
  initial_conds.open("initial_conds.dat");
  for(int i = 0;i<S;i++){
    for(int k=0;k<S;k++){
      initial_conds << potential[i][k] << " ";
    }
    initial_conds << 0 << endl;
  }
  initial_conds.close();

  ElectricField electricfield[S][S];
  for(i = 1;i<S-1;i++){
    for( k=1;k<S-1;k++){
      electricfield[i][k].x = -(potential[i+1][k] - potential[i-1][k])/(2*h);
      electricfield[i][k].y = -(potential[i][k+1] - potential[i][k-1])/(2*h);
    }
  }

  return 0;
}
