
#include "GenesRepo.h"
#include "Tests.h"
#include <assert.h>

void Tests::test_insertGene() {

	GenesRepo gr;

	gr.insertGene(Gene("E_Coli_K12", "yqgE", "ATGACATCATCATTG"));
	gr.insertGene(Gene("M_tuberculosis", "ppiA", "TCTTCATCATCATCGG"));
	gr.insertGene(Gene("Mouse", "Col2a1", "TTAAAGCATGGCTCTGTG"));
	gr.insertGene(Gene("E_Coli_ETEC", "yqgE", "GTGACAGCGCCCTTCTTTCCACG"));
	gr.insertGene(Gene("E_Coli_K12", "hokC", "TTAATGAAGCATAAGCTTGATTTC"));

	try {
		gr.insertGene(Gene("E_Coli_K12", "yqgE", "ATGACATCATCATTG"));
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	assert(gr.getSize() == 5);

	gr.insertGene(Gene("E_Coli_K123", "yqgEE", "ATGACATCATCATTG"));

	assert(gr.getSize() == 6);

	gr.insertGene(Gene("E_Coli_K1234", "yqgEE", "ATGACATCATCATTG"));
	assert(gr.getSize() == 7);
}
