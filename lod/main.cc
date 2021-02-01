#include <stdio.h>
#include <stdint.h>
#include <string>
#include "inc/loader.h"


int main(int argc, char* argv[]) {

	size_t i;
	Binary bin;
	Section *sec;
	Symbol *sym;
	std::string fname;
	std::string sec_to_get  = "";


	if (argc < 2) {
		printf("Usage %s <binary>\n", argv[0]);
		return 1;
	}

	if (argv[1][0] == '-') {
		// If flag used
		// update as add flags
		if (argv[1][1] == 's') {
			sec_to_get = argv[2];
			fname.assign(argv[3]);
		}
	} else {
		fname.assign(argv[1]);
	}

	if(load_binary(fname, &bin, Binary::BIN_TYPE_AUTO) < 0) {
		return 1;
	}

	printf("loaded binary '%s' %s%s (%u bits) entry@0%016jx\n", bin.filename.c_str(), bin.type_str.c_str(), bin.arch_str.c_str(), bin.bits, bin.entry);

	if (sec_to_get != "") {

		for (i = 0; bin.sections.size(); i++) {
			sec = &bin.sections[i];
			if(sec->name == sec_to_get) {
				for(int j = 1; j < sec->size; j++) {
					printf("%02x ", sec->bytes[j]);
					if(j % 16 == 0) {
						for (int as_i = 0; as_i < 16; as_i++) {
							char c_toprint = sec->bytes[j-as_i];
							if (c_toprint > 0x20 && c_toprint < 0x7E) {
								printf("%c", c_toprint);
							} else printf(".");
						}
						printf("\n");
					}
				}
				break;
			}
		}
	} else {



		printf("Sections: %lu\n", bin.sections.size());
		for (i = 0; i < bin.sections.size(); i++) {
			sec = &bin.sections[i];
			printf("  0x%016jx %-8ju %-20s %s\n", sec->vma, sec->size, sec->name.c_str(), sec->type == Section::SEC_TYPE_CODE ? "CODE" : "DATA");
		}



		if(bin.symbols.size() > 0) {
			for (i = 0; i < bin.symbols.size(); i++) {
				sym = &bin.symbols[i];
				printf("  %-40s 0x%016jx %s\n", sym->name.c_str(), sym->addr, (sym->type & Symbol::SYM_TYPE_FUNC) ? "FUNC" : "");
			}
		}


	}



	unload_binary(&bin);
	return 0;


	




}
