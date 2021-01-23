#define PACKAGE "libgrive" /* dummy to keep <bfd.h> happy */
#include <bfd.h>
#include "loader.h"

int load_binary(std::string &fname, Binary *bin, Binary::BinaryType type) {

	return load_binary_bfd(fname, bin, type);

}

void unload_binary(Binary *bin) {

	size_t i;
	Section *sec;

	for(i = 0; i < bin->sections.size(); i++) {
		sec = &bin->sections[i];
		if (sec->bytes) free(sec->bytes);
	}

}

static bfd* open_bfd(std::string &fname) {

	static int bfd_inited = 0;
	bfd *bfd_h;

	if (!bfd_inited) {
		bfd_init();
		bfd_inited = 1;
	}

	bfd_h = bfd_openr(fname.c_str(), NULL);
	if(!bfd_h) {
		fprintf(stderr, "failed to open binary '%s' (%s)\n", fname.c_str(), bfd_errmsg(bfd_get_error()));
		return NULL;
	}

	if(!bfd_check_format(bfd_h, bfd_object)) {
		fprintf(stderr, "file '%s' does not look like an executable (%s)\n", fname.c_str(), bfd_errmsg(bfd_get_error()));
		return NULL;
	}

	/* Some versions of bfd_check_format set a wrong_format error before detecting the format and then 
	 * neglect to unset it once the format has been detected. 
	 * We unset it manually to prevent problems.
	 */

	bfd_set_error(bfd_error_no_error);

	if(bfd_get_flavour(bfd_h) == bfd_target_unknown_flavour) {
		fprintf(stderr, "unrecognized format for binary '%s' (%s)\n", fname.c_str(), bfd_errmsg(bfd_get_error()));
		return NULL;
	}

	return bfd_h;


}

static int load_binary_bfd(std::string &fname, Binary *bin, Binary::BinaryType type) {

	int ret;
	bfd *bfd_h;
	const bfd_arch_info_type *bfd_info;
	
	bfd_h = NULL;
	bfd_h = open_bfd(fname);

	if(!bfd_h) {
		goto fail;
	}

	bin->filename = std::string(fname);
	bin->entry = bfd_get_start_address(bfd_h);

	bin->type_str = std::string(bfd_h->xvec->name);
	switch(bfd_h->xvec->flavour) {
		case bfd_target_elf_flavour:
			bin->type = Binary::BIN_TYPE_ELF;
			break;
		case bfd_target_coff_flavour:
			bin->type = Binary::BIN_TYPE_PE;
			break;
		case bfd_target_unknown_flavour:
		default:
			fprintf(stderr, "unsupported binary type (%s)\n", bfd_h->xvec->name);
			goto fail;
	}

	bfd_info = bfd_get_arch_info(bfd_h);
	bin->arch_str = std::string(bfd_info->printable_name);

	switch(bfd_info->mach) {
		case bfd_mach_i386_i386:
			bfd->arch = Binary::ARCH_X86;
			bfd->bits = 32;
			break;
		case bfd_mach_x86_64:
			bin->arch = Binary::ARCH_X86;
			bin->bits = 64;
			break;
		default:
			fprintf(stderr, "unsupported architecture (%s)\n", bfd_info->arch_name);
			goto fail;
	}
	/* Attempt Symbol Handling */
	load_symbols_bfd(


}

