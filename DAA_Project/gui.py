#!/usr/bin/python3

from tkinter import *
fields = 'NUMBER OF STATES', 'NUMBER OF SYMBOLS', 'STATES', 'SYMBOLS'
states=[]
symbols=[]
ents1=[]
import subprocess


def fetch(entries):
    for entry in entries:
        field = entry[0]
        text = entry[1].get()
        if(field=='NUMBER OF STATES'or field=='NUMBER OF SYMBOLS'):
            f.write(text+"\n")
        if(field=='STATES'):
              for i in text.split():
                    f.write(i+"\n")
                    states.append(i)
        if(field=='SYMBOLS'):
              for i in text.split():
                    f.write(i+"\n")
                    symbols.append(i)

        print('%s: "%s"' % (field, text))
    root1 = Tk()
    ents1=makeform1(root1,states,symbols)
    b3 = Button(root1, text='SUBMIT',
                command=(lambda e1=ents1: fetch1(e1)))
    b3.pack(side=LEFT, padx=5, pady=5)
    b4 = Button(root1, text='QUIT', command=root1.quit)
    b4.pack(side=LEFT, padx=5, pady=5)
def fetch1(entries):
    for entry in entries:
        field = entry[0]
        text = entry[1].get()
        f.write(''.join(text.split())+"\n")
        print('%s: "%s"' % (field, text))
    f.close()
    subprocess.call(['./nfa_to_dfa.sh'],shell=True)
def makeform(root, fields):
    entries = []
    for field in fields:
        row = Frame(root)
        lab = Label(row, width=15, text=field, anchor='w')
        ent = Entry(row)
        row.pack(side=TOP, fill=X, padx=5, pady=5)
        lab.pack(side=LEFT)
        ent.pack(side=RIGHT, expand=YES, fill=X)
        entries.append((field, ent))
    return entries


def makeform1(root1, states,symbols):
    entries = []
    symbols.append("lambda")
    width_label=int(550/(len(states)*len(symbols)))
    for state in states:
      for symbol in symbols:           
            row = Frame(root1)
            lab = Label(row, width=width_label, text="Transition from "+state+" on "+symbol, anchor='w')
            ent = Entry(row)
            row.pack(side=TOP, fill=X, padx=0, pady=0)
            lab.pack(side=LEFT)
            ent.pack(side=RIGHT, expand=YES, fill=X)
            entries.append((state, ent))
    return entries


if __name__ == '__main__':
    root = Tk()
    f=open("inputc.txt","w")
    ents = makeform(root, fields)
    # print(ents)
    # print(type(fields))
#     root.bind('<Return>', (lambda event, e=ents: fetch(e)))
    b1 = Button(root, text='SUBMIT',
                command=(lambda e=ents: fetch(e)))
    b1.pack(side=LEFT, padx=5, pady=5)
    b2 = Button(root, text='QUIT', command=root.quit)
    b2.pack(side=LEFT, padx=5, pady=5)

    root.mainloop()
