# 数据结构类型、数据存储结构、基本数据类型
*所有的数据结构类型都可以用不同的存储类型(连续)来实现*

* 数据4种逻辑结构:
    1. 集合结构:数据元素之间没有任何关系.
    2. 线性结构:数据元素之间定义了线性关系.1对1
    3. 树形结构:数据元素之间定义了层次关系 1对多.
    4. 图状结构:数据元素之间定义了网状关系 多对多.

* 常见的4种数据存储结构:
    1. 顺序存储结构:借助数据元素之间的相对位置来表示元素之间的逻辑结构.（vector动态数组、 deque双端队列、stack栈容器、queue队列容器）
    2. 链式存储结构:借助数据元素之间的元素的指针表示数组元素的逻辑结构.
    3. 散列存储结构:顺序存储+散列.
    4. 索引存储结构:顺序存储+索引.
  >顺序结构和链接结构适用在内存结构中。索引结构和散列结构适用在外存与内存交互结构。

* 基本数据类型
  >不同的编程语言定义了不同的基本数据类型，其实就是单位数据的访问方式而已。

>基本数据类型是单位数据的大小与结构，数据结构类型（数据逻辑结构）就是单位数据之间的关系，数据存储结构是数据在内存中存储方式
# 一、数据结构(链表、栈、队列，哈希表，树，图)的基本操作{增，删，改，查，遍历(暴力、技巧遍历)，排序}
  0. 数组：数据元素之间没有任何关系，可以使用集合，也能使用顺序表，这时一般选用实现简单的数据结构。数组就经常用来表示这种结构；同时数组又经常用来表示线性结构。
  1. 集合结构 
     * 哈希表
  2. 线性结构 
     * 顺序表
     * 栈
     * 队列
  3. 树形结构
     * 二叉树
     * 二叉搜索树
     * 堆
  3. 图形结构
     * 有向图与无向图
     * 有环图与无环图
  
  #### 数组
    整数、字符、整数数组、字符数组、字符串的基本操作,多维数组

    415. 字符串相加 (大数之和)
    5. 最长回文子串：字符串（一维字符数组）的子串技巧遍历
    11. 盛最多水的容器:一维数组的子串遍历
    
  #### 链表：
  ###### 单链表
    92 反转链表 II：单链表的迭代
  ###### 双向链表
  ###### 循环链表
    
  #### 栈（基于数组实现、基于链表实现）
    leetcode 20. 有效的括号 https://leetcode-cn.com/problems/valid-parentheses/
    leetcode 71. 简化路径：https://leetcode-cn.com/problems/simplify-path/
    leetcode 84. 柱状图中最大的矩形. https://leetcode-cn.com/problems/largest-rectangle-in-histogram/
    leetcode 496. 下一个更大元素 I https://leetcode-cn.com/problems/next-greater-element-i/
    leetcode 503. 下一个更大元素 II https://leetcode-cn.com/problems/next-greater-element-ii/
  #### 队列（基于数组实现、基于链表实现）：
  
 
  #### 优先队列
  
  #### 哈希表
    leetcode 609. 在系统中查找重复文件 https://leetcode-cn.com/problems/find-duplicate-file-in-system/
    leetcode 49. 字母异位词分组 https://leetcode-cn.com/problems/group-anagrams/
    leetcode 1. 两数之和 https://leetcode-cn.com/problems/two-sum/
    leetcode 771. 宝石与石头. https://leetcode-cn.com/problems/jewels-and-stones/
    leetcode 49. 字母异位词分组 https://leetcode-cn.com/problems/group-anagrams/
  #### 树：
  
  ###### 二叉树
 
  ###### 字典树

  #### 图：
  
  #### 数据结构设计：系统设计类题目，增删改查接口。
    leetcode 355. 设计推特https://leetcode-cn.com/problems/design-twitter/
    leetcode 1845. 座位预约管理系统
    
    https://oj.rnd.huawei.com/problems/2217/details
    https://oj.rnd.huawei.com/problems/2218/details
    https://oj.rnd.huawei.com/problems/2236/details
    https://oj.rnd.huawei.com/problems/2237/details


