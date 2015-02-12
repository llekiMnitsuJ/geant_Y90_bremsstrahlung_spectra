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
/// \file B4aSteppingAction.cc
/// \brief Implementation of the B4aSteppingAction class

#include "B4aSteppingAction.hh"
#include "B4aEventAction.hh"
#include "B4DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aSteppingAction::B4aSteppingAction(
                      const B4DetectorConstruction* detectorConstruction,
                      B4aEventAction* eventAction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aSteppingAction::~B4aSteppingAction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4aSteppingAction::UserSteppingAction(const G4Step* step)
{
// Collect photon energy that crosses from sphere into world

  
  // get pointer to prestep & poststep
  G4StepPoint* prePoint = step->GetPreStepPoint();
  G4StepPoint* postPoint = step->GetPostStepPoint();

//  G4cout << "in user stepping action!" << G4endl;
  //check if on surface of sphere...
  if ( (postPoint->GetStepStatus() == fGeomBoundary) &&
	   (prePoint->GetPhysicalVolume()->GetName() == "sphere") &&
	   (postPoint->GetPhysicalVolume()->GetName() == "World")){


	  //now check that it is a photon
	  G4Track* myTrack = step->GetTrack();
	  const G4ParticleDefinition* myParticleDef = myTrack->GetParticleDefinition();
	  const G4String particleName = myParticleDef->GetParticleName();
//	  G4cout << "on surface of sphere with " << particleName << G4endl;
	  if (particleName == "gamma"){
		  G4double photonEnergy = postPoint->GetKineticEnergy();
		  fEventAction->AddToEnergyVector(photonEnergy);
	  }

	  /*
	  const G4VProcess* currentProcess=prePoint->GetProcessDefinedStep();
	  if (currentProcess != 0) {
		  const G4String & StepProcessName = currentProcess->GetProcessName();
		  G4String volumePos = aTrack->GetNextVolume()->GetName();

		  if(StepProcessName== "Transportation" && volumePos == thisVolume) {

	  // processing hit when entering the volume

	  G4double kineticEnergy = aStep->GetTrack()->GetKineticEnergy();
      */

  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
