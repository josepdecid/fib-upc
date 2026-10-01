import re
import os
import time
import argparse
import tkinter as tk


class GameBoard(tk.Frame):
    def __init__(self, parent, rows=5, columns=5, size=50):
        self.rows = rows
        self.columns = columns
        self.size = size

        self.ships = {}
        self.pieces = {}

        canvas_width = columns * size
        canvas_height = rows * size

        tk.Frame.__init__(self, parent)
        self.canvas = tk.Canvas(self,
                                borderwidth=0,
                                highlightthickness=0,
                                width=canvas_width,
                                height=canvas_height,
                                background='bisque')

        self.canvas.pack(side='top', fill='both', expand=True, padx=2, pady=2)
        self.canvas.bind('<Configure>', self.refresh)

        self.winfo_toplevel().title('Lunar Lockout')

    def add_piece(self, name, row=0, column=0):
        self.canvas.create_oval(0, 0, self.size - 10, self.size - 10,
                                outline='black', fill=name, tags=('piece', name))
        self.place_piece(name, row, column)

    def place_piece(self, name, row, column):
        self.pieces[name] = (row, column)
        x0 = (column * self.size) + 5
        y0 = (row * self.size) + 5
        self.canvas.coords(name, x0, y0, x0 + self.size - 10, y0 + self.size - 10)

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
                bg_color = '#FF9991' if (row == 2) and (col == 2) else '#CFCFC4'
                self.canvas.create_rectangle(x1, y1, x2, y2, outline='black', fill=bg_color, tags='square')
        for name in self.pieces:
            self.place_piece(name, self.pieces[name][0], self.pieces[name][1])

        self.canvas.tag_raise('piece')
        self.canvas.tag_lower('square')


def read_spacecrafts(problem_number):
    with open(f'lunar_lockout_{problem_number}.pddl', mode='r') as f:
        lines = ''.join(f.readlines())
        matches = [x.group() for x in re.finditer(r'\(at [A-Za-z]+ C[1-5] C[1-5]\)', lines)]
        
        spacecrafts = {}
        for match in matches:
            _, k, x, y = match[:-1].split()
            if k == 'Red' and x == 'C3' and y == 'C3':
                continue
            spacecrafts[k] = (int(x[1]), int(y[1]))

    return spacecrafts


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('problem_number', type=int)
    parser.add_argument('--file', action='store_true')
    args = parser.parse_args()

    spacecrafts = read_spacecrafts(args.problem_number)

    if args.file:
        with open('plan.txt', mode='r') as f:
            plan = ''.join(f.readlines())
    else:
        cmd = f'./ff -o lunar_lockout_domain.pddl -f lunar_lockout_{args.problem_number}.pddl'
        plan = os.popen(cmd).read()
    plan = [x.group().lower() for x in re.finditer(r'MOVE\-[A-Z]+ [A-Z]+ C[0-9] C[0-9] C[0-9]', plan)]

    root = tk.Tk()
    board = GameBoard(root)
    board.pack(side='top', fill='both', expand='true', padx=4, pady=4)

    for spacecraft_name, coords in spacecrafts.items():
        board.add_piece(spacecraft_name.lower(), coords[0] - 1, coords[1] - 1)

    root.update_idletasks()
    root.update()

    for idx, line in enumerate(plan):
        time.sleep(2)

        action = line.strip().split('move-')[1]
        direction, spacecraft, _, _, cell = action.split()
        if direction == 'up' or direction == 'down':
            new_coords = (int(cell[-1]) - 1, board.pieces[spacecraft][1])
        else:
            new_coords = (board.pieces[spacecraft][0], int(cell[-1]) - 1)

        print(f'Step {idx + 1:2}: move {spacecraft} to ({new_coords[0] + 1}, {new_coords[1] + 1})')
        board.place_piece(spacecraft, new_coords[0], new_coords[1])

        root.update_idletasks()
        root.update()

    root.mainloop()
