--- Read input from STDIN. Print output to STDOUT
import Data.List
import Debug.Trace

shuffle [] _ mult = trace ("shuffle: def:" ++ show mult)  mult
shuffle list@(x:xs) maxVal mult | x > maxVal = trace ("shuffle base:" ++ show maxVal ++ show mult ++ show list ) 0
				| otherwise  = trace ("shuffle: " ++ show maxVal ++ show mult ++ show list ) ( shuffle xs (maxVal + 1) (mult * (length takeList)))
				     where
				  	(takeList, restList) = span (<= maxVal) list
				  	takeListLength = length takeList

shuffleHelper list = trace ("helper: "++ show list ++ ".") (shuffle list 0 1)

testcase [] = []
testcase (count : restList) = (shuffleHelper (sort firstN)) : (testcase remainingList)
					where 
					  (firstN, remainingList) = splitAt count restList
main = do
          input1 <- getContents
          let resultList = testcase (map read (tail (words input1)))
          putStr . concat . intersperse "\n" . map show $ resultList


