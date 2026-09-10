# Haskell 与 C 对比示例

本目录用于对比同一组小任务在 Haskell 和 C 中的写法。

## 目录结构

- `Haskell/`：Haskell 源文件（`.hs`）
- `C/`：C 源文件（`.c`）

两个目录中的文件主名一一对应，例如：

- `Haskell/06_data_stack.hs`
- `C/06_data_stack.c`

每个文件内部若有多个子任务，用两个空行隔开；源码中带 `----------` 注释分节。

## 编号说明

- 数字前缀按实际代码任务顺序连续编号。
- 原列表中的 `经典问题及算法` 是章节说明，没有单独生成代码文件，因此不单独占编号。
- 最长上升子序列的 5 个方案来自同一行任务，文件名共用前缀 `20_`，各自保留原主名：
  `lis_bruteforce`、`lis_dp`、`lis_memo`、`lis_binary_search`、`lis_fenwick`。

## 编译与运行

C（使用 GCC 或 Clang，数学函数需要 `-lm`）：

```bash
gcc -std=c11 -O2 -Wall -Wextra -o demo C/文件名.c -lm
./demo
```

Haskell（使用 GHC）：

```bash
runghc Haskell/文件名.hs
```

部分程序从标准输入读数据，例如最短路、MST、LIS 等，请按文件头部注释中的输入格式运行。

## 说明

- 所有 C 文件已用 Clang 14 / `-Wall -Wextra` 编译验证。
- 所有 Haskell 文件已用 GHC 9.10.3 做类型检查。
- Luogu 经典题使用以下题目作为简单情境：
  - DFS：洛谷 P1605 迷宫
  - BFS：洛谷 P1443 马的遍历
  - 贪心：洛谷 P1090 合并果子
  - 简单 DP：洛谷 P1216 数字三角形
- 最长上升子序列提供了 5 个独立文件：暴力、O(n^2) DP、递归记忆化、贪心二分、树状数组。

## 文件对照表

| 任务 | Haskell | C |
| --- | --- | --- |
| 1. 数学计算 | `01_math_basic_calculations.hs` | `01_math_basic_calculations.c` |
| 2. 质数筛、sigma、矩阵、微积分、排列组合 | `02_math_primes_sigma_matrix_calculus_combinatorics.hs` | `02_math_primes_sigma_matrix_calculus_combinatorics.c` |
| 3. 判断、循环、跳过/跳出 | `03_basic_syntax_condition_loops_break.hs` | `03_basic_syntax_condition_loops_break.c` |
| 4. 函数递归、IO、跳转 | `04_functions_recursion_io_jump.hs` | `04_functions_recursion_io_jump.c` |
| 5. 列表/数组 | `05_data_list_array.hs` | `05_data_list_array.c` |
| 6. 栈 | `06_data_stack.hs` | `06_data_stack.c` |
| 7. 队列 | `07_data_queue.hs` | `07_data_queue.c` |
| 8. vector、链表 | `08_data_vector_linked_list.hs` | `08_data_vector_linked_list.c` |
| 9. 二叉树与前中后序遍历 | `09_data_binary_tree_traversal.hs` | `09_data_binary_tree_traversal.c` |
| 10. 有向图、无向图（链式前向星） | `10_data_graph_forward_star.hs` | `10_data_graph_forward_star.c` |
| 11. 堆、红黑树 | `11_data_heap_red_black_tree.hs` | `11_data_heap_red_black_tree.c` |
| 12. 前向星 Dijkstra | `12_shortest_path_dijkstra_forward_star.hs` | `12_shortest_path_dijkstra_forward_star.c` |
| 13. Bellman-Ford | `13_shortest_path_bellman_ford.hs` | `13_shortest_path_bellman_ford.c` |
| 14. 最小生成树 Kruskal/Prim | `14_mst_kruskal_prim.hs` | `14_mst_kruskal_prim.c` |
| 15. DFS（洛谷 P1605） | `15_classic_luogu_dfs_maze.hs` | `15_classic_luogu_dfs_maze.c` |
| 16. BFS（洛谷 P1443） | `16_classic_luogu_bfs_horse.hs` | `16_classic_luogu_bfs_horse.c` |
| 17. 贪心（洛谷 P1090） | `17_classic_luogu_greedy_merge_fruit.hs` | `17_classic_luogu_greedy_merge_fruit.c` |
| 18. 简单 DP（洛谷 P1216） | `18_classic_luogu_dp_number_triangle.hs` | `18_classic_luogu_dp_number_triangle.c` |
| 19. Fibonacci | `19_fibonacci_recursion_memo_formula.hs` | `19_fibonacci_recursion_memo_formula.c` |
| 20. LIS 暴力 | `20_lis_bruteforce.hs` | `20_lis_bruteforce.c` |
| 20. LIS O(n^2) DP | `20_lis_dp.hs` | `20_lis_dp.c` |
| 20. LIS 记忆化 | `20_lis_memo.hs` | `20_lis_memo.c` |
| 20. LIS 贪心二分 | `20_lis_binary_search.hs` | `20_lis_binary_search.c` |
| 20. LIS 树状数组 | `20_lis_fenwick.hs` | `20_lis_fenwick.c` |

## 人类有话说

看完这些代码吧，不能说是豁然开朗，至少也可以说是一窍不通。仅供参考吧。