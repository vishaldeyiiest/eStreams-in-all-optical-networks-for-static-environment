#include <bits/stdc++.h>
using namespace std;
char path_file[100] = "../paths/nsfnet/gstream/4.txt";
char test[100] = "../testing/nsfnet10/1.txt";
typedef vector<vector<int> > vvi;
#define FLR 1
#define BLR 0

int reject = 0;

void display(vector<int> a)
{
	for(uint i = 0; i < a.size(); i++)
		cout<<a[i]<<" ";
	cout<<"\n";
}

vector<int> get_primary(int src, int dest)
{
	ifstream fp(path_file);
	string line;
	vvi a;
	while(getline(fp,line))
	{
		stringstream is(line);
		vector<int> path;
		int n;
		while(is >> n)
		{
			path.push_back(n);
		}
		if(path.front() == src && path.back() == dest)
			a.push_back(path);
	}
	return a[0];
}

vector<int> get_backup(int src, int dest, int p, int q)
{
	ifstream fp(path_file);
	string line;
	vvi a;
	vector<int> chosen;
	while(getline(fp,line))
	{
		stringstream is(line);
		vector<int> path;
		int n;
		while(is >> n)
		{
			path.push_back(n);
		}
		if(path.front() == src && path.back() == dest)
			a.push_back(path);
	}
	for(unsigned int i = 0; i < a.size(); i++)
	{
		int flag = 0;
		//display(a[i]);
		for(unsigned int j = 0; j < a[i].size()-1; j++)
		{
			if(a[i][j] == p && a[i][j+1] == q)
				flag = 1;
		}
		if(flag == 0)
		{
			//display(a[i]);
			return a[i];
			break;
		} 
	}
	return chosen;
}

vvi get_backup_set(vector<int> p)
{
	vvi back;
	//int a, b;
	for(unsigned int i = 0; i < p.size()-1; i++)
	{
		vvi temp;
		uint m = INT_MAX, k = 0;
		for(uint j = i; j < p.size()-1; j++)
		{
			temp.push_back(get_backup(p[i], p[j+1], p[j], p[j+1]));
		}
		for(uint j = 0; j < temp.size(); j++)
		{
			printf("Available backup for %d-%d link failure: ", p[i], p[i+1]);
			display(temp[j]);
			if(m > temp[j].size() && temp[j].size() != 0)
				k = j;
		}
		if(!temp[k].empty())
			back.push_back(temp[k]);
		else
			reject++;
	}
	return back;
}

vector<int> get_node_disjoint_backup(vector<int> p)
{
	ifstream fp(path_file);
	string line;
	vvi a;
	int c = -1;
	while(getline(fp,line))
	{
		stringstream is(line);
		vector<int> path;
		int n;
		while(is >> n)
		{
			path.push_back(n);
		}
		if(path.front() == p.front() && path.back() == p.back())
			a.push_back(path);
	}
	
	for(uint i = 0; i < a.size(); i++)
	{
		int flag = 0;
		for(uint j = 0; j < a[i].size(); j++)
		{
			for(uint k = 1; k < p.size()-1; k++)
			{
				if(a[i][j] == p[k])
				{
					flag = 1;
					break;
				}
			}
		}
		if(flag == 0)
		{
			c = i;
			break;
		}
	}
	if(c == -1)
	{
		reject++;
		return vector<int>();
	}
	return a[c];
}

int compute(vvi back)
{
	int gain = 0;	
	for(uint k = 0; k < back.size()-1; k++)
	{
		vector<int> a = back[k];
		vector<pair<int,int> > pairs;
		
		for(unsigned int i = 0; i < a.size()-1; i++)
			pairs.push_back(make_pair(a[i], a[i+1]));
	
		for(uint l = k+1; l < back.size(); l++)
		{
			vector<int> b = back[l];
			for(unsigned int i = 0; i < b.size()-1; i++)
			{
				//di[b[i]]++, o[b[i]]++;
				if (find(pairs.begin(), pairs.end(), make_pair(b[i], b[i+1])) != pairs.end())
					gain++;		
			}
		}
	}
	//cout<<gain<<endl;
	return gain;
}

int main()
{
	ifstream fp(test);
	//ofstream fo("../results.txt",ios_base::app);
	vector<pair<int, int> > set_pairs;
	string line;
	int count = 0;
	vvi ppath, path;
	while(getline(fp, line))
	{
		istringstream is(line);
		int n, x;
		pair<int, int> p;
		is >> n , is >> x;
		set_pairs.push_back(make_pair(n,x));
	}
	vector<pair<int, int> > served;
	/*bpath.push_back(check_longest(set_pairs));					//finding the longest backup path request
	path.push_back(check_longest(set_pairs));
	for(unsigned int i=0; i < bpath[0].size(); i++)					//storing served pairs
	{
		for(unsigned int j = i+1 ; j < bpath[0].size(); j++)
		{
			served.push_back(make_pair(bpath[0][i], bpath[0][j]));
		}
	}
	*/
	for(uint i = 0; i < set_pairs.size(); i++)
	{
		vvi bpath;
		ppath.push_back(get_primary(set_pairs[i].first, set_pairs[i].second));
		cout<<"Primary path: ";
		display(ppath[i]);
		//count += ppath[i].size()-1;
		int rej = 0;
		#if FLR
		bpath = get_backup_set(ppath[i]);
		if(bpath.size() < ppath[i].size()-1)
			rej = 1, cout<<"Rejected"<<endl;
		#endif
		/*
		#if BLR
		bpath.push_back(get_node_disjoint_backup(ppath[i]));
		#endif*/
		
		cout<<"Chosen Backup paths: \n";
		for(uint k = 0; k < bpath.size(); k++)
		{
			display(bpath[k]);
			if(rej == 0)
				count += bpath[k].size()-1;
		}
		count -= compute(bpath);
		cout<<"Count: "<<count<<endl;
	}
	printf("Total no of entries: %d\n", count); 
	printf("Rejected requests: %d\n", reject);
	return 0;
}
