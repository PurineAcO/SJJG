# 数据结构复用代码

> **作者：** 航空科学与工程学院 流体力学研究所

---

## 目录

- [链表](#链表)
- [队列和堆栈](#队列和堆栈)
- [树和二叉树](#树和二叉树)
- [图](#图)
- [排序、查找](#排序查找)
- [附录：题目清单与分析](#附录题目清单与分析)

---

## 链表

1. **链表的定义方法**（*由于链表非常恶心一般不建议在很复杂的算法上使用*）

```c
typedef struct nodeptr {
  int data;
  struct nodeptr* next;
}* node;  // node 的性质是指针
```

2. **基于指针数组的查找加速**：一般可以用指针数组 `node nodelist[MAXN]={}` 来加快 `find` 的速度，使之变成 $O(1)$，但是根治的手段是使用双向链表，或者可以根据操作次数，来判断是否需要进行优化，*可见洛谷的 `B3631` 题*。

3. **链表的初始化**（建议使用）

```c
node initlist(int firstnum) {
  node head;
  // 分三步走：申请内存、写数据、写指针（单向链表是NULL）
  head = (node)malloc(sizeof(struct nodeptr));
  head->data = firstnum;
  head->next = NULL;
  nodelist[firstnum] = head; // 可选
  // 返回整个链表头指针p
  return head;
}
```

4. **链表的插入**，你需要先知道插入位置 `place` 是啥，会插入到该点*后面*

```c
void insert(node place, int newdata) {
  node thisdata;
  thisdata = (node)malloc(sizeof(struct nodeptr));
  thisdata->data = newdata;
  thisdata->next = place->next;
  place->next = thisdata;
  // nodelist[newdata] = thisdata; // 可选
}
```

5. **查找位置**，给出了两种实现，一是基于遍历的，二是基于指针数组的

```c
// 慢速方法
node find(node head, int target) {
  // 这里没有处理找不到的情况
  for (node fast = head; fast != NULL; fast = fast->next) {
  if (fast->data == target) {return fast;}}}
  // 快速方法，但是费内存。
node find(int target){return nodelist[target];}
```

6. **删除**，需要注意的点是删除的顺序，以及对头和尾的处理，此外，注意 `del_one` 是删除 `nowplace` *后面* 的元素。

```c
void del_one(node nowplace) {
  node temp = nowplace->next;
  if (temp == NULL) {return;}// 尾部特别处理
  nowplace->next = temp->next;
  free(temp);// 可选
}
```

`del_two` 给出了删除 `target` 所代表的*当前位置*的方法：

```c
node del_two(node head, int target) {
  // 处理头结点
  if (head->data == target) {
    node temp = head->next;
    free(head);
    return temp;}
  // 查找目标及其前驱
  node prev = head;node cur = head->next;
  while (cur != NULL && cur->data != target) {
    prev = cur;
    cur = cur->next;}
  // 删除 cur
  prev->next = cur->next;
  free(cur);
  return head;
}
```

7. **链表内容检查**（自测）

```c
void printlist(node head) {
  for (node p = head; p != NULL; p = p->next) {
    printf("%d ", p->data);}}
```

8. **循环链表**：多用于解决 Joseph 环问题（*洛谷 `U616683`*）

此种链表只需在执行 `init` 或者 `insert` 时将 `NULL` 修正为 `head` 即可，在执行删除时，需使用有前驱的方案 `del_two`，由于头结点只是一个入口，而没有其他特别性质，所以无需对头尾节点进行特殊处理。

对于可变步长的 Joseph 环问题，队列是更好的方式。对于等步长 $k$ 的 $n$ 个体 Joseph 问题，有递推公式 $f(1)=0,\ f(n) = (f(n-1)+k)\%n+1$

---

## 队列和堆栈

### 队列

参考练习题：*洛谷 `U306073` 即第二次作业 T1*，*注意开 `long long`*

1. **队列初始化**，这里 `info` 是目标类型

```c
info queue[MAXN]={};
int head;int cnt;int tail;
void initqueue(){
  head=0;tail=MAXN-1;cnt=0;}
```

2. **判空**，需说明判满是不必要的，都用循环队列，没有满的概念。

```c
int ifempty(){
  return (cnt==0 ? 1 : 0);}
```

3. **入队**

```c
void intoqueue(info item){
    tail = (tail+1)%MAXN;
    queue[tail] = item;
    cnt++;}
```

4. **出队**

```c
info outqueue(){
  info target = queue[head];
  head = (head+1)%MAXN;
  cnt--;return target;
}
```

### 栈

参考题目：*洛谷 `P1449`、`T364393` 对应第二次作业后缀表达式*

1. **栈的定义**

```c
int stack[MAXN] = {};int top;
```

2. **栈的初始化**，栈只需要栈顶 `top`

```c
void initstack() {top = -1;}
```

3. **判空**

```c
short ifempty(){
  return top==-1;
}
```

4. **进栈**，或者简写为 `stack[++top]`

```c
void push(int item) {
  top++;
  stack[top] = item;
}
```

5. **出栈**

```c
int pop() {
  return stack[top--];
}
```

---

## 树和二叉树

1. **基于数组存储**，此种方法看起来消耗内存很大，实际上对于 100 万个由 3 个 `int` 组成的结构体数组，占用空间仅为 11MB，远远小于评测系统要求，所以推荐使用这种方案。

```c
struct BTnode{int left;int data;int right;} node[MAXN]={};
```

2. **三种遍历**
   - 三种顺序的遍历这里均只给出递归写法，如果要迁移到链表上，只需把 `0` 换成 `NULL`，基于这一个条件，在写数组式二叉树时候，请将 `0` 位留空。
   - 三种遍历模式的区别在于何时处理自身，前序遍历总是优先处理自己，后序在访问左右都失败才处理自己，中序遍历则是在一侧访问失败后处理自己。

**前序遍历：**

```c
void preorder(int root){
  if(root==0){return;}
  process(root);
  preorder(node[root].left);
  preorder(node[root].right);
}
```

**后序遍历：**

```c
void aftorder(int root){
  if(root==0){return;}
  aftorder(node[root].left);
  aftorder(node[root].right);
  process(root);
}
```

**中序遍历：**

```c
void midorder(int root){
  if(root==0){return;}
  midorder(node[root].left);
  process(root);
  midorder(node[root].right);
}
```

> `process(root)` 指的是处理当前节点的逻辑。如果要求输出序列，一般可以是 `printf("%d",node[root].data);`

---

## 图

1. **图的存储**：图的存储依赖邻接表或者邻接矩阵，其中邻接矩阵是一种基于数组的方式，邻接表是基于链表的方式，一般如果 $n \le 100$ 可以尝试使用邻接矩阵，如果 $n \ge 500$ 则推荐使用邻接表。*重要提醒：本板子均假设图点序号从 1 开始*

### 基于邻接矩阵的图存储模式（*洛谷 `B3643`*）

```c
int graph[MAXN][MAXN]={};// 基于邻接矩阵的图表示法

void readgraph(int edgecnt){
// 这种记录"1"适用于无向权图，有权需存权，有向需明确方向，无向图邻接阵对称
    for(int i=1;i<=edgecnt;i++){
        int from,to;scanf("%d %d",&from,&to);
        graph[from][to]=1;graph[to][from]=1;}}

void printgraph(int nodecnt){// 检测图的内容
    for(int i=1;i<=nodecnt;i++){
        for(int j=1;j<=nodecnt;j++){printf("%d ",graph[i][j]);}
        printf("\n");}}
```

### 基于邻接表的图存储模式（以有向图为例），无向图则两次 `insertedge`

```c
typedef struct edger{
  int to;
  int weight;// 权重
  struct edger* next;}* edge;
  // 边的性质是指针

typedef struct noder{
  int data;
  struct edger* link;}node;
// 点的性质是结构体
node graph[MAXN]={};
```

```c
edge insertedge(int from,int to,int weight){
  // 在使用时，应该由graph[from].link来承接返回值否则无法插入边
    edge head = graph[from].link;edge p;
    edge e = (edge) malloc(sizeof(struct edger));
    e->to =to; e-> weight = weight; e->next = NULL;// 链表三步走
    if(head==NULL){head = e;return head;}
    for(p=head;p->next!=NULL;p = p->next);// 找到链表末尾
    p->next =e; return head;}

void printgraph(int nodecnt){// 检查图的内容
  for(int i=1;i<=nodecnt;i++){
      printf("node%d: ",i);
      for(edge p = graph[i].link;p!=NULL;p = p->next){
          printf("%d ",p->to);}
      printf("\n");}}
```

2. **DFS 深度优先**：如果要求从某个点开始进行遍历，请使用 `DFS`，如果遍历一个可能非联通的图，请使用 `travelDFS`，在每次使用 `DFS` 前都应确保 `visit` 全 `0`

```c
short visit[MAXN]={};

void DFS(int start){
// 从某个点开始进行DFS遍历
    edge p;visit[start]=1;printf("%d ",start);// 可自行更改处理逻辑
    for(p = graph[start].link;p!=NULL;p=p->next){
        if(visit[p->to]==0){DFS(p->to);}}}

void travelDFS(int nodecnt){
// 如果一个图有多个不联通部分则全部遍历
    for(int i=1;i<=nodecnt;i++){visit[i]=0;}
    // DFS每个联通区间
    for(int i=1;i<=nodecnt;i++){if(visit[i]==0){DFS(i);}}
}
```

3. **BFS 广度优先**：需要基于之前的队列代码。其他要求同 `DFS`、`travelDFS`

两种遍历参考习题：*`B3862`、`P3916`、`P5318`*

```c
void BFS(int start){
// 从某个点开始进行BFS遍历
    edge p;
    printf("%d ",start);// 可自行修改处理逻辑
    visit[start]=1;
    intoqueue(start);
    while(!ifempty()){
        start = outqueue();
        for(p = graph[start].link;p!=NULL;p=p->next){
            if(visit[p->to]==0){
                printf("%d ",p->to);// 可自行修改处理逻辑
                visit[p->to]=1;
                intoqueue(p->to);}}}}

void travelBFS(int nodecnt){
// 如果一个图有多个不联通部分则全部遍历
    initqueue();
    for(int i=1;i<=nodecnt;i++){visit[i]=0;}
    for(int i=1;i<=nodecnt;i++){if(visit[i]==0){BFS(i);}}}
```

4. **基于深度优先的全部路径搜索算法**，`printpath` 指的是打印出路径（此函数简单没写）。可以看出相比于 `DFS` 只是加了退出机制

```c
void eDFS(int nownode, int level, int nodelast) {
  edge p;
  if (nownode == nodelast) {printpath(level);return;}
  for (p = graph[nownode].link; p != NULL; p = p->next) {
    if (!visited[p->to]) {
      path[level] = p->to;// 或者也可以是边的编号，看题目了
      visited[p->to] = 1;
      eDFS(p->to, level + 1, nodelast);
      visited[p->to] = 0;
    }}}
```

使用方法：

```c
visited[node0] = 1;// 需要加这个不然会往回走
eDFS(node0, 0, nodelast);// 三个参数：起点、0（固定）、终点
```

5. **最小生成树**：最小生成树仅针对于无向图。这里只展示 Prim 算法，剩下的道理类似没有显著性能提升。

```c
int prim(int n) {
    int dist[MAXN];// 各节点到整个生成树的最小边权
    int visited[MAXN] = {};
    int sum = 0;
    // 所有点先保持未联通INF
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[1] = 0; // 起点已经在生成树里了，所以是0（默认起点为1号位）

    for (int i = 1; i <= n; i++) {
        // 第一步：找出未访问且dist最小的节点u（u的序号也尽可能小了）
        int u = -1, min = INF;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;}}
        if (u == -1) {return -1;}   // 图不连通
        // 第二步：将u加入生成树
        visited[u] = 1;
        sum += dist[u];
        // 第三步：用u的邻接边更新其他节点的 dist
        for (edge p = graph[u].link; p != NULL; p = p->next) {
            int v = p->to;
            if (!visited[v] && p->weight < dist[v]) {
                dist[v] = p->weight;}}}
    return sum;}
```

6. **Dijkstra 算法**，最短路径计数的补丁有：声明 `cnt[MAXN]`，规定 `cnt[src]=1`，以及在发现更短路径（`dist[u]+w < dist[v]`）时 `cnt[v]=cnt[u]`，在发现同距离路径（`dist[u]+w == dist[v]`）时 `cnt[v]+=cnt[u]`

```c
void dijkstra(int src, int n) {
    int dist[MAXN];int visited[MAXN] = {};
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[src] = 0;// src离自己的距离是0

    for (int i = 1; i <= n; i++) {
        // 第一步：选出未访问且dist最小的点u（最开始显然是src）
        int u = -1;int min_dist = INF;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;}}
        if (u == -1) {break;}   // 剩余点不可达（图不连通）
        // 第二步：标记u已访问
        visited[u] = 1;
        // 第三步：用u的邻接边更新其邻接点v的dist
        for (edge p = graph[u].link; p != NULL; p = p->next) {
            int v = p->to;
            int w = p->weight;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;}}}

    // 输出从 src 到所有点的最短距离
    for (int i = 1; i <= n; i++) {
        if(dist[i]==INF){printf("2147483647 ");continue;}
        // 各个题对不可达点有自己的规定，这里只是一个案例
        printf("%d ", dist[i]);}
        printf("\n");}
```

7. **Floyd 算法**：只适用于 `nodecnt` $\le 200$ 的情形，但是最简单的方法，务必使用邻接矩阵！

```c
int dist[MAXN][MAXN];
void floyd(){// floyd 三循环
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];}}}}}
```

> 以上路径算法中，都能够处理重边、自环，但是 Floyd 通常适配邻接阵，所以在重边、自环这个问题上要做好处理，一般的做法是，储存一个边的权重时进行一次 `min` 运算。

---

## 排序、查找

1. **冒泡排序**

```c
void bbst(int arr[], int n) {
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= n - i; j++) {
      if (arr[j] > arr[j + 1]) {
        int tmp = arr[j + 1];arr[j + 1] = arr[j];arr[j] = tmp;
        total++;//不一定非要有，统计数量用的，如去年那个题
        }}}}
```

---

## 附录：题目清单与分析

### 项目文件结构

```
SJJG/
├── README.md              # 本文件
├── sjjg.typ               # Typst 源码（数据结构模板）
├── test.c                 # Hello World 测试文件
├── LG/                    # 洛谷（Luogu）平台题目
│   ├── B3631.c            # 单向链表
│   ├── B3642.c            # 二叉树的遍历
│   ├── B3643.c            # 图的存储
│   ├── B3862.c            # 图的遍历（简单版）
│   ├── P1144.c            # 最短路计数
│   ├── P1449.c            # 后缀表达式
│   ├── P1540.c            # [NOIP2010] 机器翻译
│   ├── P3366.c            # 【模板】最小生成树
│   ├── P3371.c            # 【模板】单源最短路径（弱化版）
│   ├── P3884.c            # [JLOI2009] 二叉树问题
│   ├── P3916.c            # 图的遍历
│   ├── P5318.c            # 【深基18.例3】查找文献
│   ├── P5755.c            # [NOI2000] 单词查找树
│   ├── U306073.c          # 排队模拟（队列）
│   └── U616683.c          # Joseph 环（循环链表）
├── W1/                    # 第1周作业
│   ├── primes.c           # 质因数分解
│   ├── rotate.c           # 矩阵旋转对称判断
│   ├── T3.c               # 平均分排名
│   └── typeset.c          # 文本排版对齐
├── W2/                    # 第2周作业
│   ├── package.c          # 包裹排序
│   ├── T2.c               # 单向链表操作
│   ├── T3.c               # Joseph 环变体
│   └── T4.c               # 链表去重
├── W3/                    # 第3周作业
│   ├── T1.c               # 兔子排队模拟
│   ├── T2.c               # 中缀转后缀表达式
│   ├── T3.c               # 二叉排序树（BST）
│   └── T4.c               # 树的 LCA 与距离
├── W4/                    # 第4周作业
│   ├── graphSearch.c      # 图的增删改查
│   ├── T2.c               # 图的全部路径搜索
│   ├── T3.c               # 最小生成树（Prim）
│   └── T4.c               # Floyd 全源最短路
└── W5/                    # 第5周作业
    ├── T1.c               # 机器翻译（FIFO 缓存）
    ├── T2.c               # 冒泡排序（统计交换次数）
    ├── T3.c               # 最短路计数（BFS）
    └── T4.c               # Trie 树（字典树）
```

---

### LG — 洛谷平台题目

| 文件 | 题号 | 题目名称 | 考察内容 | 难度 |
|------|------|----------|----------|------|
| `B3631.c` | [B3631](https://www.luogu.com.cn/problem/B3631) | 单向链表 | 链表的插入、查询、删除操作。维护一张表，支持三种操作：在元素后插入、查询后继、删除后继。 | 普及− |
| `B3642.c` | [B3642](https://www.luogu.com.cn/problem/B3642) | 二叉树的遍历 | 给定二叉树每个节点的左右孩子编号，输出前序、中序、后序三种遍历结果。数组存储二叉树 + 递归遍历。 | 普及− |
| `B3643.c` | [B3643](https://www.luogu.com.cn/problem/B3643) | 图的存储 | 以邻接矩阵和邻接表两种形式输出无向图。同时计算每个顶点的度数并按升序输出邻接点。 | 普及− |
| `B3862.c` | [B3862](https://www.luogu.com.cn/problem/B3862) | 图的遍历（简单版） | 有向图，求每个点出发能到达的编号最大的点。使用邻接表 + DFS 遍历。 | 普及− |
| `P1144.c` | [P1144](https://www.luogu.com.cn/problem/P1144) | 最短路计数 | 无向无权图，求从顶点 1 到其他每个点的最短路径条数。Dijkstra 算法 + 路径计数（`cnt[v] += cnt[u]` 当等距时）。 | 普及+/提高 |
| `P1449.c` | [P1449](https://www.luogu.com.cn/problem/P1449) | 后缀表达式 | 用栈计算后缀表达式的值。操作数以 `.` 结尾，`@` 为表达式结束符。运算符仅 `+ - * /`。 | 普及− |
| `P1540.c` | [P1540](https://www.luogu.com.cn/problem/P1540) | [NOIP2010] 机器翻译 | 模拟 FIFO 缓存（队列），内存容量为 M，查词典时若单词不在内存中则计入外存访问次数。 | 普及− |
| `P3366.c` | [P3366](https://www.luogu.com.cn/problem/P3366) | 【模板】最小生成树 | 无向图，求最小生成树的边权和。若图不连通输出 `orz`。使用 Prim 算法（邻接表）。 | 普及/提高− |
| `P3371.c` | [P3371](https://www.luogu.com.cn/problem/P3371) | 【模板】单源最短路径（弱化版） | 有向图，输出从起点到所有点的最短路径长度。不可达输出 `2147483647`。使用朴素 Dijkstra。 | 普及/提高− |
| `P3884.c` | [P3884](https://www.luogu.com.cn/problem/P3884) | [JLOI2009] 二叉树问题 | 求二叉树的深度、宽度以及两指定节点间的距离（距离 = 向上边数×2 + 向下边数）。涉及 DFS 求深度、层次宽度统计、LCA 与路径回溯。 | 普及/提高− |
| `P3916.c` | [P3916](https://www.luogu.com.cn/problem/P3916) | 图的遍历 | 有向图，求每个点出发能到达的编号最大的点。**关键技巧：反向建图 + 从大到小 DFS**，避免对每个点分别 DFS 导致超时。 | 普及/提高− |
| `P5318.c` | [P5318](https://www.luogu.com.cn/problem/P5318) | 【深基18.例3】查找文献 | 给定文章引用关系图，要求分别输出 DFS 和 BFS 遍历结果，优先遍历编号较小的参考文献。需要先对边排序再建图。 | 普及− |
| `P5755.c` | [P5755](https://www.luogu.com.cn/problem/P5755) | [NOI2000] 单词查找树 | 给定单词列表（全大写），求对应 Trie（字典树）的节点总数（含根节点）。统计不同前缀的数量。 | 普及/提高− |
| `U306073.c` | U306073 | 排队模拟 | 模拟多个顾客排队处理业务，每位顾客有一个到达时间和若干个处理事项。每单位时间处理队首一个事项，事项未处理完则重新入队。求**总等待时间**。使用循环队列模拟。 | — |
| `U616683.c` | U616683 | Joseph 环 | 经典的 Josephus 问题变体：n 个人围成一圈，报数中含 7 或是 7 的倍数则出局，求最后剩下的人的编号。使用循环链表实现。 | — |

---

### W1 — 第1周作业

| 文件 | 题目情景 | 考察知识点 |
|------|----------|------------|
| `primes.c` | 输入一个正整数，输出其质因数分解中**仅出现一次**的质因子（按升序）。例如 `12 = 2²×3`，输出 `3`。 | 质因数分解、试除法、循环 |
| `rotate.c` | 输入一个 $n \times n$ 的字符矩阵，判断该矩阵顺时针旋转 90°、180°、270° 后是否与原矩阵相同。若任一种旋转后相同则输出 `Yes`，否则 `No`。 | 二维数组、矩阵旋转、索引变换 |
| `T3.c` | 输入 $n$ 个学生的 $k$ 门指标成绩，计算每个学生的平均分，输出平均分最高和次高的学生编号。 | 数组、遍历求最值、浮点运算 |
| `typeset.c` | 从文件 `listin.txt` 读取文本，按照指定的冒号对齐位置重新排版，输出到 `listout.txt`。要求在冒号前填充空格使其对齐到指定列。 | 文件读写、字符串处理、格式排版 |

---

### W2 — 第2周作业

| 文件 | 题目情景 | 考察知识点 |
|------|----------|------------|
| `package.c` | 输入若干包裹信息（8 位单号、收件人姓名、电话），按电话降序排序，电话相同时按单号升序排序，格式化输出。 | 结构体、冒泡排序、多关键字排序 |
| `T2.c` | 同洛谷 `B3631`（单向链表）：实现链表的插入、查询后继、删除后继三种操作。 | 单向链表、动态内存分配 |
| `T3.c` | Joseph 环变体：n 门课程名称 + 每门课对应的步长 k，从第 1 门开始循环报数，每次按当前课程指定的步长 k 出队并输出课程名。 | 循环链表、Josephus 问题 |
| `T4.c` | 输入一个链表（以 EOF 结束），删除所有**出现超过一次**的节点值，只保留仅出现一次的元素，保持原顺序输出。 | 链表遍历、去重、哈希计数 |

---

### W3 — 第3周作业

| 文件 | 题目情景 | 考察知识点 |
|------|----------|------------|
| `T1.c` | 同洛谷 `U306073`：兔子排队吃饭模拟。每只兔子有到达时间和食物数量，每单位时间处理队首兔子的一份食物，未吃完重新入队，求总等待时间。 | 循环队列、离散事件模拟 |
| `T2.c` | 中缀表达式转后缀表达式（逆波兰表示法）。正确处理运算符优先级（`* /` > `+ -`）和括号。数字直接输出，运算符按优先级入栈出栈。 | 栈、表达式转换、运算符优先级 |
| `T3.c` | 二叉排序树（BST）：输入若干整数，构建 BST（相同值计数器 +1），然后中序遍历输出每个值及其出现次数（升序去重统计）。 | BST 插入、中序遍历、词频统计 |
| `T4.c` | 树的最近公共祖先（LCA）与距离：给定一棵树的若干父子关系边和两个节点 s、t，求 s 到 t 的路径长度（经过的边数）。通过回溯父节点找 LCA。 | 树的双亲表示法、LCA、路径计算 |

---

### W4 — 第4周作业

| 文件 | 题目情景 | 考察知识点 |
|------|----------|------------|
| `graphSearch.c` | 图的增删改查：实现图的创建（邻接表）、删除指定节点（同时删除所有关联边）、DFS 遍历。 | 邻接表、图的删除操作、DFS |
| `T2.c` | 图的全部路径搜索（eDFS）：给定无向图，每条边有编号，求从起点（节点 0）到终点（节点 n-1）的所有路径，按边的编号输出每条路径。 | 图的 DFS 回溯、所有路径枚举 |
| `T3.c` | 最小生成树（Prim 算法）：输入带权无向图（边有编号），求最小生成树的总权重，并按边的编号升序输出所选边。 | Prim 算法、邻接矩阵、排序 |
| `T4.c` | Floyd 全源最短路：输入邻接矩阵（`-` 表示不可达），用 Floyd-Warshall 算法计算从指定源点到所有其他点的最短距离并格式化输出。 | Floyd 算法、邻接矩阵、全源最短路径 |

---

### W5 — 第5周作业

| 文件 | 题目情景 | 考察知识点 |
|------|----------|------------|
| `T1.c` | 同洛谷 `P1540`（机器翻译）：FIFO 缓存模拟，内存容量 M，查单词时若不在内存中则计入查词典次数，缓存满时淘汰最早进入的单词。 | 队列、FIFO 缓存模拟 |
| `T2.c` | 冒泡排序，统计**交换次数**：输入 n 个数，进行冒泡排序（升序），输出总共发生的交换次数。 | 冒泡排序、交换计数 |
| `T3.c` | 最短路计数（BFS 版）：同洛谷 `P1144`，但使用 **BFS + 链式前向星** 实现无权图的最短路径计数。`dist[v] == -1` 时赋值，`dist[v] == dist[u]+1` 时累加计数。 | BFS、链式前向星、最短路径计数 |
| `T4.c` | Trie 树（字典树）：同洛谷 `P5755`。输入若干大写单词（EOF 结束），构建 Trie 树并输出总节点数。使用二维数组 `trie[MAXN][26]` 实现，初始化为 `-1`。 | Trie 树、字典树、字符串前缀 |

---

> **注：** LG 文件夹中 U306073 和 U616683 为校内题目（非洛谷标准题号），其余均为洛谷（luogu.com.cn）平台题目。W1~W5 为按教学周组织的配套编程作业。
