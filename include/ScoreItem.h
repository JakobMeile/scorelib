//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Wed Feb  5 21:34:02 PST 2014
// Last Modified: Thu Feb  6 01:05:52 PST 2014
// Filename:      ScoreItem.h
// URL:           https://github.com/craigsapp/scorelib/blob/master/include/ScoreItem.h
// Syntax:        C++11
//
// Description:   The ScoreItem class stores one SCORE item as well as
//                adds key/value named parameters for analysis and extensions.
//                This class adds manipulation to the ScoreItemEdit /
//                ScoreItemBase classes.
//

#ifndef _SCOREITEM_H_INCLUDED
#define _SCOREITEM_H_INCLUDED

#include "DatabaseBeam.h"
#include "RationalDuration.h"
#include <list>
#include <vector>

using namespace std;

class ScoreItem;

// ScoreItem typedefs:
using listSIp     = list<ScoreItem*>;
using vectorSIp   = vector<ScoreItem*>;
using vectorVSIp  = vector<vector<ScoreItem*>>;


// define SCOREITEMEDIT when compiling this class to use the ScoreItemEdit
// class to keep track of the parameter changes (for undo/redo options
// in a user interface).

#ifdef SCOREITEMEDIT
   #include "ScoreItemEdit.h"
   class ScoreItem : public ScoreItemEdit {
   public:
                    ScoreItem      (const ScoreItemEdit& anItem);
#else
   #include "ScoreItemBase.h"
   class ScoreItem : public ScoreItemBase {
#endif

   public:
                    ScoreItem             (void);
                    ScoreItem             (const ScoreItem& anItem);
                    ScoreItem             (const ScoreItemBase& anItem);
                    ScoreItem             (const vectorSF& parameters);
                   ~ScoreItem             ();

      ScoreItem&    operator=             (const ScoreItem& anItem);

      int          getParameterDigit      (int pindex, int position);
      int          getPDigit              (int pindex, int position);
      void         setParameterDigit      (int pindex, int position, int value);
      void         setPDigit              (int pindex, int position, int value);
      void         setParameterIntegerPart(int pindex, int intval);
      void         setPIntPart            (int pindex, int intval);

      // P1-P4 are the same for most P1 item types.

      // P1 accessors
      int          getItemType            (void);
      void         setItemType            (SCORE_FLOAT type);
      bool         isNoteItem             (void);    // P1==1
      bool         isRestItem             (void);    // P1==2
      bool         isClefItem             (void);    // P1==3
      bool         isLineItem             (void);    // P1==4
      bool         isSlurItem             (void);    // P1==5
      bool         isBeamItem             (void);    // P1==6
      bool         isTrillItem            (void);    // P1==7
      bool         isStaffItem            (void);    // P1==8
      bool         isSymbolItem           (void);    // P1==9
      bool         isNumberItem           (void);    // P1==10
      bool         isUserItem             (void);    // P1==11
      bool         isSpecialItem          (void);    // P1==12
      bool         isBadLuckItem          (void);    // P1==13
      bool         isBarlineItem          (void);    // P1==14
      bool         isEpsItem              (void);    // P1==15
      bool         isTextItem             (void);    // P1==16
      bool         isKeySigItem           (void);    // P1==17
      bool         isKeySignatureItem     (void);    // P1==17
      bool         isTimeSigItem          (void);    // P1==18

      // P2 accessors
      unsigned int getStaffNumber         (void);
      unsigned int getStaffNum            (void);
      void         setStaffNumber         (int staffnum);
      void         setStaffNum            (int staffnum);

      // P3 accessors
      SCORE_FLOAT  getHorizontalPosition  (void);
      SCORE_FLOAT  getHPos                (void);
      SCORE_FLOAT  getHorizontalPositionLeft(void);
      SCORE_FLOAT  getHPosL               (void);
      void         setHorizontalPosition  (SCORE_FLOAT pos);
      void         setHPos                (SCORE_FLOAT pos);

      // P4 accessors
      SCORE_FLOAT  getVerticalPosition    (void);
      SCORE_FLOAT  getVPos                (void);

      // P5 vertical position of right end accessors

      // P6 horizontal position of right end accessors
      SCORE_FLOAT  getHorizontalPositionRight(void);
      SCORE_FLOAT  getHPosR(void);

      // Duration processing
      void         setStaffOffsetDuration(SCORE_FLOAT duration);
      SCORE_FLOAT  getStaffOffsetDuration (void);
      bool         hasDuration            (void);
      SCORE_FLOAT  getDuration            (void);
      RationalDuration getRationalDuration(void);

      // Note (P1=1) processing functions  (defined in ScoreItem_notes.cpp)
      int          hasStem                (void);
      int          getStemDirection       (void);
      int          stemUp                 (void);
      int          stemDown               (void);
      int          stemFlip               (void);
      int          getPrintedAccidental   (void);
      bool         hasPrintedAccidental   (void);
      int          hasNatural             (void);
      int          hasEditorialAccidental (void);
      int          getStemBottomVPos      (void);
      int          getStemTopVPos         (void);
      int          getStemLength          (void);
      int          isCueSize              (void);
      void         removeArticulation     (void);
      void         hideNotehead           (void);
      void         hideStem               (void);
      void         setNoAccidental        (void); 
      void         setAccidentalParentheses(void);
      void         removeAccidentalParentheses(void); 
      void         removeFlags            (void);
      int          getDotCount            (void);

      // Rest (P1=2) processing functions

      // Clef (P1=3) processing functions
      int          getMiddleCVpos         (void);

      // Line (P1=4) processing functions

      // Slur (P1=5) processing functions

      // Beam (P1=6) processing functions
      // int hasStem(void) from Note section also works for Beams.
      // int getStemDirection(void) from Note section also works for Beams.

      // Trill (P1=7) processing functions

      // Staff (P1=8) processing functions

      // Symbol (P1=9) processing functions

      // Number (P1=10) processing functions

      // User (P1=11) processing functions

      // Special (P1=12) processing functions

      // BadLuck (P1=13) processing functions

      // Barline (P1=14) processing functions
      int          getBarlineHeight       (void);
      int          getBarHeight           (void);

      // ImportedEPSGraphic (P1=15) processing functions

      // Text (P1=16) processing functions
      void         make99Text             (const string& text);
      void         makeSvgCode            (const string& text);

      // KeySignature (P1=17) processing functions
      int          getDiatonicAccidentalState(vectorI& states);

      // MeterSignature (P1=18) processing functions


      // Page-related functions (defined in ScoreItem_page.cpp):
      int          getPageSystemIndex     (void);

      vectorSIp*   getChordNotes          (void);
      bool         isPrimaryChordNote     (void);
      bool         isSecondaryChordNote   (void);
      ScoreItem*   getPrimaryChordNote    (void);

      BeamGroup*   getBeamGroup           (void);
      BeamGroup*   getBeamInfo            (void);
      BeamGroup*   beamInfo               (void);
      BeamGroup*   beamGroup              (void);
      int          inBeamGroup            (void);

      SCORE_FLOAT  getHPosOff             (void);


      /////////////////////////////////////////////////////////////////////
      //
      // Analysis dependent functions: (the analysis is not checked before
      // the function is called).
      //

      // Chord analysis dependent functions:
      string       getHumdrumPitch        (void);

};


// external printing functions (defined in ScoreItem_print.cpp):
ostream& operator<<(ostream& out, ScoreItem& si);
ostream& operator<<(ostream& out, ScoreItem* si);
ostream& operator<<(ostream& out, listSIp& sipvector);
ostream& operator<<(ostream& out, vectorSIp& sipvector);
ostream& operator<<(ostream& out, vectorVSIp& sipvvector);


// Selecting filters for list of ScoreItems (defined in ScoreItem_select.cpp):
int    selectP1Items       (vectorSIp& output, const vectorSIp& input, 
                            const vectorI& p1values);
int    selectP1Items       (vectorSIp& output, const listSIp& input, 
                            const vectorI& p1values);
int    selectP1Items       (vectorSIp& output, const vectorSIp& input, 
                            int p1value);
int    selectP1Items       (vectorSIp& output, const listSIp& input, 
                            int p1value);
int    selectDurationItems (vectorSIp& output, const vectorSIp& input);
int    selectDurationItems (vectorSIp& output, const listSIp& input);
int    selectBarlines      (vectorSIp& output, const vectorSIp& input);
int    selectBarlines      (vectorSIp& output, const listSIp& input);




#endif  /* _SCOREITEM_H_INCLUDED */

