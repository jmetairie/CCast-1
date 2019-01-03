import math ; 
to_radian  = lambda x : (x/180.0)*3.14159 ; 
fid = open("cos.txt", "w") ; 
start = False ;
for ten_angle in range(0, 900):
	angle = ten_angle/10 ;
	fid.write(str(float(math.cos(to_radian(angle))))+",") ; 
	if ten_angle%5==0 and start:
		fid.write("\n") ;
	start = True ; 
fid.close() ; 
