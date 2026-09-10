-- 最长上升子序列 -- 方案 4：贪心 + 二分（O(n log n)）。
-- 输入：n，然后 n 个整数。
-- 运行：runghc 20_20_lis_binary_search.hs

import Data.List (foldl')


main :: IO ()
main = do
    input <- getContents
    let ws = words input
        n = read (head ws) :: Int
        xs = map (read :: String -> Int) (take n (drop 1 ws))
    print (lisBinarySearch xs)

lisBinarySearch :: [Int] -> Int
lisBinarySearch xs = length (foldl' step [] xs)
  where
    -- 用第一个 >= x 的位置替换；若不存在则追加。
    step tails x =
        case break (>= x) tails of
            (pre, [])       -> pre ++ [x]
            (pre, _ : post) -> pre ++ [x] ++ post