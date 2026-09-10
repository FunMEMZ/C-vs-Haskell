-- 任务：数学计算 -- 加减乘除；幂指对；三角函数；反三角函数；双曲函数；gcd。
-- 运行：runghc 01_01_math_basic_calculations.hs

import Text.Printf (printf)


-- ---------- 加减乘除 ----------

arithmeticDemo :: IO ()
arithmeticDemo = do
    let a = 17 :: Int
        b = 5  :: Int
    printf "int:  a+b=%d, a-b=%d, a*b=%d, a div b=%d, a mod b=%d\n"
           (a + b) (a - b) (a * b) (a `div` b) (a `mod` b)

    let x = 17.0 :: Double
        y = 5.0  :: Double
    printf "real: x+y=%.3f, x-y=%.3f, x*y=%.3f, x/y=%.3f\n"
           (x + y) (x - y) (x * y) (x / y)


-- ---------- 幂、指数、对数 ----------

powerExpLogDemo :: IO ()
powerExpLogDemo = do
    printf "pow(2,10)=%.1f\n" (2.0 ** 10.0 :: Double)
    printf "exp(1)=%.6f\n" (exp 1 :: Double)
    printf "log(e)=%.6f, log10(1000)=%.6f, log2(8)=%.6f\n"
           (log (exp 1) :: Double)
           (logBase 10 1000 :: Double)
           (logBase 2 8 :: Double)
    printf "sqrt(2)=%.6f\n" (sqrt 2 :: Double)


-- ---------- 三角函数 ----------

trigDemo :: IO ()
trigDemo = do
    let degToRad :: Double -> Double
        degToRad d = d * pi / 180
    printf "sin30=%.6f, cos60=%.6f, tan45=%.6f\n"
           (sin (degToRad 30)) (cos (degToRad 60)) (tan (degToRad 45))


-- ---------- 反三角函数 ----------

inverseTrigDemo :: IO ()
inverseTrigDemo = do
    let x = 0.5 :: Double
    printf "asin(0.5)=%.6f rad\n" (asin x)
    printf "acos(0.5)=%.6f rad\n" (acos x)
    printf "atan(1)=%.6f rad\n" (atan 1 :: Double)
    printf "atan2(1,1)=%.6f rad\n" (atan2 1 1 :: Double)


-- ---------- 双曲函数 ----------

hyperbolicDemo :: IO ()
hyperbolicDemo = do
    printf "sinh(1)=%.6f, cosh(1)=%.6f, tanh(1)=%.6f\n"
           (sinh 1 :: Double) (cosh 1 :: Double) (tanh 1 :: Double)
    printf "asinh(1)=%.6f, acosh(2)=%.6f, atanh(0.5)=%.6f\n"
           (asinh 1 :: Double) (acosh 2 :: Double) (atanh 0.5 :: Double)


-- ---------- gcd ----------

main :: IO ()
main = do
    arithmeticDemo
    putStrLn ""
    powerExpLogDemo
    putStrLn ""
    trigDemo
    putStrLn ""
    inverseTrigDemo
    putStrLn ""
    hyperbolicDemo
    putStrLn ""
    printf "gcd(48, 18) = %d\n" (gcd 48 18 :: Int)
    printf "gcd(-48, 18) = %d\n" (gcd (-48) 18 :: Int)