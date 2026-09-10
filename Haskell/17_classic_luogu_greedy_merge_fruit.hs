-- 任务：贪心（洛谷 P1090 合并果子）。
-- 每次取出最小的两堆合并；这里用 Data.Map 计数模拟小根堆。
-- 样例输入：
--   3
--   1 2 9
-- 样例输出：15
-- 运行：runghc 17_17_classic_luogu_greedy_merge_fruit.hs

import qualified Data.Map.Strict as M


main :: IO ()
main = do
    input <- getContents
    let ws = words input
        n = read (head ws) :: Int
        xs = map (read :: String -> Int) (take n (drop 1 ws))
    print (mergeFruits xs)

mergeFruits :: [Int] -> Int
mergeFruits xs = go (M.fromListWith (+) [(x, 1) | x <- xs]) 0
  where
    go bag acc
        | M.size bag < 2 = acc
        | otherwise =
            case popMin bag of
                Nothing -> acc
                Just (a, bag1) ->
                    case popMin bag1 of
                        Nothing -> acc
                        Just (b, bag2) ->
                            go (M.insertWith (+) (a + b) 1 bag2) (acc + a + b)

    popMin bag =
        case M.minViewWithKey bag of
            Nothing -> Nothing
            Just ((k, cnt), rest) ->
                Just (k, if cnt == 1 then rest else M.insert k (cnt - 1) rest)