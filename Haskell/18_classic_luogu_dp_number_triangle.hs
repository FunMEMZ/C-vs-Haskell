-- 任务：简单 DP（洛谷 P1216 数字三角形）。
-- 样例输入：
--   5
--   7
--   3 8
--   8 1 0
--   2 7 4 4
--   4 5 2 6 5
-- 样例输出：30
-- 运行：runghc 18_18_classic_luogu_dp_number_triangle.hs


main :: IO ()
main = do
    input <- getContents
    let ls = filter (not . null) (lines input)
        n = read (head ls) :: Int
        rows = take n (map (map (read :: String -> Int) . words) (tail ls))
    print (maxPath rows)

maxPath :: [[Int]] -> Int
maxPath rows = head (foldr1 combine rows)
  where
    combine row below =
        zipWith (\x (a, b) -> x + max a b) row (zip below (tail below))