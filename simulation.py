import random
import math
import tkinter as tk
from functools import partial


WINDOW_GEOMETRY = "2500x1200" # WxH
DEFAULT_MAX_DIAMETER = 400
DEFAULT_N_OBJECTS = 10
DEFAULT_VELOCITY = 5 # pixels per tick
INFLATE_RADIUS = 1.5
SIMULATION_UPDATE_FREQ = 60  # ticks per second
COLORS = ["white", "black", "red", "blue", "cyan", "yellow", "magenta"]


def frequency_to_millisecond():
    return int(1000.0 / SIMULATION_UPDATE_FREQ)


class Circle:
    def __init__(self, canvas, w, h, velocity):
        self.canvas = canvas
        self.w = w
        self.h = h
        self.velocity = velocity
        self.ticks = 0
        # Ensure that x,y is inside the frame by using the radius
        # as boundary when generating
        self.diameter = random.randrange(5, 15, 1)
        r = int(self.diameter / 2)
        self.x = random.randrange(r, self.w - r, 1)
        self.y = random.randrange(r, self.h - r, 1)
        color = COLORS[random.randrange(0, len(COLORS), 1)]
        self.id = self.canvas.create_oval(self.x-r, self.y-r, self.x+r,
                                          self.y+r, fill=color, outline=color)

    def move(self):
        coords = self.canvas.coords(self.id)
        if (len(coords) == 0):
            return
        if (self.ticks <= 0):
            angle = math.radians(random.randrange(0, 360, 1))
            # convert an angle to coordinates
            self.x_inc = int(self.velocity * math.cos(angle))
            self.y_inc = int(self.velocity * math.sin(angle))
            # keep the same course for 10 - 120 ticks
            self.ticks = random.randrange(10, 120, 5)
        self.ticks -= 1

        # keep the object inside the frame
        x1, y1, x2, y2 = coords

        if (x1 + self.x_inc <= 0):
            self.x_inc = abs(self.x_inc)
        elif (x2 + self.x_inc >= self.w):
            self.x_inc = -abs(self.x_inc)
        if (y1 + self.y_inc <= 0):
            self.y_inc = abs(self.y_inc)
        elif (y2 + self.y_inc >= self.h):
            self.y_inc = -abs(self.y_inc)

        self.canvas.move(self.id, self.x_inc, self.y_inc)

    def collided(self, diameter):
        # we can only eat smaller or equally sized opponents
        if (self.diameter <= diameter):
            return False
        # use an fixed inflation radius instead of the radius of the object
        # to be eaten since it makes the simulation more interesting to watch
        r = INFLATE_RADIUS
        c = self.canvas.coords(self.id)
        self.canvas.coords(self.id, c[0]-r, c[1]-r, c[2]+r, c[3]+r)
        c = self.canvas.coords(self.id)
        self.diameter = c[2] - c[0]
        self.velocity += 1 # increase velocity for each hit

        return True

    def color_scroll(self):
        if (self.ticks <= 0):
            self.canvas.itemconfig(self.id,
                                   fill=COLORS[random.randrange(0, len(COLORS), 1)])
            self.ticks = int(SIMULATION_UPDATE_FREQ / 5)
        self.ticks -= 1


