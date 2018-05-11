/*
  g++ -o cuerda.o cuerda.cpp
*/
#include <iostream>
#include <cmath>
using namespace std;
#include <fstream>
float c = sqrt(40./10);
const int L =100;
int t0 = 0;
const int tf = 200;
int dx=1;
const int PI = 3.1415926589793238;
const int N = 200;
float dt = float(tf-t0)/N;
float D = 0.5;
float sigma = 1e-3*L*L;
float times[N];
void other_initial_condition(float matrix[N][L]){
  for(int i=0;i<N;i++){
    for(int k=0;k<L;k++){
      matrix[i][k]=0;
    }
  }
  for(int k=0;k<L;k++){
    matrix[0][k] = (1./(sqrt(2*PI)*sigma))*exp(-0.5*pow(k-50,2)/(sigma*sigma));
  }
}
void set_rho(float arr[N], float k){
  for(int i=0;i<N;i++){
    arr[i] = 0.5 + pow(times[N], k);
  }
}
void init_times( float arr[N], float tmin, float tmax, int len){
  for(int i=0;i<N;i++){
    float step = (tmax-tmin)/len;
    arr[i] = tmin+i*step;
  }
}
int main(int argc, char const *argv[]) {
  init_times(times, t0, tf, N);
  float rho[N];
  set_rho(rho, 1);
  float string_history[N][L];
  other_initial_condition(string_history);
  int t=t0+dt;
  for(t=t0+1*dt;t<N;t+=dt){
    float A = 1*PI*rho[t]/1.;
    float B=A;
    for(int x = 1; x<L-1;x++){
      string_history[t][x] = dt*(A*string_history[t-1][x] + (x*B + D/x)*(string_history[t-1][x+1]-string_history[t-1][x])/dx +D*(string_history[t-1][x+1]-2*string_history[t-1][x] + string_history[t-1][x-1])/(dx*dx))+string_history[t-1][x];
    }
  }
  ofstream string;
  string.open("Pcosa.dat");
  for(int i = 0;i<tf;i++){
    for(int k=0;k<L;k++){
      string << string_history[i][k] << " ";
    }
    string << 0 << endl;
  }
  string.close();


  return 0;
}
