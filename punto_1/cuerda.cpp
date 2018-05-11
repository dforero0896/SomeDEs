/*
g++ -fopenmp -o cuerda.o cuerda.cpp `gsl-config --cflags --libs`
*/
#include <iostream>
#include <cmath>
using namespace std;
#include <gsl/gsl_matrix.h>
#include <omp.h>
#include <fstream>
float c = sqrt(40./10);
const int L =100;
int t0 = 0;
const int tf = 200;
int dx=1;
const int N = 200;
float dt = float(tf-t0)/N;
void initial_condition(float matrix[N][L]){
  for(int i=0;i<N;i++){
    for(int k=0;k<L;k++){
      matrix[i][k]=0;
    }
  }
  for(int k=0;k<L;k++){
    if(k<0.8*L){
      matrix[0][k] = 1.25*float(k)/L;
    }
    else{
      matrix[0][k] = 5-5*float(k)/L;
    }
  }
}
void other_initial_condition(float matrix[N][L]){
  for(int i=0;i<N;i++){
    for(int k=0;k<L;k++){
      matrix[i][k]=0;
    }
  }
  for(int k=0;k<L;k++){
    matrix[0][k] = exp(-pow(k-50,2)/(1e-3*L*L));
  }
}
int main(int argc, char const *argv[]) {
  float string_history[N][L];
  other_initial_condition(string_history);
  int t=t0+dt;
  for(int x = 1; x<L-1;x++){
    string_history[t][x] = (dt*dt/(dx*dx*c*c))*(string_history[t-1][x+1] - 2*string_history[t-1][x] + string_history[t-1][x-1]) + 2*string_history[t-1][x] - string_history[t-1][x];
  }
  for(t=t0+2*dt;t<N;t++){
    for(int x = 1; x<L-1;x++){
      string_history[t][x] = (dt*dt/(dx*dx*c*c))*(string_history[t-1][x+1] - 2*string_history[t-1][x] + string_history[t-1][x-1]) + 2*string_history[t-1][x] - string_history[t-2][x];
    }
  }
  ofstream string;
  string.open("string.dat");
  for(int i = 0;i<tf;i++){
    for(int k=0;k<L;k++){
      string << string_history[i][k] << " ";
    }
    string << 0 << endl;
  }
  string.close();


  return 0;
}
