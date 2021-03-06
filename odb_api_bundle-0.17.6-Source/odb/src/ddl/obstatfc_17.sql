//
//-- ODB/SQL file 'obstatfc_17.sql'
//
//   Last updated:  06/09/10
//   By          :  Gabor Radnoti 

READONLY;

SET $tslot = -1;
SET $kset = 0;

CREATE VIEW obstatfc_17 AS
  SELECT
    seqno, entryno, 
    an_depar,
    fc_depar UPDATED,
    fc_step UPDATED,
    FROM   timeslot_index, index, hdr, body, fcdiagnostic, fcdiagnostic_body[min(17,$nmxfcdiag)]
    WHERE  (($tslot == -1 AND timeslot@timeslot_index > 0) OR (timeslot@timeslot_index == $tslot))
    AND  kset = $kset

;

