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
/// \file B4DetectorConstruction.hh
/// \brief Definition of the B4DetectorConstruction class

#ifndef B4DetectorConstruction_h
#define B4DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Box;
class G4Orb;
class G4VPhysicalVolume;
class G4GenericMessenger;

/// Detector construction class to define materials and geometry.
/// This is just a sphere in a volume.
///
/// You can adjust the radius of the sphere.
///
///

class B4DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    B4DetectorConstruction();
    virtual ~B4DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();

    // get methods
    //
    const G4VPhysicalVolume* GetSpherePV() const;

  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
  
    // data members
    //
    G4GenericMessenger*  fMessenger; // messenger
    G4VPhysicalVolume* fSpherePV; // the sphere physical volume
    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

// inline functions

inline const G4VPhysicalVolume* B4DetectorConstruction::GetSpherePV() const {
  return fSpherePV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

