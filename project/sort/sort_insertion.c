/************************************************************************************
 1 复杂度 n*n  n小时比较有效
 ************************************************************************************
 举个例子:屋子里有10个椅子，屋外有10个人，个子高低不同。
 第1个人(称为p1):
    进来直接做第1个椅子上。
 第2个人(称为p2):
    走到第2个椅子旁边，如果发现自己比p1高，直接坐下。如果没有p1高，就让p1坐在第2个椅
    子上，自己做第1个椅子上。
 第3个人:
    走到第3个椅子旁边，如果发现自己比前面那个人高，直接坐下。否则按照第二个人的做法找
    到合适自己的位置坐下。
 ......
************************************************************************************/
   

/*
 1 Insert array[j] into the sorted sequence array[0] ... array[j-1]
 2 ele_num >= 1
 3 small to big
*/  
void sort_insertion(int array[],int ele_num)
{
    int i,j,key;
	for(j = 1; j < ele_num; j++){
        key = array[j];
		i = j - 1;
		while(i >= 0 && array[i] > key){
		    array[i+1] = array[i];
			i--;
		}
		array[i+1] = key;
	}
}

void sort_insertion_withgap(int array[],int nums,int gap)
{
    int i,j,key;
	for(i = gap; i < nums; i++){
		key = array[i];
		j = i - gap;
		while((j >= 0) && (array[j] > key)){
			array[j+gap] = array[j];
			j -= gap;
		}
		array[j+gap] = key;
	}	
}

void sort_insertion_v2(int array[],int nums)
{
	sort_insertion_withgap(array,nums,1);
}

