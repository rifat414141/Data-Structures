// first circle is at (x0, y0) with radius r0
// second circle is at (x1, y1) with radius r1
// (x3, y3) are intersection of two circles
d=sqr((x1-x0)^2 + (y1-y0)^2)
a=(r0^2-r1^2+d^2)/(2*d)
h=sqr(r0^2-a^2)
x2=x0+a*(x1-x0)/d   
y2=y0+a*(y1-y0)/d   
x3=x2+h*(y1-y0)/d       // also x3=x2-h*(y1-y0)/d
y3=y2-h*(x1-x0)/d       // also y3=y2+h*(x1-x0)/d
x4=x2-h*(y1-y0)/d
y4=y2+h*(x1-x0)/d

