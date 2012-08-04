--- Read input from STDIN. Print output to STDOUT
import Data.List
import Debug.Trace

shuffle [] _ mult = mult
shuffle list@(x:xs) maxVal mult | x > maxVal = 0
				| otherwise  = ( shuffle xs (maxVal + 1) (rem (mult * (length takeList)) 1000000007))
				     where
				  	(takeList, restList) = span (<= maxVal) list

shuffleHelper list = (shuffle list 0 1)

testcase [] = []
testcase (count : restList) = (shuffleHelper (sort firstN)) : (testcase remainingList)
					where 
					  (firstN, remainingList) = splitAt count restList
main = do
          input1 <- getContents
          let resultList = testcase (map read (tail (words input1)))
          putStr . concat . intersperse "\n" . map show $ resultList


