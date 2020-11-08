# Git的诞生

很多人都知道，Linus在1991年创建了开源的Linux，从此，Linux系统不断发展，已经成为最大的服务器系统软件了。Linus虽然创建了Linux，但Linux的壮大是靠全世界热心的志愿者参与的，这么多人在世界各地为Linux编写代码，那Linux的代码是如何管理的呢？事实是，在2002年以前，世界各地的志愿者把源代码文件通过diff的方式发给Linus，然后由Linus本人通过手工方式合并代码！

你也许会想，为什么Linus不把Linux代码放到版本控制系统里呢？不是有CVS、SVN这些免费的版本控制系统吗？因为Linus坚定地反对CVS和SVN，这些集中式的版本控制系统不但速度慢，而且必须联网才能使用。有一些商用的版本控制系统，虽然比CVS、SVN好用，但那是付费的，和Linux的开源精神不符。  

不过，到了2002年，Linux系统已经发展了十年了，代码库之大让Linus很难继续通过手工方式管理了，社区的弟兄们也对这种方式表达了强烈不满，于是Linus选择了一个商业的版本控制系统BitKeeper，BitKeeper的东家BitMover公司出于人道主义精神，授权Linux社区免费使用这个版本控制系统。安定团结的大好局面在2005年就被打破了，原因是Linux社区牛人聚集，不免沾染了一些梁山好汉的江湖习气。开发Samba的Andrew试图破解BitKeeper的协议（这么干的其实也不只他一个），被BitMover公司发现了（监控工作做得不错！），于是BitMover公司怒了，要收回Linux社区的免费使用权。

Linus可以向BitMover公司道个歉，保证以后严格管教弟兄们，嗯，这是不可能的。实际情况是这样的：Linus花了两周时间自己用C写了一个分布式版本控制系统，这就是Git！一个月之内，Linux系统的源码已经由Git管理了！牛是怎么定义的呢？大家可以体会一下。

Git迅速成为最流行的分布式版本控制系统，尤其是2008年，GitHub网站上线了，它为开源项目免费提供Git存储，无数开源项目开始迁移至GitHub，包括jQuery，PHP，Ruby等等。  

历史就是这么偶然，如果不是当年BitMover公司威胁Linux社区，可能现在我们就没有免费而超级好用的Git了。

# 基本概念，todo

 工作区、版本库(暂存区、版本库)、[远端仓库](https://blog.csdn.net/zy00000000001/article/details/70505150)，origin、upstream、local

## 工作区和暂存区

Git和其他版本控制系统如SVN的一个不同之处就是有暂存区的概念。

## 工作区（Working Directory）

就是你在电脑里能看到的目录，比如我的learngit文件夹就是一个工作区：          

## 版本库（Repository）

工作区有一个隐藏目录.git，这个不算工作区，而是Git的版本库。Git的版本库里存了很多东西，其中最重要的就是称为stage（或者叫index）的暂存区，还有Git为我们自动创建的第一个分支master，以及指向master的一个指针叫HEAD。

## 分支和HEAD

分支和HEAD的概念我们以后再讲。前面讲了我们把文件往Git版本库里添加的时候，是分两步执行的：第一步是用git add把文件添加进去，实际上就是把文件修改添加到暂存区；第二步是用git commit提交更改，实际上就是把暂存区的所有内容提交到当前分支。因为我们创建Git版本库时，Git自动为我们创建了唯一一个master分支，所以，现在，git commit就是往master分支上提交更改。你可以简单理解为，需要提交的文件修改通通放到暂存区，然后，一次性提交暂存区的所有修改。

********************************************************************************
# git使用基础场景

## git初始配置

1. 命令行启动 git bash here

2. 配置用户名和邮箱

   $ git config --global user.name "Your Name"
   $ git config --global user.email "email@example.com"

3. 命令行输入 ssh-keygen -t rsa -C "email@example.com"

   邮箱是你github的邮箱，按回车三次

4. 进入C:\Users\Administrator\.ssh\id_rsq.pub复制其内容

5. 进入github-setting-SSH AND GPG keys-New SSH KEY添加

   进入 [https://github.com/settings/keys](https://link.zhihu.com/?target=https%3A//github.com/settings/keys)。点击 New SSH key，你需要输入 Title 和 Key

6. 测试是否成功ssh -T [git@github.com](mailto:git@github.com)

   你可能会看到这样的提示，输入 yes。然后如果你看到 `Permission denied (publickey).` 就说明你失败了。如果你看到 `Hi FrankFang! You've successfully authenticated, but GitHub does not provide shell access.` 就说明你成功了！

## fork工程并修改推送

1. 点击 Fork ，他人的代码库(假设是test2工程)就会复制到自己的github账号上，

2. 从自己的账号下载代码(我的账号名是xuyuanxin)
   $ git clone https://github.com/xuyuanxin/test2.git
   
3. Configuring a remote for a fork
      $ git remote add upstream https://github.com/xyxin/test2.git
      git remote -v             查看一些信息
      
4. 获取原始代码库的更新
   
   git fetch upstream                 只是把原始代码库下载到本地，还没有合并到你的代码中
   git merge upstream/master   把原始代码合并到本地，本地修改不会丢失
   
5. Syncing your fork only updates your local copy of the repository. To update your fork on GitHub, you must push your changes.

## 下载代码库并修改上传

1. git clone https://github.com/xuyuanxin/notes    下载代码(生成一个notes目录)
2. git add .                                     添加文件到暂存区
   git add --all                                添加所有的文件到暂存区(从工作区到暂存区)
3. git commit -a -m "message"      提交到本地版本库
4. git push origin master                提交到github，origin是远程仓库，master是本地仓库
5. git pull                                        更新代码

# git基础命令

## 回退修改

git checkout -- filename  回退filename的修改(进入到文件所在的目录)

## 删除文件(进入当前目录下)

1 git rm filename
2 git commit filename

## 文件或文件夹重命名

1 git mv <旧文件名> <新文件名> 
2 commit即可



…or create a new repository on the command line

touch README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/xuyuanxin/myproj.git
git push -u origin master
…or push an existing repository from the command line


git remote add origin https://github.com/xuyuanxin/myproj.git
git push -u origin master

yuanxin@XW /C/Program Files (x86)/Git
$ git config --global user.name "yuanxin"

yuanxin@XW /C/Program Files (x86)/Git
$ git config --global user.email "xxuyuanxin@163.com"