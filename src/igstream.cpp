#include <bits/stdc++.h>
using namespace std;

void display(vector<int> a)									//display the vector
{
	ofstream fo("../paths2/nsfnet100/igstream/bpe1.txt",ios_base::app);
	for(unsigned int i = 0; i < a.size(); i++)
		cout<<a[i]<<" ",fo<<a[i]<<" ";
	cout<<endl;
	fo << endl;
}

vector<int> get_path(int src,int dest)			//choosing the longest path as backup path
{
	ifstream fp("../paths/nsfnet/gstream/5.txt");
	string line;
	vector<vector<int> > a;
	while(getline(fp, line))
	{
		stringstream is(line);
		int n;
		vector<int> path;
		while(is >> n)
		{
			path.push_back(n);
		}

		if(path.front() == src && path.back() == dest)
			a.push_back(path);
			//cout<<path.size()<<" ";
	}

	unsigned int max=0,c;
	for(unsigned int r = 0; r < a.size(); r++)
		if(max < a[r].size())
			max=a[r].size(),c=r;
	
	if(max == 0)
		return vector<int>();
	return a[c];
}

pair<int, int> longest;
vector<int> check_longest(vector<pair<int,int> > r)			//finding the request giving the longest backup path
{
	vector<int> p,pm;
	unsigned int max = 0;
	for(unsigned int i=0; i < r.size(); i++)
	{
		p = get_path(r[i].first, r[i].second);
		if (p.size() > max)
		{
			max = p.size();
			pm = p;
			longest=make_pair(r[i].first,r[i].second);
		}
	}
	cout<<"Request first served: "<<longest.first<<" "<<longest.second<<endl;
	cout<<"Longest backup path:";
	display(pm);
	return pm;
}

void update(vector<pair<int, int> > sp, vector<pair<int,int> > served, pair<int,int> x)			//update the served and remaining requests
{
	
	vector<pair<int,int> >::iterator it = find(sp.begin(), sp.end(), x);
	if(it != sp.end())
		sp.erase(it);
	served.push_back(x);
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
			if(b[j] == a[i] && b[j+1] != a[i+1])
				return INT_MIN;
		}
	}
	//cout<<gain<<endl;
	return gain;
}

pair<vector<int>,int> find_contain(vector<vector<int> > bpath, vector<vector<int> > path)			//find if both src and dest are already present
{
	int max = INT_MIN;
	pair<vector<int>,int> t;
	for(unsigned int i = 0; i < bpath.size(); i++)
	{
		for(unsigned int j = 0; j < path.size(); j++)
		{
			int g = compute_gain(bpath[i], path[j]);
			//cout<<g<<" ";
			/*if(i == 0)
			{
				if(find(bpath[i].begin(), bpath[i].end(), path[j].back()) != bpath[i].end())
					g = INT_MIN;
			}*/
			if(g == INT_MIN)
				return make_pair(vector<int> (), INT_MIN);
			if(g > max)
			{
				max = g;
				t = make_pair(path[j], max);
			}
		}
	}
	
	return t;
}

pair<vector<int>,int> get_maxcomp_path(pair<int, int> p, vector<vector<int> > bpath)	//return most compatible path
{
	ifstream fp("../paths/nsfnet/gstream/5.txt");
	string line;
	vector<vector<int> > a;
	while(getline(fp, line))
	{
		stringstream is(line);
		int n;
		vector<int> path;
		while(is >> n)
		{
			path.push_back(n);
		}
		if(path.front() == p.first && path.back() == p.second)
			a.push_back(path);
	}
	pair<vector<int>,int> x = find_contain(bpath, a);
	return x;
}

int gain = 0;

