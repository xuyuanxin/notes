/*******************************************************************************
                      Longest Consecutive Sequence(Hard)
 *******************************************************************************
 Given an unsorted array of integers, find the length of the longest consecutive 
 elements sequence.
 
 For example,
 Given [100, 4, 200, 1, 3, 2],
 The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
 
 Your algorithm should run in O(n) complexity.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int longestConsecutive(vector<int> &num) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 利用map记录如下数据，对于每个数据value，它的映射值表示如下含义
 1 value是连续数据的最大值:映射值表示小于等于value的连续数字的个数
 3 其他情况:映射值表示大于等于value的连续数字的个数，例如
 
  99:4    表示大于等于 99的连续数字有4个
 100:3    表示大于等于100的连续数字有3个   
 101:2    表示大于等于101的连续数字有2个
 102:4    表示小于等于102的连续数字有4个
  
 ******************************************************************************/
#include <iostream>
#include <string>
#include <unordered_map> /* g++ -std=c++11 */
#include <vector>
	 
using namespace std;

class Solution 
{

public:
int longestConsecutive(vector<int> &num) 
{
    unordered_map<int, int> map;
    int size = num.size();
    int len = 1;

	for (int i = 0; i < size; i++) 
	{
        if (map.find(num[i]) != map.end()) continue;
		
        map[num[i]] = 1;

		if (map.find(num[i] - 1) != map.end()) 
		{
            len = max(len, mergeCluster(map, num[i] - 1, num[i]));
        }
		
        if (map.find(num[i] + 1) != map.end()) 
		{
            len = max(len, mergeCluster(map, num[i], num[i] + 1));
        }
	
		show_map(map,num[i]);
    }
	
    return size == 0 ? 0 : len;
}

private:
int mergeCluster(unordered_map<int, int> &map, int left, int right) 
{
    int upper = right + map[right] - 1;
    int lower = left - map[left] + 1;
    int length = upper - lower + 1;
    map[upper] = length;
    map[lower] = length;
    return length;
}

int show_map (unordered_map<int, int> &map,int val)
{
  std::cout << "insert : " << val << endl;
  
  for ( auto it = map.begin(); it != map.end(); ++it )
    std::cout << " " << it->first << ":" << it->second << endl;
  
  #if 0
  std::cout << "map's buckets contain:\n";
  for ( unsigned i = 0; i < map.bucket_count(); ++i) {
    std::cout << "bucket #" << i << " contains:";
    for ( auto local_it = map.begin(i); local_it!= map.end(i); ++local_it )
      std::cout << " " << local_it->first << ":" << local_it->second;
    std::cout << std::endl;
  }
  #endif

  return 0;
}


};

int lcs_test01()
{
    vector<int> v;
    int tmp,cnt=0;
    unordered_map<int, bool> used;
	Solution solu;

    v.push_back(4);
    v.push_back(4);
    v.push_back(4);

    for (unsigned int i = 0; i < v.size( ); i++)
        cout << v[i] << " " << endl;

	cout << "longest : " << solu.longestConsecutive(v);

}

int lcs_test02()
{
    vector<int> v;
    int tmp,cnt=0;
    unordered_map<int, bool> used;
	Solution solu;

    v.push_back(100);
    v.push_back(101);
    v.push_back(102);
    v.push_back(99);
    v.push_back(101);

    for (unsigned int i = 0; i < v.size( ); i++)
        cout << v[i] << " " << endl;

	cout << "longest : " << solu.longestConsecutive(v);

}



int main()
{
    lcs_test02();
}
