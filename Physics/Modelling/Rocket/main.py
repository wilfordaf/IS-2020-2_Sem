from tkinter import *
from formulas import *
from sys import *


def start():
    alpha = float(ent1.get()) * pi / 180
    rocket_weight = float(ent2.get())*10**3
    fuel_weight = float(ent3.get())*10**3
    gas_velocity = float(ent4.get())
    burn_velocity = float(ent5.get())
    earth_weight = float(ent6.get())*10**24
    window.quit()
    graph(abs(alpha), rocket_weight, fuel_weight, gas_velocity, burn_velocity, earth_weight)


window = Tk()
window.title("Ввод данных")
window.geometry('350x160')
lbl1 = Label(window, text="Угол старта ракеты")
lbl1.grid(column=0, row=0)
lbl2 = Label(window, text="Масса ракеты")
lbl2.grid(column=0, row=1)
lbl3 = Label(window, text="Масса топлива")
lbl3.grid(column=0, row=2)
lbl4 = Label(window, text="Скорость истечения газа из сопла ракеты")
lbl4.grid(column=0, row=3)
lbl5 = Label(window, text="Скорость сжигания топлива")
lbl5.grid(column=0, row=4)
lbl6 = Label(window, text="Масса Земли")
lbl6.grid(column=0, row=5)
ent1 = Entry(window, width=10)
ent1.grid(column=1, row=0)
ent2 = Entry(window, width=10)
ent2.grid(column=1, row=1)
ent3 = Entry(window, width=10)
ent3.grid(column=1, row=2)
ent4 = Entry(window, width=10)
ent4.grid(column=1, row=3)
ent5 = Entry(window, width=10)
ent5.grid(column=1, row=4)
ent6 = Entry(window, width=10)
ent6.grid(column=1, row=5)
lbl_1 = Label(window, text="°")
lbl_1.grid(column=2, row=0)
lbl_2 = Label(window, text="кг^3")
lbl_2.grid(column=2, row=1)
lbl_3 = Label(window, text="кг^3")
lbl_3.grid(column=2, row=2)
lbl_4 = Label(window, text="м/c")
lbl_4.grid(column=2, row=3)
lbl_5 = Label(window, text="кг/c")
lbl_5.grid(column=2, row=4)
lbl_6 = Label(window, text="кг^24")
lbl_6.grid(column=2, row=5)
ent1.insert(1, "90")
ent2.insert(1, "34")
ent3.insert(1, "274")
ent4.insert(1, "4000")
ent5.insert(1, "800")
ent6.insert(1, "5.972")
btn = Button(window, text="     Пуск     ", command=start)
btn.grid(column=1, row=6)
window.mainloop()