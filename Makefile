.PHONY: lod dis

lod:
	g++ -g -o clod main.cc inc/loader.cc -lbfd

dis:
	g++ -g -o cldis  dis/linear.cc inc/loader.cc -lbfd -lcapstone

disrec:
	g++ -g -o cldis  dis/recursive.cc inc/loader.cc -lbfd -lcapstone