pair<vector<int>, pair<int,int> > next_request(vector<pair<int,int> > set_pairs, vector<vector<int> > bpath)				//next request giving more gain
{
	pair<int,int> temp = make_pair(0,0);
	pair<vector<int>,int> x,t;
	int max = 0;
	for(unsigned int i = 0; i < set_pairs.size(); i++)
	{
		x = get_maxcomp_path(set_pairs[i], bpath);	
		if (x.second > max)
		{
			max = x.second;
			t = x;
			temp = set_pairs[i];
		}
	}
	if(!t.first.empty())
	{
		gain += max;
		//bpath.push_back(t.first);
		cout<<"Request: "<<temp.first<<" "<<temp.second<<endl;
		cout<<"Backup path: ",display(t.first);
		cout<<"Gain: "<<max<<endl;
	}
	else
	{
		t.first = vector<int> ();
		temp = make_pair(0,0);
	}
	return make_pair(t.first,temp);

}
vector<vector<int> > bpath;
pair<pair<int,int>,pair<int,int> > first_tworequests(vector<pair<int,int> >  set_pairs)
{
	vector<vector<int> > a;
	for(unsigned int i = 0; i < set_pairs.size(); i++)
	{
		ifstream fp("../paths/nsfnet/gstream/5.txt");
		string line;
	
		while(getline(fp, line))
		{
			stringstream is(line);
			int n;
			vector<int> path;
			while(is >> n)
			path.push_back(n);
			if(path.front() == set_pairs[i].first && path.back() == set_pairs[i].second)
				a.push_back(path);
		}
		fp.close();
	}
	int max = 0, p, q;
	for(unsigned int i = 0; i < a.size()-1; i++)
	{
		//display(a[i]);
			for(unsigned int j = i+1; j < a.size(); j++)
			{
			int t = compute_gain(a[i], a[j]);
			if(t >= max)
			{
				max = t;
				p = i, q =j;
			}
		}
	}
	if(max != 0 && a[p] != a[q])
	{
		cout<<"Requests: "<<a[p].front()<<" "<<a[p].back()<<" and "<<a[q].front()<<" "<<a[q].back()<<endl;
		cout<<"Gain: "<<max<<endl;
		gain += max;
		display(a[p]);
		display(a[q]);
		bpath.push_back(a[p]);
		bpath.push_back(a[q]);
		return make_pair(make_pair(a[p].front(),a[p].back()),make_pair(a[q].front(),a[q].back()));
	}
	cout<<"None can be found"<<endl;
	return make_pair(make_pair(0,0),make_pair(0,0));
}

int main()
{
	ifstream fp("../testing/nsfnet100/1.txt");
	vector<pair<int, int> > set_pairs, served;
	string line;
	
	while(getline(fp, line))
	{
		istringstream is(line);
		int n, x;
		pair<int, int> p;
		is >> n , is >> x;
		set_pairs.push_back(make_pair(n,x));
	}
	//set_pairs.pop_back();
	clock_t t;
	t = clock();
	while(!set_pairs.empty())
	{
		bpath.clear();
		
		pair<pair<int,int>,pair<int,int> > t = first_tworequests(set_pairs);
		pair<int,int> p = t.first;
		pair<int,int> q = t.second;
		if(p != q)
		{
			set_pairs.erase(find(set_pairs.begin(), set_pairs.end(), p));
			set_pairs.erase(find(set_pairs.begin(), set_pairs.end(), q));
		}
		else
		{
			bpath.push_back(check_longest(set_pairs));
			served.push_back(longest);
			vector<pair<int,int> >::iterator it = find(set_pairs.begin(), set_pairs.end(), longest);
			if(it != set_pairs.end())
				set_pairs.erase(it);
		}
		pair<vector<int>, pair<int,int> > temp = next_request(set_pairs, bpath);
		pair<int, int> x = temp.second;
		while(!temp.first.empty())
		{
		//update(set_pairs, served, x);
			vector<pair<int,int> >::iterator it = find(set_pairs.begin(), set_pairs.end(), x);
			if(it != set_pairs.end())
				set_pairs.erase(it);
			served.push_back(x);
			bpath.push_back(temp.first);
			temp = next_request(set_pairs, bpath);
			x = temp.second;
		}
	}		
	# if 0
	for(unsigned int i = 0; i < bpath.size(); i++)
	{
		for(unsigned int j = 0; j < bpath[i].size(); j++)
			cout<<bpath[i][j]<<" ";
		cout<<endl;
	}
	#endif
	t = clock() - t ;
	cout<<"Total gain: "<<gain<<endl;
	cout<<"Time: "<<((double)t)/CLOCKS_PER_SEC<<endl;
}
	
