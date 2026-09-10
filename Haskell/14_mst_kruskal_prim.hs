-- 任务：最小生成树（Kruskal 与 Prim）。
-- 输入：n m，接下来 m 行 u v w（无向边）。
-- 运行：runghc 14_14_mst_kruskal_prim.hs

import Data.Array (accumArray, (!), Array, listArray)
import qualified Data.IntMap.Strict as IM
import qualified Data.IntSet as IS
import Data.List (foldl', sortOn)
import Text.Printf (printf)

type Edge = (Int, Int, Int)

infW :: Int
infW = 10 ^ 15


-- ---------- Kruskal + 并查集（IntMap 版） ----------

kruskal :: Int -> [Edge] -> Maybe Int
kruskal n edges = go (sortOn (\(_, _, w) -> w) edges) (IM.fromList [(i, i) | i <- [1 .. n]]) 0 0
  where
    find parent x =
        case IM.lookup x parent of
            Just y | y == x    -> x
                   | otherwise -> find parent y
            Nothing -> x

    go [] _ total cnt
        | cnt == n - 1 = Just total
        | otherwise    = Nothing
    go ((u, v, w) : rest) parent total cnt
        | find parent u == find parent v = go rest parent total cnt
        | otherwise =
            let ru = find parent u
                rv = find parent v
            in go rest (IM.insert ru rv parent) (total + w) (cnt + 1)


-- ---------- Prim + 邻接矩阵 ----------

prim :: Int -> [Edge] -> Maybe Int
prim n edges = go (IM.singleton 1 0) IS.empty 0 0
  where
    adj = accumArray min infW ((1, 1), (n, n))
              (concat [[((u, v), w), ((v, u), w)] | (u, v, w) <- edges])

    go distMap visited total cnt
        | cnt == n = Just total
        | IM.null distMap = Nothing
        | otherwise =
            let (u, du) = IM.findMin distMap
                rest = IM.deleteMin distMap
            in if IS.member u visited
                  then go rest visited total cnt
                  else
                      let visited' = IS.insert u visited
                          rest' = foldl' (addEdge u visited') rest [1 .. n]
                      in go rest' visited' (total + du) (cnt + 1)

    addEdge u visited distMap v =
        let w = adj ! (u, v)
        in if not (IS.member v visited) && w < infW
              then IM.insertWith min v w distMap
              else distMap


main :: IO ()
main = do
    input <- getContents
    let ws = words input
        n = read (ws !! 0) :: Int
        m = read (ws !! 1) :: Int
        nums = map (read :: String -> Int) (drop 2 ws)
        edges = [ (u, v, w) | (u : v : w : _) <- chunksOf 3 nums ]
        showResult (Just x) = show x
        showResult Nothing  = "-1"
    printf "Kruskal MST weight = %s\n" (showResult (kruskal n edges))
    putStrLn ""
    printf "Prim MST weight = %s\n" (showResult (prim n edges))

chunksOf :: Int -> [a] -> [[a]]
chunksOf _ [] = []
chunksOf k xs = let (a, b) = splitAt k xs in a : chunksOf k b