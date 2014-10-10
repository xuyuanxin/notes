   
void sort_bubble(int array[],int ele_num)
{
    int i,j,temp;

	for(i = 0; i < ele_num; i++)
	{
	    for(j = ele_num-1; j > i; j--)
	    {
	        if(array[j] < array[j-1])
	        {
	            temp = array[j];
				array[j] = array[j-1];
				array[j-1] = temp;
	        }
	    }
	}
}


















