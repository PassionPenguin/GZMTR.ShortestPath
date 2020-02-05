# 广州地铁最短路径问题计算
广州地铁最短路径计算器是一个基于C++的程序，用于快速计算两个站点之间的最短路径。同时该程序也支持简单计算票价（由于新票价计算方案对于2006年前开通的线路，按照哪个方案低用哪个的标准与2010年二八拆解会有所不准确）

![Logo](background.png)

[ENGLISH](README.md) [CHINESE](README.cn.md)
:grinning: 感谢您关注我们项目

## 安装方法
直接克隆一下这个repo即可

## 使用方法
使用您的C++编译器，直接编译即可

```shell script
g++ main.cpp -o ./exec
./exec
```

## 贡献
我们对于所有推送请求都是非常欢迎的。如果您想要提交大更改，请麻烦在issue页提出您的建议与理由，让我们先一起讨论一下。

## 开源协议
Creative Commons V3 BY-SA协议

## DOC
我们有这些函数:
```c++
void getSourceAndTarget() // -> Get Source and Get Target ID, eg: 0 240
void initPath() // -> init all links between vertices as infinite or 0
void readPath() // -> Get source from data.in in this format: id1 id2 time-cost length, all parameters are Int
void initData() // -> Make exists data into Time, dis, res
int priceCalc(int distance) // -> Return Price
void printResult() // -> Print result in this format: targetID time-cost result price
void dijkstra() // -> Calc
```

我们有这些文件:
|---Root
 |---main.cpp // the program file
 |---data.in // store the data
 |---src.in // where user input the source and the target
 |---data.out // where the program outputs the result