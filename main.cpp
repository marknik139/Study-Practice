#include <iostream>
#include "plant.h"
#include <cmath>
#include <string.h>
using namespace std;

#define Const 100

//Input default values of channels
void input_channels(double M[], int size)
{
    for (int i=0; i<size; i++)
    {
        cout<<"Define M"<<i+1<<" (Channel "<<i+1<<") >> ";
        cin>>M[i];
    }
}

//Measuring N values for k channels
void measure_X(double M[],double X[][Const], int raws, int columns)
{
    Plant plant;
    plant_init(plant);

    for (int i=0; i<raws; i++)
    {
        for (int j=0; j<columns; j++)
        {
            X[i][j]=plant_measure(M[i], plant);
        }
    }

}

//Calculation the average of N values
void average(double X[][Const],  int raws, int columns, double Result[])
{
    double temp;

    for (int i=0; i<raws; i++)
    {
        temp=0;

        for (int j=0; j<columns; j++)
        {
            temp+=X[i][j];
        }
        Result[i]=temp/columns;
    }
}

//Calculation the covariation between X[i] and X[j]
double covariation(double X[][Const], double X_a[], int i, int j, int N)
{
    long double temp=0;

    for (int k=0; k<N; k++)
    {
        temp+=(X[i][k]-X_a[i])*(X[j][k]-X_a[j]);
    }
    temp=(static_cast<long double>(temp)/N);
    return temp;
}

//Output for 2-x matrix
void output_measure(double X[][Const], int raws, int columns, string text, string text2)
{
    cout<<"\n";
    cout<<text<<"\n";
    for (int i=0; i<raws; i++)
    {
        cout<<i+1<<") Measure \n";
        for (int j=0; j<columns; j++)
        {
            cout<<"\t"<<text2<<"["<<i+1<<"]["<<j+1<<"]="<<X[i][j];
            cout<<"\n";
        }
    }
}

//Output for 1-x matrix
void output_average(double X[],int size_of_X, string text)
{
    cout<<"\n";
    cout<<text<<"\n";

    for (int i=0; i<size_of_X; i++)
    {
        cout<<i+1<<") Average measure";
        cout<<"\t"<<"X["<<i+1<<"]="<<X[i];
        cout<<"\n";
    }
}

int main()
{
    int continue_programm=1;

    do
    {

        Plant plant;
        plant_init(plant);

        int k;
        cout<<"Define k (number of channels) >> ";
        cin>>k;

        int N;
        cout<<"Define N (Cycle number) >> ";
        cin>>N;

        double M[k];
        input_channels(M, k);

        double X[k][Const];
        measure_X(M, X, k, N);
        output_measure(X,k, N, "Measures of devices:", "X");

        double X_a[k];
        average(X, k, N, X_a);
        output_average(X_a, k, "Average values of measurements: ");

        double covar[k][Const];

        //Calculating covariations of all values
        for (int i=0; i<k; i++)
        {
            for (int j=0; j<k; j++)
            {
                covar[i][j]=covariation(X, X_a, i, j, N);
            }
        }

        output_measure(covar, k, k, "Covariations:", "C");

        cout<<"\n Repeat??? (1-YES; Anything-NO) >> ";
        cin>>continue_programm;

    }
    while (continue_programm==1);

    return 0;
}
