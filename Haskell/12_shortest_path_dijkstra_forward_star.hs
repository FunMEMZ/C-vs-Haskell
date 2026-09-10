-- 任务：前向星下图的最短路（Dijkstra，O(n^2 + m)）。
-- 输入：n m s，接下来 m 行 u v w（有向边，非负权）。
-- 运行：runghc 12_12_shortest_path_dijkstra_forward_star.hs

import Data.Array (Array, (!), elems, listArray, (//))
import qualified Data.IntMap.Strict as IM
import Data.List (foldl')
import Text.Printf (printf)

type Edge = (Int, Int, Int)

infDist :: Int
infDist = 10 ^ 15


-- ---------- 链式前向星 ----------

data ForwardStar = ForwardStar
    { fsN      :: Int
    , fsM      :: Int
    , fsHead   :: Array Int Int
    , fsTo     :: Array Int Int
    , fsNext   :: Array Int Int
    , fsWeight :: Array Int Int
    }

buildForwardStar :: Int -> [Edge] -> ForwardStar
buildForwardStar n edges = ForwardStar n m headArr toArr nextArr weightArr
  where
    m = length edges

    step (hm, nm, tm, wm) (e, (u, v, w)) =
        let prev = IM.findWithDefault 0 u hm
        in ( IM.insert u e hm
           , IM.insert e prev nm
           , IM.insert e v tm
           , IM.insert e w wm
           )

    (headMap, nextMap, toMap, weightMap) =
        foldl' step (IM.empty, IM.empty, IM.empty, IM.empty) (zip [1 ..] edges)

    headArr   = listArray (1, n) [IM.findWithDefault 0 v headMap | v <- [1 .. n]]
    edgeArr f = listArray (1, m) [IM.findWithDefault 0 e f | e <- [1 .. m]]
    toArr     = edgeArr toMap
    nextArr   = edgeArr nextMap
    weightArr = edgeArr weightMap

edgesFrom :: ForwardStar -> Int -> [(Int, Int)]
edgesFrom g u = go (fsHead g ! u)
  where
    go 0 = []
    go e = (fsTo g ! e, fsWeight g ! e) : go (fsNext g ! e)


-- ---------- Dijkstra ----------

dijkstra :: Int -> Int -> ForwardStar -> [Int]
dijkstra n s g = go dist0 vis0
  where
    dist0 = listArray (1, n) (replicate n infDist) // [(s, 0)]
    vis0  = listArray (1, n) (replicate n False)

    go dist vis
        | all id (elems vis) = elems dist
        | otherwise =
            let candidates = [v | v <- [1 .. n], not (vis ! v), dist ! v < infDist]
            in case candidates of
                [] -> elems dist
                _ ->
                    let u = foldl1 (\a b -> if dist ! a <= dist ! b then a else b) candidates
                        dist' = foldl' (relax (dist ! u)) dist (edgesFrom g u)
                        vis'  = vis // [(u, True)]
                    in go dist' vis'

    relax du dist (v, w) =
        let nd = du + w
        in if nd < dist ! v then dist // [(v, nd)] else dist


main :: IO ()
main = do
    input <- getContents
    let ws = words input
        n = read (ws !! 0) :: Int
        m = read (ws !! 1) :: Int
        s = read (ws !! 2) :: Int
        nums = map (read :: String -> Int) (drop 3 ws)
        edges = [ (u, v, w) | (u : v : w : _) <- chunksOf 3 nums ]
        g = buildForwardStar n edges
        ans = map (\d -> if d >= infDist then -1 else d) (dijkstra n s g)
    printf "%s\n" (unwords (map show ans))

chunksOf :: Int -> [a] -> [[a]]
chunksOf _ [] = []
chunksOf k xs = let (a, b) = splitAt k xs in a : chunksOf k b