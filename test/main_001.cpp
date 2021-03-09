#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
#include <map>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <chrono>
#include <unistd.h>

#define rep(i,N) for(int i=0; i<(int)N;i++)
using namespace std;


int main(int argc,char *argv[]){
    int N=200;
    vector<vector<double>> ca(N, vector<double>(N)), ci(N, vector<double>(N)), ca_new(N, vector<double>(N)), ci_new(N, vector<double>(N));
   // double Da=1*pow(10, -5); test2
   // double Da=1*pow(10, -4); test3
    double Da=1.0*pow(10, -5);
    double Di=2.0*pow(10, -5);
//    double f=0.012;
    double f=0.04; //test5
    double k=0.06;
   // double B0=0.041;
   // double B1=0.041;
    double delx=0.1;
    double delt=0.1;
    int time=1000000;
    int step_save=1000;
    int k1=0;
    const double PI=3.14159265358979323846;
    double sigma=20;
    mt19937 rand(1);
    rep(i, N){
        rep(j, N){
     //       ca.at(i).at(j)=1/(2*PI*sigma)*exp(-0.5*(pow(i-N/2,2)+pow(j-N/2,2))/pow(sigma,2));
     //       ci.at(i).at(j)=1/(2*PI*sigma)*exp(-0.5*(pow(i-N/2,2)+pow(j-N/2,2))/pow(sigma,2));
            //ca.at(i).at(j)=(double)rand()/(double)(~0U)*0.1;
            //ci.at(i).at(j)=(double)rand()/(double)(~0U)*0.1;
            if(pow(i-N/2,2)+pow(j-N/2,2)<100){
                ca.at(i).at(j)=1.0;
                ci.at(i).at(j)=0.3;
            }
       }
    }
    rep(l,time){
        double ddcax,ddcix,ddcay,ddciy;
        rep(i,N){
            rep(j,N){
                if(i==N-1){
                    ddcax=(ca.at(0).at(j)-2*ca.at(i).at(j)+ca.at(i-1).at(j))/pow(delx,2);
                    ddcix=(ci.at(0).at(j)-2*ci.at(i).at(j)+ci.at(i-1).at(j))/pow(delx,2);
                }else if(i==0){
                    ddcax=(ca.at(i+1).at(j)-2*ca.at(i).at(j)+ca.at(N-1).at(j))/pow(delx,2);
                    ddcix=(ci.at(i+1).at(j)-2*ci.at(i).at(j)+ci.at(N-1).at(j))/pow(delx,2);
                }else if(j==N-1){
                    ddcay=(ca.at(i).at(0)-2*ca.at(i).at(j)+ca.at(i).at(j-1))/pow(delx,2);
                    ddciy=(ci.at(i).at(0)-2*ci.at(i).at(j)+ci.at(i).at(j-1))/pow(delx,2);
                }else if(j==0){
                    ddcay=(ca.at(i).at(j+1)-2*ca.at(i).at(j)+ca.at(i).at(N-1))/pow(delx,2);
                    ddciy=(ci.at(i).at(j+1)-2*ci.at(i).at(j)+ci.at(i).at(N-1))/pow(delx,2);
                }else{
                    ddcax=(ca.at(i+1).at(j)-2*ca.at(i).at(j)+ca.at(i-1).at(j))/pow(delx,2);
                    ddcix=(ci.at(i+1).at(j)-2*ci.at(i).at(j)+ci.at(i-1).at(j))/pow(delx,2);
                    ddcay=(ca.at(i).at(j+1)-2*ca.at(i).at(j)+ca.at(i).at(j-1))/pow(delx,2);
                    ddciy=(ci.at(i).at(j+1)-2*ci.at(i).at(j)+ci.at(i).at(j-1))/pow(delx,2);
                }
                // Gray-Scott model
                ca_new.at(i).at(j)=ca.at(i).at(j)+delt*(Da*ddcax+Da*ddcay-(f+k)*ca.at(i).at(j)+ci.at(i).at(j)*pow(ca.at(i).at(j),2));
                ci_new.at(i).at(j)=ci.at(i).at(j)+delt*(Di*ddcix+Di*ddciy+f-f*ca.at(i).at(j)-ci.at(i).at(j)*pow(ca.at(i).at(j),2));
            //    ca_new.at(i).at(j)=ca.at(i).at(j)+delt*(Da*ddcax+Da*ddcay-A1*ca.at(i).at(j)+A2*ci.at(i).at(j)*pow(ca.at(i).at(j),2)+B0-B1*ca.at(i).at(j));
            //    ci_new.at(i).at(j)=ci.at(i).at(j)+delt*(Di*ddcix+Di*ddciy+A1*ca.at(i).at(j)-A2*ci.at(i).at(j)*pow(ca.at(i).at(j),2));
                if(ca_new.at(i).at(j)<0){ca_new.at(i).at(j)=0;}
                if(ci_new.at(i).at(j)>1){ci_new.at(i).at(j)=1;}
                ci.at(i).at(j)=ci_new.at(i).at(j);
                ca.at(i).at(j)=ca_new.at(i).at(j);
            }
        }
        if(l%step_save==0){
            k1++;
            string sim="sim_001";
            ostringstream ss;
            ss << setw(4) << setfill('0') <<k1;
            string name(ss.str());
//            string file_out="/nfs/home/masashi/turing/data/2021.01.28/hist_"+sim+"_"+name+".dat";
            string file_out="/nfs/home/masashi/turing/test/test/hist_"+sim+"_"+name+".dat";
            ofstream outputfile(file_out.c_str());
            rep(i,N){
                rep(j,N){
                    outputfile << i*delx<<" "<<j*delx<<" "<<ca.at(i).at(j)<<" "<<ci.at(i).at(j)<<endl;
                }
            }
            outputfile.close();
        }
    }
    
    return 0;
}
