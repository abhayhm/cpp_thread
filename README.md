  # Question:
  Given number of threads, string and number of characters to print given number of times.\
  Challenge is to print given number of characters from string in each thread in a circular way.\
  
  Input: ./a.out 3 4 2 abcdefghijklm
  
  Output:\
  Input: Thread count 3 | Char count 4 | Iterations 2 | String abcdefghijklm \
  Created Thread 1 with ID: 140351054304832 \
  Created Thread 2 with ID: 140351045912128 \
  Created Thread 3 with ID: 140351037519424 \
  Thread 0 :abcd \
  Thread 1 :efgh \
  Thread 2 :ijkl \
  Thread 0 :mabc \
  Thread 1 :defg \
  Thread 2 :hijk