#include <iostream>
#include <string>
#include <unordered_map> /* g++ -std=c++11 */
#include <vector>

using namespace std;

int unordered_map_test1(const vector<int> &num) 
{
    int tmp,cnt=0;
	
    unordered_map<int, bool> used;
	
    for (auto i : num) 
	{
	    used[i] = false;
		cout << "i = "<< i << endl;
		cnt++;
    }

	
	cout << "cnt = "<< cnt << endl;

    return 0;
}

int unordered_map_test2( )
{
    vector<int> v;
    int tmp,cnt=0;
    unordered_map<int, bool> used;
	
    v.push_back(6);
    v.push_back(9);
    v.push_back(1);
	
	unordered_map_test1(v);

    return 0;
}

int unordered_map_test3()
{
    std::unordered_map<std::string, int> months;
    months["january"] = 31;
    months["february"] = 28;
    months["march"] = 31;
    months["april"] = 30;
    months["may"] = 31;
    months["june"] = 30;
    months["july"] = 31;
    months["august"] = 31;
    months["september"] = 30;
    months["october"] = 31;
    months["november"] = 30;
    months["december"] = 31;
    std::cout << "september -> " << months["september"] << std::endl;
    std::cout << "april     -> " << months["april"] << std::endl;
    std::cout << "december  -> " << months["december"] << std::endl;
    std::cout << "february  -> " << months["february"] << std::endl;
    return 0;
}

/* unordered_map::begin/end examples */
int unordered_map_test04 ()
{
  std::unordered_map<std::string,std::string> mymap;
  mymap = 
  {{"01","aa"},{"02","bb"},{"03","cc"},{"04","dd"},
   {"05","ee"},{"06","ff"},{"07","gg"},{"08","hh"},
   {"09","ii"},{"10","jj"},{"11","kk"},{"12","ll"},
   {"13","mm"}};

  std::cout << "mymap contains:" << endl;
  
  for ( auto it = mymap.begin(); it != mymap.end(); ++it )
    std::cout << " " << it->first << ":" << it->second << endl;
  
  std::cout << std::endl;

  std::cout << "mymap's buckets contain:\n";
  for ( unsigned i = 0; i < mymap.bucket_count(); ++i) {
    std::cout << "bucket #" << i << " contains:";
    for ( auto local_it = mymap.begin(i); local_it!= mymap.end(i); ++local_it )
      std::cout << " " << local_it->first << ":" << local_it->second;
    std::cout << std::endl;
  }

  return 0;
}

/* unordered_map::find/size examples*/
int unordered_map_test05 ()
{
  std::unordered_map<std::string,double> mymap = {
     {"a",5.4},
     {"b",6.1},
     {"c",5.9} };

  std::cout << "mymap.size() is " << mymap.size() << std::endl;

  std::string input;
  std::cout << "who? ";
  getline (std::cin,input);

  std::unordered_map<std::string,double>::const_iterator got = mymap.find (input);

  if ( got == mymap.end() )
    std::cout << "not found";
  else
    std::cout << got->first << " is " << got->second;

  std::cout << std::endl;

  return 0;
}

int main()
{
	unordered_map_test05();


	return 0;
}
