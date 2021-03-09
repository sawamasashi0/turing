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
    int sample=1;
    //int r_div=30;
    //int th_div=20;

    int r_div=200;
    int th_div=360;
    string sim="sim_072";
    int num=96;
    vector<double> r_list(r_div*th_div);
    vector<double> th_list(r_div*th_div);
    vector<double> average1(r_div*th_div);
    vector<double> average2(r_div*th_div);
    rep(i,num){
        ostringstream ss;
        ss << setw(3) << setfill('0') <<i+1;
        string name=(ss.str());
        rep(j,sample){
            ostringstream ss;
            ss << setw(5) << setfill('0') <<j+1;
            string name1(ss.str());
            string input_dir="/nfs/home/masashi/colloid/ensemble/"+sim+"/"+name+"/dpd_eng/";
            //input_dir=input_dir+"vel_"+name1+".dat";
            //input_dir=input_dir+"tem_"+name1+".dat";
            input_dir=input_dir+"hist_"+name1+".dat";
            //input_dir=input_dir+"pres_th_"+name1+".dat";
            cout <<input_dir<<endl;
            ifstream in(input_dir.c_str());
            cin.rdbuf(in.rdbuf());
            rep(k,r_div*th_div){
                double r,th,x1,x2;
                //cin>>r>>th>>x1>>x2;
                cin>>r>>th>>x1;
                r_list.at(k)=r;
                th_list.at(k)=th;
                average1.at(k)+=x1;
               // average2.at(k)+=x2;
               // cout <<average1.at(k);
            }

        }
    }

    //string file_out="/nfs/home/masashi/colloid/data/2020.11.12/vel_"+sim+"_non.dat";
    //string file_out="/nfs/home/masashi/colloid/data/2020.05.25/pres_th_"+sim+".dat";
    //string file_out="/nfs/home/masashi/colloid/data/2020.11.12/tem_"+sim+".dat";
    string file_out="/nfs/home/masashi/colloid/data/2020.11.12/hist_"+sim+".dat";
    ofstream outputfile(file_out.c_str());
    rep(k,r_div*th_div){
        average1.at(k)/=sample*num;
        //average2.at(k)/=sample*num;
        //outputfile << r_list.at(k)<<" "<<th_list.at(k)<<" "<<average1.at(k)<<" "<<average2.at(k)<<endl;
        outputfile << r_list.at(k)<<" "<<th_list.at(k)<<" "<<average1.at(k)<<endl;//<<" "<<average2.at(k)<<endl;
    }
    outputfile.close();
    return 0;
}
