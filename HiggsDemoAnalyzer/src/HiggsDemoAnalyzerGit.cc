// user include files, general
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

//------ EXTRA HEADER FILES--------------------//
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// for Root tree
#include "TTree.h"

// for muon information
#include "DataFormats/MuonReco/interface/Muon.h"

// class declaration
class HiggsDemoAnalyzerGit : public edm::EDAnalyzer
{
public:
  explicit HiggsDemoAnalyzerGit(const edm::ParameterSet &);
  ~HiggsDemoAnalyzerGit();

private:
  virtual void beginJob();
  virtual void analyze(const edm::Event &, const edm::EventSetup &);
  virtual void endJob();
  bool providesGoodLumisection(const edm::Event &iEvent);

  // Declaring a Tree
  TTree *t1;

  double pt_gmu;

  int nRun, nEvt, nLumi; 
};

HiggsDemoAnalyzerGit::HiggsDemoAnalyzerGit(const edm::ParameterSet &iConfig)
{
  // now do what ever initialization is needed
  edm::Service<TFileService> fs;

  // Transverse momentum of Global Muon in a Tree
  t1 = fs->make<TTree>("treegmu", "treegmu");
  t1->Branch("pt_gmu", &pt_gmu, "pt_gmu/D");
}

HiggsDemoAnalyzerGit::~HiggsDemoAnalyzerGit()
{
}

// ------------ method called for each event  ------------//
void HiggsDemoAnalyzerGit::analyze(const edm::Event &iEvent, const edm::EventSetup &iSetup)
{
  edm::Handle<reco::TrackCollection> gmuons;
  iEvent.getByLabel("globalMuons", gmuons);

  for (unsigned t = 0; t < gmuons->size(); t++)
  {
    const reco::Track &iMuon = (*gmuons)[t];

    pt_gmu = iMuon.pt();
    t1->Fill();

  }
} // HiggsDemoAnalyzerGit::analyze ends

// ------ method called once each job just before starting event loop ---------//

void HiggsDemoAnalyzerGit::beginJob()
{

}

// ------------ method called once each job just after ending the event loop  ------------
void HiggsDemoAnalyzerGit::endJob()
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(HiggsDemoAnalyzerGit);
