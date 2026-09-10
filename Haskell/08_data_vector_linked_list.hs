-- 任务：数据结构 -- vector（动态数组）和链表。
-- 运行：runghc 08_08_data_vector_linked_list.hs

import Data.Array (Array, elems, listArray, (!), (//))
import Text.Printf (printf)


-- ---------- vector：动态数组（用不可变数组模拟） ----------

data Vec a = Vec
    { vSize :: Int
    , vData :: Array Int a
    }
    deriving (Show)

emptyVec :: Vec a
emptyVec = Vec 0 (listArray (0, -1) [])

vecFromList :: [a] -> Vec a
vecFromList xs = Vec (length xs) (listArray (0, length xs - 1) xs)

vecGet :: Vec a -> Int -> a
vecGet (Vec n arr) i
    | i < 0 || i >= n = error "vecGet: index out of bounds"
    | otherwise       = arr ! i

vecSet :: Vec a -> Int -> a -> Vec a
vecSet (Vec n arr) i x
    | i < 0 || i >= n = error "vecSet: index out of bounds"
    | otherwise       = Vec n (arr // [(i, x)])

vecPush :: a -> Vec a -> Vec a
vecPush x (Vec n arr) = Vec (n + 1) (listArray (0, n) (elems arr ++ [x]))

vecToList :: Vec a -> [a]
vecToList = elems . vData


-- ---------- 链表：自定义单链表 ----------

data LinkedList a = Nil | Cons a (LinkedList a)
    deriving (Show)

listFromList :: [a] -> LinkedList a
listFromList = foldr Cons Nil

listToList :: LinkedList a -> [a]
listToList Nil         = []
listToList (Cons x xs) = x : listToList xs

listPushFront :: a -> LinkedList a -> LinkedList a
listPushFront x xs = Cons x xs

listLength :: LinkedList a -> Int
listLength Nil         = 0
listLength (Cons _ xs) = 1 + listLength xs

listReverse :: LinkedList a -> LinkedList a
listReverse = go Nil
  where
    go acc Nil         = acc
    go acc (Cons x xs) = go (Cons x acc) xs


main :: IO ()
main = do
    let v1 = vecFromList [10, 20, 30, 40] :: Vec Int
    printf "vector = %s\n" (show (vecToList v1))
    printf "v1 ! 2 = %d\n" (vecGet v1 2)
    let v2 = vecPush 99 (vecSet v1 2 99)
    printf "after set/push = %s\n" (show (vecToList v2))
    putStrLn ""

    let l1 = listFromList [1, 2, 3, 4, 5] :: LinkedList Int
    printf "list = %s\n" (show (listToList l1))
    printf "length = %d\n" (listLength l1)
    printf "reverse = %s\n" (show (listToList (listReverse l1)))
    printf "pushFront 0 = %s\n" (show (listToList (listPushFront 0 l1)))