--- Read input from STDIN. Print output to STDOUT
import Data.List
import Debug.Trace

shuffle [] 0 _ mult = mult
shuffle list matchedCount maxVal mult 	| matchedCount ==0 && (head list) > maxVal = 0
					| otherwise  = trace ("shuffle:"++ show list ++ show matchedCount ) ( shuffle restList (newMatchedCount-1) (maxVal + 1) (rem (mult * newMatchedCount) 1000000007))
				     			where
					  			(takeList, restList) = span (<= maxVal) list
								newMatchedCount = (length takeList) + matchedCount

shuffleHelper list = (shuffle list 0 0 1)

testcase [] = []
testcase (count : restList) = (shuffleHelper (sort firstN)) : (testcase remainingList)
					where 
					  (firstN, remainingList) = splitAt count restList
main = do
          input1 <- getContents
          let resultList = testcase (map read (tail (words input1)))
          putStr . concat . intersperse "\n" . map show $ resultList


