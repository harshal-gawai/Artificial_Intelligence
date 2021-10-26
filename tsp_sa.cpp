#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#define INITIAL_T 999999999999999
#define T_UPDATE_FACTOR 0.999
using namespace	std;

class TSP_SA 
{
	private:
		int n;
		double **edge;
		int *path_current, *path_new, *path_best;
		double T;

	public:
		TSP_SA(double ** edge, int n)
		{
			srand((unsigned int) time(NULL));

			this->n = n;
			this->edge = edge;
			T = INITIAL_T;
			
			//Initialisations of path arrays
			path_new = new int[n+1];
			path_new[0] = path_new[n]=0;
			for(int i = 1;i < n;i++)
				path_new[i] = i;
			path_current = new int[n+1];
			path_current[0] = path_current[n]=0;
			for(int i = 1;i < n;i++)
				path_current[i] = i;
			path_best = new int[n+1];
			path_best[0] = path_best[n]=0;
			for(int i = 1;i < n;i++)
				path_best[i] = i;
			
		}
		void twoEdgeExchange(int a, int b, int* path_new)
		{
			if(a > b)
			{
				int tmp = a;
				a = b;
				b = tmp;
			}
			int i, j;
			i = a;
			j = b;
			//reverse the substring
			while(i<j)
			{
				swapNodes(i,j,path_new);
				i++;
				j--;
			}
		}
		void swapNodes(int a, int b, int* path_new)
		{
			int tmp = path_new[a];
			path_new[a] = path_new[b];
			path_new[b] = tmp;
		}
		void begin()
		{
			srand((unsigned int)time(NULL));
			int ctr = 0;
			int k = 1;
			while(1)
			{
				int itr=100;
				
				while(--itr)
				{
					for(int i=1;i<n;i++)
						path_new[i]=path_current[i];
					int a = (rand()%(n-1))+1;
					int b = (rand()%(n-1))+1;
					twoEdgeExchange(a, b, path_new);
					double delta_E = getPathCost(path_new) - getPathCost(path_current);
					double r = (double) (rand()/ (double) RAND_MAX);
					double p = 1/(1+ pow(M_E, (delta_E/T)));
					if(p > r)
						for(int i=1;i<n;i++)
							path_current[i]=path_new[i];
				
					if(getPathCost(path_new) < getPathCost(path_best))
					{
						for(int i=1;i<n;i++)
							path_best[i]=path_new[i];
						printBestPath();
						ctr = 0;
					}
					else
						ctr++;
				}
				T *= T_UPDATE_FACTOR;
				if(ctr > 1000000)
				{
					T = k*10*n;
					k += k;
					if(T>INITIAL_T)
					{
						T = INITIAL_T;
						k = 1;
					}
					ctr = 0 ;
					// cout<<"\nchange T "<<T<<endl;
				}
			}
		}
		void printBestPath()
		{
			cout<<"Path: "<<getPathCost(path_best)<<endl;
			for(int i=0;i<n;i++)
				cout<<path_best[i]+1<<" ";
			cout<<endl;
		}

		double getPathCost(int* path)
		{
			double cost = 0;
			for(int i = 0;i < n;i++)
			{
				cost += edge[path[i]][path[i+1]];
			}
			return cost;
		}
};


int main()
{
	
	int n, dist_type;
	string s;
	cin>>s;
	if(s=="euclidean")
		dist_type = 0;
	else
		dist_type = 1;
	cin>>n;
	double *x_coordinates, *y_coordinates, **edge;
	x_coordinates = new double[n];	
	y_coordinates = new double[n];

	edge = new double*[n];
	for(int i=0;i<n;i++)
	{
		edge[i]	= new double[n];
	}

	for(int i=0;i<n;i++)
	{
		cin>>x_coordinates[i]>>y_coordinates[i];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>edge[i][j];
		}
	}
	TSP_SA tsp(edge,n);
	tsp.begin();
	return 0;
}

