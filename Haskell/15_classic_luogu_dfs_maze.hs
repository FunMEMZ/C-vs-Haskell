-- 任务：DFS（洛谷 P1605 迷宫）。
-- 输入格式：n m t / sx sy ex ey / t 行障碍坐标。
-- 样例输入：
--   2 2 1
--   1 1 2 2
--   1 2
-- 样例输出：1
-- 运行：runghc 15_15_classic_luogu_dfs_maze.hs

import Data.Set (Set)
import qualified Data.Set as Set


main :: IO ()
main = do
    input <- getContents
    let ls = lines input
        ints s = map (read :: String -> Int) (words s)
        (n : m : t : _) = ints (ls !! 0)
        (sx : sy : ex : ey : _) = ints (ls !! 1)
        obstacles = Set.fromList [ (x, y)
                                 | line <- take t (drop 2 ls)
                                 , let (x : y : _) = ints line
                                 ]
        answer = dfs n m (ex, ey) obstacles (Set.singleton (sx, sy)) sx sy
    print answer

dfs :: Int -> Int -> (Int, Int) -> Set (Int, Int) -> Set (Int, Int) -> Int -> Int -> Int
dfs n m (ex, ey) obstacles visited x y
    | (x, y) == (ex, ey) = 1
    | otherwise = sum
        [ dfs n m (ex, ey) obstacles (Set.insert (nx, ny) visited) nx ny
        | (dx, dy) <- [(-1, 0), (1, 0), (0, -1), (0, 1)]
        , let nx = x + dx
        , let ny = y + dy
        , nx >= 1, nx <= n, ny >= 1, ny <= m
        , not (Set.member (nx, ny) obstacles)
        , not (Set.member (nx, ny) visited)
        ]