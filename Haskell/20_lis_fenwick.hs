-- 最长上升子序列 -- 方案 5：树状数组（Fenwick）优化 DP，O(n log n)。
-- 输入：n，然后 n 个整数。
-- 运行：runghc 20_20_lis_fenwick.hs

import Data.Array (Array, (!), listArray, (//))
import Data.Bits ((.&.))
import Data.List (foldl')
import qualified Data.Map.Strict as M
import qualified Data.Set as S


main :: IO ()
main = do
    input <- getContents
    let ws = words input
        n = read (head ws) :: Int
        xs = map (read :: String -> Int) (take n (drop 1 ws))
    print (lisFenwick xs)

lisFenwick :: [Int] -> Int
lisFenwick xs = fst (foldl' step (0, bit0) ranks)
  where
    vals = S.toAscList (S.fromList xs)
    m = length vals
    rankMap = M.fromList (zip vals [1 ..])
    ranks = [rankMap M.! x | x <- xs]

    bit0 = listArray (1, m) (replicate m 0) :: Array Int Int

    step (ans, bit) rank =
        let best = query bit (rank - 1) + 1
            bit' = update bit rank best
        in (max ans best, bit')

    -- 前缀最大值查询。
    query _ i | i <= 0 = 0
    query bit i =
        let j = i - (i .&. (-i))
        in max (bit ! i) (query bit j)

    -- 单点取最大值更新。
    update bit i v
        | i > m     = bit
        | otherwise = update (bit // [(i, max v (bit ! i))]) (i + (i .&. (-i))) v