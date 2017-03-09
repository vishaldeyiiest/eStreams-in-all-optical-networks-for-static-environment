#include <bits/stdc++.h>
using namespace std;
char *fpig = "../paths2/usanet20/igstream/pige1.txt";
char *fbp = "../paths2/usanet20/igstream/bpe1.txt";
void write(vector<int> p)
{
	ofstream fo(fbp, ios_base::app);
	
	//for(unsigned int i = 0; i < p.size(); i++)
	{
		for(unsigned int j = 0; j < p.size(); j++)
			fo<<p[j]<<" ";
		fo<<endl;
	}
}

int compute_gain(vector<int> a, vector<int> b)
{
	
	int gain = 0;
	int di[47], o[47];
	memset(di, 0, 47);
	memset(o, 0, 47);
	vector<pair<int,int> > pairs;
	for(unsigned int i = 0; i < a.size()-1; i++)
	{
		di[a[i]] = o[a[i]] = 1; 
		pairs.push_back(make_pair(a[i], a[i+1]));
	}
	for(unsigned int i = 0; i < b.size()-1; i++)
	{
		di[b[i]]++, o[b[i]]++;
		if (find(pairs.begin(), pairs.end(), make_pair(b[i], b[i+1])) != pairs.end())
			gain++;
			
	}
	for(unsigned int i = 0; i < a.size()-1; i++)
	{
		for(unsigned int j = 0; j < b.size()-1; j++)
		{
			if((b[j] == a[i] && b[j+1] != a[i+1])|| (b[j] == a[i] && b[j+1] != a[i+1]))
				gain = INT_MIN;
		}
	}
	//cout<<gain<<endl;
	return gain;
}
	
void make_bp()
{
	
	ifstream f("../testing/nsfnet10/1.txt");
	string line;
	
	while(getline(f, line))
	{
		istringstream is(line);
		int src, dest;
		//pair<int, int> p;
		is >> src , is >>dest;
		
			ifstream fp("../paths/nsfnet/gstream/3.txt");
			vector<vector<int> > a;
			while(getline(fp,line))
			{
				istringstream is(line);
				vector<int> path;
				int n;
				while(is >> n)
					path.push_back(n);
				if(path.front() == src && path.back() == dest)
					a.push_back(path);
			}
			fp.close();
			int x = rand() % a.size();
			cout<<x<<endl;
			write(a[x]);
			
	}
	f.close();
}

void make_pig()
{
	
	ofstream fo(fpig);
	string line;
	ifstream fp(fbp);			//optimal pig
	//ifstream fp("../bpi.txt");
	vector<vector<int> > a;
	while(getline(fp,line))
	{
		istringstream is(line);
		vector<int> path;
		int n;
		while(is >> n)
			path.push_back(n);

		a.push_back(path);
	}
	
	for(unsigned int i = 0; i < a.size(); i++)
	{
		for(unsigned int j = 0; j < a.size(); j++)
		{
			if(j != i)
				fo<<i<<" "<<j<<" "<<compute_gain(a[i], a[j])<<endl;
		}
	}
	fp.close();		
	fo.close();
}

int main()
{
	clock_t t;
	t = clock();
	//make_bp();
	make_pig();
	t = clock() - t;
	cout<<"Time: "<<((double)t)/CLOCKS_PER_SEC<<endl;
}
