-- 任务：数据结构 -- 栈及基本操作。
-- 运行：runghc 06_06_data_stack.hs

import Text.Printf (printf)

newtype Stack a = Stack [a]
    deriving (Show)


-- ---------- 栈及基本操作 ----------

emptyStack :: Stack a
emptyStack = Stack []

push :: a -> Stack a -> Stack a
push x (Stack xs) = Stack (x : xs)

pop :: Stack a -> Maybe (a, Stack a)
pop (Stack [])       = Nothing
pop (Stack (x : xs)) = Just (x, Stack xs)

peek :: Stack a -> Maybe a
peek (Stack [])       = Nothing
peek (Stack (x : _))  = Just x

size :: Stack a -> Int
size (Stack xs) = length xs


main :: IO ()
main = do
    let s1 = foldl (flip push) (emptyStack :: Stack Int) [10, 20, 30, 40, 50]
    printf "after pushes: %s\n" (show s1)
    printf "peek: %s\n" (show (peek s1))
    printf "size: %d\n" (size s1)

    case pop s1 of
        Nothing -> putStrLn "pop failed"
        Just (x, s2) -> do
            printf "popped %d, now: %s\n" x (show s2)
            case pop s2 of
                Nothing -> putStrLn "second pop failed"
                Just (y, s3) -> printf "popped %d, now: %s\n" y (show s3)