#include <bits/stdc++.h>
using namespace std;
int gain = 0, m;
#define N 25
char *fpig = "../paths2/usanet20/igstream/pige1.txt";
char *fpath = "../paths2/usanet20/igstream/bpe1.txt";
int compute_gain(set<int> s, int x)
{
	set<int>::iterator it;
	int max = INT_MIN;
	for(it = s.begin(); it != s.end(); it++)
	{
		ifstream fp(fpig);
		string line;
		while(getline(fp, line))			
		{
			istringstream is(line);
			int a,b,c;
			is >> a, is >> b, is >> c;
			if(a == x && b == *it)
			{	
				if(c > max)
					max = c;
			}
		}
		fp.close();
	}
	return max;
}
int calc_gain(set<int> s, int x)
{
	
	int gain = 0;
	set<int>::iterator it;
	for(it = s.begin(); it != s.end(); it++)
	{
		ifstream fp(fpig);
		string line;
		while(getline(fp, line))			
		{
			istringstream is(line);
			int a,b,c;
			is >> a, is >> b, is >> c;
			if(a == x && b == *it)
			{	
				if(c == INT_MIN)
					return INT_MIN;
				else
					gain += c;
			}
		}
		fp.close();
	}
	return gain;
}
set<int> served;			
int get_nextvertex(set<int> s)					//get the next vertex having maximum gain
{
	ifstream fp(fpig);
	string line;
	int max = INT_MIN,v = -1;
	
	while(getline(fp, line))			
	{
		istringstream is(line);
		int a,b,c;
		is >> a, is >> b, is >> c;
		if(s.count(a) == 0 && served.count(a) == 0)
		{
			int temp = calc_gain(s, a);
			
			if(temp > max)
				max = temp, v = a;
		}
	}
	cout<<"Next vertex: "<<v<<endl;
	int t = compute_gain(s, v);
	if(t != INT_MIN)
		gain += t;
	fp.close();
	cout<<"Gain: "<<t<<endl;
	served.insert(v);
	return v;
}

void write(vector<int> p)
{
	for(unsigned int i = 0; i < p.size(); i++)
		cout<<p[i]<<" ";
	cout<<endl;
}

int main()
{
	ifstream fp(fpig);
	string line;
	clock_t t;
	//int k = ;
	int max = INT_MIN, s, d;
	set<int> Vk, V;

	for(int i = 0; i < N; i++)
		V.insert(i);
	t = clock();
	ifstream f(fpath);
	vector<vector<int> > a;
	while(getline(f,line))
	{
		istringstream is(line);
		vector<int> path;
		int n;
		while(is >> n)
			path.push_back(n);
	
		a.push_back(path);
	}
	f.close();
	//while(!V.empty()){
	while(getline(fp, line))			//get the edge which has maximum gain
	{
		istringstream is(line);
		int a,b,c;
		is >> a, is >> b, is >> c;
		if(c > max )
			max = c, s = a, d = b;
	}
	cout<<s<<" "<<d<<endl;
	cout<<"Gain: "<<max<<endl;
	gain += max;
	Vk.insert(s);
	served.insert(s);
	V.erase(find(V.begin(), V.end(), s));
	Vk.insert(d);
	served.insert(d);						//add the vertex to the served
	V.erase(find(V.begin(), V.end(), d));
	//while(Vk.size() != 3)
	int v = get_nextvertex(Vk);
	while(v != -1)
	{
		Vk.insert(v);
		V.erase(find(V.begin(), V.end(), v));
		v = get_nextvertex(Vk);
	}
	cout<<"Vertex set Size: "<<Vk.size()<<endl;
	fp.close();

	set<int>:: iterator iter;
	for(iter = Vk.begin(); iter != Vk.end(); iter++)
		write(a[*iter]);
	
	set<int> Vks;
	/*for(iter = V.begin(); iter != V.end(); iter++)
		cout<<*iter<<" ";*/
	while(!V.empty())		//serve the left requests	
	{
		
		Vks.clear();
		set<int>:: iterator iter;
		int index;	
		
		set <int>::iterator it;
		index = rand() % V.size();
		it = find(V.begin(), V.end(), index);
		if(it != V.end())
		{
			cout<<"Next vertex: "<<index<<endl;
			V.erase(it);
			Vks.insert(index); 	
			served.insert(index);
		}
		
		int t = get_nextvertex(Vks);
			if(t == -1)
			{
				//Vks.push_back(Vk[k]);
				break;
			}
			Vks.insert(t);
			V.erase(find(V.begin(), V.end(), t));
		set<int>:: iterator i;
		for(i = Vks.begin(); i != Vks.end(); i++)
			write(a[*i]);
		cout<<"Vertex set: "<<Vks.size()<<endl;
	}
	t = clock() - t;
	cout<<"Time: "<<((double)t)/CLOCKS_PER_SEC<<endl;
	cout<<"Total gain: "<<gain<<endl;
}
