//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id$
// 
/// \file B4PrimaryGeneratorAction.cc
/// \brief Implementation of the B4PrimaryGeneratorAction class

#include "B4PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4PrimaryGeneratorAction* B4PrimaryGeneratorAction::fgInstance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const B4PrimaryGeneratorAction* B4PrimaryGeneratorAction::Instance()
{
	//Static access function via G4RunManager
	return fgInstance;
}

B4PrimaryGeneratorAction::B4PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fGenParticleSrc(0)
{
  fGenParticleSrc = new G4GeneralParticleSource();

  // default particle kinematic
  //
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
//  G4ParticleDefinition* particleDefinition = particleTable->FindParticle(particleName="e-");
  G4ParticleDefinition* particleDefinition = particleTable->FindParticle(particleName="gamma");
  fGenParticleSrc->SetParticleDefinition(particleDefinition);

  //set initial energy distribution
  this->setEnergyToY90betaICRP();

  //set initial position distribution to point source at origin
  G4SPSPosDistribution* posDist = fGenParticleSrc->GetCurrentSource()->GetPosDist();
  posDist->SetPosDisType("Point");
  posDist->SetCentreCoords(G4ThreeVector(0.,0.,0.));

  //set initial angular distribution
  G4SPSAngDistribution* angDist = fGenParticleSrc->GetCurrentSource()->GetAngDist();
  angDist->SetAngDistType("iso");

  fgInstance = this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4PrimaryGeneratorAction::~B4PrimaryGeneratorAction()
{
  delete fGenParticleSrc;
  fgInstance = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // This function is called at the begining of event

//  fGenParticleSrc->SetVerbosity(2);
  fGenParticleSrc->GeneratePrimaryVertex(anEvent);
//  fGenParticleSrc->SetVerbosity(0);
}

G4SPSEneDistribution* B4PrimaryGeneratorAction::setEnergyToY90betaICRP() {

	//set to Abr type, read point wise from file,
	G4SPSEneDistribution* eneDist = fGenParticleSrc->GetCurrentSource()->GetEneDist();
	eneDist->SetEnergyDisType("Arb");
	eneDist->ArbEnergyHistoFile("Y90_ICRP_beta_spectra.txt");
	eneDist->ArbInterpolate("Spline");
	return eneDist;

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

