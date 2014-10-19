#ifndef __TREE_SHOW_H__
#define __TREE_SHOW_H__


/*显示树的节点,树的高度最多是6,节点的key值最多是两位数.显示的样式如下图所示:

                                |------------------------------20------------------------------|
                                |                                                              |
                |--------------15--------------|                                |--------------30--------------|
                |                              |                                |                              |
        |------14------|                |------16------|                |------25------|                |------40------| */
int tree_show(tree_node_t *pnode,int depth);












#endif



/*

                                |------------------------------NN------------------------------|
                                |                                                              |
                |--------------NN--------------|                                |--------------NN--------------|
                |                              |                                |                              |
        |------NN------|                |------NN------|                |------NN------|                |------NN------|
        |              |                |              |                |              |                |              |
    |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|        |--NN--|
    |      |        |      |        |      |        |      |        |      |        |      |        |      |        |      |
   NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN      NN
  |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |    |  |
 NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN  NN
 ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||
NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN

                                                               64
                               32                                                              96
               16                              48                              80                              112
*/