# 二、算法思想： 排序、二分查找、滑动窗口、双指针、递归、分治、搜索（DFS、BFS、回溯算法），贪心、动态规划。
  #### 排序
     
  
  #### 二分
 
  #### 滑动窗口：
    1004

  #### 双指针
 
   >将计算过程仅与「两端点」相关的称为「双指针」，将计算过程与「两端点表示的区间」相关的称为「滑动窗口」
   >「滑动窗口」是固定大小的，「双指针」是不固定大小的；「滑动窗口」一定是同向移动的，「双指针」可以相向移动。
 
 
  #### 递归
  
  #### 回溯：
    遍历类方法：寻找满足条件的分支，执行到结束条件后回退一步。
    46 全排列：多叉树结构的回溯
    51 N皇后：二维数组结构的回溯

  #### DFS(深度优先搜索)：
    遍历类方法：将走过的节点标记减少重复计算
    200 岛屿数量: 二维数组的遍历，深度优先和广度优先都行。 但是广度优先算法需要再提供一个队列
    695 岛屿的最大面积:二维数组的遍历，深度优先和广度优先都行。 但是广度优先算法需要再提供一个队列
    130 被围绕的区域:二维数组的遍历
    417 太平洋大西洋水流问题
    547 省份数量

  #### BFS(广度优先搜索)：一般都是求最少步数
    遍历类方法：使用队列（数组或者链表实现）将每一步需要遍历的节点的加入队列；将走过的节点标记可以减少重复计算
    279 完全平方数：
    127 单词接龙：
    752 打开转盘锁:

  #### 贪心：
  > 局部解就是最优解
 
  ###### 一维数组的贪心
  ###### 树的贪心
  

  #### 动态规划：
  >最优子结构

  ###### 一维数组的dp:
    
  ###### 树形结构的dp 
    124 二叉树中的最大路径和

# 三、高级数据结构：
  #### 前缀树
  
  
# 四、系列类型题
  #### 木棍切割问题

  #### 背包九讲：
    https://blog.csdn.net/pdsu_congshuang/article/details/79823015?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-4.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-4.control
  #### 打家劫舍
    leetcode 121. 买卖股票的最佳时机	   
    leetcode 122. 买卖股票的最佳时机 II   
    leetcode 123. 买卖股票的最佳时机 III	   
    leetcode 188. 买卖股票的最佳时机 IV   
    leetcode 309. 最佳买卖股票时机含冷冻期	   
    leetcode 714. 买卖股票的最佳时机含手续费   
    https://leetcode-cn.com/circle/article/qiAgHn/
    https://labuladong.github.io/algo/1/12/
  #### 换零钱

  #### 全排列 、集合、子集问题
       78. 子集
       90. 子集 II
       77. 组合
       39. 组合总和
       40. 组合总和 II
       216. 组合总和 III
       46. 全排列
       47. 全排列 II
       
       15. 三数之和
       18. 四数之和
     
       https://labuladong.github.io/algo/4/30/106/
     
     
  #### 重叠空间


# 刷题参考
  * 按照这个大佬的总结刷一遍题
  https://github.com/liweiwei1419/LeetCode-Solutions-in-Good-Style
  
  * 刷题笔记
  https://github.com/SharingSource/LogicStack-LeetCode/wiki/%E8%AE%B0%E5%BF%86%E5%8C%96%E6%90%9C%E7%B4%A2

  * 题目汇总
  https://leetcode-cn.com/u/feeenedumplings/
  
  * 宫水三叶题目汇总
  https://github.com/SharingSource/LogicStack-LeetCode/wiki

  * leetcode 刷题总结
  https://github.com/youngyangyang04/leetcode-master