class Simulation:
    def __init__(self, gui):
        self.root = gui.root
        self.gui = gui
        self.populate()
        self.paused = False
        self.winner = None
        self.simulation_running = False
        self.n_objects = DEFAULT_N_OBJECTS
        self.velocity = DEFAULT_VELOCITY
        # start the main simulation loop
        self.root.after(frequency_to_millisecond(), self.mainloop)

    def populate(self):
        # the simulation frame with a canvas so we can draw objects on it
        simulation_frame = tk.Frame(self.root)
        simulation_frame.pack(anchor=tk.N, fill=tk.BOTH, expand=True,
                              side=tk.BOTTOM)
        self.canvas = tk.Canvas(simulation_frame,
                                width=simulation_frame.winfo_width(),
                                height=simulation_frame.winfo_width(),
                                borderwidth=0,
                                highlightthickness=0,
                                bg="green")
        self.canvas.pack(fill=tk.BOTH, expand=tk.YES)
        # must call to ensure right geometry
        self.root.update()
        # get canvas geometry
        self.w = self.canvas.winfo_width()
        self.h = self.canvas.winfo_height()

    def start(self, n_objects, velocity):
        self.simwinner = None
        self.objects = []
        self.canvas.delete("all")
        self.objects = [Circle(self.canvas, self.w, self.h, velocity)
                        for obj in range(n_objects)]

    def stop(self):
        self.paused = False

    def pause(self):
        self.paused = not self.paused

    def collision_detection(self, obj):
        bb = self.canvas.bbox(obj.id) # find bounding box of object
        if (bb is None):
            return
        # Give me all objects except myself
        lst = list(filter(lambda id: id != obj.id,
                          list(self.canvas.find_overlapping(*bb))))
        for id in lst:
            object_hit = list(filter(lambda o: o.id == id, self.objects))[0]
            if (obj.collided(object_hit.diameter)):
                self.canvas.delete(object_hit.id)
                # create an new list of all objects except for the one we collided with
                self.objects = list(filter(lambda o: o.id != id, self.objects))

    def visit_all(self):
        # iterate over all objects that are still part of the simulation
        for obj in list(self.objects):
            obj.move()
            self.collision_detection(obj)

        return len(self.objects)

    def mainloop(self):
        # schedule that this function is called again after x milliseconds
        self.root.after(frequency_to_millisecond(), self.mainloop)
        if (not self.simulation_running or self.paused):
            if (self.winner is not None):
                self.winner.color_scroll()
            return
        if (self.visit_all() <= 1):
            # if there is only one object left we have a winner
            self.gui.start_stop_command()
            self.winner = self.objects[0] if len(self.objects) == 1 else None


class UserInterface:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title('Simulation - to eat or to be eaten')
        self.root.geometry(WINDOW_GEOMETRY)
        self.root.resizable(False, False)
        self.populate()
        self.simulation = Simulation(self)
        # start the GUI event loop
        self.root.mainloop()

    def populate(self):
        widget_frame = tk.Frame(self.root)
        widget_frame.pack(anchor=tk.W, fill=tk.Y, expand=False, side=tk.TOP)
        label = tk.Label(widget_frame, text="# objects")
        label.pack(side=tk.LEFT)
        self.n_objects_entry = tk.Entry(widget_frame, bd=5)
        self.n_objects_entry.pack(side=tk.LEFT)
        self.n_objects_entry.insert(tk.END, str(DEFAULT_N_OBJECTS))
        label = tk.Label(widget_frame, text="Velocity")
        label.pack(side=tk.LEFT)
        self.velocity_entry = tk.Entry(widget_frame, bd=5)
        self.velocity_entry.insert(tk.END, str(DEFAULT_VELOCITY))
        self.velocity_entry.pack(side=tk.LEFT)
        # we use partial so we can call a member function, it would not
        # be neccessary if the function did not belong to a class
        # command is called when the button is pressed
        self.start_button = tk.Button(widget_frame, text="Start",
                                      command=partial(self.start_stop_command))
        self.start_button.pack(side=tk.LEFT)
        self.pause_button = tk.Button(widget_frame, text ="Pause",
                                      command=partial(self.pause_resume_command))
        self.pause_button.pack(side=tk.LEFT)
        self.pause_button["state"] = tk.DISABLED
        button = tk.Button(widget_frame, text="Exit",
                           command = self.root.destroy)
        button.pack(side=tk.LEFT)

    def start_stop_command(self):
        self.simulation.simulation_running = not self.simulation.simulation_running
        if (self.simulation.simulation_running):
            # ugly method for ensuring that we only input numbers
            try:
                n_objects = int(self.n_objects_entry.get())
            except:
                n_objects = DEFAULT_N_OBJECTS
                self.n_objects_entry.delete(0, 'end')
                self.n_objects_entry.insert(tk.END, str(DEFAULT_N_OBJECTS))
            try:
                velocity = int(self.velocity_entry.get())
            except:
                velocity = DEFAULT_VELOCITY
                self.velocity_entry.delete(0, 'end')
                self.velocity_entry.insert(tk.END, str(DEFAULT_VELOCITY))
            self.start_button['text'] = 'Stop'
            self.pause_button["state"] = tk.ACTIVE
            self.simulation.start(n_objects, velocity)
        else:
            self.start_button['text'] = 'Start'
            self.pause_button['text'] = 'Pause'
            self.pause_button["state"] = tk.DISABLED
            self.simulation.stop()

    def pause_resume_command(self):
        self.simulation.pause()
        self.pause_button['text'] = 'Resume' if self.simulation.paused else 'Pause'
        return


if __name__ == "__main__":
    simulation = UserInterface()
