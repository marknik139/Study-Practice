#include <iostream>
#include "plant.h"
#include <cmath>
#include <string.h>
using namespace std;

#define Const 100

//Input default values of channels
void input_channels(int M[], int number_of_channels)
{
    for (int i=0; i<number_of_channels; i++)
    {
        cout<<"Define number of channel for measuring (1-6) >> ";
        cin>>M[i];
    }
}

//Measuring N values for k channels
void measure_X(int M[],double X[][Const], int raws, int columns)
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

void name(int ELEM)
{
    if (ELEM==1)
        cout<<"Temperature";
    if (ELEM==2)
        cout<<"Pressure";
    if (ELEM==3)
        cout<<"Wetness";
    if (ELEM==4 || ELEM==5 || ELEM==6)
        cout<<"Discret";
}

//Output for 2-x matrix
void output_measure(double X[][Const], int M[], int raws, int columns, string text, string text2)
{
    cout<<"\n";
    cout<<text<<"\n";
    for (int i=0; i<raws; i++)
    {
        cout<<M[i]<<") Measure \n";
        name(M[i]);
        cout<<"\n";
        for (int j=0; j<columns; j++)
        {
            if (text2=="C")
            {
                cout<<"\t"<<text2<<M[i]<<"="<<X[i][j]<<"\n";
            }
            else
            {
                cout<<"\t"<<text2<<"["<<M[i]<<"]["<<j+1<<"]="<<X[i][j]<<"\n";
            }
        }
    }
}

//Output for 1-x matrix
void output_average(double X[],int M[], int size_of_X, string text)
{
    cout<<"\n";
    cout<<text<<"\n";

    for (int i=0; i<size_of_X; i++)
    {
        cout<<M[i]<<") Average measure of ";
        name(M[i]);
        cout<<"\t"<<"X="<<X[i];
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

        int M[k];
        input_channels(M, k);

        double X[k][Const];
        measure_X(M, X, k, N);
        output_measure(X,M, k,N, "Measures of devices:", "X");

        double X_a[k];
        average(X, k, N, X_a);
        output_average(X_a,M, k, "Average values of measurements: ");

        double covar[k][Const];

        //Calculating covariations of all values
        for (int i=0; i<k; i++)
        {
            for (int j=0; j<k; j++)
            {
                covar[i][j]=covariation(X, X_a, i, j, N);
            }
        }

        output_measure(covar, M, k, k, "Covariations:", "C");

        cout<<"\n Repeat??? (1-YES; Anything-NO) >> ";
        cin>>continue_programm;

    }
    while (continue_programm==1);

    return 0;
}
