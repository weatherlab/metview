//
//-- ODB/SQL file 'ecmwf_matchup_gbrad.sql'
//
//   Created:  22-Jul-2010
//

SET $tslot = -1;
SET $pe = 0;
SET $hdr_min = 1; // Here: the smallest procid (=global poolno) of the obs.grp. (ECMA)
SET $hdr_max = 0; // Here: the number of pools in (output) ECMA-database

CREATE VIEW ecmwf_matchup_gbrad AS
  SELECT seqno  READONLY,      // r/o
         report_rrflag,       // update
    FROM timeslot_index, index, hdr, gbrad
   WHERE target > 0
     AND 1 <= procid - $hdr_min + 1 <= $hdr_max
     AND (($tslot == -1 AND timeslot@timeslot_index > 0) OR (timeslot@timeslot_index == $tslot))
     AND report_status.active
     AND obstype = $gbrad
     AND codetype = $radrr
     AND paral($pe, procid - $hdr_min + 1)
;
