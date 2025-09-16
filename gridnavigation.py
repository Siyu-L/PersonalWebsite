
from collections import deque
import copy
import itertools
import math
from queue import PriorityQueue
import random

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
