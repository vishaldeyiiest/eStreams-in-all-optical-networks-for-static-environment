#include <bits/stdc++.h>
using namespace std;
int gain = 0, m;
char "../paths/usanet/gstream/2.txt";
void write(vector<vector<int> > p)
{
	ofstream fo("../paths2/usanet20/optimal/bpo1.txt",ios_base::app);
	
	for(unsigned int i = 0; i < p.size(); i++)
	{
		for(unsigned int j = 0; j < p[i].size(); j++)
			fo<<p[i][j]<<" ";
		fo<<endl;
	}
}

int compute_gain1(vector<int> a, vector<int> b)
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
			if((b[j] != a[i] && b[j+1] == a[i+1]) || (b[j] == a[i] && b[j+1] != a[i+1]))
				gain = INT_MIN;
			
		}
	}
	//cout<<gain<<endl;
	return gain;
}
	
void make_bp()
{	
	ifstream f("../testing/usanet20/1.txt");
	string line;
	
	while(getline(f, line))
	{
		istringstream is(line);
		int src, dest;
		//pair<int, int> p;
		is >> src , is >>dest;
		
			ifstream fp();
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
			
			//cout<<x<<endl;
			write(a);
	}		
	f.close();
}

void make_pig()
{
	
	ofstream fo("../paths2/usanet25/optimal1/pigo1.txt");
	string line;
	ifstream fp("../paths2/usanet25/optimal1/bpo1.txt");			//optimal pig
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
				fo<<i<<" "<<j<<" "<<compute_gain1(a[i], a[j])<<endl;
		}
	}
	fp.close();		
	fo.close();
}

int compute_gain(set<int> s, int x)
{
	set<int>::iterator it;
	int max = INT_MIN;
	for(it = s.begin(); it != s.end(); it++)
	{
		ifstream fp("../paths2/usanet25/optimal1/pigo1.txt");
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
		ifstream fp("../paths2/usanet25/optimal1/pigo1.txt");
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
				{
					gain += c;
				}
			}
		}
		fp.close();
	}
	return gain;
}


void display(vector<int> p)
{
	for(unsigned int i = 0; i < p.size(); i++)
		cout<<p[i]<<" ";
	cout<<endl;
}

bool check(int p, int q)
{
	ifstream f("../paths2/usanet25/optimal1/bpo1.txt");
	vector<vector<int> > a;
	vector<int> b, c;
	string line;
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
	b = a[p], c = a[q];
	//display(b),display(c);
	if(b.front() == c.front() && b.back() == c.back())
		return false;
	return true;
}

set<int> served;			
int get_nextvertex(set<int> s)					//get the next vertex having maximum gain
{
	ifstream fp("../paths2/usanet25/optimal1/pigo1.txt");
	string line;
	int max = INT_MIN,v = -1;
	
	while(getline(fp, line))			
	{
		istringstream is(line);
		int a,b,c;
		is >> a, is >> b, is >> c;
		if(s.count(a) == 0 && served.count(a) == 0 && served.count(b) == 0 && check(a,b) == true) 
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

pair<int, int> get_nexttwo(set<int> V)
{
	ifstream fp("../paths2/usanet25/optimal1/pigo1.txt");
	string line;
	int max = INT_MIN, s, d;
	while(getline(fp, line))			//get the edge which has maximum gain
	{
		istringstream is(line);
		int a,b,c;
		is >> a, is >> b, is >> c;
		if(c > max && V.count(a) == 1 && V.count(b) == 1 && check(a,b))
			max = c, s = a, d = b;
	}
	if(max != INT_MIN)
	{
		cout<<s<<" "<<d<<endl;
		cout<<"Gain: "<<max<<endl;
		gain += max;
		return make_pair(s, d);
	}
	return make_pair(0,0);
}

int main()
{
	make_bp();
	make_pig();
	#if 1
	ifstream fp("../paths2/usanet25/optimal1/pigo1.txt");
	string line;
	clock_t t;
	
	set<int> V;

	for(unsigned int i = 0; i < 50; i++)
		V.insert(i);
	t = clock();
	
	while(served.size() <= 25)
	{
		set<int> Vks;
		Vks.clear();
		int index;
		pair<int,int> temp = make_pair(0,0);
		if(served.size() != 19)
			temp = get_nexttwo(V);
		if(temp != make_pair(0,0))
		{
			Vks.insert(temp.first);
			served.insert(temp.first);
			V.erase(find(V.begin(), V.end(), temp.first));
			Vks.insert(temp.second);
			served.insert(temp.second);						//add the vertex to the served
			V.erase(find(V.begin(), V.end(), temp.second));
		}
		else
		{
			index = rand()/(double)INT_MAX*V.size();	
			set <int>::iterator it;
			it = find(V.begin(), V.end(), index);
			if(it != V.end())
			{
				cout<<"Next vertex: "<<index<<endl;
				V.erase(it);
				Vks.insert(index); 	
				served.insert(index);
			}
		}
		int t = get_nextvertex(Vks);
		if(served.size() == 25)
			break;
		while(t != -1)
		{
			Vks.insert(t);
			served.insert(t);
			V.erase(find(V.begin(), V.end(), t));
			if(served.size() == 25)
				break;
			t = get_nextvertex(Vks);

		}
		
		cout<<endl;
		//write(served);
		//cout<<"Vertex set: "<<Vks.size()<<endl;
	}
	set<int>:: iterator it;
		for(it = served.begin(); it != served.end(); it++)
			cout<<*it<<" ";
	t = clock() - t;
	cout<<"Time: "<<((double)t)/CLOCKS_PER_SEC<<endl;
	cout<<"Total gain: "<<gain<<endl;
	#endif
}
