-- 任务：基础语法 -- 判断；循环及跳过和跳出机制。
-- 说明：Haskell 没有命令式的 continue/break，
--       通常用 filter/takeWhile/递归表达 skip 和 break。
-- 运行：runghc 03_03_basic_syntax_condition_loops_break.hs

import Control.Monad (forM_)
import Data.IORef (modifyIORef', newIORef, readIORef)
import Text.Printf (printf)


-- ---------- 判断：if 与 guard ----------

classify :: Int -> String
classify n
    | n < 0     = "negative"
    | n == 0    = "zero"
    | otherwise = "positive"

conditionDemo :: IO ()
conditionDemo = do
    printf "classify(-3)=%s, classify(0)=%s, classify(8)=%s\n"
           (classify (-3)) (classify 0) (classify 8)

    let day = 3 :: Int
    putStrLn $ case day of
        1 -> "day 1: workday"
        2 -> "day 2: workday"
        3 -> "day 3: workday"
        4 -> "day 4: workday"
        5 -> "day 5: workday"
        6 -> "day 6: weekend"
        7 -> "day 7: weekend"
        _ -> "invalid day"


-- ---------- 循环、跳过、跳出 ----------

loopDemo :: IO ()
loopDemo = do
    -- 函数式 skip: filter；函数式 break: takeWhile。
    let oddsUntilSeven = takeWhile (<= 7) (filter odd [1 .. 10])
    printf "filter/takeWhile equivalents: %s\n" (show oddsUntilSeven)

    -- 单子循环中的 continue/break：用递归和条件分支表达。
    ref <- newIORef (1 :: Int)
    let go = do
            i <- readIORef ref
            if i > 10
                then return ()
                else do
                    modifyIORef' ref (+ 1)
                    if even i
                        then go                 -- 相当于 continue
                        else if i > 7
                            then return ()      -- 相当于 break
                            else do
                                printf "%d " i
                                go
    putStr "for with continue/break equivalent: "
    go
    putStrLn ""

    -- 常见的 for 循环：forM_。
    printf "forM_ 1..5: "
    forM_ [1 .. 5 :: Int] $ \i -> printf "%d " i
    putStrLn ""

    -- while 循环：递归。
    let whileLoop :: Int -> Int -> IO Int
        whileLoop k acc
          | k >= 5    = return acc
          | otherwise = whileLoop (k + 1) (acc + k)
    total <- whileLoop 0 0
    printf "while recursive sum 0..4: %d\n" total


main :: IO ()
main = do
    conditionDemo
    putStrLn ""
    loopDemo