# Git�ĵ���

�ܶ��˶�֪����Linus��1991�괴���˿�Դ��Linux���Ӵˣ�Linuxϵͳ���Ϸ�չ���Ѿ���Ϊ���ķ�����ϵͳ����ˡ�Linus��Ȼ������Linux����Linux��׳���ǿ�ȫ�������ĵ�־Ը�߲���ģ���ô�������������ΪLinux��д���룬��Linux�Ĵ�������ι�����أ���ʵ�ǣ���2002����ǰ��������ص�־Ը�߰�Դ�����ļ�ͨ��diff�ķ�ʽ����Linus��Ȼ����Linus����ͨ���ֹ���ʽ�ϲ����룡

��Ҳ����룬ΪʲôLinus����Linux����ŵ��汾����ϵͳ���أ�������CVS��SVN��Щ��ѵİ汾����ϵͳ����ΪLinus�ᶨ�ط���CVS��SVN����Щ����ʽ�İ汾����ϵͳ�����ٶ��������ұ�����������ʹ�á���һЩ���õİ汾����ϵͳ����Ȼ��CVS��SVN���ã������Ǹ��ѵģ���Linux�Ŀ�Դ���񲻷���  

����������2002�꣬Linuxϵͳ�Ѿ���չ��ʮ���ˣ������֮����Linus���Ѽ���ͨ���ֹ���ʽ�����ˣ������ĵ�����Ҳ�����ַ�ʽ�����ǿ�Ҳ���������Linusѡ����һ����ҵ�İ汾����ϵͳBitKeeper��BitKeeper�Ķ���BitMover��˾�����˵����徫����ȨLinux�������ʹ������汾����ϵͳ�������Ž�Ĵ�þ�����2005��ͱ������ˣ�ԭ����Linux����ţ�˾ۼ�������մȾ��һЩ��ɽ�ú��Ľ���ϰ��������Samba��Andrew��ͼ�ƽ�BitKeeper��Э�飨��ô�ɵ���ʵҲ��ֻ��һ��������BitMover��˾�����ˣ���ع������ò�����������BitMover��˾ŭ�ˣ�Ҫ�ջ�Linux���������ʹ��Ȩ��

Linus������BitMover��˾����Ǹ����֤�Ժ��ϸ�̵ܽ����ǣ��ţ����ǲ����ܵġ�ʵ������������ģ�Linus��������ʱ���Լ���Cд��һ���ֲ�ʽ�汾����ϵͳ�������Git��һ����֮�ڣ�Linuxϵͳ��Դ���Ѿ���Git�����ˣ�ţ����ô������أ���ҿ������һ�¡�

GitѸ�ٳ�Ϊ�����еķֲ�ʽ�汾����ϵͳ��������2008�꣬GitHub��վ�����ˣ���Ϊ��Դ��Ŀ����ṩGit�洢��������Դ��Ŀ��ʼǨ����GitHub������jQuery��PHP��Ruby�ȵȡ�  

��ʷ������ôżȻ��������ǵ���BitMover��˾��вLinux�����������������Ǿ�û����Ѷ��������õ�Git�ˡ�

