//
//-- ODB/SQL file 'obsdist_scatt.sql'
//
//   Created:  22-Jun-2009
//

READONLY;

SET $pe = 0;
SET $obstype = -1;
SET $codetype = -1;
SET $sensor = -1;
SET $hdr_min = -1; // contains window offset

// Make sure the SQL applies only to rows where sat.len@hdr & scatt.len@sat are > 0 :
SAFEGUARD;

CREATE VIEW obsdist_scatt AS
  SELECT distribid, seqno, window_offset, "*@scatt"
    FROM hdr, sat, scatt
    WHERE obstype = $scatt
     AND 1 <= distribid
     AND  distribtype = 1
      AND (obstype = $obstype OR $obstype = -1 )
     AND (codetype = $codetype OR $codetype = -1)
     AND (sensor = $sensor OR $sensor = -1)
     AND (window_offset = $hdr_min OR $hdr_min = -1)
     AND paral($pe, distribid)
;
