-- 最长上升子序列 -- 方案 2：O(n^2) 动态规划。
-- 输入：n，然后 n 个整数。
-- 运行：runghc 20_20_lis_dp.hs

import Data.Array (Array, (!), elems, listArray)


main :: IO ()
main = do
    input <- getContents
    let ws = words input
        n = read (head ws) :: Int
        xs = map (read :: String -> Int) (take n (drop 1 ws))
    print (lisDP xs)

lisDP :: [Int] -> Int
lisDP [] = 0
lisDP xs = maximum (elems dp)
  where
    n = length xs
    arr = listArray (0, n - 1) xs :: Array Int Int
    dp = listArray (0, n - 1)
            [ 1 + maximum (0 : [dp ! j | j <- [0 .. i - 1], arr ! j < arr ! i])
            | i <- [0 .. n - 1]
            ]