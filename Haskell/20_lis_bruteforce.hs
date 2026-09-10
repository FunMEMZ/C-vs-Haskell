-- 最长上升子序列 -- 方案 1：暴力枚举所有子序列。
-- 输入：n，然后 n 个整数。
-- 运行：runghc 20_20_lis_bruteforce.hs

import Data.List (subsequences)


main :: IO ()
main = do
    input <- getContents
    let ws = words input
        n = read (head ws) :: Int
        xs = map (read :: String -> Int) (take n (drop 1 ws))
    print (lisBrute xs)

lisBrute :: [Int] -> Int
lisBrute xs = maximum (0 : [length ys | ys <- subsequences xs, isIncreasing ys])

isIncreasing :: Ord a => [a] -> Bool
isIncreasing ys = and (zipWith (<) ys (tail ys))