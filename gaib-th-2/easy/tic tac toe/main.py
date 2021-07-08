
# --- Heuristic ---
# Let x as max and o as min
def linechecker(array : "Array") -> int:
    if array[0] == array[1] and array[1] == array[2]:
        if array[0] == 'x':
            return 10
        elif array[0] == 'o':
            return -10
    return 0

def h(gameBoard : "2D Array") -> int:
    lines = []
    for row in gameBoard:
        lines.append(row)

    for i in range(3):
        col = [gameBoard[0][i], gameBoard[1][i], gameBoard[2][i]]
        lines.append(col)

    lines.append([gameBoard[i][i] for i in range(3)])
    lines.append([gameBoard[2-i][i] for i in range(3)])

    for line in lines:
        if linechecker(line) != 0:
            return linechecker(line)

    return 0



def isdone(gameBoard : "2D Array") -> bool:
    for row in gameBoard:
        for el in row:
            if el == None:
                return False
    return True

def copy(a):
    newcp = []
    for x in a:
        rw = [p for p in x]
        newcp.append(rw)
    return newcp


def minimax(gameBoard : "2D Array", isMax : bool) -> int:
    if isdone(gameBoard) or h(gameBoard) != 0:
        return h(gameBoard)

    currentHeuristic = 0
    if isMax:
        currentHeuristic = -1000
        for i in range(3):
            for j in range(3):
                if gameBoard[i][j] == None:
                    testMove = copy(gameBoard)
                    testMove[i][j] = 'x'
                    rec = minimax(testMove, False)
                    currentHeuristic = max(rec, currentHeuristic)
    else:
        currentHeuristic = 1000
        for i in range(3):
            for j in range(3):
                if gameBoard[i][j] == None:
                    testMove = copy(gameBoard)
                    testMove[i][j] = 'o'
                    rec = minimax(testMove, True)
                    currentHeuristic = min(rec, currentHeuristic)
    return currentHeuristic


def getMove(gameBoard : "2D Array") -> (int, int):
    currentMove = (-1, -1)
    for i in range(3):
        for j in range(3):
            if gameBoard[i][j] == None:
                currentMove = (i, j)

    currentHeuristic = 1000
    for i in range(3):
        for j in range(3):
            if gameBoard[i][j] == None:
                testMove = copy(gameBoard)
                testMove[i][j] = 'o'
                evaluated = minimax(testMove, False)
                if evaluated < currentHeuristic:
                    currentMove = (i, j)
                    currentHeuristic = evaluated

    return currentMove



game = [ [None, None, None],
        [None, None, None],
        [None, None, None] ]

while not isdone(game) or h(game) != 0:
    row = int(input("Row ")) - 1
    col = int(input("Col ")) - 1
    game[row][col] = 'x'

    (aiRow, aiCol) = getMove(game)
    game[aiRow][aiCol] = 'o'

    for i in range(3):
        for j in range(3):
            print(game[i][j], " ", end="")
        print()
