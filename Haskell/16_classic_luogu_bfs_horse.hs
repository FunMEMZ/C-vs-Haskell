-- 任务：BFS（洛谷 P1443 马的遍历）。
-- 输入格式：n m x y。
-- 样例输入：3 3 1 1
-- 运行：runghc 16_16_classic_luogu_bfs_horse.hs

import Control.Monad (forM_)
import Data.List (foldl')
import qualified Data.Map.Strict as M
import qualified Data.Sequence as Seq
import Text.Printf (printf)


main :: IO ()
main = do
    input <- getContents
    let (n : m : sx : sy : _) = map (read :: String -> Int) (words input)
        dist = bfs n m sx sy
        cell x y = M.findWithDefault (-1) (x, y) dist
    forM_ [1 .. n] $ \i -> do
        forM_ [1 .. m] $ \j -> printf "%5d" (cell i j)
        putStrLn ""

bfs :: Int -> Int -> Int -> Int -> M.Map (Int, Int) Int
bfs n m sx sy = go (Seq.singleton ((sx, sy), 0)) (M.singleton (sx, sy) 0)
  where
    moves = [(1, 2), (1, -2), (-1, 2), (-1, -2),
             (2, 1), (2, -1), (-2, 1), (-2, -1)]

    go queue dist
        | Seq.null queue = dist
        | otherwise =
            let ((x, y), d) = Seq.index queue 0
                rest = Seq.drop 1 queue
                neighbors =
                    [ (x + dx, y + dy)
                    | (dx, dy) <- moves
                    , let nx = x + dx
                    , let ny = y + dy
                    , nx >= 1, nx <= n, ny >= 1, ny <= m
                    ]
                (queue', dist') = foldl' (addNeighbor d) (rest, dist) neighbors
            in go queue' dist'

    addNeighbor d (queue, dist) pos
        | M.member pos dist = (queue, dist)
        | otherwise = (queue Seq.|> (pos, d + 1), M.insert pos (d + 1) dist)