# �������todo

 ���������汾��(�ݴ������汾��)��[Զ�˲ֿ�](https://blog.csdn.net/zy00000000001/article/details/70505150)��origin��upstream��local

## ���������ݴ���

Git�������汾����ϵͳ��SVN��һ����֮ͬ���������ݴ����ĸ��

## ��������Working Directory��

�������ڵ������ܿ�����Ŀ¼�������ҵ�learngit�ļ��о���һ����������          

## �汾�⣨Repository��

��������һ������Ŀ¼.git��������㹤����������Git�İ汾�⡣Git�İ汾������˺ܶණ������������Ҫ�ľ��ǳ�Ϊstage�����߽�index�����ݴ���������GitΪ�����Զ������ĵ�һ����֧master���Լ�ָ��master��һ��ָ���HEAD��

## ��֧��HEAD

��֧��HEAD�ĸ��������Ժ��ٽ���ǰ�潲�����ǰ��ļ���Git�汾������ӵ�ʱ���Ƿ�����ִ�еģ���һ������git add���ļ���ӽ�ȥ��ʵ���Ͼ��ǰ��ļ��޸���ӵ��ݴ������ڶ�������git commit�ύ���ģ�ʵ���Ͼ��ǰ��ݴ��������������ύ����ǰ��֧����Ϊ���Ǵ���Git�汾��ʱ��Git�Զ�Ϊ���Ǵ�����Ψһһ��master��֧�����ԣ����ڣ�git commit������master��֧���ύ���ġ�����Լ����Ϊ����Ҫ�ύ���ļ��޸�ͨͨ�ŵ��ݴ�����Ȼ��һ�����ύ�ݴ����������޸ġ�

********************************************************************************
# gitʹ�û�������

## git��ʼ����

1. ���������� git bash here

2. �����û���������

   $ git config --global user.name "Your Name"
   $ git config --global user.email "email@example.com"

3. ���������� ssh-keygen -t rsa -C "email@example.com"

   ��������github�����䣬���س�����

4. ����C:\Users\Administrator\.ssh\id_rsq.pub����������

5. ����github-setting-SSH AND GPG keys-New SSH KEY���

   ���� [https://github.com/settings/keys](https://link.zhihu.com/?target=https%3A//github.com/settings/keys)����� New SSH key������Ҫ���� Title �� Key

6. �����Ƿ�ɹ�ssh -T [git@github.com](mailto:git@github.com)

   ����ܻῴ����������ʾ������ yes��Ȼ������㿴�� `Permission denied (publickey).` ��˵����ʧ���ˡ�����㿴�� `Hi FrankFang! You've successfully authenticated, but GitHub does not provide shell access.` ��˵����ɹ��ˣ�

## fork���̲��޸�����

1. ��� Fork �����˵Ĵ����(������test2����)�ͻḴ�Ƶ��Լ���github�˺��ϣ�

2. ���Լ����˺����ش���(�ҵ��˺�����xuyuanxin)
   $ git clone https://github.com/xuyuanxin/test2.git
   
3. Configuring a remote for a fork
      $ git remote add upstream https://github.com/xyxin/test2.git
      git remote -v             �鿴һЩ��Ϣ
      
4. ��ȡԭʼ�����ĸ���
   
   git fetch upstream                 ֻ�ǰ�ԭʼ��������ص����أ���û�кϲ�����Ĵ�����
   git merge upstream/master   ��ԭʼ����ϲ������أ������޸Ĳ��ᶪʧ
   
5. Syncing your fork only updates your local copy of the repository. To update your fork on GitHub, you must push your changes.

## ���ش���Ⲣ�޸��ϴ�

1. git clone https://github.com/xuyuanxin/notes    ���ش���(����һ��notesĿ¼)
2. git add .                                     ����ļ����ݴ���
   git add --all                                ������е��ļ����ݴ���(�ӹ��������ݴ���)
3. git commit -a -m "message"      �ύ�����ذ汾��
4. git push origin master                �ύ��github��origin��Զ�ֿ̲⣬master�Ǳ��زֿ�
5. git pull                                        ���´���

# git��������

## �����޸�

git checkout -- filename  ����filename���޸�(���뵽�ļ����ڵ�Ŀ¼)

## ɾ���ļ�(���뵱ǰĿ¼��)

1 git rm filename
2 git commit filename

## �ļ����ļ���������

1 git mv <���ļ���> <���ļ���> 
2 commit����



��or create a new repository on the command line

touch README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/xuyuanxin/myproj.git
git push -u origin master
��or push an existing repository from the command line


git remote add origin https://github.com/xuyuanxin/myproj.git
git push -u origin master

yuanxin@XW /C/Program Files (x86)/Git
$ git config --global user.name "yuanxin"

yuanxin@XW /C/Program Files (x86)/Git
$ git config --global user.email "xxuyuanxin@163.com"