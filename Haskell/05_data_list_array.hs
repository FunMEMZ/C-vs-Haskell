-- 任务：数据结构 -- 列表/数组。
-- 运行：runghc 05_05_data_list_array.hs

import Data.Array (Array, elems, listArray, (!), (//))
import Data.List (foldl', sort)
import Text.Printf (printf)


-- ---------- 列表操作 ----------

listDemo :: IO ()
listDemo = do
    let xs = [3, 1, 4, 1, 5, 9, 2, 6] :: [Int]
    printf "xs = %s\n" (show xs)
    printf "length=%d, sum=%d, maximum=%d\n" (length xs) (sum xs) (maximum xs)
    printf "map (*2) = %s\n" (show (map (* 2) xs))
    printf "filter even = %s\n" (show (filter even xs))
    printf "foldl' (+) 0 = %d\n" (foldl' (+) 0 xs)
    printf "reverse = %s\n" (show (reverse xs))
    printf "sort = %s\n" (show (sort xs))
    printf "take 3 = %s, drop 3 = %s\n" (show (take 3 xs)) (show (drop 3 xs))
    printf "zipWith (+) xs (tail xs) = %s\n" (show (zipWith (+) xs (tail xs)))


-- ---------- 数组操作（不可变数组） ----------

arrayDemo :: IO ()
arrayDemo = do
    let arr = listArray (0, 4) [10, 20, 30, 40, 50] :: Array Int Int
    printf "arr ! 2 = %d\n" (arr ! 2)
    printf "elems arr = %s\n" (show (elems arr))
    let arr' = arr // [(2, 99)]          -- 返回新数组，旧数组不变
    printf "after update: arr ! 2 = %d, arr' ! 2 = %d\n" (arr ! 2) (arr' ! 2)

    let m = listArray ((0, 0), (1, 2)) [1, 2, 3, 4, 5, 6] :: Array (Int, Int) Int
    printf "2D array = %s\n" (show [[m ! (i, j) | j <- [0 .. 2]] | i <- [0 .. 1]])


main :: IO ()
main = do
    listDemo
    putStrLn ""
    arrayDemo