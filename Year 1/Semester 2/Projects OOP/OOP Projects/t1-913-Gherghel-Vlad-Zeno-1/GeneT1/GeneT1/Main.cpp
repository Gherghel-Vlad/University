

#include "GenesRepo.h"
#include "GenesService.h"
#include "Gene.h"
#include "UI.h"
#include "Tests.h"

int main() {

	GenesRepo gr;

	//E_Coli_K12 | yqgE | ATGACATCATCATTG
	//	M_tuberculosis | ppiA | TCTTCATCATCATCGG
	//	Mouse | Col2a1 | TTAAAGCATGGCTCTGTG
	//	E_Coli_ETEC | yqgE | GTGACAGCGCCCTTCTTTCCACG
	//	E_Coli_K12 | hokC | TTAATGAAGCATAAGCTTGATTTC

	gr.insertGene(Gene("E_Coli_K12", "yqgE", "ATGACATCATCATTG"));
	gr.insertGene(Gene("M_tuberculosis", "ppiA", "TCTTCATCATCATCGG"));
	gr.insertGene(Gene("Mouse", "Col2a1", "TTAAAGCATGGCTCTGTG"));
	gr.insertGene(Gene("E_Coli_ETEC", "yqgE", "GTGACAGCGCCCTTCTTTCCACG"));
	gr.insertGene(Gene("E_Coli_K12", "hokC", "TTAATGAAGCATAAGCTTGATTTC"));

	GenesService gs{ gr };

	UI ui{ gs };

	ui.startUI();

	Tests t;

	t.test_insertGene();

	return 0;
}