from graphics import *
from time import *
from random import *
#s=set()
#print(list(map(str,input().split('*********************'))))
#print(input())
string=input()
while("DFA TRANSITION STATE TABLE" not in string):
	string=input()
	#print(string)
string=input()
string=input()
statesline=list(map(str,input().split(':')))
#print(statesline)
states=list(map(str,statesline[1].split(',')))[:-1]
for i in range(len(states)):
	string=""
	for j in states[i]:
		if(j.isalnum()):
			string+=j
	states[i]=string
string=input()
symbolline=list(map(str,input().split(':')))
alphabet=list(map(str,symbolline[1].split(',')))[:-1]
for i in range(len(alphabet)):
	string=""
	for j in alphabet[i]:
		if(j.isalnum()):
			string+=j
	alphabet[i]=string
for i in range(3):
	string=input()
li_dfa=[]
for i in range(len(states)):
	li=list(map(str,input().split('|')))[1:]
	for j in range(len(li)):
		string=""
		for k in li[j]:
			if(k.isalnum() or k=='-'):
				string+=k
		li[j]=string
	li_dfa.append(li)
#print(li_dfa)


#alphabet=["a","b","c"]
'''
for i in range(20000):
	li1=[]
	for j in range(3):
		li1.append(randint(0,19999))
	li.append(li1)
li=[[0,1,2],[2,3,0],[1,2,3],[3,3,4],[4,1,1]]
length=len(s)
while(length!=len(li[0])*len(li)):
	s.add(randint(10,100))
	length=len(s)
li_lengths=list(s)'''
di={}
for i in range(len(states)):
	di[states[i]]=i
li=[]
for i in li_dfa:
	temp=[]
	for j in i:
		if(j!='-'):
			temp.append(di[j])
	li.append(temp)
#print(li)
radius=375/len(li)
s=set()
l=len(s)
while(l<=len(states)*len(alphabet)):
	s.add(randint(10,100))
	l=len(s)
li_rand=list(s)
#print(li_rand)
win = GraphWin("DFA", 750, 750)
k=0
for i in range(len(li)):
	string=states[i]
	c = Circle(Point((2*i+1)*radius,375),radius)
	c.setFill(color_rgb(0, 0, 255))
	c.draw(win)
	state=Text(Point((2*i+1)*radius,375),string)
	state.setTextColor("white")
	state.draw(win)
	for j in range(len(li[i])):
		if(k%2==0):
			#rand=randint(10,100)
			rand=li_rand[k]
			xcoord=abs(((2*i+1)*radius-10)+((2*li[i][j]+1)*radius))/2
			aLine1 = Line(Point((2*i+1)*radius-10,375-radius), Point((2*i+1)*radius-10,375-radius-rand))
			aLine2 = Line(Point((2*i+1)*radius-10,375-radius-rand), Point((2*li[i][j]+1)*radius,375-radius-rand))
			#state=Text(Point((2*i+1)*radius,375-radius-rand),alphabet[j])
			state=Text(Point(xcoord,375-radius-rand),alphabet[j])
			aLine3 = Line(Point((2*li[i][j]+1)*radius,375-radius-rand), Point((2*li[i][j]+1)*radius,375-radius))
			aLine3.setArrow("last")
			aLine1.draw(win)
			aLine2.draw(win)
			state.draw(win)
			aLine3.draw(win)
			k+=1
		else:
			#rand=randint(10,100)
			rand=li_rand[k]
			xcoord=abs(((2*i+1)*radius+10)+((2*li[i][j]+1)*radius))/2
			aLine1 = Line(Point((2*i+1)*radius+10,375+radius), Point((2*i+1)*radius+10,375+radius+rand))
			aLine2 = Line(Point((2*i+1)*radius+10,375+radius+rand), Point((2*li[i][j]+1)*radius,375+radius+rand))
			#state=Text(Point((2*i+1)*radius,375+radius+rand),alphabet[j])
			state=Text(Point(xcoord,375+radius+rand),alphabet[j])
			aLine3 = Line(Point((2*li[i][j]+1)*radius,375+radius+rand), Point((2*li[i][j]+1)*radius,375+radius))
			aLine3.setArrow("last")
			aLine1.draw(win)
			aLine2.draw(win)
			state.draw(win)
			aLine3.draw(win)
			k+=1
	#win.getMouse() # pause for click in window
sleep(50)
win.close()