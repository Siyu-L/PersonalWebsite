
from collections import deque
import copy
import itertools
import math
from queue import PriorityQueue
import random

def create_tile_puzzle(rows, cols):
    temp = [[0 for j in range(cols)] for i in range(rows)]
    for i in range(rows):
        for j in range(cols):
            temp[i][j] = i*cols + j + 1
    temp[rows-1][cols-1] = 0

    return TilePuzzle(temp)

def find_zero(matrix, rows, cols):
    for i in range(rows):
        for j in range(cols):
            if matrix[i][j] == 0:
                return (i, j)
    


class TilePuzzle(object):
    
    # Required
    def __init__(self, board):
        self.board = board
        self.rows = len(self.board)
        self.cols = len(self.board[0])

    def get_board(self):
        return self.board

    def perform_move(self, direction):
        empty = find_zero(self.board, self.rows, self.cols)
        empty_row = empty[0]
        empty_col = empty[1]

        if direction == "up" and empty_row > 0:
            self.board[empty_row][empty_col] = self.board[empty_row-1][empty_col]
            self.board[empty_row-1][empty_col] = 0
            return True

        if direction == "down" and empty_row < self.rows-1:
            self.board[empty_row][empty_col] = self.board[empty_row+1][empty_col]
            self.board[empty_row+1][empty_col] = 0
            return True
                    
        if direction == "left" and empty_col > 0:
            self.board[empty_row][empty_col] = self.board[empty_row][empty_col-1]
            self.board[empty_row][empty_col-1] = 0            
            return True

        if direction == "right" and empty_col < self.cols-1:
            self.board[empty_row][empty_col] = self.board[empty_row][empty_col+1]
            self.board[empty_row][empty_col+1] = 0            
            return True

        return False

    def scramble(self, num_moves):
        for i in range(num_moves):
            direction = random.choice(["up", "down", "left", "right"])
            self.perform_move(direction)

    def is_solved(self):
        solved = create_tile_puzzle(self.rows, self.cols)
        return (self.board == solved.get_board())

    def copy(self):
        temp = copy.deepcopy(self.board)
        return TilePuzzle(temp)

    def successors(self):
        moves = ["up", "down", "left", "right"]
        for m in moves:
            new_p = self.copy()
            if new_p.perform_move(m):
                yield m, new_p

    # yields all solutions to current board of length no more than limit
    def iddfs_helper(self, limit, moves, visited):
        # get hashable representation of current puzzle
        curr_p = tuple(tuple(row) for row in self.board)

        # check if current puzzle has already been visited
        if curr_p in visited:
            return
        visited.add(curr_p)
        
        # if current board is solved, yield result and return
        if self.is_solved():
            yield moves
            return

        # if allowed number of moves left is 0, return
        if limit == 0:
            return
        
        # if current board is not solved
        # recursive call for each successor puzzle, having depth limit-1
        next = self.successors()
        for move, next_p in next:
            for i in next_p.iddfs_helper(limit-1, moves + [move], visited.copy()):
                yield i

    def find_solutions_iddfs(self):
        depth = 0
        
        # iterate over possible depth
        while True:
            # each depth must have its own visited set so deeper searches don't ignore paths visited by shorter searches
            visited = set()
            
            result = list(self.iddfs_helper(depth, [], visited))
            if result:
                for r in result:
                    yield r
                return
            depth += 1

    # manhattan distance heuristic
    def manhattan_dist(self):
        dist = 0
        for i in range(self.rows):
            for j in range(self.cols):
                val = self.board[i][j]
                
                # continue if grid is empty
                if val == 0:
                    continue
                
                # find the correct position of value using 1D array to 2D array index math
                # val = 1D array index + 1
                solved_col = (val - 1) % self.cols
                solved_row = (val - 1) // self.cols
                dist += abs(i - solved_row) + abs(j - solved_col)
        
        return dist

    def find_solution_a_star(self):
        # A* search for valid board
        # similar to LightsOutPuzzle, but with critical difference in priority of search
        frontier = PriorityQueue()
        # frontier will store tuples of (f_val, g_val, path, puzzle)
        frontier.put((self.manhattan_dist(), 0, [], self))

        visited = set()
        while not frontier.empty():
            f_val, g_val, path, puzzle = frontier.get()
            # get hashable representation of current puzzle

            curr_p = tuple(tuple(row) for row in puzzle.board)
            if curr_p in visited:
                continue
            visited.add(curr_p)

            # if current board is solved
            if puzzle.is_solved():
                return path
            
            # if current board is not solved
            next = puzzle.successors()
            for move, next_p in next:
                next_g = g_val + 1
                next_f = next_g + next_p.manhattan_dist()
                frontier.put((next_f, next_g, path + [move], next_p))
        
