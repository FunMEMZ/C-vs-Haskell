-- 任务：树，二叉树及其前中后序遍历。
-- 运行：runghc 09_09_data_binary_tree_traversal.hs

import Text.Printf (printf)


-- ---------- 二叉树与二叉搜索树插入 ----------

data Tree a = Empty | Node (Tree a) a (Tree a)
    deriving (Show)

insertBST :: Ord a => a -> Tree a -> Tree a
insertBST x Empty = Node Empty x Empty
insertBST x t@(Node left val right)
    | x < val   = Node (insertBST x left) val right
    | x > val   = Node left val (insertBST x right)
    | otherwise = t

treeFromList :: Ord a => [a] -> Tree a
treeFromList = foldl (flip insertBST) Empty

treeHeight :: Tree a -> Int
treeHeight Empty = 0
treeHeight (Node l _ r) = 1 + max (treeHeight l) (treeHeight r)


-- ---------- 前序、中序、后序遍历 ----------

preorder :: Tree a -> [a]
preorder Empty = []
preorder (Node l x r) = x : preorder l ++ preorder r

inorder :: Tree a -> [a]
inorder Empty = []
inorder (Node l x r) = inorder l ++ [x] ++ inorder r

postorder :: Tree a -> [a]
postorder Empty = []
postorder (Node l x r) = postorder l ++ postorder r ++ [x]


main :: IO ()
main = do
    let tree = treeFromList [5, 3, 8, 1, 4, 7, 9, 2, 6] :: Tree Int
    printf "tree height = %d\n" (treeHeight tree)
    printf "preorder:  %s\n" (show (preorder tree))
    printf "inorder:   %s\n" (show (inorder tree))
    printf "postorder: %s\n" (show (postorder tree))