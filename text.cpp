#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

struct Node
{
    double x;
    double y;
};

float Gzz(Node *stations, Node *agents, int k)
{
    double min = sqrt(pow(stations[0].x - agents[0].x, 2) + pow(stations[0].y - agents[0].y, 2));
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (abs(stations[i].x - agents[j].x) > min || abs(stations[i].y - agents[j].y) > min)
                continue;
            else
            {
                double distance = sqrt(pow(stations[i].x - agents[j].x, 2) + pow(stations[i].y - agents[j].y, 2));
                if (min > distance)
                    min = distance;
            }
        }
    }
    return min;
}

int main()
{
    int i;
    cin >> i;
    for (int i0 = 0; i0 < i; i0++)
    {
        int k;
        cin >> k;
        Node *stations = new Node[k];
        Node *agents = new Node[k];
        for (int n = 0; n < k; n++)
        {
            cin >> stations[n].x >> stations[n].y;
        }
        for (int n = 0; n < k; n++)
        {
            cin >> agents[n].x >> agents[n].y;
        }
        double min = Gzz(stations, agents, k);
        cout << fixed << setprecision(3) << min << endl;

        // Remember to free the allocated memory
        delete[] stations;
        delete[] agents;
    }
    return 0;
}
