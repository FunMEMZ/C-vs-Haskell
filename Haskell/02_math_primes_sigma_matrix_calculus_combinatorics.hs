-- 任务：质数的无优化筛、埃筛和欧拉筛；sigma 求和；矩阵；导数、积分；排列、组合。
-- 运行：runghc 02_02_math_primes_sigma_matrix_calculus_combinatorics.hs

import Data.Array (Array, (!))
import Data.Array.ST (STArray, newArray, readArray, runSTArray, writeArray)
import Data.List (transpose)
import Text.Printf (printf)


-- ---------- 无优化筛：试除法 ----------

isPrimeNaive :: Int -> Bool
isPrimeNaive n = n >= 2 && all (\d -> n `mod` d /= 0) [2 .. floor (sqrt (fromIntegral n))]

naivePrimes :: Int -> [Int]
naivePrimes limit = [i | i <- [2 .. limit], isPrimeNaive i]


-- ---------- 埃拉托斯特尼筛 ----------

eratosthenes :: Int -> [Int]
eratosthenes limit = [i | i <- [2 .. n], not (arr ! i)]
  where
    n = max 2 limit
    arr = runSTArray $ do
        a <- newArray (2, n) True
        let mark p x
              | x > n = return ()
              | otherwise = writeArray a x False >> mark p (x + p)
            loop p
              | p * p > n = return a
              | otherwise = do
                  isPrimeP <- readArray a p
                  if isPrimeP then mark p (p * p) else return ()
                  loop (p + 1)
        _ <- loop 2
        return a


-- ---------- 欧拉（线性）筛 ----------

eulerSieve :: Int -> [Int]
eulerSieve limit = [i | i <- [2 .. n], not (comp ! i)]
  where
    n = max 2 limit
    comp = runSTArray $ do
        a <- newArray (0, n) False
        let mark i [] = return ()
            mark i (p : ps)
              | i * p > n = return ()
              | otherwise = do
                  writeArray a (i * p) True
                  if i `mod` p == 0 then return () else mark i ps
            loop i ps
              | i > n = return ()
              | otherwise = do
                  c <- readArray a i
                  let ps' = if c then ps else i : ps
                  mark i ps'
                  loop (i + 1) ps'
        loop 2 []
        return a


-- ---------- sigma 求和 ----------

sigma :: Int -> Int
sigma n = sum [d | d <- [1 .. n], n `mod` d == 0]


-- ---------- 矩阵 ----------

matMul :: Num a => [[a]] -> [[a]] -> [[a]]
matMul a b =
    [ [ sum (zipWith (*) row col)
      | col <- transpose b
      ]
    | row <- a
    ]

matrixDemo :: IO ()
matrixDemo = do
    let a = [[1, 2], [3, 4]] :: [[Int]]
        b = [[5, 6], [7, 8]] :: [[Int]]
    printf "matrix A*B = %s\n" (show (matMul a b))


-- ---------- 导数、积分（多项式，系数升幂存储） ----------

evalPoly :: Num a => [a] -> a -> a
evalPoly coeffs x = foldr (\a acc -> a + x * acc) 0 coeffs

derivativePoly :: Num a => [a] -> [a]
derivativePoly [] = []
derivativePoly (_ : as) = zipWith (\i a -> fromIntegral i * a) [1 :: Int ..] as

integralPoly :: Fractional a => [a] -> [a]
integralPoly as = 0 : zipWith (\i a -> a / fromIntegral i) [1 :: Int ..] as

calculusDemo :: IO ()
calculusDemo = do
    let f = [5, -2, 0, 1] :: [Double]       -- f(x) = x^3 - 2x + 5
    printf "f(2) = %.0f\n" (evalPoly f 2)
    printf "f'(x) coefficients (asc) = %s\n" (show (derivativePoly f))
    printf "Integral coefficients (asc) = %s\n" (show (integralPoly f))


-- ---------- 排列、组合 ----------

permCount :: Integer -> Integer -> Integer
permCount n k = product [n - k + 1 .. n]

combCount :: Integer -> Integer -> Integer
combCount n k
    | k < 0 || k > n = 0
    | otherwise = product [n - k + 1 .. n] `div` product [1 .. k]

picks :: [a] -> [(a, [a])]
picks [] = []
picks (x : xs) = (x, xs) : [(y, x : ys) | (y, ys) <- picks xs]

permutationsOf :: [a] -> [[a]]
permutationsOf [] = [[]]
permutationsOf xs = [x : ys | (x, rest) <- picks xs, ys <- permutationsOf rest]

combinationsOf :: Int -> [a] -> [[a]]
combinationsOf k _ | k < 0 = []
combinationsOf 0 _ = [[]]
combinationsOf _ [] = []
combinationsOf k (x : xs) =
    map (x :) (combinationsOf (k - 1) xs) ++ combinationsOf k xs

combinatoricsDemo :: IO ()
combinatoricsDemo = do
    printf "P(5,2)=%d, C(5,2)=%d\n" (permCount 5 2) (combCount 5 2)
    printf "permutations of [1,2,3]: %s\n" (show (permutationsOf [1, 2, 3]))
    printf "combinations of size 2 from [1,2,3,4]: %s\n"
           (show (combinationsOf 2 [1, 2, 3, 4]))


main :: IO ()
main = do
    printf "naive  primes <= 30: %s\n" (show (naivePrimes 30))
    putStrLn ""
    printf "eratosthenes primes <= 30: %s\n" (show (eratosthenes 30))
    putStrLn ""
    printf "euler  primes <= 30: %s\n" (show (eulerSieve 30))
    putStrLn ""
    printf "sigma(12)=%d\n" (sigma 12)
    putStrLn ""
    matrixDemo
    putStrLn ""
    calculusDemo
    putStrLn ""
    combinatoricsDemo