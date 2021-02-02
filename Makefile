.PHONY: lod dis rop

lod:
	g++ -g -o clod main.cc inc/loader.cc -lbfd

dis:
	g++ -g -o cldis  dis/linear.cc inc/loader.cc -lbfd -lcapstone

disrec:
	g++ -g -o cldis  dis/recursive.cc inc/loader.cc -lbfd -lcapstone
rop:
	g++ -g -o ropper  rop/main.cc inc/loader.cc -lbfd -lcapstone

clean:
	rm ./cldis
	rm ./clod

