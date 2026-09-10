-- 任务：Bellman-Ford 最短路（可检测负环）。
-- 输入：n m s，接下来 m 行 u v w。
-- 运行：runghc 13_13_shortest_path_bellman_ford.hs

import Data.Array (listArray, (!), elems, (//))
import Data.List (foldl')
import Text.Printf (printf)

type Edge = (Int, Int, Int)

infDist :: Int
infDist = 10 ^ 15

bellmanFord :: Int -> Int -> [Edge] -> Maybe [Int]
bellmanFord n s edges
    | hasNegativeCycle distFinal = Nothing
    | otherwise                  = Just (elems distFinal)
  where
    dist0 = listArray (1, n) (replicate n infDist) // [(s, 0)]

    relax dist (u, v, w)
        | dist ! u < infDist && dist ! u + w < dist ! v = dist // [(v, dist ! u + w)]
        | otherwise = dist

    distFinal = iterate (\d -> foldl' relax d edges) dist0 !! (n - 1)

    hasNegativeCycle dist =
        any (\(u, v, w) -> dist ! u < infDist && dist ! u + w < dist ! v) edges


main :: IO ()
main = do
    input <- getContents
    let ws = words input
        n = read (ws !! 0) :: Int
        m = read (ws !! 1) :: Int
        s = read (ws !! 2) :: Int
        nums = map (read :: String -> Int) (drop 3 ws)
        edges = [ (u, v, w) | (u : v : w : _) <- chunksOf 3 nums ]
    case bellmanFord n s edges of
        Nothing -> putStrLn "NEGATIVE CYCLE"
        Just ds -> putStrLn (unwords (map showDist ds))
  where
    showDist d = if d >= infDist then "INF" else show d

chunksOf :: Int -> [a] -> [[a]]
chunksOf _ [] = []
chunksOf k xs = let (a, b) = splitAt k xs in a : chunksOf k b