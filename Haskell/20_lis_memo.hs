-- 最长上升子序列 -- 方案 3：递归 + 记忆化（自顶向下）。
-- 输入：n，然后 n 个整数。
-- 运行：runghc 20_20_lis_memo.hs

import Data.Array (Array, (!), elems, listArray)


main :: IO ()
main = do
    input <- getContents
    let ws = words input
        n = read (head ws) :: Int
        xs = map (read :: String -> Int) (take n (drop 1 ws))
    print (lisMemo xs)

lisMemo :: [Int] -> Int
lisMemo [] = 0
lisMemo xs = maximum (elems memo)
  where
    n = length xs
    arr = listArray (0, n - 1) xs :: Array Int Int
    memo = listArray (0, n - 1) [ dfs i | i <- [0 .. n - 1] ]

    dfs i = 1 + maximum (0 : [ memo ! j | j <- [i + 1 .. n - 1], arr ! j > arr ! i ])