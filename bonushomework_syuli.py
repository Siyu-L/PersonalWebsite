############################################################
# ECS170: Informed Search
############################################################

student_name = "Siyu Li"

############################################################
# Imports
############################################################

# Include your imports here, if any are used.

from collections import deque
import copy
import itertools
import math
from queue import PriorityQueue
import random

############################################################
# Section 1: Tile Puzzle
############################################################

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
        

############################################################
# Section 2: Grid Navigation
############################################################

def euclid_dist(p1, p2):
    # euclid distance = sqrt((x2-x1)^2 + (y2-y1)^2)
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

def get_grid_successors(grid, scene):
    rows, cols = len(scene), len(scene[0])
    curr_row, curr_col = grid[0], grid[1]
    
    # directions: up, down, left, right, up-left, up-right, down-left, down-right
    directions = [(1, 0), (-1, 0), (0, -1), (0, 1), (1, -1), (1, 1), (-1, -1), (-1, 1)]

    for d in directions:
        new_row = curr_row + d[0]
        new_col = curr_col + d[1]

        # ensure that the new grid is within the range of the scene and that there is no obstacle at that grid
        if (new_row >= 0 and new_row < rows) and (new_col >= 0 and new_col < cols) and scene[new_row][new_col] == False:
            yield (new_row, new_col) 

def find_path(start, goal, scene):
    # A* for goal grid
    # similar implementation to find_solution_a_star
    start_x, start_y = start[0], start[1]
    goal_x, goal_y = goal[0], goal[1]
    
    # if the start or goal an obstacle, no solution
    if scene[start_x][start_y] or scene[goal_x][goal_y]:
        return None
    
    # frontier will store tuples of (f_val, g_val, current, path)
    frontier = PriorityQueue()
    frontier.put((euclid_dist(start, goal), 0, start, [start]))
    visited = set()
    
    while not frontier.empty():
        f_val, g_val, curr_grid, path = frontier.get()

        if curr_grid in visited:
            continue
        visited.add(curr_grid)

        # if goal has been reached
        if curr_grid == goal:
            return path
        
            
        # if current grid is not goal
        next = get_grid_successors(curr_grid, scene)
        for next_grid in next:
            if next_grid not in visited:
                next_g = g_val + euclid_dist(curr_grid, next_grid)
                next_f = next_g + euclid_dist(next_grid, goal)
                frontier.put((next_f, next_g, next_grid, path + [next_grid]))
    
    return None

############################################################
# Section 3: Linear Disk Movement, Revisited
############################################################

# successor function reused from homework 1
def disk_successors_distinct(grid, length):

    for i in range(length):
        # if there is a disk at this position
        if grid[i] > 0:
            
            # Option 1: move to adjacent empty cell
            if i + 1 < length and grid[i+1] == 0:
                temp_list = list(grid)
                temp_list[i+1] = temp_list[i]
                temp_list[i] = 0
                
                yield (i, i+1), tuple(temp_list)
            
            # Option 2: move to empty cell two spaces away, provided disk is located between
            if i + 2 < length and grid[i+1] > 0 and grid[i+2] == 0:
                temp_list = list(grid)
                temp_list[i+2] = temp_list[i]
                temp_list[i] = 0
                
                yield (i, i+2), tuple(temp_list)

            # Option 3: move back to adjacent empty cell
            if i - 1 >= 0 and grid[i-1] == 0:
                temp_list = list(grid)
                temp_list[i-1] = temp_list[i]
                temp_list[i] = 0
                
                yield (i, i-1), tuple(temp_list)
            
            # Option 4: move to empty cell two spaces back, provided disk is located between
            if i - 2 >= 0 and grid[i-1] > 0 and grid[i-2] == 0:
                temp_list = list(grid)
                temp_list[i-2] = temp_list[i]
                temp_list[i] = 0
                
                yield (i, i-2), tuple(temp_list)

# heuristic function h(x)
def heuristic(curr, goal, n):
    dist = 0
    for i in range(1,n+1):
        dist += abs(curr.index(i) - goal.index(i))
    
    return dist



def solve_distinct_disks(length, n):
    # A* for valid disk placement
    frontier = PriorityQueue()

    start = tuple(i for i in range(1,n+1)) + tuple([0] * (length - n))
    end = tuple([0] * (length - n)) + tuple(i for i in reversed(range(1,n+1)))

    # frontier will store tuples of (f_val, g_val, current, moves)
    # heuristic: total distance from goal
    frontier.put((heuristic(start, end, n), 0, start, []))
    visited = set()
    
    # same logic as with the previous two A* searches
    while not frontier.empty():
        f_val, g_val, curr_grid, moves = frontier.get()
        
        
        if curr_grid in visited:
            continue
        visited.add(curr_grid)
        
        # if disks have been solved
        if curr_grid == end:
            return moves

        # if current disk placement is not the goal
        next = disk_successors_distinct(curr_grid, length)
        for move, next_grid in next:
            if next_grid not in visited:
                next_g = g_val + 1
                next_f = next_g + heuristic(next_grid, end, n)
                frontier.put((next_f, next_g, next_grid, moves + [move]))
    return []


############################################################
# Section 4: Dominoes Game
############################################################

def create_dominoes_game(rows, cols):
    pass

class DominoesGame(object):

    # Required
    def __init__(self, board):
        pass

    def get_board(self):
        pass

    def reset(self):
        pass

    def is_legal_move(self, row, col, vertical):
        pass

    def legal_moves(self, vertical):
        pass

    def perform_move(self, row, col, vertical):
        pass

    def game_over(self, vertical):
        pass

    def copy(self):
        pass

    def successors(self, vertical):
        pass

    def get_random_move(self, vertical):
        pass

    # Required
    def get_best_move(self, vertical, limit):
        pass

