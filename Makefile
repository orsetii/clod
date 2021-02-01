.PHONY: lod dis

lod:
	g++ -g -o clod main.cc inc/loader.cc -lbfd

dis:
	g++ -g -o cldis  dis/main.cc inc/loader.cc -lbfd -lcapstone
