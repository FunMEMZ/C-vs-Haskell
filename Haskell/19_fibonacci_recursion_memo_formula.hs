-- 任务：Fibonacci -- 递归、列表记忆化、通项公式。
-- 运行：runghc 19_19_fibonacci_recursion_memo_formula.hs

import Text.Printf (printf)


-- ---------- 朴素递归 ----------

fibRec :: Int -> Integer
fibRec n
    | n < 2     = fromIntegral n
    | otherwise = fibRec (n - 1) + fibRec (n - 2)


-- ---------- 列表记忆化（惰性无穷列表） ----------

fibs :: [Integer]
fibs = 0 : 1 : zipWith (+) fibs (tail fibs)

fibMemo :: Int -> Integer
fibMemo n = fibs !! n


-- ---------- 通项公式（Binet，浮点近似） ----------

fibFormula :: Int -> Integer
fibFormula n = round ((phi ** fromIntegral n - psi ** fromIntegral n) / sqrt 5)
  where
    phi = (1 + sqrt 5) / 2 :: Double
    psi = (1 - sqrt 5) / 2 :: Double


main :: IO ()
main = do
    printf "recursive: %s\n" (unwords (map (show . fibRec) [0 .. 10]))
    printf "memoized:  %s\n" (unwords (map (show . fibMemo) [0 .. 20]))
    printf "formula:   %s\n" (unwords (map (show . fibFormula) [0 .. 20]))