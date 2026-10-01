import re
import os
import time
import random
import argparse
import tkinter as tk


class GameBoard(tk.Frame):
    def __init__(self, parent, config):
        self.config = config
        
        self.rows = config['nsize']
        self.columns = config['nsize']
        self.size = 50
        self.cost = 0

        self.ships = {}
        self.pieces = {}

        canvas_width = self.rows * self.size
        canvas_height = self.rows * self.size

        tk.Frame.__init__(self, parent)
        self.canvas = tk.Canvas(self,
                                borderwidth=0,
                                highlightthickness=0,
                                width=canvas_width,
                                height=canvas_height + 20,
                                background='white')

        self.canvas.pack(side='top', fill='both', expand=True, padx=2, pady=2)
        self.canvas.bind('<Configure>', self.refresh)

        self.winfo_toplevel().title('Lunar Lockout')

    def add_piece(self, name, row=0, column=0):
        self.canvas.create_oval(0, 0, self.size - 15, self.size - 15,
                                outline='black', fill=name, tags=('piece', name))
        self.place_piece(name, row, column)

    def place_piece(self, name, row, column):
        self.pieces[name] = (row, column)
        x0 = (column * self.size) + 5
        y0 = (row * self.size) + 10
        self.canvas.coords(name, x0 + 5, y0 + 5, x0 + self.size - 15, y0 + self.size - 15)

    def update_cost(self, cost):
        yc = self.size * self.rows + 10
        if self.cost is not None:
            self.canvas.delete(self.cost)
        self.cost = self.canvas.create_text((0, yc), text=f'Total Cost: {cost}', anchor='w')

    def refresh(self, event):
        x_size = int((event.width - 1) / self.columns)
        y_size = int((event.height - 1) / self.rows)
        self.size = min(x_size, y_size)
        self.canvas.delete('square')
        for row in range(self.rows):
            for col in range(self.columns):
                x1 = (col * self.size)
                y1 = (row * self.size)
                x2 = x1 + self.size
                y2 = y1 + self.size
                bg_color = '#FF9991' if (row, col) in self.config['sequence'] else '#CFCFC4'
                self.canvas.create_rectangle(x1, y1, x2, y2, outline='black', fill=bg_color, tags='square')
                
                # Cell costs
                x3 = x2 - 45
                y3 = y1 + self.size / 10 + 3
                self.canvas.create_text((x3, y3), text=config['costs'][row][col], anchor='w')

        for name in self.pieces:
            self.place_piece(name, self.pieces[name][0], self.pieces[name][1])

        self.canvas.tag_raise('piece')
        self.canvas.tag_lower('square')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('problem_number', type=int)
    parser.add_argument('--file', action='store_true')
    args = parser.parse_args()

    if args.file:
        with open('plan.txt', mode='r') as f:
            plan = ''.join(f.readlines())
    else:
        cmd = f'./ff -o moving_target_domain.pddl -f moving_target_problem_{args.problem_number}.pddl'
        plan = os.popen(cmd).read()

    plan = re.findall(r'MOVE R C\d+ C\d+ C\d+ C\d+ G C\d+ C\d+ C\d+ C\d+ T\d+ T\d+\n', plan)
    if len(plan) == 0:
        print('No possible plan found!')
        exit()
    
    total_cost = 0
    
    with open(f'moving_target_problem_{args.problem_number}.pddl', mode='r') as f:
        config = ''.join(f.readlines())

        nsize = re.findall(r'C\d', config)
        nsize = max(list(map(lambda x: int(x[1:]), nsize))) + 1

        robot = re.findall(r'at R C\d+ C\d+ T\d+\)', config)[0][:-1]
        ghost = re.findall(r'at G C\d+ C\d+ T\d+\)', config)[0][:-1]

        sequence = re.findall(r'scheduled C\d+ C\d+ T\d+\)', config)

        costs = re.findall(r'\(cost C\d+ C\d+\) \d+\)', config)
        cost_matrix = [[1 for _ in range(nsize)] for _ in range(nsize)]
        for i in range(nsize):
            for j in range(nsize):
                _, _, _, c = costs[i * nsize + j].split()
                cost_matrix[i][j] = c[:-1]

        config = {
            'nsize': nsize,
            'robot': (int(robot.split()[2][1:]), int(robot.split()[3][1:])),
            'ghost': (int(ghost.split()[2][1:]), int(ghost.split()[3][1:])),
            'sequence': list(map(lambda x: (int(x.split()[1][1:]), int(x.split()[2][1:])), sequence)),
            'costs': cost_matrix
        }

    root = tk.Tk()
    board = GameBoard(root, config)
    board.pack(side='top', fill='both', expand='true', padx=4, pady=4)

    total_cost = 0

    board.add_piece('red', config['robot'][0], config['robot'][1])
    board.add_piece('green', config['ghost'][0], config['ghost'][1])
    board.update_cost(0)

    root.update_idletasks()
    root.update()

    for idx, line in enumerate(plan):
        time.sleep(1)

        _, _, xr, yr, xrn, yrn, _, xg, yg, xgn, ygn, _, _ = line[:-1].split()
        xr, yr, xrn, yrn = int(xr[1:]), int(yr[1:]), int(xrn[1:]), int(yrn[1:])
        xg, yg, xgn, ygn = int(xg[1:]), int(yg[1:]), int(xgn[1:]), int(ygn[1:])

        print(f'Step {idx + 1:2}: Robot from ({xr}, {yr}) to ({xrn}, {yrn})')
        total_cost += int(cost_matrix[xrn][yrn])
        board.update_cost(total_cost)
        board.place_piece('red', xrn, yrn)
        board.place_piece('green', xgn, ygn)

        root.update_idletasks()
        root.update()

    root.mainloop()
