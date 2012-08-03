--- Read input from STDIN. Print output to STDOUT
import Data.List (intersperse)

nextLoc k s i =  k - (quot i s) -1 + (rem i s) * k 

shuffle k s 0 count = count
shuffle k s i count =  shuffle k s (nextLoc k s i) (count +1)

shuffleHelper n k = shuffle k s (nextLoc k s 0) 1
			where s = div n k

--testcase :: a -> a
testcase [] = []
testcase (cardSizeN : cardPileK : restList) = (shuffleHelper cardSizeN cardPileK) : (testcase restList)

main = do
          input1 <- getContents
          let resultList = testcase (map read (tail (words input1)))
          putStr . concat . intersperse "\n" . map show $ resultList


