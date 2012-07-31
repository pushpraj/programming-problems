--- Read input from STDIN. Print output to STDOUT

import Data.Char
import Data.List
import Debug.Trace

breakIn _ [] = []
breakIn size list =  (take size list) : (breakIn size (drop size list)) 
breakInAct size list = reverse (breakIn size list)


shuffleOnce [] = []
shuffleOnce (x:xs) = (head x) : (shuffleOnce ( xs ++ [tail x]))


--shuffle n k [1..n] = 0
--shuffle n n _ = 2
shuffle n k list | list == [1..n] = 0
		 | otherwise = 1 + (shuffle n k (shuffleOnce (breakInAct pileSize list)))
				where pileSize = div n k 

--testcase :: a -> a
testcase [] = []
testcase (cardSizeN : cardPileK : restList) = (shuffle cardSizeN cardPileK [1..cardSizeN]) : (testcase restList)

main = do
          input1 <- getContents
          let resultList = testcase (map read (tail (words input1)))
          putStr (show resultList)


