--- eead input from STDIN. Print output to STDOUT
import Data.Char
import Debug.Trace

max_lcd::Int->[Int]->Int
max_lcd friend unfriendList = foldl lcm 1 (map (gcd friend) unfriendList)

max_remaining::Int->[Int]->Int
max_remaining friend unfriendList = div friend  (max_lcd friend unfriendList) - 1

get_ans::Int->[Int]->Int
get_ans a b | trace ("myfun " ++ show a ++ " " ++ show b) False = undefined
get_ans friend unfriendList = length ( divisors (max_remaining friend unfriendList) )

divisors 0 = []
divisors n = 1 : filter ((==0) . rem n) [2 .. n `div` 2]

main = do 
          input1 <- getLine
          input2 <- getLine
          let count = read ((words input1)!!0)
          let friend = read ((words input1)!!1) 
          putStr (show count)
          putStr " "
          putStr (show friend)
          let unfriendList = [read ((words input2)!!n) | n<-[0..(count-1)]]
          putStr (show unfriendList)
          let ans = get_ans friend unfriendList
          putStr (show ans)

