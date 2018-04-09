//
//-- ODB/SQL file 'discard_dep_2.sql'
//
//   Last updated:   28-Aug-2001
//

UPDATED;

SET $tslot = -1;

CREATE VIEW discard_dep_2 AS
  SELECT hires,    // Updated
	 lores,    // Updated
  FROM   index, hdr, update[min(2,$nmxupd)] 
  WHERE	 timeslot = $tslot OR $tslot = -1
;