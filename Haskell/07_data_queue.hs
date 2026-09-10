-- 任务：数据结构 -- 队列及基本操作（双列表队列）。
-- 运行：runghc 07_07_data_queue.hs

import Text.Printf (printf)

data Queue a = Queue
    { qFront :: [a]      -- 出队端
    , qBack  :: [a]      -- 入队端
    }
    deriving (Show)


-- ---------- 队列及基本操作 ----------

emptyQueue :: Queue a
emptyQueue = Queue [] []

push :: a -> Queue a -> Queue a
push x (Queue f b) = Queue f (x : b)

pop :: Queue a -> Maybe (a, Queue a)
pop (Queue (x : f) b) = Just (x, Queue f b)
pop (Queue [] [])     = Nothing
pop (Queue [] b) =
    case reverse b of
        []     -> Nothing
        (x:xs) -> Just (x, Queue xs [])

peek :: Queue a -> Maybe a
peek (Queue (x : _) _) = Just x
peek (Queue [] [])     = Nothing
peek (Queue [] b)      = case reverse b of
                            []     -> Nothing
                            (x : _) -> Just x

size :: Queue a -> Int
size (Queue f b) = length f + length b


main :: IO ()
main = do
    let q1 = foldl (flip push) (emptyQueue :: Queue Int) [10, 20, 30, 40, 50]
    printf "queue = %s\n" (show q1)
    printf "peek = %s, size = %d\n" (show (peek q1)) (size q1)

    case pop q1 of
        Nothing -> putStrLn "pop failed"
        Just (x, q2) -> do
            printf "dequeued %d, queue = %s\n" x (show q2)
            case pop q2 of
                Nothing -> putStrLn "second pop failed"
                Just (y, q3) -> printf "dequeued %d, queue = %s\n" y (show q3)