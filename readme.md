#  2024秋数据结构课程设计
> 课设题目来自普林斯顿课程,确实是相当有挑战,写完感觉非常受用,对C++的泛型,函子等内容有了比较深的把握,总体是比较满意的.

## Platform & Dependencies
原生C++项目.使用ImGUI框架绘制界面.

> Xcode C++ compiler:
> Apple clang version 15.0.0 (clang-1500.3.9.4)
> Target: arm64-apple-darwin23.5.0
> Thread model: posix

| 依赖名称 | 当前版本 | 最低版本 | 说明 |
| -- | -- | -- | -- |
| GLEW | 2.2.0 | 2.1.0 | 加载 OpenGL 函数指针 |
| GLFW | 3.4.0 | 3.3.0 | 创建窗口、管理上下文、处理输入等 OpenGL 相关的基础功能 |
| glm | 1.0.1 | 1.0.0 | 提供OpenGL各种数学实体和功能|
| gtest | 1.15.2 | 1.13.0 | 提供单元测试框架|

## Content
1. 从底层实现全体ADT.

<p align="center">
    <img src="https://cdn.jsdelivr.net/gh/HereIsZephyrus/zephyrus.img/images/blog/WUSGraph_structure.png" alt="structure" />
</p>

2. 文件读入和场景漫游

<p align="center">
    <img src=https://cdn.jsdelivr.net/gh/HereIsZephyrus/zephyrus.img/images/blog/20250103234331409-ezgif.com-video-to-gif-converter.gif"" alt="read file and roaming" />
</p>

3. 数据库全局特征查询

<p align="center">
    <img src=https://cdn.jsdelivr.net/gh/HereIsZephyrus/zephyrus.img/images/blog/global.gif"" alt="query city and road" />
</p>

4. 城市和道路查询

<p align="center">
    <img src="https://cdn.jsdelivr.net/gh/HereIsZephyrus/zephyrus.img/images/blog/search_city_and_road.gif" alt="query city and road" />
</p>

5. 添加和删除城市

<p align="center">
    <img src="https://cdn.jsdelivr.net/gh/HereIsZephyrus/zephyrus.img/images/blog/add_and_remove_city.gif" alt="add and remove city" />
</p>

6. 添加和删除道路

<p align="center">
    <img src="" alt="add and remove road" />
</p>

7. 获取相邻城市和缓冲区内城市信息

<p align="center">
    <img src="" alt="add and remove road" />
</p>

8. 求两点间最短路径

<p align="center">
    <img src="" alt="add and remove road" />
</p>

9. 求多点最短距离(斯坦纳树)

<p align="center">
    <img src="" alt="add and remove road" />
</p>

10. 求某点出发的最小生成树

<p align="center">
    <img src="" alt="add and remove road" />
</p>
