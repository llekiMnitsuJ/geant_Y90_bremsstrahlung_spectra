{
	const Int_t numFiles=24;
	//the sumHist has to match the original...?
	TH1D* sumHist = new TH1D("photonSpectra", "photon spectra in sphere", 231, 0., 2.3);
	
	cout << "Opening, reading, and summing histograms or you can just use hadd command!!!...\n";
	for(Int_t i=1; i <=numFiles; ++i){
		TString str;
		str = "Y90_beta_spectra_photons_"+TString::Itoa(i, 10)+".root";
		cout << "file: " << str << "\n";
		TFile *f =  (TFile*)gROOT->GetListOfFiles()->FindObject(str);
		if (!f) {
			f = new TFile(str);
			TH1D* tempHistogram = f->Get("photonSpectra");
			sumHist->Add(tempHistogram);
			delete tempHistogram;		
		} else {
			cout << "could't find file: " << str << "\n";
		}
		//delete f;	
	}


	// **************************************** Plots  **********************************************
	
	//gStyle->SetPalette(1);
	//gStyle->SetOptStat(0);
	
	// First Canvas
	sumHist->Draw();
	
	//write contents of summed histogram.
	cout << "---------------contents of summed histogram----------------\n";
	cout << "low edge, high edge, val\n";
	for(Int_t i=1; i <= sumHist->GetNbinsX(); ++i){
		cout << sumHist->GetBinLowEdge(i) << ","
			<< sumHist->GetBinLowEdge(i) + sumHist->GetBinWidth(i) << ","
			<< sumHist->GetBinContent(i) << "\n";
	}
	cout << "-----------------------------------------------------------\n";
}
