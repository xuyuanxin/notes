



bst_ctrl *bst_create(char *bstname)
{
    bst_ctrl *temp;

	temp = (bst_ctrl *)malloc(sizeof(bst_ctrl));

	if(NULL == temp)
	{
	    printf("bst create fail!\r\n");
		return NULL;
	}

	temp->bst_root       = NULL;
	temp->bst_nodenums   = 0;

	(void)strncpy(temp->bst_name,bstname,BST_NAMELEN);
	temp->bst_name[BST_NAMELEN-1] = '\0';

	return temp;
}

int bst_insert(bst_ctrl *treectrl,int key)
{
}
