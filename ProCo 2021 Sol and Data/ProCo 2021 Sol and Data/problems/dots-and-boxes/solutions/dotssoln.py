import sys

lines = sys.stdin.readlines()
N = int(lines[0].strip('\n'))

# Dict storing information about the boxes
# Each key is the center coordinate (x+0.5, y+0.5)
# of the box
grid = {}

player_moves = ""
score_a = 0
score_b = 0
player_turn = "A"
scored_this_round = False
# Loop over moves
for line in lines[1:]:
    scored_this_round = False
    player_moves += player_turn
    x1, y1, x2, y2 = [int(x) for x in line.strip('\n').split(' ')]
    if y1 == y2:
        # Horizontal line
        # Affects boxes above and below
        for i in range(2):
            cell_x = (x1 + x2) / 2.0
            cell_y = y1 - 0.5
            if i == 1:
                cell_y = y1 + 0.5
            if (cell_x, cell_y) in grid:
                grid[(cell_x, cell_y)] += 1
            else:
                grid[(cell_x, cell_y)] = 1

            # All four walls present, it is a score
            # Increment score, player goes again next turn
            if grid[(cell_x, cell_y)] == 4:
                if player_turn == "A":
                    score_a += 1
                    scored_this_round = True
                else:
                    score_b += 1
                    scored_this_round = True
    elif x1 == x2:
        # Vertical line
        # Affects boxes to the left and right
        for i in range(2):
            cell_y = (y1+y2) / 2.0
            cell_x = x1 - 0.5
            if i == 1:
                cell_x = x1 + 0.5
            if (cell_x, cell_y) in grid:
                grid[(cell_x, cell_y)] += 1
            else:
                grid[(cell_x, cell_y)] = 1

            # All four walls present, it is a score
            # Increment score, player goes again next turn
            if grid[(cell_x, cell_y)] == 4:
                if player_turn == "A":
                    score_a += 1
                    scored_this_round = True
                else:
                    score_b += 1
                    scored_this_round = True


    if not scored_this_round:
        if player_turn == "A":
            player_turn = "B"
        else:
            player_turn = "A"

print(player_moves)
print(str(score_a) + " " + str(score_b))