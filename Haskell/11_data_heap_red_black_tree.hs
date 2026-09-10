-- 任务：堆、红黑树。
-- 运行：runghc 11_11_data_heap_red_black_tree.hs

import Data.List (foldl')
import Text.Printf (printf)


-- ---------- 二叉堆（列表实现，小根堆） ----------

-- 完全二叉树按层序存放在列表中：i 的孩子是 2i+1 和 2i+2。
pushHeap :: Ord a => a -> [a] -> [a]
pushHeap x h = siftUp (h ++ [x]) (length h)
  where
    siftUp arr i
        | i <= 0 = arr
        | arr !! p <= arr !! i = arr
        | otherwise = siftUp (swapAt i p arr) p
      where
        p = (i - 1) `div` 2

popHeap :: Ord a => [a] -> Maybe (a, [a])
popHeap [] = Nothing
popHeap h@(x : _)
    | n == 1 = Just (x, [])
    | otherwise = Just (x, siftDown (replaceHead (init h) (last h)) 0)
  where
    n = length h

    replaceHead (_ : xs) v = v : xs
    replaceHead [] _ = []

    siftDown arr i =
        let n' = length arr
            l = 2 * i + 1
            r = 2 * i + 2
            m = pickSmallest arr i l r
        in if m == i then arr else siftDown (swapAt i m arr) m

    pickSmallest arr i l r =
        let m1 = if l < length arr && arr !! l < arr !! i then l else i
        in if r < length arr && arr !! r < arr !! m1 then r else m1

swapAt :: Int -> Int -> [a] -> [a]
swapAt i j xs =
    [ if k == i then xs !! j
      else if k == j then xs !! i
      else xs !! k
    | k <- [0 .. length xs - 1]
    ]

heapFromList :: Ord a => [a] -> [a]
heapFromList = foldl' (flip pushHeap) []


-- ---------- 红黑树（左倾红黑树 LLRB） ----------

data Color = Red | Black
    deriving (Eq, Show)

data RBTree a = RBE | RBN Color (RBTree a) a (RBTree a)
    deriving (Show)

rbEmpty :: RBTree a
rbEmpty = RBE

rbInsert :: Ord a => a -> RBTree a -> RBTree a
rbInsert x t = blacken (ins t)
  where
    ins RBE = RBN Red RBE x RBE
    ins (RBN c l y r)
        | x < y     = fixup (RBN c (ins l) y r)
        | x > y     = fixup (RBN c l y (ins r))
        | otherwise = RBN c l y r

    fixup t1 =
        let t2 = if isRed (rightOf t1) && not (isRed (leftOf t1))
                    then rotateLeft t1
                    else t1
            t3 = if isRed (leftOf t2) && isRed (leftOf (leftOf t2))
                    then rotateRight t2
                    else t2
        in if isRed (leftOf t3) && isRed (rightOf t3)
              then flipColors t3
              else t3

    rotateLeft (RBN c l x r@(RBN _ rl y rr)) = RBN c (RBN Red l x rl) y rr
    rotateLeft t = t

    rotateRight (RBN c l@(RBN _ ll x lr) y r) = RBN c ll x (RBN Red lr y r)
    rotateRight t = t

    flipColors (RBN _ l x r) = RBN Red (setBlack l) x (setBlack r)
    flipColors t = t

    setBlack (RBN _ l x r) = RBN Black l x r
    setBlack t = t

    blacken (RBN _ l x r) = RBN Black l x r
    blacken t = t

isRed :: RBTree a -> Bool
isRed (RBN Red _ _ _) = True
isRed _ = False

leftOf :: RBTree a -> RBTree a
leftOf (RBN _ l _ _) = l
leftOf _ = RBE

rightOf :: RBTree a -> RBTree a
rightOf (RBN _ _ _ r) = r
rightOf _ = RBE

rbFromList :: Ord a => [a] -> RBTree a
rbFromList = foldl' (flip rbInsert) RBE

rbInorder :: RBTree a -> [a]
rbInorder RBE = []
rbInorder (RBN _ l x r) = rbInorder l ++ [x] ++ rbInorder r


main :: IO ()
main = do
    let h = heapFromList [5, 3, 8, 1, 9, 2, 7] :: [Int]
    let popAll heap acc = case popHeap heap of
                              Nothing -> reverse acc
                              Just (x, rest) -> popAll rest (x : acc)
    printf "heap pop order: %s\n" (show (popAll h []))

    putStrLn ""
    let tree = rbFromList [7, 3, 18, 10, 22, 8, 11, 26, 2, 6, 13] :: RBTree Int
    printf "red-black tree inorder: %s\n" (show (rbInorder tree))