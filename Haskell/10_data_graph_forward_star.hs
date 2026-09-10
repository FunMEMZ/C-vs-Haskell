-- 任务：有向图、无向图（强制使用链式前向星）。
-- 运行：runghc 10_10_data_graph_forward_star.hs

import Data.Array (Array, (!), listArray)
import qualified Data.IntMap.Strict as IM
import Data.List (foldl')
import Text.Printf (printf)

type Edge = (Int, Int, Int)   -- (u, v, weight)

data ForwardStar = ForwardStar
    { fsN      :: Int
    , fsM      :: Int
    , fsHead   :: Array Int Int    -- 顶点 -> 第一条边编号；0 表示无边
    , fsTo     :: Array Int Int    -- 边编号 -> 终点
    , fsNext   :: Array Int Int    -- 边编号 -> 下一条边编号
    , fsWeight :: Array Int Int    -- 边编号 -> 边权
    }


-- ---------- 链式前向星：从边表构建 ----------

buildForwardStar :: Int -> Bool -> [Edge] -> ForwardStar
buildForwardStar n directed inputEdges = ForwardStar n m headArr toArr nextArr weightArr
  where
    edges = if directed
                then inputEdges
                else concatMap (\(u, v, w) -> [(u, v, w), (v, u, w)]) inputEdges
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


-- ---------- 遍历某个顶点的所有出边 ----------

edgesFrom :: ForwardStar -> Int -> [(Int, Int)]   -- [(终点, 边权)]
edgesFrom g u = go (fsHead g ! u)
  where
    go 0 = []
    go e = (fsTo g ! e, fsWeight g ! e) : go (fsNext g ! e)

printGraph :: String -> ForwardStar -> IO ()
printGraph title g = do
    putStrLn title
    mapM_ (\u -> printf "%d: %s\n" u (show (edgesFrom g u))) [1 .. fsN g]


main :: IO ()
main = do
    let dg = buildForwardStar 4 True
                [ (1, 2, 3), (1, 3, 4), (2, 4, 5), (3, 4, 6) ]
    printGraph "directed graph:" dg
    putStrLn ""
    let ug = buildForwardStar 4 False
                [ (1, 2, 3), (2, 3, 4), (3, 4, 5) ]
    printGraph "undirected graph:" ug