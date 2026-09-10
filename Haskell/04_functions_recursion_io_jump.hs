-- 任务：函数及其递归；文件和控制台 IO；跳转。
-- 说明：Haskell 没有 goto/longjmp；非局部跳转通常用异常实现。
-- 运行：runghc 04_04_functions_recursion_io_jump.hs

import Control.Exception as E
import Text.Printf (printf)


-- ---------- 函数及其递归 ----------

factorial :: Integer -> Integer
factorial n = if n <= 1 then 1 else n * factorial (n - 1)

ackermann :: Integer -> Integer -> Integer
ackermann m n
    | m == 0    = n + 1
    | n == 0    = ackermann (m - 1) 1
    | otherwise = ackermann (m - 1) (ackermann m (n - 1))

isEven, isOdd :: Int -> Bool
isEven 0 = True
isEven n = isOdd (n - 1)
isOdd 0 = False
isOdd n = isEven (n - 1)          -- 互递归


-- ---------- 文件和控制台 IO ----------

ioDemo :: IO ()
ioDemo = do
    let path = "04_04_functions_recursion_io_jump_demo.txt"
    writeFile path "line one\nline two\n"
    content <- readFile path
    putStrLn ("file content: " ++ show content)

    putStr "console input (one line): "
    line <- E.catch getLine (\(_ :: E.IOException) -> return "(EOF/no input)")
    putStrLn ("you typed: " ++ line)


-- ---------- 跳转 ----------

-- 纯函数中的提前返回：用 Either 表示成功 / 失败。
earlyReturn :: Int -> Either String Int
earlyReturn x
    | x < 0     = Left "negative input"
    | otherwise = Right (x * 2)

-- IO 中的非局部跳转：抛出并捕获异常。
jumpDemo :: IO ()
jumpDemo = do
    print (earlyReturn (-3) :: Either String Int)

    E.catch
        (do
            putStrLn "before jump"
            E.throwIO (E.ErrorCall "jump out")
            putStrLn "never printed")
        (\(E.ErrorCall msg) -> putStrLn ("caught: " ++ msg))


main :: IO ()
main = do
    printf "factorial(10)=%d\n" (factorial 10)
    printf "ackermann(2,3)=%d\n" (ackermann 2 3)
    printf "isEven(10)=%s, isOdd(10)=%s\n" (show (isEven 10)) (show (isOdd 10))
    putStrLn ""
    ioDemo
    putStrLn ""
    jumpDemo