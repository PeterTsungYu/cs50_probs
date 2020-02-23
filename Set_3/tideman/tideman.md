## Test-1
./tideman Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Charlie

## Test-2
./tideman Alice Bob Charlie
Number of voters: 2
Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Rank 1: Charlie
Rank 2: Bob
Rank 3: Alice

Charlie:Alice   = 2:0 (Edge = 2 - 0 = 2)
Charlie:Bob     = 2:0 (Edge = 2 - 0 = 2)
Alice:Bob       = 1:1 (tie)
pair_count = 2

Charlie -> Alice    (true)
Charlie -> Bob      (true)
Locked = 2

Source: Charlie

## Test-3-1
./tideman Alice Bob Charlie
Number of voters: 4
Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Rank 1: Charlie
Rank 2: Bob
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Bob
Rank 3: Alice

Charlie:Alice   = 4:0 (Edge = 4 - 0 = 4)
Charlie:Bob     = 3:1 (Edge = 3 - 1 = 2)
Alice:Bob       = 1:3 (Edge = 3 - 1 = 2)
pair_count = 3

Charlie -> Alice    (true)
Charlie -> Bob    (true)
locked = 2

Source: Charlie

## Test-3-2
./tideman Alice Bob Charlie
Number of voters: 4
Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

Charlie:Alice   = 2:2 (tie)
Charlie:Bob     = 1:3 (Edge = 2)
Alice:Bob       = 3:1 (Edge = 2)
pair_count = 2

Bob -> Charlie    (true)
Alice -> Bob      (true)
locked = 2

Source: Alice (1 true 0 false)

## Test-4
./tideman Alice Bob Charlie
Number of voters: 5
Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

Rank 1: Charlie
Rank 2: Bob
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Alice
Rank 3: Charlie

Charlie:Alice   = 3:2 (Edge = 3 - 2 = 1)
Charlie:Bob     = 2:3 (Edge = 3 - 2 = 1)
Alice:Bob       = 2:3 (Edge = 3 - 2 = 1)
pair_count = 3

Charlie -> Alice    (true)
Bob -> Charlie      (true)
Bob -> Alice        (true)
locked = 3

Source: Bob (2 true 0 false)

## Test-5
./tideman Alice Bob Charlie
Number of voters: 5
Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

Rank 1: Charlie
Rank 2: Bob
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

Charlie:Alice   = 3:2 (Edge = 3 - 2 = 1)
Charlie:Bob     = 2:3 (Edge = 3 - 2 = 1)
Alice:Bob       = 3:2 (Edge = 3 - 2 = 1)
pair_count = 3

Charlie -> Alice    (true)
Bob -> Charlie      (true)
Alice -> Bob        (true)
locked = 3

Source: None

## Test-6
./tideman Alice Bob Charlie Peter
Number of voters: 3
Rank 1: Charlie
Rank 2: Alice
Rank 3: Peter
Rank 4: Bob

Rank 1: Alice
Rank 2: Peter
Rank 3: Bob
Rank 4: Charlie

Rank 1: Bob
Rank 2: Charlie
Rank 3: Peter
Rank 4: Alice

Charlie:Alice   = 2:1
Charlie:Bob     = 1:2
Alice:Bob       = 2:1
Peter:Alice     = 1:2
Peter:Bob       = 2:1
Peter:Charlie   = 1:2
pair_count = 6

Charlie -> Alice    (true)
Bob -> Charlie      (true)
Alice -> Bob        (true)
Peter -> Bob        (true)
Alice -> Peter      (true)
Charlie -> Peter    (true)
locked = 6

Source: Alice (2 true 1 false) Charlie (2 true 1 false)