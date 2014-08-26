/*
1033. To Fill or Not to Fill (25)

With highways available, driving a car from Hangzhou to any other city is easy. But since the tank capacity of a car is limited, we have to find gas stations on the way from time to time. Different gas station may give different price. You are asked to carefully design the cheapest route to go.

Input Specification:

Each input file contains one test case. For each case, the first line contains 4 positive numbers: Cmax (<= 100), the maximum capacity of the tank; D (<=30000), the distance between Hangzhou and the destination city; Davg (<=20), the average distance per unit gas that the car can run; and N (<= 500), the total number of gas stations. Then N lines follow, each contains a pair of non-negative numbers: Pi, the unit gas price, and Di (<=D), the distance between this station and Hangzhou, for i=1,...N. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print the cheapest price in a line, accurate up to 2 decimal places. It is assumed that the tank is empty at the beginning. If it is impossible to reach the destination, print "The maximum travel distance = X" where X is the maximum possible distance the car can run, accurate up to 2 decimal places.

Sample Input 1:
50 1300 12 8
6.00 1250
7.00 600
7.00 150
7.10 0
7.20 200
7.50 400
7.30 1000
6.85 300
Sample Output 1:
749.17
Sample Input 2:
50 1300 12 2
7.10 0
7.00 600
Sample Output 2:
The maximum travel distance = 1200.00

*/


// This is a greedy algorithm

#include <stdio.h>
#include <stdlib.h>
#define MAX_VALUE 1000000000.0

typedef struct GasStation
{
    double price;
    int distance;
} GasStation;

int cmp(const void* a, const void* b)
{
    return (*(GasStation*)a).distance - (*(GasStation*)b).distance;
}

int main()
{
    double capacityMax;
    double destDistance;
    double disPerGas;
    int n;
    scanf("%lf %lf %lf %d", &capacityMax, &destDistance, &disPerGas, &n);

    GasStation stations[n];
    int i;
    for(i = 0; i < n; i++)
    {
        scanf("%lf %d", &stations[i].price, &stations[i].distance);
    }

    qsort(stations, n, sizeof(GasStation), cmp);

    // #0
    // hangzhou has no gas station
    if(stations[0].distance != 0)
    {
        printf("The maximum travel distance = 0.00");
        return 0;
    }

    int currentGS = 0; 			// we are now at the current gs
    double currentCapacity = 0.0; 	// the tank has currentCapacity before adding gas in currentGS
    double cost = 0.0; 				// the current cost of gas
    double maxDistance = capacityMax * disPerGas; // the max distance a car can run when the tank is full
    int id = 1;
    while(id <= n)
    {
        double max = maxDistance + stations[currentGS].distance; // the max point a car car run to from current distance

        // #1
        int flag = 0;
        int pos = -1;
        double price = MAX_VALUE;
        while(id < n && stations[id].distance <= max)   // the gas station between currentGS and max
        {
            if(stations[id].price < stations[currentGS].price)   // find the first gs whose price is less than current gs
            {
                int dis = stations[id].distance - stations[currentGS].distance; // distance between current gs and the lower price gs
                double gas2Use = dis / disPerGas; // gas used to run from current gs to gs id
                if(currentCapacity >= gas2Use)     // tank has enough gas, so just use it and don't add at currentGS
                {
                    currentCapacity -= gas2Use;    // update the current capacity
                }
                else
                {
                    double gas2Add = gas2Use - currentCapacity;
                    currentCapacity = 0.0; // run out of gas
                    cost += stations[currentGS].price * gas2Add; // add cost
                }
                currentGS = id; // now we are at the station id
                flag = 1;
                id++; // start from the next gas station
                break;
            }
            else if(stations[id].price <= price)    // find the most lower price
            {
                pos = id;
                price = stations[id].price;
            }
            id++;
        }

        if(flag == 1)
        {
            continue;
        }

        // #2
        if(destDistance <= max)   // the dest is within the currentGS and max
        {
            double dis = destDistance - stations[currentGS].distance;
            double gas2Use = dis / disPerGas;
            if(currentCapacity < gas2Use)
            {
                double gas2Add = gas2Use - currentCapacity;
                cost += stations[currentGS].price * gas2Add;
            }
            printf("%.2f\n", cost);
            return 0;
        }

        // #3
        if(pos == -1)
        {
            printf("The maximum travel distance = %.2f\n", max);
            return 0;
        }
        else     // #4
        {
            double dis = stations[pos].distance - stations[currentGS].distance;
            double gas2Add = capacityMax - currentCapacity; // the gas we need to add in this station
            currentCapacity = capacityMax; // fill the tank to the max
            cost += stations[currentGS].price * gas2Add;
            currentCapacity -= dis / disPerGas; // then run to the pos, use dis / disPerGas
            currentGS = pos;
            id = currentGS + 1;
        }

    }

    return 0;
}

